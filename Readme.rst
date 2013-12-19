Overview
========

MNMLSTC Flyweight is a small and easy to use C++11 library that implements the
`flyweight pattern <http://en.wikipedia.org/wiki/Flyweight_pattern>`_. It is a
header only library.

Information on installing and using MNMLSTC Flyweight (as well as its
limitations) can be found in its documentation.

MNMLSTC Flyweight is released under the Apache 2.0 License.

Basic Example
-------------

Below is a basic example of how to use MNMLSTC Flyweight::

    #include <flyweight/flyweight.hpp>
    #include <string>


    struct user {
      flyweight::object<std::string> first_name;
      flyweight::object<std::string> last_name;
    };

    int main () {
      user a_user { "john", "smith" };
      user b_user { "john", "knight" };
      /* Both user's first_name data member refer to the same std::string
       * in memory.
       */
      assert(a_user.first_name == b_user.first_name);
    }

Requirements
------------

There are several requirements to use MNMLSTC Flyweight:

 * A C++11 compliant compiler (GCC 4.8.1 or Clang 3.3 will suffice)
 * `CMake 2.8.12 <http://cmake.org>`_
 * `MNMLSTC Unittest <https://github.com/mnmlstc/unittest>`_
 * `MNMLSTC Core <https://github.com/mnmlstc/core>`_
 * `Sphinx Documentation Generator <http://sphinx-doc.org>`_
 * `Cloud Sphinx Theme <https://pypi.python.org/pypi/cloud_sptheme>`_

MNMLSTC Unittest is required if building and running the unit tests.

Sphinx and the Cloud Sphinx Theme are only necessary if generating
documentation manually.
