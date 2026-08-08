#include "../h Files/CombatLogic.h"
#include <iostream>

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

    //initializing player and enemy to default
    player = new Unit();
    enemy = new Unit();

    //callculating position to have user spawn at the bottom center of the battlefield
    int spawnX = map.GetWidth() / 2;
    int spawnY = map.GetHeight() - 1;

    //spawning user
    map.PlaceUnit(player, spawnX, spawnY);

    std::cout << "> " << player->GetName() << " deployed\n";

    isBattleActive = true;

    //printing battlefield
    map.DisplayGrid();

    //TODO: enemy spawns

    //TODO: generate initiative order

    //TODO: add combat logic
}

