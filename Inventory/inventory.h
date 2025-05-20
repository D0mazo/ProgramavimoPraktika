#ifndef INVENTORY_H
#define INVENTORY_H
#include "player.h"
#include <string>

class Inventory {
public:
    // Apply health potion: Restore 50 health
    void useHealthPotion(Player& player) {
        player.restoreHealth(50); // Assumes Player has restoreHealth
    }

    // Apply stamina potion: Restore 30 stamina
    void useStaminaPotion(Player& player) {
        player.restoreStamina(30);
    }

    // Apply power boost: Increase power by 5
    void usePowerBoost(Player& player) {
        player.increasePower(5);
    }

    // Equip weapon: Increase power based on weapon type
    void equipWeapon(Player& player, const std::string& weapon) {
        if (weapon == "Sword" || weapon == "Staff" || weapon == "Bow") {
            player.increasePower(10); // Example: Weapons increase power by 10
        }
    }

    // Use magic: Increase power based on spell type
    void useMagic(Player& player, const std::string& spell) {
        if (spell == "Fireball" || spell == "Power Shot" || spell == "Battle Cry") {
            player.increasePower(8); // Example: Spells increase power by 8
        }
    }
};

#endif // INVENTORY_H