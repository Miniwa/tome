cmake_minimum_required(VERSION 3.0)

project(tome)

#Versions
set (tome_VERSION_MAJOR 0)
set (tome_VERSION_MINOR 1)

#Includes
include_directories("${PROJECT_SOURCE_DIR}/include")

#Manage sources
set (tome_base_SOURCES ${PROJECT_SOURCE_DIR}/src/field_descriptor.cpp)

#Library
add_library(tome_base ${tome_base_SOURCES})

#Tests
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

#Dyn link to tests
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

#Enable testing and gather the test sources
enable_testing()
set (tome_TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/tests/main.cpp
    ${PROJECT_SOURCE_DIR}/src/tests/field_descriptor_test.cpp)

#Compile and link the tests.
add_executable(tome_test ${tome_TEST_SOURCES})
target_link_libraries(tome_test tome_base ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(tome_test tome_test)
