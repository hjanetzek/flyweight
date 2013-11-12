add_custom_target(check COMMAND ${CMAKE_TEST_COMMAND})
find_package(unittest REQUIRED)

include_directories(${UNITTEST_INCLUDE_DIR})

#------------------------------------------------------------------------------
# Executable Section
#------------------------------------------------------------------------------
add_executable(test-object "${TEST_SOURCE_DIR}/object.cpp")
add_executable(test-cache "${TEST_SOURCE_DIR}/cache.cpp")

#------------------------------------------------------------------------------
# Test Section
#------------------------------------------------------------------------------
add_test(object test-object)
add_test(cache test-cache)

#------------------------------------------------------------------------------
# Dependency Section
#------------------------------------------------------------------------------
add_dependencies(check test-object)
add_dependencies(check test-cache)
