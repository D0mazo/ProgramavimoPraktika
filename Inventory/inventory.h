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


};

#endif // INVENTORY_H