cmake_minimum_required(VERSION 3.12)
project(DynamicArray)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp lib/Tests/test.cpp lib/Tests/DynamicArray.hpp)
add_executable(Dynamic_Array ${SOURCE_FILES} lib/Tests/test.cpp)
target_link_libraries(Dynamic_Array gtest gtest_main)
