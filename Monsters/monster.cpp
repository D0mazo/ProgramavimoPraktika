#include "monster.h"

// Constructor with initialization list
Monster::Monster(std::string monsterName, int monsterHealth, int monsterPower, int monsterSpeed)
    : name(monsterName),
      health(monsterHealth),
      power(monsterPower),
      speed(monsterSpeed)
{
    // No need for seeding here - handled by static rng initialization
}

// Getters
int Monster::getHealth() const { return health; }
int Monster::getPower() const { return power; }
int Monster::getSpeed() const { return speed; }
std::string Monster::getName() const { return name; }

// Modifiers
void Monster::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0; // Prevent negative health
}

// ⚔️ Attack function: Random damage between 0 and power
int Monster::attack() {
    std::uniform_int_distribution<int> dist(0, power);
    return dist(rng); // Use static rng
}

// Utility method
bool Monster::isAlive() const {
    return health > 0;
}