cmake_minimum_required(VERSION 3.26)
project(yadro_tape)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Boost 1.83.0 COMPONENTS program_options REQUIRED)


include_directories(include ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
set(CMAKE_CXX_FLAGS "-lboost_program_options")

file(MAKE_DIRECTORY ${directory} "${CMAKE_CURRENT_BINARY_DIR}\\tmp")