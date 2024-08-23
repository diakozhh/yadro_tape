cmake_minimum_required(VERSION 3.8)

project(yadro_tape)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories( ${Boost_INCLUDE_DIRS})

find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})

file(MAKE_DIRECTORY ${directory} "${CMAKE_CURRENT_SOURCE_DIR}\\tmp")

add_executable(yadro_tape 
    ${SOURCES}
)

target_include_directories(yadro_tape PUBLIC
   "${CMAKE_CURRENT_SOURCE_DIR}/src"
   ${Boost_INCLUDE_DIRS}
)

target_link_libraries(yadro_tape ${Boost_LIBRARIES})

#enable_testing()

add_executable(tape_tests
    tests/test.cpp
    tests/main.cpp
#    ${SOURCES}
)

target_include_directories(
    tape_tests PUBLIC
    ${GTest_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(tape_tests ${GTEST_LIBRARIES})