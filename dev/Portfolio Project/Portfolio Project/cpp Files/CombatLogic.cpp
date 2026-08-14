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

    //initializing default player and orc enemy
    player = new Unit();
    enemy = new Unit("Orc Brute", UnitType::ORC_BRUTE);

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

    // Safety check: Ensure the enemy doesn't spawn on top of the player
    while (enemySpawnX == spawnX && enemySpawnY == spawnY) {
        enemySpawnX = disX(gen);
        enemySpawnY = disY(gen);
    }

    //spawning enemy
    map.PlaceUnit(enemy, enemySpawnX, enemySpawnY);

    isBattleActive = true;

    //printing battlefield
    map.DisplayGrid();

    //TODO: generate initiative order

    //TODO: add combat logic
}

