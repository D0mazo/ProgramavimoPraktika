#include "monster.h"
#include <cstdlib> // For rand()
#include <ctime>   // For seeding random generator

// Constructor (Reordered for clarity)
Monster::Monster(std::string monsterName, int monsterHealth, int monsterPower, int monsterSpeed)
    : name   (monsterName),
      health (monsterHealth),
      power  (monsterPower),
      speed  (monsterSpeed)
{
    std::srand(std::time(0)); // Seed the random number generator once
}

// Getters
int Monster::getHealth() const   { return health; }
int Monster::getPower() const    { return power; }
int Monster::getSpeed() const    { return speed; }
std::string Monster::getName() const { return name; }

// Modifiers
void Monster::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0; // Prevent negative health
}

// ⚔️ Attack function: Random damage between 0 and power
int Monster::attack() {
    return rand() % (power + 1); // Random damage from 0 to power
}
