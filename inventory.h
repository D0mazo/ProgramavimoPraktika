#ifndef INVENTORY_H
#define INVENTORY_H

#include "player.h"
#include <string>

class Inventory {
public:
    // Item methods
    void useHealthPotion(Player& player);
    void usePowerBoost(Player& player);
    void useStaminaPotion(Player& player);

    // New methods
    void equipWeapon(Player& player, const std::string& weaponName);
    void useMagic(Player& player, const std::string& spellName);
};

#endif // INVENTORY_H
