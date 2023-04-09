cmake_minimum_required(VERSION 3.16.3)
project(dbus-service-app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES src/DbusMethodInstance.cpp src/command_line_parser.cpp)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp ${SOURCES})

find_package(sdbus-c++ REQUIRED)
find_package(Boost 1.81.0 COMPONENTS program_options REQUIRED )


target_link_libraries(${CMAKE_PROJECT_NAME} sdbus-c++ ${Boost_LIBRARIES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include/ ${Boost_INCLUDE_DIR})