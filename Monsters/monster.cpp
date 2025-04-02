#include "monster.h"

std::mt19937 Monster::rng{static_cast<unsigned>(std::time(nullptr))};

Monster::Monster(std::string monsterName, int monsterHealth, int monsterPower, int monsterSpeed)
    : name(monsterName),
      health(monsterHealth),
      power(monsterPower),
      speed(monsterSpeed) {
    if (health < 0) health = 0;
    if (power < 0) power = 0;
    if (speed < 0) speed = 0;
}

int Monster::getHealth() const { return health; }
int Monster::getPower() const { return power; }
int Monster::getSpeed() const { return speed; }
std::string Monster::getName() const { return name; }

void Monster::takeDamage(int amount) {
    if (amount > 0) {
        health -= amount;
        if (health < 0) health = 0;
    }
}

int Monster::attack() {
    std::uniform_int_distribution<int> damageDist(0, power);
    return damageDist(rng);
}

bool Monster::isAlive() const {
    return health > 0;
}