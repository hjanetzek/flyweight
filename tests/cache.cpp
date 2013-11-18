#include <flyweight/cache.hpp>
#include <string>

#include <unittest/unittest.hpp>

int main () {
  using namespace unittest;

  test("ordered-cache") = {
    task("find") = [] {
      auto value = flyweight::cache<std::string>::ref().find("not there");
      assert::is_not_null(value.get());
    },

    task("size") = [] {
      flyweight::cache<std::string>::ref().clear();
      assert::equal(flyweight::cache<std::string>::ref().size(), 0);

      auto value = flyweight::cache<std::string>::ref().find("size-1");
      assert::equal(flyweight::cache<std::string>::ref().size(), 1);
      auto value2 = flyweight::cache<std::string>::ref().find("size-2");
      assert::equal(flyweight::cache<std::string>::ref().size(), 2);
    },

    task("empty") = [] {
      flyweight::cache<std::string>::ref().clear();
      assert::is_true(flyweight::cache<std::string>::ref().empty());
    },

    task("clear") = [] {
      auto value = flyweight::cache<std::string>::ref().find("clear");
      assert::is_not_null(value.get());
      flyweight::cache<std::string>::ref().clear();
      assert::is_true(flyweight::cache<std::string>::ref().empty());
    },
  };

  test("unordered-cache") = {
    task("find") = [] { assert::fail(); },
    task("size") = [] { assert::fail(); },
    task("empty") = [] { assert::fail(); },
    task("clear") = [] { assert::fail(); }
  };

  monitor::run();
}
