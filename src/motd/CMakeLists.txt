cmake_minimum_required(VERSION 2.8.4)
project(dynamic_motd)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.49.0 COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lpthread")

include_directories(${Boost_INCLUDE_DIRS})
set(SOURCE_FILES viridian-motd.cpp)
add_executable(viridian-motd uptime.cpp ${SOURCE_FILES})
target_link_libraries(viridian-motd ${Boost_LIBRARIES})
