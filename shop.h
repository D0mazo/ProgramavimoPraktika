#ifndef SHOP_H
#define SHOP_H

#include "player.h"
#include "inventory.h"
#include <string>

class Shop {
public:
    void displayItems();
    void buyItem(Player& player, Inventory& inventory, const std::string& itemName);
};

#endif // SHOP_H
