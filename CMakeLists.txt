cmake_minimum_required(VERSION 3.10)

set(P_NAME "InventoryGame")

project(${P_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include_directories("/inc")
link_directories("/lib")

add_executable(${P_NAME} "src/main.cpp")

target_link_libraries(${P_NAME} SDL2)
