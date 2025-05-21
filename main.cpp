#include <iostream>
#include <random>
#include <ctime>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include "menu.h"
#include "Player/player.h"
#include "Battle/battle.h"
#include "shop.h"
#include "inventory.h"
#include "monster_data.h"

using namespace std;

// Struct to store game session history
struct GameSession {
    string playerName;
    string playerType;
    string difficulty;
    string result;
    string defeatedMonsters;
};

// Function to convert player type to string
string getPlayerTypeString(int playerType) {
    switch (playerType) {
        case 1: return "Warrior";
        case 2: return "Mage";
        case 3: return "Archer";
        default: return "Unknown";
    }
}

// Function to convert difficulty to string
string getDifficultyString(int difficulty) {
    switch (difficulty) {
        case 1: return "Easy";
        case 2: return "Medium";
        case 3: return "Hard";
        default: return "Unknown";
    }
}

// Function to join defeated monsters into a string
string joinMonsters(const set<string>& monsters) {
    if (monsters.empty()) return "None";
    string result;
    for (auto it = monsters.begin(); it != monsters.end(); ++it) {
        result += *it;
        if (next(it) != monsters.end()) result += ";";
    }
    return result;
}

// Function to load game history from CSV
vector<GameSession> loadGameHistory() {
    vector<GameSession> history;
    ifstream file("game_history.csv");
    if (!file.is_open()) return history; // Return empty vector if file doesn't exist

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        GameSession session;
        getline(ss, session.playerName, ',');
        getline(ss, session.playerType, ',');
        getline(ss, session.difficulty, ',');
        getline(ss, session.result, ',');

        getline(ss, session.defeatedMonsters, ',');
        history.push_back(session);
    }
    file.close();
    return history;
}

// Function to save game session to CSV
void saveGameSession(const GameSession& session) {
    ofstream file("game_history.csv", ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open game_history.csv for writing.\n";
        return;
    }
    // Write header if file is empty
    if (file.tellp() == 0) {
        file << "PlayerName,PlayerType,Difficulty,Result,DefeatedMonsters\n";
    }
    file << session.playerName << ","
         << session.playerType << ","
         << session.difficulty << ","
         << session.result << ","
         << session.defeatedMonsters << "\n";
    file.close();
}

// Function to display game history
void displayGameHistory(const vector<GameSession>& history) {
    if (history.empty()) {
        cout << "No game history available.\n";
        return;
    }
    cout << "\n====== GAME HISTORY ======\n";
    cout << "Player Name | Player Type | Difficulty | Result | Defeated Monsters\n";
    cout << "------------|-------------|------------|--------|------------------\n";
    for (const auto& session : history) {
        cout << session.playerName << " | "
             << session.playerType << " | "
             << session.difficulty << " | "
             << session.result << " | "
             << session.defeatedMonsters << "\n";
    }
}

int main() {
    // Seed RNG once at program start
    srand(static_cast<unsigned>(time(nullptr)));

    // Load game history
    vector<GameSession> gameHistory = loadGameHistory();
    if (!gameHistory.empty()) {
        cout << "\nPrevious Game Sessions:\n";
        displayGameHistory(gameHistory);
        cout << "\n";
    }

    // Show the menu and let the player choose a character
    MenuChoices choices = menu();
    Player player(choices.playerType);
    Inventory inventory;
    Shop shop;

    // Track defeated monsters
    set<string> defeatedMonsters;

    cout << "Welcome, warrior! Here are your stats:\n";
    cout << "Health: " << player.getHealth() << endl;
    cout << "Power: " << player.getPower() << endl;
    cout << "Stamina: " << player.getStamina() << endl;
    cout << "Gold: " << player.getGold() << endl;
    cout << "Points: " << player.getPoints() << endl;

    // Initialize game session
    GameSession currentSession;
    currentSession.playerName = choices.playerName;
    currentSession.playerType = getPlayerTypeString(choices.playerType);
    currentSession.difficulty = getDifficultyString(choices.difficulty);
    currentSession.result = "Quit"; // Default result

    // Main game loop
    while (true) {
        // Check win condition for all difficulty levels
        vector<string> levelMonsters = getMonstersByDifficulty(choices.difficulty);
        bool allDefeated = true;
        for (const auto& monster : levelMonsters) {
            if (defeatedMonsters.find(monster) == defeatedMonsters.end()) {
                allDefeated = false;
                break;
            }
        }
        if (allDefeated) {
            cout << "\nCongratulations, " << choices.playerName << "! You have defeated all "
                 << currentSession.difficulty << " mode monsters ("
                 << joinMonsters(set<string>(levelMonsters.begin(), levelMonsters.end()))
                 << ")!\n";
            cout << "You win the game!\n";
            currentSession.result = "Win";
            currentSession.defeatedMonsters = joinMonsters(defeatedMonsters);
            saveGameSession(currentSession);
            break; // Exit game loop
        }

        cout << "\n====== MAIN MENU ======\n";
        cout << "1. Battle\n";
        cout << "2. View Stats\n";
        cout << "3. Visit Shop\n";
        cout << "4. View Game History\n";
        cout << "5. Quit Game\n";
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
                currentSession.result = "Loss";
                currentSession.defeatedMonsters = joinMonsters(defeatedMonsters);
                saveGameSession(currentSession);
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
                default: cout << "Invalid item number!\n"; continue;
            }

            shop.buyItem(player, inventory, itemName);
        }
        else if (choice == 4) {
            // View game history
            displayGameHistory(gameHistory);
        }
        else if (choice == 5) {
            cout << "Thanks for playing! See you next time.\n";
            currentSession.result = "Quit";
            currentSession.defeatedMonsters = joinMonsters(defeatedMonsters);
            saveGameSession(currentSession);
            break; // Exit game loop
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}