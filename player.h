#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int health;    // Represents the player's current health (e.g., hit points)
    int power;     // Represents the player's attack strength or ability power
    int stamina;   // Represents the player's endurance or energy for actions

public:
    // Constructor to initialize the player's attributes
    Player(int initialHealth = 100, int initialPower = 10, int initialStamina = 50);

    // Getters
    int getHealth() const;
    int getPower() const;
    int getStamina() const;

    // Setters or methods to modify attributes
    void takeDamage(int amount);       // Reduces health by a specified amount
    void increasePower(int amount);    // Increases power by a specified amount
    void useStamina(int amount);       // Decreases stamina by a specified amount
    void restoreStamina(int amount);   // Increases stamina by a specified amount
};

#endif // PLAYER_H