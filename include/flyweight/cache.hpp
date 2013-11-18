#ifndef FLYWEIGHT_CACHE_HPP
#define FLYWEIGHT_CACHE_HPP

#include <unordered_map>
#include <deque>

#include <algorithm>
#include <memory>
#include <mutex>

#include <flyweight/extractor.hpp>
#include <core/type_traits.hpp>

namespace flyweight {
inline namespace v1 {
namespace impl {

template <class, class, class, bool> struct insert;
template <class, class, class, bool> struct find;
template <class> struct compare;
template <class> struct unique;
template <class> struct sort;

/* is_unordered == true */
template <class Container, class Mapped, class Key>
struct insert<Container, Mapped, Key, true> final {
  using container_type = std::reference_wrapper<Container>;
  using mapped_type = std::shared_ptr<Mapped>;
  using key_type = Key;

  void operator () (key_type const& key, mapped_type const& mapped) {
    auto result = this->container.get().emplace(key, mapped);
    if (not std::get<1>(result)) {
      /* TODO: Handle this case that shouldn't ever happen */
    }
  }

  container_type container;
};

/* is_unordered == false */
template <class Container, class Mapped, class Key>
struct insert<Container, Mapped, Key, false> final {
  using container_type = std::reference_wrapper<Container>;
  using mapped_type = std::shared_ptr<Mapped>;
  using key_type = Key;

  void operator () (key_type const&, mapped_type const& mapped) {
    this->container.get().emplace_back(mapped);
  }

  container_type container;
};


/* is_unordered == true */
template <class Container, class Mapped, class Key>
struct find<Container, Mapped, Key, true> final {
  using container_type = std::reference_wrapper<Container>;
  using argument_type = Key;
  using result_type = std::shared_ptr<Mapped>;
  using iterator = typename Container::const_iterator;

  iterator begin () const { return std::begin(this->container.get()); }
  iterator end () const { return std::end(this->container.get()); }

  result_type operator () (argument_type const& key) {
    auto iter = this->container.get().find(key);
    if (iter == this->end()) { return result_type { }; }
    return std::get<1>(*iter).lock();
  }

  container_type container;
};

/* is_unordered == false */
template <class Container, class Mapped, class Key>
struct find<Container, Mapped, Key, false> final {
  using container_type = std::reference_wrapper<Container>;
  using argument_type = Key;
  using result_type = std::shared_ptr<Mapped>;
  using iterator = typename Container::iterator;

  iterator begin () const { return std::begin(this->container.get()); }
  iterator end () const { return std::end(this->container.get()); }

  result_type operator () (argument_type const& key) {
    std::sort(this->begin(), this->end(), impl::sort<Mapped> { });
    this->container.get().erase(
      std::unique(this->begin(), this->end(), impl::unique<Mapped> { }),
      this->end()
    );

    auto iter = std::lower_bound(
      this->begin(),
      this->end(),
      key,
      impl::compare<argument_type> { }
    );
    if (iter == this->end()) { return result_type { }; }
    return (*iter).lock();
    return result_type { };
  }

  container_type container;
};

/* Used to sort weak_ptr's by the value they may or may not point to. */
template <class T>
struct sort final {
  using argument_type = std::weak_ptr<T>;
  bool operator () (argument_type const& lhs, argument_type const& rhs) const {
    auto lhs_shared = lhs.lock();
    auto rhs_shared = rhs.lock();

    if (not lhs_shared) { return false; }
    if (not rhs_shared) { return true; }
    return std::less<T> { }(*lhs_shared, *rhs_shared);
  }
};

template <class T>
struct unique final {
  using argument_type = std::weak_ptr<T>;

  bool operator () (argument_type const& lhs, argument_type const& rhs) const {
    auto lhs_shared = lhs.lock();
    auto rhs_shared = rhs.lock();

    return not lhs_shared and not rhs_shared;
  }
};

template <class T>
struct compare final {
  using argument_type = std::weak_ptr<T>;

  bool operator ()(argument_type const& lhs, T const& rhs) const {
    auto shared = lhs.lock();
    if (not shared) { return false; }
    return std::less<T> { }(*shared, rhs);
  }
};

} /* namespace impl */

template <class... Ts> struct tag final { };

/* This entire cache is based around the 'magic' of the thread-safe
 * reference counted object cache' suggested by Herb Sutter
 *
 * A cache is a non-movable, non-copyable, non-inheritable,
 * non-publically-constructible object. At most, one may access the cache
 * by way of its 'ref' static member funtions.
 */

template <
  class T,
  class Allocator=std::allocator<T>,
  class Tag=tag<>
> struct cache final {

  using extractor_type = extractor<T const>;
  using tag_type = Tag;

  using mapped_type = core::add_const_t<T>;
  using key_type = core::add_const_t<
    core::decay_t<typename extractor_type::result_type>
  >;

  using weak_ptr = std::weak_ptr<mapped_type>;

  /* booleans used to perform a compile time query on the cache instance */
  static constexpr bool is_unordered = not std::is_same<
    key_type,
    mapped_type
  >::value;

  using allocator_traits = std::allocator_traits<Allocator>;

  template <class U>
  using rebind_alloc = typename allocator_traits::template rebind_alloc<U>;
  template <class U>
  using rebind_traits = typename allocator_traits::template rebind_traits<U>;

  using allocator_type = rebind_alloc<core::remove_const_t<mapped_type>>;

  /* Get the correct container */
  using container_type = core::conditional_t<
    is_unordered,
    std::unordered_map<
      key_type,
      weak_ptr,
      std::hash<key_type>,
      std::equal_to<key_type>,
      rebind_alloc<std::pair<key_type, weak_ptr>>
    >,
    std::deque<weak_ptr, rebind_alloc<weak_ptr>>
  >;

  using find_type = impl::find<
    container_type,
    mapped_type,
    key_type,
    is_unordered
  >;

  using insert_type = impl::insert<
    container_type,
    mapped_type,
    key_type,
    is_unordered
  >;

  using difference_type = typename container_type::difference_type;
  using size_type = typename container_type::size_type;

  using const_iterator = typename container_type::const_iterator;
  using iterator = typename container_type::iterator;

  using const_reference = typename container_type::const_reference;
  using reference = typename container_type::reference;

  using const_pointer = typename container_type::const_pointer;
  using pointer = typename container_type::pointer;

  cache (cache const&) = delete;
  cache (cache&&) = delete;

  cache& operator = (cache const&) = delete;
  cache& operator = (cache&&) = delete;

  static cache& ref () {
    static cache instance;
    return instance;
  }

  template <class ValueType>
  std::shared_ptr<mapped_type> find (ValueType&& value) {
    std::lock_guard<std::mutex> lock { this->mutex };
    key_type const& key = extractor_type { }(std::forward<ValueType>(value));
    auto shared = find_type { std::ref(this->container) }(key);
    if (not shared) {
      shared = std::allocate_shared<mapped_type>(
        this->allocator,
        std::forward<ValueType>(value)
      );
      insert_type { std::ref(this->container) }(key, shared);
    }
    return shared;
  }

  const_iterator begin () const { return std::begin(this->container); }
  const_iterator end () const { return std::end(this->container); }
  iterator begin () { return std::begin(this->container); }
  iterator end () { return std::end(this->container); }

  size_type size () const { return this->container.size(); }
  bool empty () const { return this->container.empty(); }

  void clear () {
    std::lock_guard<std::mutex> lock { this->mutex };
    return this->container.clear();
  }

private:
  cache () = default;
  ~cache () = default;

  container_type container;
  allocator_type allocator;
  std::mutex mutex;
};

}} /* namespace flyweight::v1 */

#endif /* FLYWEIGHT_CACHE_HPP */
