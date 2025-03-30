#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster {
private:
    int health;     // Monster's hit points
    int power;      // Maximum attack strength
    int speed;      // Speed (could be used for initiative or evasion)
    std::string name; // Monster's name

public:
    // Constructor
    Monster(std::string monsterName, int monsterHealth, int monsterPower, int monsterSpeed);

    // Getters
    int getHealth() const;
    int getPower() const;
    int getSpeed() const;
    std::string getName() const;

    // Modifiers
    void takeDamage(int amount);

    // ⚔️ Attack function: Random damage between 0 and max power
    int attack();
};

#endif // MONSTER_H
