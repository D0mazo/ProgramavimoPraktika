#include <iostream>
#include "menu.h"
#include "Player/player.h"
#include "Battle/battle.h"  // Include the battle system

using namespace std;

int main() {
 // Show the menu and let the player choose a character
 MenuChoices choices = menu();
 Player player(choices.playerType);

 cout << "🔥 Welcome, warrior! Here are your stats:\n";
 cout << "Health: " << player.getHealth() << endl;
 cout << "Power: " << player.getPower() << endl;
 cout << "Stamina: " << player.getStamina() << endl;
 cout << "Gold: " << player.getGold() << " 💰" << endl;

 // Main game loop
 while (true) {
  cout << "\n====== MAIN MENU ======\n";
  cout << "1. Battle ⚔️\n";
  cout << "2. View Stats 📊\n";
  cout << "3. Quit Game ❌\n";
  cout << "Choose an action: ";

  int choice;
  cin >> choice;

  if (choice == 1) {
   battle(player);  // Start a fight
  }
  else if (choice == 2) {
   cout << "\n📊 Player Stats:\n";
   cout << "Health: " << player.getHealth() << endl;
   cout << "Power: " << player.getPower() << endl;
   cout << "Stamina: " << player.getStamina() << endl;
   cout << "Gold: " << player.getGold() << " 💰" << endl;
  }
  else if (choice == 3) {
   cout << "🏆 Thanks for playing! See you next time.\n";
   break;  // Exit game loop
  }
  else {
   cout << "❌ Invalid choice! Try again.\n";
  }
 }

 return 0;
}
