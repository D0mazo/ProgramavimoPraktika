#ifndef MONSTER_H
#define MONSTER_H
#include <string>

class Monster {
private:
    int health;    // Monster's hit points
    int power;     // Monster's base attack strength
    int speed;     // Monster's speed (e.g., for initiative or evasion)
    int damage;    // Current damage dealt per attack
    std::string name; // Monster's name

public:
    // Constructor declaration with parameters for all attributes
    Monster(std::string monsterName, int monsterHealth, int monsterPower, int monsterSpeed, int monsterDamage);

    // Getters
    int getHealth() const;
    int getPower() const;
    int getSpeed() const;
    int getDamage() const;
    std::string getName() const;

    // Methods to modify attributes
    void takeDamage(int amount);
};

#endif // MONSTER_H