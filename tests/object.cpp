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
      assert::fail();
    },

    task("operator-not-equal") = [] { assert::fail(); },
    task("operator-greater-equal") = [] { assert::fail(); },
    task("operator-less-equal") = [] { assert::fail(); },
    task("operator-greater") = [] { assert::fail(); },
    task("operator-less") = [] { assert::fail(); }
  };

  monitor::run();
}
