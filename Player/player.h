#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib> // For rand() - Note: Consider modern <random> later
#include <ctime>   // For seeding random generator with time(0)

class Player {
private:
    int type;      // 1 = Warrior, 2 = Mage, 3 = Archer
    int health;    // Current health points
    int power;     // Max attack damage
    int stamina;   // Energy for actions
    int gold;      // 💰 Player's gold

public:
    // Constructor with default parameters
    Player(int playerType,
           int initialHealth = 100,
           int initialPower = 10,
           int initialStamina = 50,
           int initialGold = 100);

    // Destructor (optional, but good practice)
    virtual ~Player() = default;

    // Getters (const correctness already present - great!)
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

    // Optional: Additional utility methods
    bool isAlive() const;  // Check if health > 0
    bool hasStamina(int amount) const;  // Check if enough stamina
};

#endif // PLAYER_H