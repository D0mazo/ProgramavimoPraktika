#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib> // For rand()
#include <ctime>   // For seeding random generator

class Player {
private:
    int type;      // 1 = Warrior, 2 = Mage, 3 = Archer
    int health;
    int power;     // Max attack damage
    int stamina;
    int gold;      // 💰 Player's gold

public:
    // Constructor with default gold
    Player(int playerType, int initialHealth = 100, int initialPower = 10, int initialStamina = 50, int initialGold = 100);

    // Getters
    int getType() const;
    int getHealth() const;
    int getPower() const;
    int getStamina() const;
    int getGold() const;

    // Attribute modifiers
    void takeDamage(int amount);
    void increasePower(int amount);
    void useStamina(int amount);
    void restoreStamina(int amount);

    // 💰 Gold management
    void addGold(int amount);
    bool spendGold(int amount);

    // ⚔️ Attack function: Random damage between 0 and power
    int attack();
};

#endif // PLAYER_H
