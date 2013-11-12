#include <unittest/unittest.hpp>

int main () {
  using namespace unittest;

  test("cache") = {
    task("ordered-find") = [] { assert::fail(); }
  };

  monitor::run();
}
