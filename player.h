#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int type;      // 1 = Warrior, 2 = Mage, 3 = Archer
    int health;    // Represents the player's current health (e.g., hit points)
    int power;     // Represents the player's attack strength or ability power
    int stamina;   // Represents the player's endurance or energy for actions

public:
    // Constructor to initialize the player's attributes based on type
    Player(int playerType, int initialHealth = 100, int initialPower = 10, int initialStamina = 50) {
        type = playerType;
        health = initialHealth;
        power = initialPower;
        stamina = initialStamina;

        // Adjust attributes based on type
        switch (type) {
            case 1: // Warrior: High health, decent power, moderate stamina
                health = 150;
                power = 15;
                stamina = 40;
                break;
            case 2: // Mage: Lower health, high power, low stamina
                health = 80;
                power = 20;
                stamina = 30;
                break;
            case 3: // Archer: Balanced health, moderate power, high stamina
                health = 100;
                power = 12;
                stamina = 60;
                break;
            default: // Invalid type keeps default values
                break;
        }
    }

    // Getters
    int getType() const { return type; }
    int getHealth() const { return health; }
    int getPower() const { return power; }
    int getStamina() const { return stamina; }

    // Setters or methods to modify attributes
    void takeDamage(int amount) {
        health -= amount;
        if (health < 0) health = 0; // Prevent negative health
    }
    void increasePower(int amount) { power += amount; }
    void useStamina(int amount) {
        stamina -= amount;
        if (stamina < 0) stamina = 0; // Prevent negative stamina
    }
    void restoreStamina(int amount) {
        stamina += amount;
        if (stamina > 100) stamina = 100; // Cap stamina (optional)
    }
};

#endif // PLAYER_H