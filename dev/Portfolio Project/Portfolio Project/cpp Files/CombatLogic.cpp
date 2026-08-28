#include "../h Files/CombatLogic.h"
#include <iostream>
#include <random>

//constructor
CombatLogic::CombatLogic(int mapWidth, int mapHeight)
    : map(mapWidth, mapHeight),
    party(),
    enemies(),
    isBattleActive(false) {
}

//destructor
CombatLogic::~CombatLogic() {

    for (Unit* member : party) {

        delete member;
    }
    party.clear();

    for (Unit* enemy : enemies) {

        delete enemy;
    }
    enemies.clear();
}

void CombatLogic::StartNewBattle() {

    //printing header
    std::cout << "\n========================================\n";
    std::cout << "         STARTING NEW BATTLEFIELD       \n";
    std::cout << "========================================\n";

    //variables for menu navigation and validation
    std::string inputChoice;
    int menuChoice = 0;

    while (true) {

        //prompting user if they want to customize battlefield
        std::cout << "Would you like to customize the battlegrid size? (1 = Yes, 2 = No): ";
        std::cin >> inputChoice;

        //checking for integer
        try {

            menuChoice = std::stoi(inputChoice);
        }
        catch (...) {

            //informing user input is not an integer
            std::cout << "Input is not an integer. Please enter 1 for Yes or 2 for No.\n";
            continue;
        }

        //checking if input is a valid option
        if (menuChoice == 1 || menuChoice == 2) {

            break;
        }

        //reprompting user
        std::cout << "Please enter 1 or 2.\n";
    }

    //setting default dimensions
    int gridWidth = 6;
    int gridHeight = 6;

    if (menuChoice == 1) {

        //prompting user for grid width
        while (true) {

            std::cout << "Enter custom grid width (5 - 9): ";
            std::cin >> inputChoice;

            //validating integer
            try {

                gridWidth = std::stoi(inputChoice);
            }
            catch (...) {

                //reprompting user
                std::cout << "Input is not an integer. Please enter a valid integer.\n";
                continue;
            }

            //checking for valid range
            if (gridWidth >= 5 && gridWidth <= 9) {

                break;
            }

            //reprompting user
            std::cout << "Width must be between 5 and 9 to fit the window properly.\n";
        }

        //prompting user for grid height
        while (true) {

            std::cout << "Enter custom grid height (5 - 9): ";
            std::cin >> inputChoice;

            //validating integer
            try {

                gridHeight = std::stoi(inputChoice);
            }
            catch (...) {

                //reprompting user
                std::cout << "Input is not an integer. Please enter a valid integer.\n";
                continue;
            }

            //checking for valid range
            if (gridHeight >= 5 && gridHeight <= 9) {

                break;
            }

            //reprompting user
            std::cout << "Height must be between 5 and 9 to fit the window properly.\n";
        }

        //printing grid details
        std::cout << "\n[Custom grid selected: " << gridWidth << "x" << gridHeight << "]\n";
    }
    else {

        //informing user default grid size will be used
        std::cout << "\n[Using standard default grid size: 6x6]\n";
        gridWidth = 6;
        gridHeight = 6;
    }

    // Instantiate map using your overloaded constructor with chosen dimensions
    map = BattleGrid(gridWidth, gridHeight);

    //clearing previous party memory
    for (Unit* member : party) {
        delete member;
    }
    party.clear();

    for (Unit* enemyUnit : enemies) {
        delete enemyUnit;
    }
    enemies.clear();

    //vector for combatants
    std::vector<Unit*> combatants;

    //initializing random generator engine once for enemy selection and spawn calculations
    std::random_device rd;
    std::mt19937 gen(rd());

    //prompting user for party size
    int partySize = 1;
    std::string partySizeStr;

    std::cout << "\n--- PARTY FORMATION ---\n";
    std::cout << "How many units would you like in your party? (1 - 3): ";

    while (true) {

        std::cin >> partySizeStr;

        try {

            partySize = std::stoi(partySizeStr);
        }
        catch (...) {

            std::cout << "Input is not an integer. Please enter a number between 1 and 3: ";
            continue;
        }

        if (partySize >= 1 && partySize <= 3) {

            break;
        }

        std::cout << "Selection out of range. Please enter 1, 2, or 3: ";
    }

    //populating user unit vector
    for (int i = 0; i < partySize; ++i) {

        //printing menu for unit slection
        std::cout << "\n--- RECRUIT MEMBER " << (i + 1) << " OF " << partySize << " ---\n";
        std::cout << "1. Warrior  (HP: 30 | ATK: 6  | MOV: 2 | RNG: 1)\n";
        std::cout << "2. Archer   (HP: 18 | ATK: 8  | MOV: 4 | RNG: 3)\n";
        std::cout << "3. Mage     (HP: 14 | ATK: 10 | MOV: 3 | RNG: 2)\n";
        std::cout << "Select class (1-3): ";

        std::string archetypeChoiceStr;
        int archetypeChoice = 0;
        UnitType memberType = UnitType::WARRIOR;

        while (true) {

            std::cin >> archetypeChoiceStr;

            //validating input
            try {

                archetypeChoice = std::stoi(archetypeChoiceStr);
            }
            catch (...) {

                //reprompting user to amke new slection
                std::cout << "Input is not an integer. Please enter 1, 2, or 3: ";
                continue;
            }

            if (archetypeChoice >= 1 && archetypeChoice <= 3) {

                break;
            }

            //reprompting user
            std::cout << "Selection out of range. Please enter 1, 2, or 3: ";
        }

        //getting unit type
        switch (archetypeChoice) {

        case 1:

            memberType = UnitType::WARRIOR;
            break;

        case 2:

            memberType = UnitType::ARCHER;
            break;

        case 3:

            memberType = UnitType::MAGE;
            break;
        }

        //prompting user for unit name
        std::string memberName;
        std::cout << "Enter name for Unit " << (i + 1) << ": ";
        std::cin >> memberName;

        //creating unit and adding to party and global turn order vector
        Unit* member = new Unit(memberName, memberType);
        party.push_back(member);
        combatants.push_back(member);
    }

    //initializing vector of enemy archetypes
    std::vector<std::pair<std::string, UnitType>> enemyPool = {

        {"Orc Brute", UnitType::ORC_BRUTE},
        {"Skeleton Archer", UnitType::SKELETON_ARCHER},
        {"Goblin Scrapper", UnitType::GOBLIN_SCRAPPER}
    };

    //getting enemy archetype
    std::uniform_int_distribution<> enemyDist(0, static_cast<int>(enemyPool.size() - 1));

    //spawning matching number of random enemies
    for (int i = 0; i < partySize; ++i) {

        int randomIndex = enemyDist(gen);

        //setting enemy archetype
        std::string enemyName = enemyPool[randomIndex].first + " " + std::to_string(i + 1);
        UnitType enemyType = enemyPool[randomIndex].second;

        //setting random enemy as combatant
        Unit* newEnemy = new Unit(enemyName, enemyType);
        enemies.push_back(newEnemy);
        combatants.push_back(newEnemy);
    }

    std::cout << "\n[" << enemies.size() << " hostile forces have appeared on the battlefield!]\n";

    //calculating starting position to deploy party centered along the bottom row
    int startX = (map.GetWidth() - static_cast<int>(party.size())) / 2;
    int spawnY = map.GetHeight() - 1;

    for (size_t i = 0; i < party.size(); ++i) {

        int spawnX = startX + static_cast<int>(i);
        map.PlaceUnit(party[i], spawnX, spawnY);
        std::cout << "> " << party[i]->GetName() << " deployed at (" << spawnX << ", " << spawnY << ")\n";
    }

    //generating random coordinates on the opposite half of the map from party spawn
    std::uniform_int_distribution<> disX(0, map.GetWidth() - 1);
    std::uniform_int_distribution<> disY(0, (map.GetHeight() / 2) - 1);

    for (Unit* enemyUnit : enemies) {

        int enemySpawnX = disX(gen);
        int enemySpawnY = disY(gen);

        //checking tile occupancy before placing
        while (map.GetTile(enemySpawnX, enemySpawnY)->IsOccupied()) {

            enemySpawnX = disX(gen);
            enemySpawnY = disY(gen);
        }

        //spawning enemy
        map.PlaceUnit(enemyUnit, enemySpawnX, enemySpawnY);
        std::cout << "> " << enemyUnit->GetName() << " spawned at (" << enemySpawnX << ", " << enemySpawnY << ")\n";
    }

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

    int roundNumber = 1;

    //looping unit turns until a combatant is slain
    while (isBattleActive) {

        //header for each round
        std::cout << "\n========================================\n";
        std::cout << "              ROUND " << roundNumber << "                  \n";
        std::cout << "========================================\n";

        //looping through combatants
        for (Unit* unit : combatants) {

            //checking if unit is alive
            if (!unit->IsAlive()) {

                continue;
            }

            //running unit turn
            UnitTurn(unit);

            //checking if any party members are still alive
            bool isPartyAlive = false;
            for (Unit* member : party) {

                if (member->IsAlive()) {

                    isPartyAlive = true;
                    break;
                }
            }

            //checking for defeat condition
            if (!isPartyAlive) {

                //printing defeat header
                std::cout << "\n========================================\n";
                std::cout << "             DEFEAT!                    \n";
                std::cout << " Your party has been slain on the battlefield.\n";
                std::cout << "========================================\n";
                isBattleActive = false;
                break;
            }

            //checking for victory condition
            bool areEnemiesAlive = false;
            for (Unit* enemyUnit : enemies) {

                if (enemyUnit->IsAlive()) {

                    areEnemiesAlive = true;
                    break;
                }
            }

            if (!areEnemiesAlive) {

                //printing victory header
                std::cout << "\n========================================\n";
                std::cout << "             VICTORY!                   \n";
                std::cout << "   You have slain all hostile forces!\n";
                std::cout << "========================================\n";
                isBattleActive = false;
                break;
            }

            //reprinting battlefield
            map.DisplayGrid();
        }

        // Advance to next round if both sides are still alive
        roundNumber++;
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

Unit* CombatLogic::SelectTargetFromList(const std::vector<Unit*>& candidates) {

    //checking if candidates vector is empty
    if (candidates.empty()) return nullptr;

    //returning sole target if only one candidate exists
    if (candidates.size() == 1) return candidates[0];

    //printing target selection header
    std::cout << "\n--- SELECT TARGET ---\n";

    //looping through candidates to display available targets
    for (size_t i = 0; i < candidates.size(); ++i) {

        std::cout << i + 1 << ". " << candidates[i]->GetName()
            << " (HP: " << candidates[i]->GetHp() << "/" << candidates[i]->GetMaxHp() << ")\n";
    }

    //variables for menu navigation and validation
    std::string choiceStr;
    int choice = 0;

    while (true) {

        //prompting user for target choice
        std::cout << "Select target (1-" << candidates.size() << "): ";
        std::cin >> choiceStr;

        //validating target choice
        try {

            choice = std::stoi(choiceStr);

            //checking if selection is within valid range
            if (choice >= 1 && choice <= static_cast<int>(candidates.size())) {

                return candidates[choice - 1];
            }
        }
        catch (...) {}

        //informing user selection is invalid
        std::cout << "Invalid target selection. Please enter a valid number.\n";
    }
}

void CombatLogic::UnitTurn(Unit* activeUnit) {
    if (!activeUnit || !activeUnit->IsAlive()) return;

    //checking if active unit is part of user party
    bool isPartyMember = false;
    for (Unit* member : party) {

        if (activeUnit == member) {

            isPartyMember = true;
            break;
        }
    }

    if (isPartyMember) {

        //informing user which unit turn it is
        std::cout << "\n>>> " << activeUnit->GetName() << "'s Turn! <<<\n";

        bool turnEnded = false;

        //looping user turn
        while (!turnEnded && isBattleActive) {

            //displaying action menu
            std::cout << "\n--- CHOOSE ACTION FOR " << activeUnit->GetName() << " ---\n";
            std::cout << "1. Move\n";
            std::cout << "2. Attack\n";
            std::cout << "3. End Turn\n";
            std::cout << "Select action (1-3): ";

            std::string actionInput;
            int actionChoice = 0;
            std::cin >> actionInput;

            //validating input
            try {

                actionChoice = std::stoi(actionInput);
            }
            catch (...) {

                std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
                continue;
            }

            switch (actionChoice) {
            case 1:

                //calling movement method
                ProcessUnitMovement(activeUnit);
                break;

            case 2: {

                //populating active enemy targets
                std::vector<Unit*> livingEnemies;
                for (Unit* e : enemies) {

                    if (e->IsAlive()) {

                        livingEnemies.push_back(e);
                    }
                }

                if (livingEnemies.empty()) {

                    std::cout << "No remaining targets available!\n";
                    break;
                }

                //selecting enemy target
                Unit* target = SelectTargetFromList(livingEnemies);

                if (target) {

                    //calling attack method
                    ProcessUnitAttack(activeUnit, target);
                }

                break;
            }

            case 3:

                //informing user the turn has ended
                std::cout << activeUnit->GetName() << " passes their turn.\n";
                turnEnded = true;
                break;

            default:

                //reprompting user for new slection
                std::cout << "Selection out of range. Please choose 1, 2, or 3.\n";
                break;
            }
        }
    }
    else {

        //populating targets
        std::vector<Unit*> livingParty;

        for (Unit* member : party) {

            if (member->IsAlive()) {

                livingParty.push_back(member);
            }
        }

        if (!livingParty.empty()) {

            //selecting target
            Unit* target = livingParty[0];
            ProcessAITurn(activeUnit, target);
        }
    }
}

void CombatLogic::ProcessUnitMovement(Unit* activeUnit) {

    //printing active unit info
    std::cout << "\n--- " << activeUnit->GetName() << "'s Movement Phase ---\n";
    std::cout << "Max Movement Range: " << activeUnit->GetMovementRange() << "\n";

    //getting unit current position
    std::pair<int, int> currentPos = activeUnit->GetPosition();
    int startX = currentPos.first;
    int startY = currentPos.second;

    //variable for user input and target location
    std::string inputStr;
    int targetX = -1;
    int targetY = -1;

    while (true) {

        //getting user input on row location
        while (true) {

            //promting user to enter a row
            std::cout << "Enter target X coordinate (0 to " << map.GetWidth() - 1 << "): ";
            std::cin >> inputStr;

            //validating integer
            try {

                targetX = std::stoi(inputStr);
                break;
            }
            catch (...) {

                //reprompting user to enter an integer
                std::cout << "Input is not an integer. Please enter a valid integer.\n";
            }
        }

        //getting user input on column location
        while (true) {


            std::cout << "Enter target Y coordinate (0 to " << map.GetHeight() - 1 << "): ";
            std::cin >> inputStr;

            //validating integer
            try {

                targetY = std::stoi(inputStr);
                break;
            }
            catch (...) {

                //repromting user to enter an integer
                std::cout << "Input is not an integer. Please enter a valid integer.\n";
            }
        }

        //checking input against grid bounds
        if (!map.IsValidPosition(targetX, targetY)) {

            //promting user that input is not a valid position
            std::cout << "Error: Target position is out of bounds. Try again.\n";
            continue;
        }

        //getting targeted tile
        Tile* destTile = map.GetTile(targetX, targetY);

        //checking if tile is occupied
        if (destTile != nullptr && destTile->IsOccupied()) {

            //repromting user to select a new location
            std::cout << "Error: That tile is already occupied by another unit. Try again.\n";
            continue;
        }

        //getting distance to new location
        int distance = std::abs(targetX - startX) + std::abs(targetY - startY);

        //checking if distance is within movement range
        if (distance > activeUnit->GetMovementRange()) {

            //repromting user for new location
            std::cout << "Error: Target is out of range! (Distance: " << distance
                << ", Max Range: " << activeUnit->GetMovementRange() << ")\n";
            continue;
        }

        break;
    }

    //moving unit
    map.RemoveUnit(startX, startY);
    map.PlaceUnit(activeUnit, targetX, targetY);

    //updating unit position
    activeUnit->SetPosition(targetX, targetY);

    std::cout << "> " << activeUnit->GetName() << " successfully moved to (" << targetX << ", " << targetY << ")!\n";

    //reprinting battlegrid
    map.DisplayGrid();
}

void CombatLogic::ProcessUnitAttack(Unit* attacker, Unit* defender) {

    std::cout << "\n--- " << attacker->GetName() << "'s Attack Phase ---\n";

    //getting position of attacker and defender
    std::pair<int, int> attackerPos = attacker->GetPosition();
    std::pair<int, int> defenderPos = defender->GetPosition();

    //getting distance using Chebyshev distance (allows 8-directional diagonal attacks at range 1)
    int distance = std::max(std::abs(attackerPos.first - defenderPos.first),
        std::abs(attackerPos.second - defenderPos.second));

    //checking if defender is within attackers specific attack range
    if (distance > attacker->GetAttackRange()) {

        //informing user defender is out of attack range
        std::cout << "Target " << defender->GetName() << " is out of range! Attack Failed! "
            << "(Distance: " << distance << " tile(s), Max Range: "
            << attacker->GetAttackRange() << " tile(s))\n";
        return;
    }

    //getting damage amount
    int damage = attacker->GetAttackPower();

    //printing attack action
    std::cout << "> " << attacker->GetName() << " attacks "
        << defender->GetName() << " for " << damage << " damage!\n";

    //applying damage to defender
    defender->TakeDamage(damage);

    //printing damage effects
    std::cout << defender->GetName() << " HP: "
        << defender->GetHp() << " / " << defender->GetMaxHp() << "\n";

    //checking if defender has been defeated
    if (!defender->IsAlive()) {

        //printing that defender has been defeated
        std::cout << "> " << defender->GetName() << " has been defeated!\n";

        //removing defending unit from the battlefield
        map.RemoveUnit(defenderPos.first, defenderPos.second);
    }
}

void CombatLogic::ProcessAITurn(Unit* enemyUnit, Unit* targetUnit) {

    //printing header for enemy turn
    std::cout << "\n========================================\n";
    std::cout << "          " << enemyUnit->GetName() << "'s TURN (AI)           \n";
    std::cout << "========================================\n";

    //getting unit positions
    std::pair<int, int> enemyPos = enemyUnit->GetPosition();
    std::pair<int, int> targetPos = targetUnit->GetPosition();

    int currentX = enemyPos.first;
    int currentY = enemyPos.second;
    int targetX = targetPos.first;
    int targetY = targetPos.second;

    //calculating distance between units using Chebyshev distance
    int distance = std::max(std::abs(currentX - targetX), std::abs(currentY - targetY));

    //moving if out of units specific attack range
    if (distance > enemyUnit->GetAttackRange()) {

        //getting movement range
        int movesLeft = enemyUnit->GetMovementRange();

        //looping until movement is depleted
        while (movesLeft > 0) {

            //setting position
            int nextX = currentX;
            int nextY = currentY;

            //getting horizontal direction
            if (currentX < targetX) {

                nextX++;
            }
            else if (currentX > targetX) {

                nextX--;
            }

            //getting vertical direction
            if (currentY < targetY) {

                nextY++;
            }
            else if (currentY > targetY) {

                nextY--;
            }

            //checking if Tile is valid to move to
            if (map.IsValidPosition(nextX, nextY)) {

                //getting tile
                Tile* tile = map.GetTile(nextX, nextY);

                //checking if tile is occupied or invalid
                if (tile != nullptr && !tile->IsOccupied()) {

                    //recording new position
                    currentX = nextX;
                    currentY = nextY;

                    //decreasing movement
                    movesLeft--;

                    //checking if within units specific attack range to stop early
                    if (std::max(std::abs(currentX - targetX), std::abs(currentY - targetY)) <= enemyUnit->GetAttackRange()) {

                        break;
                    }
                    continue;
                }
            }
            break;
        }

        //checking if unit has moved
        if (currentX != enemyPos.first || currentY != enemyPos.second) {

            //moving unit on the battlegrid
            map.RemoveUnit(enemyPos.first, enemyPos.second);
            map.PlaceUnit(enemyUnit, currentX, currentY);
            enemyUnit->SetPosition(currentX, currentY);

            //informing user position has changed
            std::cout << "> " << enemyUnit->GetName() << " advances to ("
                << currentX << ", " << currentY << ").\n";
        }
        else {

            //informing user position has not changed
            std::cout << "> " << enemyUnit->GetName() << " holds position.\n";
        }
    }

    //recalculating position and distance after movement phase
    enemyPos = enemyUnit->GetPosition();
    distance = std::max(std::abs(enemyPos.first - targetX), std::abs(enemyPos.second - targetY));

    //checking for attack range
    if (distance <= enemyUnit->GetAttackRange()) {

        //attacking
        ProcessUnitAttack(enemyUnit, targetUnit);
    }
    else {

        //informing user attack is out of range
        std::cout << "> " << enemyUnit->GetName() << " is out of range to attack.\n";
    }
}