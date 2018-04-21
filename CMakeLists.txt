cmake_minimum_required(VERSION 3.10)
project(MQ)

set(CMAKE_CXX_STANDARD 14)

find_package(cppzmq REQUIRED)

include_directories(${cppzmq_INCLUDE_DIR})

add_executable(Broker Broker.cpp)
target_link_libraries(Broker ${cppzmq_LIBRARY})

add_executable(Publisher Publisher.cpp)
target_link_libraries(Publisher ${cppzmq_LIBRARY})

add_executable(Subscriber Subscriber.cpp)
target_link_libraries(Subscriber ${cppzmq_LIBRARY})