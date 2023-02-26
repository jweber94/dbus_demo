cmake_minimum_required(VERSION 3.16.3)
project(dbus-service-app)

set(SOURCES src/data_exchange_class.cpp src/dbus_interface.cpp src/command_line_parser.cpp)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp ${SOURCES})

find_package(sdbus-c++ REQUIRED)
find_package(Boost 1.81.0 COMPONENTS program_options REQUIRED )


target_link_libraries(${CMAKE_PROJECT_NAME} sdbus-c++ ${Boost_LIBRARIES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include/ ${Boost_INCLUDE_DIR})