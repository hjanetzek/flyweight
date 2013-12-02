#include <flyweight/cache.hpp>
#include <string>

#include <unittest/unittest.hpp>

struct texture {
  texture (std::string&& name) : name { std::move(name) } { }
  std::string const& id () const { return this->name; }

  bool operator < (texture const& other) const { return this->name < other.name; }
private:
  std::string name;
};

namespace flyweight {
inline namespace v1 {

template <>
struct extractor< ::texture> {
  using argument_type = core::add_const_t<
    core::add_lvalue_reference_t<texture>
  >;
  using result_type = std::string;

  result_type operator () (argument_type argument) { return argument.id(); }
};

}} /* namespace flyweight::v1 */

namespace std {

template <>
struct hash< ::texture> {
  using argument_type = ::texture;
  using result_type = std::size_t;

  result_type operator ()(argument_type const& key) const {
    return hash<string> { }(key.id());
  }
};

} /* namespace std */

int main () {
  using namespace unittest;

  test("cache") = {
    task("is-associative") = [] {
      assert::is_false(flyweight::cache<std::string>::is_associative::value);
    },

    task("empty") = [] {
      assert::is_true(flyweight::cache<std::string>::ref().empty());
    },

    task("find") = [] {
      std::string not_there { "not there" };
      auto value = flyweight::cache<std::string>::ref().find(not_there);
      assert::is_not_null(value.get());
    },

    task("size") = [] {
      assert::equal(flyweight::cache<std::string>::ref().size(), 0);

      std::string size_1 { "size-1" };
      std::string size_2 { "size-2" };

      auto value = flyweight::cache<std::string>::ref().find(size_1);
      assert::equal(flyweight::cache<std::string>::ref().size(), 1);
      auto value2 = flyweight::cache<std::string>::ref().find(size_2);
      assert::equal(flyweight::cache<std::string>::ref().size(), 2);
    },

  };

  monitor::run();
}
