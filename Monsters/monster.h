#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <random>

class Monster {
private:
    int health;        // Monster's hit points
    int power;         // Maximum attack strength
    int speed;         // Speed (could be used for initiative or evasion)
    std::string name;  // Monster's name
    static std::mt19937 rng;  // Static random number generator

public:
    // Constructor with default parameters
    Monster(std::string monsterName,
            int monsterHealth = 100,
            int monsterPower = 10,
            int monsterSpeed = 10);

    virtual ~Monster() = default;

    // Getters
    int getHealth() const;
    int getPower() const;
    int getSpeed() const;
    std::string getName() const;

    // Modifiers
    void takeDamage(int amount);

    // ⚔️ Attack function: Random damage between 0 and max power
    int attack();

    // Utility method
    bool isAlive() const;
};

// Define static member
std::mt19937 Monster::rng{static_cast<unsigned>(std::time(nullptr))};

#endif // MONSTER_H