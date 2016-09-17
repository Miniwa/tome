cmake_minimum_required(VERSION 3.0)

project(tome)

#Versions
set (tome_VERSION_MAJOR 0)
set (tome_VERSION_MINOR 1)

#Boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework regex REQUIRED)

#Manage directories
include_directories(${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#Manage sources
file(GLOB tome_base_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

#Compile the base library
add_library(tome_base ${tome_base_SOURCES})
target_link_libraries(tome_base ${Boost_REGEX_LIBRARY})

#Enable testing and gather the test sources
enable_testing()
file(GLOB tome_TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/tests/*.cpp)

#Compile and link the tests.
add_executable(tome_test ${tome_TEST_SOURCES})
target_link_libraries(tome_test tome_base ${Boost_LIBRARIES})
add_test(tome_test tome_test COMMAND tome_test --log_format=XML --log_sink=report.xml --log_level=all --report_level=no)

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
