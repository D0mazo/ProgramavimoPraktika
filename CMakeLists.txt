# Assuming your CMakeLists.txt is at the root of your project
include_directories(
        ${CMAKE_SOURCE_DIR}/Player
        ${CMAKE_SOURCE_DIR}/Monsters
        ${CMAKE_SOURCE_DIR}/Battle
)

# Or if you are creating an executable or adding libraries, ensure proper target linkage
add_executable(untitled3 main.cpp Player/player.cpp Monsters/monster.cpp Battle/battle.cpp menu.cpp)
