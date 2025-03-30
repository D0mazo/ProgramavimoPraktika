#include "player.h"
#include <cstdlib> // For rand()
#include <ctime>   // For seeding random generator

// Constructor
Player::Player(int playerType, int initialHealth, int initialPower, int initialStamina, int initialGold) {
    std::srand(std::time(0)); // Seed the random number generator once

    type = playerType;
    gold = initialGold;

    switch (type) {
        case 1: // Warrior
            health = 150;
        power = 15;
        stamina = 40;
        break;
        case 2: // Mage
            health = 80;
        power = 20;
        stamina = 30;
        break;
        case 3: // Archer
            health = 100;
        power = 12;
        stamina = 60;
        break;
        default:
            health = initialHealth;
        power = initialPower;
        stamina = initialStamina;
        break;
    }
}

// Getters
int Player::getType() const { return type; }
int Player::getHealth() const { return health; }
int Player::getPower() const { return power; }
int Player::getStamina() const { return stamina; }
int Player::getGold() const { return gold; }

// Modifiers
void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

void Player::increasePower(int amount) {
    power += amount;
}

void Player::useStamina(int amount) {
    stamina -= amount;
    if (stamina < 0) stamina = 0;
}

void Player::restoreStamina(int amount) {
    stamina += amount;
    if (stamina > 100) stamina = 100;
}

// Gold methods
void Player::addGold(int amount) {
    gold += amount;
}

bool Player::spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

// Attack method: Random damage between 0 and max power
int Player::attack() {
    return rand() % (power + 1); // Random damage from 0 to power
}
