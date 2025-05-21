#include <iostream>
#include <random>
#include <ctime>
#include <set> // Added for tracking defeated monsters
#include "menu.h"
#include "Player/player.h"
#include "Battle/battle.h"
#include "shop.h"
#include "inventory.h"
#include "monster_data.h" // Added to access getMonstersByDifficulty

using namespace std;

int main() {
    // Seed RNG once at program start
    std::srand(std::time(0));

    // Show the menu and let the player choose a character
    MenuChoices choices = menu();
    Player player(choices.playerType);
    Inventory inventory; // Create inventory for the player
    Shop shop; // Create shop instance

    // Track defeated monsters
    set<string> defeatedMonsters;

    cout << "Welcome, warrior! Here are your stats:\n";
    cout << "Health: " << player.getHealth() << endl;
    cout << "Power: " << player.getPower() << endl;
    cout << "Stamina: " << player.getStamina() << endl;
    cout << "Gold: " << player.getGold() << endl;
    cout << "Points: " << player.getPoints() << endl;

    // Main game loop
    while (true) {
        // Check win condition for Easy mode
        if (choices.difficulty == 1) { // Easy mode
            vector<string> easyMonsters = getMonstersByDifficulty(1);
            bool allDefeated = true;
            for (const auto& monster : easyMonsters) {
                if (defeatedMonsters.find(monster) == defeatedMonsters.end()) {
                    allDefeated = false;
                    break;
                }
            }
            if (allDefeated) {
                cout << "\nCongratulations, " << choices.playerName << "! You have defeated all Easy mode monsters (Goblin, Slime, Skeleton)!\n";
                cout << "You win the game!\n";
                break; // Exit game loop
            }
        }

        cout << "\n====== MAIN MENU ======\n";
        cout << "1. Battle\n";
        cout << "2. View Stats\n";
        cout << "3. Visit Shop\n";
        cout << "4. Quit Game\n";
        cout << "Choose an action: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // Select a random monster for the chosen difficulty
            static mt19937 rng(static_cast<unsigned>(time(nullptr)));
            vector<string> validMonsters = getMonstersByDifficulty(choices.difficulty);
            uniform_int_distribution<int> dist(0, validMonsters.size() - 1);
            string selectedMonster = validMonsters[dist(rng)];

            cout << "\nYou are now facing a " << selectedMonster << "!\n";
            bool wonBattle = battle(player, selectedMonster); // Start a fight

            if (wonBattle) {
                defeatedMonsters.insert(selectedMonster); // Track defeated monster
                cout << "You defeated the " << selectedMonster << "!\n";
            } else {
                cout << "You were defeated by the " << selectedMonster << ". Game Over!\n";
                break; // Exit game loop on player defeat
            }
        }
        else if (choice == 2) {
            cout << "\nPlayer Stats:\n";
            cout << "Health: " << player.getHealth() << endl;
            cout << "Power: " << player.getPower() << endl;
            cout << "Stamina: " << player.getStamina() << endl;
            cout << "Gold: " << player.getGold() << endl;
            cout << "Points: " << player.getPoints() << endl;
            // Display defeated monsters
            cout << "Defeated Monsters: ";
            if (defeatedMonsters.empty()) {
                cout << "None";
            } else {
                for (const auto& monster : defeatedMonsters) {
                    cout << monster << " ";
                }
            }
            cout << endl;
        }
        else if (choice == 3) {
            // Shop menu
            shop.displayItems();
            cout << "Your Gold: " << player.getGold() << endl;
            cout << "Enter the item number to buy (or 0 to exit): ";

            int itemChoice;
            cin >> itemChoice;

            if (itemChoice == 0) {
                cout << "Leaving the shop.\n";
                continue;
            }

            // Map item choice to item name
            string itemName;
            switch (itemChoice) {
                case 1: itemName = "Health Potion"; break;
                case 2: itemName = "Stamina Potion"; break;
                case 3: itemName = "Power Boost"; break;
                case 4: itemName = "Sword"; break;
                case 5: itemName = "Staff"; break;
                case 6: itemName = "Bow"; break;
                case 7: itemName = (player.getType() == 1 ? "Battle Cry" :
                                   player.getType() == 2 ? "Fireball" : "Power Shot"); break;
                default: cout << "Invalid item number!\n"; continue;
            }

            shop.buyItem(player, inventory, itemName);
        }
        else if (choice == 4) {
            cout << "Thanks for playing! See you next time.\n";
            break; // Exit game loop
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}