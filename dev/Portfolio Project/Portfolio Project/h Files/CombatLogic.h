#pragma once

#ifndef COMBATLOGIC_H
#define COMBATLOGIC_H

#include "BattleGrid.h"
#include "Unit.h"

class CombatLogic {

private:

    //members
    BattleGrid map;
    Unit* player;
    Unit* enemy;
    bool isBattleActive;

public:

    //constructor
    CombatLogic(int mapWidth = 6, int mapHeight = 6);
    
    //destructor
    ~CombatLogic();

    //system initializer method
    void StartNewBattle();

    //initiative order sorting function
    void SortInitiativeOrder(std::vector<Unit*>& queue);

    //combat turn function
    void UnitTurn(Unit* activeUnit);
    void ProcessUnitMovement(Unit* activeUnit);
    void ProcessUnitAttack(Unit* attacker, Unit* defender);
    void ProcessAITurn(Unit* enemyUnit, Unit* targetUnit);
};

#endif // COMBATLOGIC_H
