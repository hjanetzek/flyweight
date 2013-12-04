#include <flyweight/object.hpp>
#include <string>

#include <unittest/unittest.hpp>

int main () {
  using namespace unittest;

  test("object") = {
    task("default-constructor") = [] {
      flyweight::object<std::string> empty { };
      assert::is_true(empty.get().empty());
    },

    task("value-constructor") = [] {
      flyweight::object<std::string> value { "value-constructor" };
      assert::is_false(value->empty());
      assert::equal(value->size(), 17);
    },

    task("copy-constructor") = [] {
      flyweight::object<std::string> value { "copy" };
      flyweight::object<std::string> copy { value };

      assert::is(value.get(), copy.get());
    },

    task("value-assign-operator") = [] {
      flyweight::object<std::string> value { };
      std::string text { "value" };
      value = text;
      assert::equal(text, value.get());
    },

    task("copy-assign-operator") = [] {
      flyweight::object<std::string> value { "value" };
      flyweight::object<std::string> copy { };
      copy = value;
      assert::is(value.get(), copy.get());
    },

    task("conversion-operator") = [] {
      flyweight::object<std::string> value { "conversion" };
      std::string converted { value };
      assert::equal(value.get(), converted);
    },

    task("arrow-operator") = [] {
      flyweight::object<std::string> value { "arrow" };
      assert::equal(value->size(), 5);
    },

    task("operator-equal") = [] {
      std::string text { "equal" };
      flyweight::object<std::string> lhs { text };
      flyweight::object<std::string> rhs { text };

      assert::equal(lhs, text);
      assert::equal(rhs, text);
      assert::equal(lhs, rhs);
    },

    task("operator-not-equal") = [] {
      std::string text { "not-equal" };
      flyweight::object<std::string> lhs { "lhs" };
      flyweight::object<std::string> rhs { "rhs" };

      assert::not_equal(lhs, text);
      assert::not_equal(rhs, text);
      assert::not_equal(lhs, rhs);
    },

    task("operator-greater-equal") = [] {
      std::string text { "abcde" };
      flyweight::object<std::string> lhs { "bcdef" };
      flyweight::object<std::string> rhs { "bcdef" };

      assert::greater_equal(lhs, text);
      assert::greater_equal(rhs, text);
      assert::greater_equal(lhs, rhs);
    },

    task("operator-less-equal") = [] {
      std::string text { "bcdef" };
      flyweight::object<std::string> lhs { "abcde" };
      flyweight::object<std::string> rhs { "abcde" };

      assert::less_equal(lhs, text);
      assert::less_equal(rhs, text);
      assert::less_equal(lhs, rhs);
    },

    task("operator-greater") = [] {
      std::string text { "abcde" };
      flyweight::object<std::string> lhs { "cdefg" };
      flyweight::object<std::string> rhs { "bcdef" };

      assert::greater(lhs, text);
      assert::greater(rhs, text);
      assert::greater(lhs, rhs);
    },

    task("operator-less") = [] {
      std::string text { "cdefg" };
      flyweight::object<std::string> lhs { "abcde" };
      flyweight::object<std::string> rhs { "bcdef" };

      assert::less(lhs, text);
      assert::less(rhs, text);
      assert::less(lhs, rhs);
    }
  };

  monitor::run();
}
