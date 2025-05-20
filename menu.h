#ifndef MENU_H
#define MENU_H

#include <string>

struct MenuChoices {
    std::string playerName;  // Player's name
    int playerType;          // Player type (1: Warrior, 2: Mage, 3: Archer)
    int difficulty;          // Difficulty level (1: Easy, 2: Medium, 3: Hard)
    std::string monsterName; // Selected monster's name
};

MenuChoices menu();  // Function prototype

#endif // MENU_H