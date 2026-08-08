#pragma once

#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <utility> 

//enum for UnitTypes
enum class UnitType {
    CUSTOM,
    WARRIOR,
    ARCHER,
    MAGE
};

class Unit {

private:

    //members
    std::string name;
    int hp;
    int maxHp;
    int attackPower;
    int movementRange;

    //variable to track unit position
    std::pair<int, int> position;

public:

    //default constructor
    Unit();

    //UnitType constructor
    Unit(std::string unitName, UnitType type);

    //custom constructor
    Unit(std::string unitName, int health, int atk, int moveRange = 3, int startX = -1, int startY = -1);

    //getters
    std::string GetName() const;
    int GetHp() const;
    int GetMaxHp() const;
    int GetAttackPower() const;
    int GetMovementRange() const;
    bool IsAlive() const;

    //position methods
    std::pair<int, int> GetPosition() const;
    void SetPosition(int x, int y);

    //combat methods
    void TakeDamage(int amount);
    void Heal(int amount);
};

#endif // UNIT_H
