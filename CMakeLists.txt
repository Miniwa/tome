cmake_minimum_required(VERSION 3.0)

project(tome)

#Versions
set (tome_VERSION_MAJOR 0)
set (tome_VERSION_MINOR 1)

#Includes
include_directories("${PROJECT_SOURCE_DIR}/include")

#Manage sources
file(GLOB tome_base_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#Library
add_library(tome_base ${tome_base_SOURCES})

#Tests
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

#Dyn link to tests
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

#Enable testing and gather the test sources
enable_testing()
file(GLOB tome_TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/tests/*.cpp)

#Compile and link the tests.
add_executable(tome_test ${tome_TEST_SOURCES})
target_link_libraries(tome_test tome_base ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(tome_test tome_test)

#Add doxygen target
find_package(Doxygen)
if(DOXYGEN_FOUND)
    #Create output dir
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)

    #Configure the doxygen file.
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
        )

    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)
endif(DOXYGEN_FOUND)
