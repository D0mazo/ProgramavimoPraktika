cmake_minimum_required(VERSION 3.28)
project(untitled3)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Player
        ${CMAKE_SOURCE_DIR}/Monsters
        ${CMAKE_SOURCE_DIR}/Battle
        ${CMAKE_SOURCE_DIR}/Shop
        ${CMAKE_SOURCE_DIR}/Inventory
)

add_executable(untitled3
        main.cpp
        Player/player.cpp
        Monsters/monster.cpp
        Battle/battle.cpp
        menu.cpp
        Shop/shop.cpp
        Monsters/monster_data.cpp
)