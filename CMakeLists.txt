cmake_minimum_required(VERSION 3.12)
project(Trees)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS -Wno-deprecated)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_subdirectory(lib/gtest)
include_directories(lib/gtest/googletest/include)
include_directories(lib/gtest/googlemock/include)

set(SOURCE_FILES main.cpp src/trees/avl.hpp src/trees/bst.hpp src/trees/datatypes.hpp src/trees/datatypes.cpp
        src/trees/exceptions.cpp src/trees/exceptions.hpp src/trees/nodes.hpp src/trees/order.hpp src/trees/order.hpp
        src/trees/rb.hpp src/trees/splayt.hpp src/trees/trees.hpp test/correctness_check.cpp test/crash_check.cpp
        test/exception_check.cpp test/test_utils.hpp test/test_utils.cpp src/trees/collection.hpp src/trees/collection.hpp src/demo.cpp src/demo.hpp)
add_executable(Trees ${SOURCE_FILES})
target_link_libraries(Trees gtest gtest_main)