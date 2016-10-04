cmake_minimum_required(VERSION 3.0)

project(tome)

#Variables
set (tome_VERSION_MAJOR 0)
set (tome_VERSION_MINOR 1)

#Link everything statically on windows.
if(WIN32)
    set(tome_BUILD_STATIC ON)
    message("-- Building statically on windows..")
endif(WIN32)

#Manage configuration flags.
if(tome_BUILD_STATIC)
    message("-- Setting static build flags..")
    set(Boost_USE_STATIC_LIBS ON)
    set(tome_LIBRARY_TYPE STATIC)
else(tome_BUILD_STATIC)
    message("-- Setting shared build flags..")
    set(tome_LIBRARY_TYPE SHARED)
    add_definitions(-DBOOST_TEST_DYN_LINK)
endif(tome_BUILD_STATIC)

#Find boost.
find_package(Boost COMPONENTS unit_test_framework regex REQUIRED)

#Manage directories
include_directories(${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#Manage sources
file(GLOB tome_base_CPP ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB tome_test_SOURCES ${PROJECT_SOURCE_DIR}/src/tests/*.cpp)
file(GLOB tome_base_HPP ${PROJECT_SOURCE_DIR}/include/*.hpp)
set(tome_base_SOURCES ${tome_base_CPP} ${tome_base_HPP})

#Compile the base library
add_library(tome_base ${tome_LIBRARY_TYPE} ${tome_base_SOURCES})
target_link_libraries(tome_base ${Boost_REGEX_LIBRARY})

#Enable testing, compile and link the tests.
enable_testing()
add_executable(tome_test ${tome_test_SOURCES})
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
