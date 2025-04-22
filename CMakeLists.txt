cmake_minimum_required(VERSION 3.10)

set(P_NAME "InventoryGame")

project(${P_NAME})

if(MSVC)
    message(FATAL_ERROR "Marcin cos nie wyszlo (Odpalil sie Visual Studio compiler)")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(${P_NAME}
    "src/main.cpp"
    "src/Game.cpp"
    "src/Inventory.cpp"
    "src/Item.cpp"
    "src/Armor.cpp"
    "src/Weapon.cpp"
    "src/Trinket.cpp"
    "src/Item.cpp"
    "src/UIElement.cpp"
    "src/UIButton.cpp"
    "src/Player.cpp"
    "src/UIImage.cpp"
    "src/Shop.cpp"
    "src/UIButtonImage.cpp"
    "src/UIGroup.cpp"
    "src/Chest.cpp"
    "src/LootTable.cpp"
    "src/Enemy.cpp"
    "src/Arena.cpp"
    "src/FightBar.cpp"
)

if(WIN32)
    include_directories("${CMAKE_BINARY_DIR}/inc/")
    link_directories("/lib")
    target_link_libraries(${P_NAME} PRIVATE
        mingw32
        "${CMAKE_BINARY_DIR}/lib/libSDL2main.a"
        "${CMAKE_BINARY_DIR}/lib/libSDL2.dll.a"
        "${CMAKE_BINARY_DIR}/lib/libSDL2_ttf.dll.a"
        "${CMAKE_BINARY_DIR}/lib/libSDL2_image.dll.a"
    )

    # ? Renable it when the project will be finnished
    # set_target_properties(${P_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
    target_compile_options(${P_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -g -O0)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories("${CMAKE_BINARY_DIR}/inc")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_image REQUIRED)
    target_link_libraries(${P_NAME} SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)
else()
    include_directories("${CMAKE_BINARY_DIR}/inc")
    link_directories("/lib")
    target_link_libraries(${P_NAME} SDL2 SDL2_ttf SDL2_image)
endif()