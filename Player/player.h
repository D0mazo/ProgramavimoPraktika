#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int type;      // Player type (1=Warrior, 2=Mage, 3=Archer)
    int health;    // Player's hit points
    int power;     // Attack strength
    int stamina;   // Stamina for actions
    int gold;      // Currency
    int points;    // Player's points (e.g., experience or score)

public:
    // Constructor
    Player(int playerType, int initialHealth = 100, int initialPower = 10,
           int initialStamina = 50, int initialGold = 50, int initialPoints = 0);

    // Getters
    int getType() const;
    int getHealth() const;
    int getPower() const;
    int getStamina() const;
    int getGold() const;
    int getPoints() const; // Added for points

    // Modifiers
    void takeDamage(int amount);
    void increasePower(int amount);
    void useStamina(int amount);
    void restoreStamina(int amount);
    void restoreHealth(int amount); // Added for health potion
    void addPoints(int amount);    // Added for points

    // Gold methods
    void addGold(int amount);
    bool spendGold(int amount);

    // Attack method
    int attack();
};

#endif // PLAYER_H