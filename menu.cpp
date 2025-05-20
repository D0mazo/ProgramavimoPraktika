#include <iostream>
#include <random>
#include <ctime>
#include "menu.h"
#include "monster_data.h"  // Include to access getMonstersByDifficulty
using namespace std;

MenuChoices menu() {
    int playerChoice, difficultyChoice;
    bool validInput = false;
    MenuChoices choices;  // Create an instance of the struct

    // Seed the random number generator
    static mt19937 rng(static_cast<unsigned>(time(nullptr)));

    // Prompt the player for their hero name
    cout << "Enter your hero name: ";
    getline(cin, choices.playerName); // Store the name in the struct

    // Player type menu
    do {
        cout << "=== Choose Your Player Type ===\n";
        cout << "1) Warrior\n";
        cout << "2) Mage\n";
        cout << "3) Archer\n";
        cout << "Enter your choice (1-3): ";
        cin >> playerChoice;

        if (playerChoice >= 1 && playerChoice <= 3) {
            validInput = true;
        } else {
            cout << "Invalid choice! Please select 1, 2, or 3.\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (!validInput);

    validInput = false;

    // Difficulty menu
    do {
        cout << "\n=== Choose Difficulty ===\n";
        cout << "1) Easy\n";
        cout << "2) Medium\n";
        cout << "3) Hard\n";
        cout << "Enter your choice (1-3): ";
        cin >> difficultyChoice;

        if (difficultyChoice >= 1 && difficultyChoice <= 3) {
            validInput = true;
        } else {
            cout << "Invalid choice! Please select 1, 2, or 3.\n\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (!validInput);

    // Get the list of monsters for the chosen difficulty
    vector<string> validMonsters = getMonstersByDifficulty(difficultyChoice);

    // Randomly select a monster from the valid monsters
    uniform_int_distribution<int> dist(0, validMonsters.size() - 1);
    choices.monsterName = validMonsters[dist(rng)];

    // Display selections
    cout << "\nYour Selections:\n";
    cout << "Hero Name: " << choices.playerName << "\n";
    cout << "Player Type: ";
    switch (playerChoice) {
        case 1: cout << "Warrior"; break;
        case 2: cout << "Mage"; break;
        case 3: cout << "Archer"; break;
    }
    cout << "\nDifficulty: ";
    switch (difficultyChoice) {
        case 1: cout << "Easy"; break;
        case 2: cout << "Medium"; break;
        case 3: cout << "Hard"; break;
    }
    cout << "\nOpponent: " << choices.monsterName << "\n";

    // Assign values to the struct and return it
    choices.playerType = playerChoice;
    choices.difficulty = difficultyChoice;
    return choices;
}
