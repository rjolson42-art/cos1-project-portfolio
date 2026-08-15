#include "../h Files/CombatLogic.h"
#include <iostream>
#include <random>

//constructor
CombatLogic::CombatLogic(int mapWidth, int mapHeight)
    : map(mapWidth, mapHeight),
    player(nullptr),
    enemy(nullptr),
    isBattleActive(false) {}

//destructor
CombatLogic::~CombatLogic() {

    delete player;
    delete enemy;
}

void CombatLogic::StartNewBattle() {

    //printing header
    std::cout << "\n========================================\n";
    std::cout << "         STARTING NEW BATTLEFIELD       \n";
    std::cout << "========================================\n";

    //deleting player and enemy data if there is any
    delete player;
    delete enemy;

    //vector for combatants
    std::vector<Unit*> combatants;

    //initializing default player and orc enemy and adding them to a combatants vector
    player = new Unit();
    combatants.push_back(player);
    enemy = new Unit("Orc Brute", UnitType::ORC_BRUTE);
    combatants.push_back(enemy);

    //callculating position to have user spawn at the bottom center of the battlefield
    int spawnX = map.GetWidth() / 2;
    int spawnY = map.GetHeight() - 1;

    //spawning user
    map.PlaceUnit(player, spawnX, spawnY);

    std::cout << "> " << player->GetName() << " deployed\n";

    //initiating random generator
    std::random_device rd;
    std::mt19937 gen(rd());

    //generating random coordinates on the opposit half of the map from player spawn
    std::uniform_int_distribution<> disX(0, map.GetWidth() - 1);
    std::uniform_int_distribution<> disY(0, (map.GetHeight() / 2) - 1);

    int enemySpawnX = disX(gen);
    int enemySpawnY = disY(gen);

    //generating new enemy spawn point if it is the same as player spawn point
    while (enemySpawnX == spawnX && enemySpawnY == spawnY) {
        enemySpawnX = disX(gen);
        enemySpawnY = disY(gen);
    }

    //spawning enemy
    map.PlaceUnit(enemy, enemySpawnX, enemySpawnY);

    isBattleActive = true;

    //printing battlefield
    map.DisplayGrid();

    //rolling initiative for each combatant
    for (Unit* unit : combatants) {

        unit->RollInitiative();
    }

    //sorting units by initiative order
    CombatLogic::SortInitiativeOrder(combatants);

    //printing out combat order
    std::cout << "\n--- Turn Order Established ---\n";

    //looping through combatants
    for (size_t i = 0; i < combatants.size(); ++i) {

        std::cout << i + 1 << ". " << combatants[i]->GetName()
            << " (Initiative: " << combatants[i]->GetInitiative() << ")\n";
    }

    //TODO: add combat logic
}

void CombatLogic::SortInitiativeOrder(std::vector<Unit*>& units) {

    //checking if sort is needed
    if (units.size() <= 1) {

        return;
    }

    //variable for sorting loop
    bool swapped = true;

    //variable for optimizing loop
    size_t n = units.size();

    //initiating sorting loop
    while (swapped) {

        swapped = false;

        for (size_t i = 0; i < n - 1; ++i) {

            //checking if units should be swapped
            if (units[i]->GetInitiative() < units[i + 1]->GetInitiative()) {

                //swapping units in vector
                Unit* temp = units[i];
                units[i] = units[i + 1];
                units[i + 1] = temp;

                //setting variable to continue sorting
                swapped = true;
            }
        }

        //adjusting optimization variable
        --n;
    }
}

