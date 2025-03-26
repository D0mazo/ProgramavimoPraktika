#include "monster.h"
#include <string>

Monster::Monster(std::string monsterName, int monsterHealth, int monsterPower, int monsterSpeed, int monsterDamage) {
    name = monsterName;
    health = monsterHealth;
    power = monsterPower;
    speed = monsterSpeed;
    damage = monsterDamage;
}

// Getters
int Monster::getHealth() const { return health; }
int Monster::getPower() const { return power; }
int Monster::getSpeed() const { return speed; }
int Monster::getDamage() const { return damage; }
std::string Monster::getName() const { return name; }

// Methods to modify attributes
void Monster::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0; // Prevent negative health
}