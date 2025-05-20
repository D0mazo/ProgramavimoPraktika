#ifndef MONSTER_DATA_H
#define MONSTER_DATA_H
#include "monster.h"
#include <string>
#include <vector>

// Function declarations
Monster createMonster(const std::string& monsterName);
std::vector<std::string> getMonstersByDifficulty(int difficulty);

#endif // MONSTER_DATA_H