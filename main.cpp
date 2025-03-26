#include <iostream>
#include "menu.h"
#include "player.h"
using namespace std;

int main() {
 MenuChoices choices = menu();
 Player player(choices.playerType);

 cout << "Player Stats:\n";
 cout << "Health: " << player.getHealth() << endl;
 cout << "Power: " << player.getPower() << endl;
 cout << "Stamina: " << player.getStamina() << endl;

 return 0;
}