#include <iostream>
#include <random>
#include <ctime>
#include <set>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm> // Added for trim
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
    int pointsEarned;
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


// Helper function to trim whitespace
string trim(const string& str) {
    string result = str;
    result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
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

// Function to validate a GameSession
bool isValidSession(const GameSession& session) {
    // Check if critical fields are non-default and non-empty
    return !session.playerName.empty() && session.playerName != "PlayerName" &&
           !session.playerType.empty() && session.playerType != "PlayerType" &&
           !session.difficulty.empty() && session.difficulty != "Difficulty" &&
           !session.result.empty() && session.result != "Result";
}

// Function to load game history from CSV
vector<GameSession> loadGameHistory() {
    vector<GameSession> history;
    ifstream file("game_history.csv");
    if (!file.is_open()) return history;

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
        string pointsStr;
        getline(ss, pointsStr, ',');

        pointsStr = trim(pointsStr);
        if (!pointsStr.empty() && pointsStr.back() == '\r') {
            pointsStr.pop_back(); // Handle Windows line endings
        }

        try {
            session.pointsEarned = pointsStr.empty() ? 0 : stoi(pointsStr);
        } catch (const invalid_argument& e) {
            session.pointsEarned = 0;
        }

        // Only add valid sessions to the history
        if (isValidSession(session)) {
            history.push_back(session);
        }
    }

    file.close();
    return history;
}

// Function to save game session to CSV
void saveGameSession(const GameSession& session) {
    // Only save valid sessions
    if (!isValidSession(session)) {
        cout << "Warning: Attempted to save an invalid game session. Skipping.\n";
        return;
    }

    ofstream file("game_history.csv", ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open game_history.csv for writing.\n";
        return;
    }

    // Write header if file is empty
    if (file.tellp() == 0) {
        file << "PlayerName,PlayerType,Difficulty,Result,DefeatedMonsters,PointsEarned\n";
    }

    // Write session data
    file << session.playerName << ","
         << session.playerType << ","
         << session.difficulty << ","
         << session.result << ","
         << session.defeatedMonsters << ","
         << session.pointsEarned << "\n";

    file.close();
}

// Function to clean the CSV file by rewriting only valid entries
void cleanGameHistoryFile() {
    vector<GameSession> history = loadGameHistory();
    ofstream file("game_history.csv", ios::trunc); // Overwrite file
    if (!file.is_open()) {
        cout << "Error: Could not open game_history.csv for writing.\n";
        return;
    }

    // Write header
    file << "PlayerName,PlayerType,Difficulty,Result,DefeatedMonsters,PointsEarned\n";

    // Write only valid sessions
    for (const auto& session : history) {
        if (isValidSession(session)) {
            file << session.playerName << ","
                 << session.playerType << ","
                 << session.difficulty << ","
                 << session.result << ","
                 << session.defeatedMonsters << ","
                 << session.pointsEarned << "\n";
        }
    }

    file.close();
    cout << "Game history file cleaned successfully.\n";
}

// Function to display game history
void displayGameHistory(const vector<GameSession>& history) {
    if (history.empty()) {
        cout << "No game history available.\n";
        return;
    }

    const int nameWidth = 15;
    const int typeWidth = 12;
    const int diffWidth = 10;
    const int resultWidth = 8;
    const int monstersWidth = 20;
    const int pointsWidth = 12;

    cout << "\n====== GAME HISTORY ======\n";
    cout << left
         << setw(nameWidth) << "Player Name" << " | "
         << setw(typeWidth) << "Player Type" << " | "
         << setw(diffWidth) << "Difficulty" << " | "
         << setw(resultWidth) << "Result" << " | "
         << setw(monstersWidth) << "Defeated Monsters" << " | "
         << setw(pointsWidth) << "Points Earned" << "\n";
    cout << string(nameWidth, '-') << "-+-"
         << string(typeWidth, '-') << "-+-"
         << string(diffWidth, '-') << "-+-"
         << string(resultWidth, '-') << "-+-"
         << string(monstersWidth, '-') << "-+-"
         << string(pointsWidth, '-') << "\n";

    for (const auto& session : history) {
        string playerName = session.playerName.length() > nameWidth - 2
            ? session.playerName.substr(0, nameWidth - 5) + "..."
            : session.playerName;
        string defeatedMonsters = session.defeatedMonsters.length() > monstersWidth - 2
            ? session.defeatedMonsters.substr(0, monstersWidth - 5) + "..."
            : session.defeatedMonsters;

        cout << left
             << setw(nameWidth) << playerName << " | "
             << setw(typeWidth) << session.playerType << " | "
             << setw(diffWidth) << session.difficulty << " | "
             << setw(resultWidth) << session.result << " | "
             << setw(monstersWidth) << defeatedMonsters << " | "
             << setw(pointsWidth) << session.pointsEarned << "\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Clean the CSV file to remove invalid entries
    cleanGameHistoryFile();

    // Load the cleaned game history
    vector<GameSession> gameHistory = loadGameHistory();
    if (!gameHistory.empty()) {
        cout << "\nPrevious Game Sessions:\n";
        displayGameHistory(gameHistory);
        cout << "\n";
    }

    MenuChoices choices = menu();
    Player player(choices.playerType);
    Inventory inventory;
    Shop shop;

    set<string> defeatedMonsters;

    cout << "Welcome, warrior! Here are your stats:\n";
    cout << "Health: " << player.getHealth() << endl;
    cout << "Power: " << player.getPower() << endl;
    cout << "Stamina: " << player.getStamina() << endl;
    cout << "Gold: " << player.getGold() << endl;
    cout << "Points: " << player.getPoints() << endl;

    GameSession currentSession;
    currentSession.playerName = choices.playerName;
    currentSession.playerType = getPlayerTypeString(choices.playerType);
    currentSession.difficulty = getDifficultyString(choices.difficulty);
    currentSession.result = "Quit";

    while (true) {
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
            currentSession.pointsEarned = player.getPoints();
            saveGameSession(currentSession);
            break;
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
            static mt19937 rng(static_cast<unsigned>(time(nullptr)));
            vector<string> validMonsters = getMonstersByDifficulty(choices.difficulty);
            uniform_int_distribution<int> dist(0, validMonsters.size() - 1);
            string selectedMonster = validMonsters[dist(rng)];

            cout << "\nYou are now facing a " << selectedMonster << "!\n";
            bool wonBattle = battle(player, selectedMonster);

            if (wonBattle) {
                defeatedMonsters.insert(selectedMonster);
                cout << "You defeated the " << selectedMonster << "!\n";
            } else {
                cout << "You were defeated by the " << selectedMonster << ". Game Over!\n";
                currentSession.result = "Loss";
                currentSession.defeatedMonsters = joinMonsters(defeatedMonsters);
                currentSession.pointsEarned = player.getPoints();
                saveGameSession(currentSession);
                break;
            }
        } else if (choice == 2) {
            cout << "\nPlayer Stats:\n";
            cout << "Health: " << player.getHealth() << endl;
            cout << "Power: " << player.getPower() << endl;
            cout << "Stamina: " << player.getStamina() << endl;
            cout << "Gold: " << player.getGold() << endl;
            cout << "Points: " << player.getPoints() << endl;
            cout << "Defeated Monsters: ";
            if (defeatedMonsters.empty()) cout << "None";
            else for (const auto& monster : defeatedMonsters) cout << monster << " ";
            cout << endl;
        } else if (choice == 3) {
            shop.displayItems();
            cout << "Your Gold: " << player.getGold() << endl;
            cout << "Enter the item number to buy (or 0 to exit): ";

            int itemChoice;
            cin >> itemChoice;

            if (itemChoice == 0) {
                cout << "Leaving the shop.\n";
                continue;
            }

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
        } else if (choice == 4) {
            displayGameHistory(gameHistory);
        } else if (choice == 5) {
            cout << "Thanks for playing! See you next time.\n";
            currentSession.result = "Quit";
            currentSession.defeatedMonsters = joinMonsters(defeatedMonsters);
            currentSession.pointsEarned = player.getPoints();
            saveGameSession(currentSession);
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}