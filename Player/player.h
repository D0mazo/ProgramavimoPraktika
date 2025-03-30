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
    Player(int playerType, int initialHealth = 100, int initialPower = 10, int initialStamina = 50, int initialGold = 100) {
        std::srand(std::time(0)); // Seed random number generator

        type = playerType;
        health = initialHealth;
        power = initialPower;
        stamina = initialStamina;
        gold = initialGold;

        // Adjust attributes based on type
        switch (type) {
            case 1: // Warrior: High health, decent attack, moderate stamina
                health = 150;
                power = 15;
                stamina = 40;
                break;
            case 2: // Mage: Low health, high attack, low stamina
                health = 80;
                power = 20;
                stamina = 30;
                break;
            case 3: // Archer: Balanced stats, good stamina
                health = 100;
                power = 12;
                stamina = 60;
                break;
            default:
                break;
        }
    }

    // Getters
    int getType() const { return type; }
    int getHealth() const { return health; }
    int getPower() const { return power; }
    int getStamina() const { return stamina; }
    int getGold() const { return gold; } // 💰

    // Attribute modifiers
    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0;
    }

    void increasePower(int amount) { power += amount; }

    void useStamina(int amount) {
        stamina -= amount;
        if (stamina < 0) stamina = 0;
    }

    void restoreStamina(int amount) {
        stamina += amount;
        if (stamina > 100) stamina = 100;
    }

    // 💰 Gold management
    void addGold(int amount) { gold += amount; }

    bool spendGold(int amount) {
        if (gold >= amount) {
            gold -= amount;
            return true;
        }
        return false; // Not enough gold
    }

    // ⚔️ Attack function: Random damage between 0 and power
    int attack() {
        return rand() % (power + 1); // Random number between 0 and power
    }
};

#endif // PLAYER_H
