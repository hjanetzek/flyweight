#ifndef FLYWEIGHT_EXTRACTOR_HPP
#define FLYWEIGHT_EXTRACTOR_HPP

#include <core/type_traits.hpp>

namespace flyweight {
inline namespace v1 {

/* Extracts a 'key-type' for a given T */
template <class T>
struct extractor {
  using argument_type = core::add_const_t<core::add_lvalue_reference_t<T>>;
  using result_type = argument_type;

  constexpr extractor () noexcept { }

  result_type operator () (argument_type argument) const noexcept {
    return argument;
  }
};

}} /* namespace flyweight::v1 */

#endif /* FLYWEIGHT_EXTRACTOR_HPP */
