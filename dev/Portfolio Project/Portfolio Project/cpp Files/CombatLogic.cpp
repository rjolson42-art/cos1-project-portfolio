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

    //initiating unit turns loop
    for (Unit* unit : combatants) {

        //cehcking if unit is still alive
        if (!unit->IsAlive()) {

            //skipping units turn
            continue;
        }

        //running UnitTurn logic
        UnitTurn(unit);
    }
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

void CombatLogic::UnitTurn(Unit* activeUnit) {

    //bools for turn phases
    bool hasMoved = false;
    bool hasAttacked = false;
    bool isTurnActive = true;

    //initiating turn loop
    while (isTurnActive && isBattleActive) {

        //printing turn menu
        std::cout << "\n--- " << activeUnit->GetName() << "'s Turn --- \n";
        std::cout << "1. Move " << (hasMoved ? "(Done)" : "") << "\n";
        std::cout << "2. Attack " << (hasAttacked ? "(Done)" : "") << "\n";
        std::cout << "3. End Turn\n";
        std::cout << "Choose an action: ";

        //getting user input
        std::string userChoice;
        std::cin >> userChoice;

        //variable for switch
        int choice;

        //attempting to convert string to int
        try {

            choice = std::stoi(userChoice);
        }
        catch (...) {

            //informing user input is invalid
            std::cout << "Input is not an integer. Please enter an integer to select a menu option.\n";

            //setting menu choice to 0 to continue menu loop
            choice = 0;

            //returning to top of loop
            continue;
        }

        switch (choice) {
        case 1:

            //checking if unit has already moved
            if (!hasMoved) {

                std::cout << "> Executing Movement (Range: " << activeUnit->GetMovementRange() << ")\n";

                //TODO: Add unit movement logic
                
                hasMoved = true;
            }
            else {

                //informing user that the unit has already moved
                std::cout << "> Already moved this turn!\n";
            }
            break;

        case 2:

            //checking if unit has already attacked
            if (!hasAttacked) {

                std::cout << "> Executing Attack\n";

                //TODO: Add unit attack logic

                hasAttacked = true;
            }
            else {

                //informing user they have already attacked
                std::cout << "> Already attacked this turn!\n";
            }
            break;

        case 3:

            //informing user that this units turn is ending
            std::cout << "> Ending turn for " << activeUnit->GetName() << ".\n";

            isTurnActive = false;
            break;

        default:

            //informing user input is out of range
            std::cout << "Selection is not a valid option. Please enter an integer between 1 and 3\n";
            break;
        }
    }
}