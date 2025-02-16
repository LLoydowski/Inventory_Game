cmake_minimum_required(VERSION 3.10)

set(P_NAME "InventoryGame")

project(${P_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include_directories("${CMAKE_BINARY_DIR}/inc")
link_directories("/lib")

add_executable(${P_NAME} "src/main.cpp" "src/Inventory.cpp" "src/Item.cpp" "src/UIElement.cpp" "src/UIButton.cpp")
target_link_libraries(${P_NAME} SDL2)
