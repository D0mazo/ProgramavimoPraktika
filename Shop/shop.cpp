#include "shop.h"
#include <iostream>

void Shop::displayItems() {
    std::cout << "\n===== Welcome to the Shop =====\n";
    std::cout << "Items Available:\n";
    std::cout << "1. Health Potion - 20 Gold\n";
    std::cout << "2. Stamina Potion - 15 Gold\n";
    std::cout << "3. Power Boost - 25 Gold\n";
    std::cout << "4. Sword (Warrior) - 50 Gold\n";
    std::cout << "5. Staff (Mage) - 50 Gold\n";
    std::cout << "6. Bow (Archer) - 50 Gold\n";

    std::cout << "===============================\n";
}

void Shop::buyItem(Player& player, Inventory& inventory, const std::string& itemName) {
    if (itemName == "Health Potion") {
        if (player.spendGold(20)) {
            inventory.useHealthPotion(player);
            std::cout << "You used a Health Potion!\n";
        } else std::cout << "Not enough gold.\n";
    }
    else if (itemName == "Stamina Potion") {
        if (player.spendGold(15)) {
            inventory.useStaminaPotion(player);
            std::cout << "You used a Stamina Potion!\n";
        } else std::cout << "Not enough gold.\n";
    }
    else if (itemName == "Power Boost") {
        if (player.spendGold(25)) {
            inventory.usePowerBoost(player);
            std::cout << "You used a Power Boost!\n";
        } else std::cout << "Not enough gold.\n";
    }
    else if (itemName == "Sword" && player.getType() == 1) {
        if (player.spendGold(50)) {
            inventory.equipWeapon(player, "Sword");
        } else std::cout << "Not enough gold.\n";
    }
    else if (itemName == "Staff" && player.getType() == 2) {
        if (player.spendGold(50)) {
            inventory.equipWeapon(player, "Staff");
        } else std::cout << "Not enough gold.\n";
    }
    else if (itemName == "Bow" && player.getType() == 3) {
        if (player.spendGold(50)) {
            inventory.equipWeapon(player, "Bow");
        } else std::cout << "Not enough gold.\n";
    }

}
