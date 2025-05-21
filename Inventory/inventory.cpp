#include "inventory.h"
#include <iostream>

// Existing Items
void Inventory::useHealthPotion(Player& player) {
    switch (player.getType()) {
        case 1: player.takeDamage(-30); break; // Warrior
        case 2: player.takeDamage(-20); break; // Mage
        case 3: player.takeDamage(-25); break; // Archer
        default: break;
    }
}

void Inventory::usePowerBoost(Player& player) {
    switch (player.getType()) {
        case 1: player.increasePower(5); break;
        case 2: player.increasePower(10); break;
        case 3: player.increasePower(6); break;
        default: break;
    }
}

void Inventory::useStaminaPotion(Player& player) {
    switch (player.getType()) {
        case 1: player.restoreStamina(20); break;
        case 2: player.restoreStamina(15); break;
        case 3: player.restoreStamina(25); break;
        default: break;
    }
}

// New: Equip Weapon
void Inventory::equipWeapon(Player& player, const std::string& weaponName) {
    if (weaponName == "Sword" && player.getType() == 1) {
        player.increasePower(10);  // Warrior boost
        std::cout << "Warrior equipped a Sword!\n";
    } else if (weaponName == "Bow" && player.getType() == 3) {
        player.increasePower(8);   // Archer boost
        std::cout << "Archer equipped a Bow!\n";
    } else if (weaponName == "Staff" && player.getType() == 2) {
        player.increasePower(12);  // Mage boost
        std::cout << "Mage equipped a Staff!\n";
    } else {
        std::cout << "Weapon not compatible with class.\n";
    }
}



