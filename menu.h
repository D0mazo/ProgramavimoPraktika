#ifndef MENU_H
#define MENU_H

#include <string>

// Struct to hold menu selections
struct MenuChoices {
    int playerType;     // 1 = Warrior, 2 = Mage, 3 = Archer
    int difficulty;     // 1 = Easy, 2 = Medium, 3 = Hard
    std::string playerName; // Player's chosen hero name
};

// Function declaration
MenuChoices menu();

#endif //MENU_H
