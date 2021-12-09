cmake_minimum_required(VERSION 3.16)
project(huffman)

file(GLOB HUFFMAN_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${HUFFMAN_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
