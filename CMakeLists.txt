cmake_minimum_required(VERSION 3.8)

project(yadro_practice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak,address -Wall -Wextra -Werror -Wpedantic")
set( SOURCES 
    src/config_parser.hpp
    src/merge_sort.cpp
    src/merge_sort.h
    src/tape_impl.cpp
    src/tape_impl.h
    src/tape.h
    src/utils.hpp
)

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories( ${Boost_INCLUDE_DIRS})

find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})

file(MAKE_DIRECTORY ${directory} "${CMAKE_CURRENT_SOURCE_DIR}\\tmp")

add_executable(yadro_tape 
    ${SOURCES}
    src/main.cpp
)

target_include_directories(yadro_tape PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/src
   ${Boost_INCLUDE_DIRS}
)

target_link_libraries(yadro_tape ${Boost_LIBRARIES})

#enable_testing()
add_executable(tape_tests
    tests/test.cpp
    tests/main.cpp
    ${SOURCES}
)

target_include_directories(
    tape_tests PUBLIC
    ${GTest_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(tape_tests ${GTEST_LIBRARIES} ${Boost_LIBRARIES})