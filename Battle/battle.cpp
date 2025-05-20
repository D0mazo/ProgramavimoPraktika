#include <iostream>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding random generator
#include "C:/Users/Domin/CLionProjects/untitled3/Player/player.h"
#include "C:/Users/Domin/CLionProjects/untitled3/Monsters/monster.h"
#include "C:/Users/Domin/CLionProjects/untitled3/Monsters/monster_data.h"

void battle(Player &player) {
    // Seed RNG
    std::srand(std::time(0));

    // List of available monster names
    std::string monsterNames[] = {
        "Goblin", "Orc", "Skeleton", "Troll", "Wraith",
        "Dragon", "Slime", "Harpy", "Minotaur", "Spider"
    };
    int numMonsters = 10; // Number of defined monsters
    std::string selectedMonster = monsterNames[rand() % numMonsters];

    // Generate a random monster using createMonster
    Monster monster = createMonster(selectedMonster);

    std::cout << "A wild " << monster.getName() << " appears!\n";
    std::cout << "Health: " << monster.getHealth() << " | Power: " << monster.getPower() << "\n\n";

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
            int playerAttack = rand() % (player.getPower() + 1);
            std::cout << "You attack the " << monster.getName() << " for " << playerAttack << " damage!\n";
            monster.takeDamage(playerAttack);

            if (monster.getHealth() <= 0) {
                std::cout << "You defeated the " << monster.getName() << "!\n";
                int goldReward = 20 + (rand() % 31); // Random gold reward (20-50)
                player.addGold(goldReward);
                std::cout << "You earned " << goldReward << " gold!\n";
                break;
            }

            // Monster's turn to attack
            int monsterAttack = monster.attack();
            std::cout << monster.getName() << " attacks you for " << monsterAttack << " damage!\n";
            player.takeDamage(monsterAttack);

            if (player.getHealth() <= 0) {
                std::cout << "You have been defeated...\n";
                break;
            }
        }

        else if (choice == 2) { // Run Away
            if (rand() % 2 == 0) {
                std::cout << "You successfully escaped!\n";
                break;
            } else {
                std::cout << "Escape failed! The " << monster.getName() << " attacks you!\n";
                int monsterAttack = monster.attack();
                player.takeDamage(monsterAttack);
            }
        }

        else if (choice == 3) { // View Stats
            std::cout << "Player Stats: Health = " << player.getHealth() << ", Power = " << player.getPower() << ", Gold = " << player.getGold() << "\n";
            std::cout << "Monster Stats: Health = " << monster.getHealth() << ", Power = " << monster.getPower() << "\n";
        }

        else if (choice == 4) { // Quit Battle
            std::cout << "You forfeited the battle.\n";
            break;
        }

        else {
            std::cout << "Invalid choice! Try again.\n";
        }
    }
}