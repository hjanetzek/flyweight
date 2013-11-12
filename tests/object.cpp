#include <unittest/unittest.hpp>

int main () {
  using namespace unittest;

  test("object") = {
    task("default-constructor") = [] { assert::fail(); },
    task("move-constructor") = [] { assert::fail(); },
    task("copy-constructor") = [] { assert::fail(); },
    task("copy-assign-operator") = [] { assert::fail(); },
    task("move-assign-operator") = [] { assert::fail(); },
    task("conversion-operator") = [] { assert::fail(); },
    task("arrow-operator") = [] { assert::fail(); }
  };

  monitor::run();
}
