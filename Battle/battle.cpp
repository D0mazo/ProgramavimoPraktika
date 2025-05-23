#include "battle.h"
#include "monster_data.h"
#include <iostream>
#include <random>
#include <ctime>

// Return values: 1 = win, 0 = loss, 2 = escape
int battle(Player& player, const std::string& monsterName) {
    // Create the monster using the provided monsterName
    Monster monster = createMonster(monsterName);
    std::cout << "A wild " << monster.getName() << " appears!\n";
    std::cout << "Health: " << monster.getHealth() << " | Power: " << monster.getPower() << "\n\n";

    // Initialize random number generator
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_int_distribution<int> damageDist(0, player.getPower()); // Player damage: 0 to power
    std::uniform_int_distribution<int> runChance(0, 1); // 50% chance to escape
    std::uniform_int_distribution<int> goldDist(20, 50); // Gold reward: 20-50
    std::uniform_int_distribution<int> pointDist(10, 30); // Point reward: 10-30

    // Battle loop
    while (player.getHealth() > 0 && monster.getHealth() > 0) {
        std::cout << "\n====== BATTLE MENU ======\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Run Away\n";
        std::cout << "3. View Stats\n";
        std::cout << "4. Quit Battle\n";
        std::cout << "Choose an action: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) { // Attack
            int playerAttack = damageDist(rng);
            std::cout << "You attack the " << monster.getName() << " for " << playerAttack << " damage!\n";
            monster.takeDamage(playerAttack);

            if (monster.getHealth() <= 0) {
                std::cout << "You defeated the " << monster.getName() << "!\n";
                int goldReward = goldDist(rng);
                int pointReward = pointDist(rng);
                player.addGold(goldReward);
                player.addPoints(pointReward);
                std::cout << "You earned " << goldReward << " gold and " << pointReward << " points!\n";
                return 1; // Player wins, monster defeated
            }

            // Monster's turn to attack
            int monsterAttack = monster.attack();
            std::cout << monster.getName() << " attacks you for " << monsterAttack << " damage!\n";
            player.takeDamage(monsterAttack);

            if (player.getHealth() <= 0) {
                std::cout << "You have been defeated...\n";
                return 0; // Player loses
            }
        }
        else if (choice == 2) { // Run Away
            if (runChance(rng) == 0) {
                std::cout << "You successfully escaped from the " << monster.getName() << "!\n";
                return 2; 
            } else {
                std::cout << "Escape failed! The " << monster.getName() << " attacks you!\n";
                int monsterAttack = monster.attack();
                player.takeDamage(monsterAttack);
                if (player.getHealth() <= 0) {
                    std::cout << "You have been defeated...\n";
                    return 0; // Player loses
                }
            }
        }
        else if (choice == 3) { // View Stats
            std::cout << "Player Stats: Health = " << player.getHealth() << ", Power = " << player.getPower()
                      << ", Gold = " << player.getGold() << ", Points = " << player.getPoints() << "\n";
            std::cout << "Monster Stats: Health = " << monster.getHealth() << ", Power = " << monster.getPower() << "\n";
        }
        else if (choice == 4) { // Quit Battle
            std::cout << "You forfeited the battle.\n";
            return 0; // Forfeit counts as a loss
        }
        else {
            std::cout << "Invalid choice! Try again.\n";
        }
    }

    return 1; // Fallback (should not reach here due to loop conditions)
}