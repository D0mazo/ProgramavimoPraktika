#include "monster_data.h"

// Function to create a monster by name
Monster createMonster(const std::string& monsterName) {
    // Easy Difficulty Monsters
    if (monsterName == "Goblin") {
        return Monster("Goblin", 50, 8, 70);
        // Description: A small, sneaky creature that relies on speed to ambush foes.
    }
    else if (monsterName == "Slime") {
        return Monster("Slime", 80, 5, 10);
        // Description: A gooey blob that engulfs its prey slowly.
    }
    else if (monsterName == "Skeleton") {
        return Monster("Skeleton", 40, 10, 50);
        // Description: An animated pile of bones, relentless but fragile.
    }
    // Medium Difficulty Monsters
    else if (monsterName == "Orc") {
        return Monster("Orc", 120, 15, 30);
        // Description: A brutish warrior with thick skin and a heavy club.
    }
    else if (monsterName == "Harpy") {
        return Monster("Harpy", 60, 10, 65);
        // Description: A winged creature with sharp talons and shrill cries.
    }
    else if (monsterName == "Spider") {
        return Monster("Spider", 70, 12, 75);
        // Description: A swift arachnid that ensnares victims in webs.
    }
    // Hard Difficulty Monsters
    else if (monsterName == "Troll") {
        return Monster("Troll", 200, 12, 20);
        // Description: A lumbering giant that regenerates wounds over time.
    }
    else if (monsterName == "Wraith") {
        return Monster("Wraith", 30, 18, 80);
        // Description: A ghostly entity that strikes with ethereal force.
    }
    else if (monsterName == "Dragon") {
        return Monster("Dragon", 250, 25, 40);
        // Description: A majestic, fire-breathing beast of legend.
    }
    else if (monsterName == "Minotaur") {
        return Monster("Minotaur", 150, 20, 25);
        // Description: A bull-headed warrior guarding its labyrinth.
    }
    // Default case
    else {
        return Monster("Unknown Beast", 50, 10, 50);
        // Description: A mysterious creature of unknown origin.
    }
}

// Helper function to get valid monster names for a given difficulty
std::vector<std::string> getMonstersByDifficulty(int difficulty) {
    std::vector<std::string> monsters;
    switch (difficulty) {
        case 1: // Easy
            monsters = {"Goblin", "Slime", "Skeleton"};
            break;
        case 2: // Medium
            monsters = {"Orc", "Harpy", "Spider"};
            break;
        case 3: // Hard
            monsters = {"Troll", "Wraith", "Dragon", "Minotaur"};
            break;
        default:
            monsters = {"Unknown Beast"};
            break;
    }
    return monsters;
}