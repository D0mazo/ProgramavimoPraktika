#include "player.h"

// Constructor
Player::Player(int initialHealth, int initialPower, int initialStamina) {
    health = initialHealth;
    power = initialPower;
    stamina = initialStamina;
}

// Getters
int Player::getHealth() const {
    return health;
}

int Player::getPower() const {
    return power;
}

int Player::getStamina() const {
    return stamina;
}

// Methods to modify attributes
void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0; // Ensure health doesn't go negative
    }
}

void Player::increasePower(int amount) {
    power += amount;
}

void Player::useStamina(int amount) {
    stamina -= amount;
    if (stamina < 0) {
        stamina = 0; // Ensure stamina doesn't go negative
    }
}

void Player::restoreStamina(int amount) {
    stamina += amount;
}