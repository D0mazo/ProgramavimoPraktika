// Created by Domin on 3.24.2025.
#ifndef MENU_H
#define MENU_H

// Struct to hold menu selections
struct MenuChoices {
    int playerType;     // 1 = Warrior, 2 = Mage, 3 = Archer
    int difficulty;     // 1 = Easy, 2 = Medium, 3 = Hard
};

// Function declaration
MenuChoices menu();

#endif //MENU_H