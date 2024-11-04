cmake_minimum_required(VERSION 3.10)
project(OrderExecutionManagement)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)
include_directories(libs/cpp-httplib)
include_directories(libs/websocketpp)
include_directories(${CMAKE_SOURCE_DIR}/libs/cpp-httplib)
include_directories(${CMAKE_SOURCE_DIR}/libs/websocketpp)
include_directories(${CMAKE_SOURCE_DIR}/libs/boost_1_86_0)
include_directories(${CMAKE_SOURCE_DIR}/libs/jsoncpp)


# Source files
file(GLOB SOURCES "src/*.cpp")

add_executable(OrderExecutionManagement ${SOURCES})

# Link libraries
target_link_libraries(OrderExecutionManagement ws2_32)
