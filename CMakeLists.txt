cmake_minimum_required(VERSION 3.10)

set(P_NAME "InventoryGame")

project(${P_NAME})

if(MSVC)
    message(FATAL_ERROR "Marcin cos nie wyszlo (Odpalil sie Visual Studio compiler)")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(${P_NAME} "src/main.cpp" "src/Inventory.cpp" "src/Item.cpp" "src/UIElement.cpp" "src/UIButton.cpp")

if(WIN32)
    include_directories("${CMAKE_BINARY_DIR}/inc/")
    link_directories("/lib")
    target_link_libraries(${P_NAME}
        mingw32
        "${CMAKE_BINARY_DIR}/lib/libSDL2main.a"
        "${CMAKE_BINARY_DIR}/lib/libSDL2.dll.a"
        "${CMAKE_BINARY_DIR}/lib/libSDL2_ttf.dll.a"
    )
else()
    include_directories("${CMAKE_BINARY_DIR}/inc")
    link_directories("/lib")
    target_link_libraries(${P_NAME} SDL2 SDL2_ttf)
endif()