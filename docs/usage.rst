.. _using-mnmlstc-flyweight:

Using MNMLSTC Flyweight
=======================

This section of documentation discusses how to use MNMLSTC Flyweight. It
briefly discusses using CMake to *discover* MNMLSTC Flyweight on a system, as
well as which headers to include.

CMake and find_package
----------------------

After installing MNMLSTC Flyweight with CMake, it is easy to use cmake's
``find_package`` command.

.. code-block:: cmake

   find_package(flyweight REQUIRED)
   add_library(my_library ${MY_LIBRARY_SOURCE_FILES})
   target_include_directories(my_library
    PUBLIC
      $<TARGET_PROPERTY:mnmlstc::flyweight,INTERFACE_INCLUDE_DIRECTORIES>)

Additionally, MNMLSTC Flyweight is not designed to be used from a build
directory.

If you are on Windows and have installed MNMLSTC Flyweight from an MSI,
CMake will be able to find the package correctly.

Including Necessary Headers
---------------------------

Only one header is needed to fully utilize MNMLSTC Flyweight::

    #include <flyweight/object.hpp>

This header pulls in all the types used by MNMLSTC Flyweight.

Feature Addition and Deprecation
--------------------------------

MNMLSTC FLyweight follows `Semantic Versioning 2.0
<http://semver.org/spec/v2.0.0.html>`_.
