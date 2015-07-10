#define CATCH_CONFIG_MAIN
#include <flyweight/object.hpp>
#include <string>
#include <unordered_map>

#include <catch.hpp>

TEST_CASE("object-constructor", "[object][constructor]") {
  flyweight::object<std::string> empty { };
  CHECK(empty.get().empty());
}

TEST_CASE("object-value-constrctor") {
  flyweight::object<std::string> value { "value-constructor" };
  CHECK_FALSE(value->empty());
  CHECK(value->size() == 17);
}

TEST_CASE("object-copy-constructor") {
  flyweight::object<std::string> value { "copy" };
  flyweight::object<std::string> copy { value };

  CHECK(value.get() == copy.get());
}

TEST_CASE("value-assign-operator") {
  flyweight::object<std::string> value { };
  std::string text { "value" };
  value = text;
  CHECK(text == value.get());
}

TEST_CASE("copy-assign-operator") {
  flyweight::object<std::string> value { "value" };
  flyweight::object<std::string> copy { };
  copy = value;
  CHECK(value.get() == copy.get());
}

TEST_CASE("conversion-operator") {
  flyweight::object<std::string> value { "conversion" };
  std::string converted = value;
  CHECK(value.get() == converted);
}

TEST_CASE("arrow-operator") {
  flyweight::object<std::string> value { "arrow" };
  CHECK(value->size() == 5);
}

TEST_CASE("operator-equal") {
  std::string text { "equal" };
  flyweight::object<std::string> lhs { text };
  flyweight::object<std::string> rhs { text };

  CHECK(lhs == text);
  CHECK(rhs == text);
  CHECK(text == lhs);
  CHECK(text == rhs);
  CHECK(lhs == rhs);
}

TEST_CASE("operator-not-equal") {
  std::string text { "not-equal" };
  flyweight::object<std::string> lhs { "lhs" };
  flyweight::object<std::string> rhs { "rhs" };

  CHECK(lhs != text);
  CHECK(rhs != text);
  CHECK(text != lhs);
  CHECK(text != rhs);
  CHECK(lhs != rhs);
}

TEST_CASE("operator-greater-equal") {
  std::string text { "abcde" };
  flyweight::object<std::string> lhs { "bcdef" };
  flyweight::object<std::string> rhs { "bcdef" };

  CHECK(lhs >= text);
  CHECK(rhs >= text);
  CHECK(lhs >= rhs);
}

TEST_CASE("operator-less-equal") {
  std::string text { "bcdef" };
  flyweight::object<std::string> lhs { "abcde" };
  flyweight::object<std::string> rhs { "abcde" };

  CHECK(lhs <= text);
  CHECK(rhs <= text);
  CHECK(lhs <= rhs);
}

TEST_CASE("operator-greater") {
  std::string text { "abcde" };
  flyweight::object<std::string> lhs { "cdefg" };
  flyweight::object<std::string> rhs { "bcdef" };

  CHECK(lhs > text);
  CHECK(rhs > text);
  CHECK(lhs > rhs);
}

TEST_CASE("operator-less") {
  std::string text { "cdefg" };
  flyweight::object<std::string> lhs { "abcde" };
  flyweight::object<std::string> rhs { "bcdef" };

  CHECK(lhs < text);
  CHECK(rhs < text);
  CHECK(lhs < rhs);
}

TEST_CASE("unordered-map-instantiation") {
  std::unordered_map<flyweight::object<std::string>, int> map;
}
