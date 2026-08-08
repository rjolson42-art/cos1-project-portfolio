#include "../h Files/Unit.h"

//default constructor
Unit::Unit()

    : name("Grunt"), hp(10), maxHp(10), attackPower(2), movementRange(3), position({ -1, -1 }) {
}

//UnitType constructor
Unit::Unit(std::string unitName, UnitType type)
    : name(unitName), position({ -1, -1 }) {

    switch (type) {

    case UnitType::WARRIOR:

        hp = maxHp = 30;
        attackPower = 6;
        movementRange = 2;
        break;

    case UnitType::ARCHER:

        hp = maxHp = 18;
        attackPower = 8;
        movementRange = 4;
        break;

    case UnitType::MAGE:

        hp = maxHp = 14;
        attackPower = 10;
        movementRange = 3;
        break;

    case UnitType::CUSTOM:

    default:

        hp = maxHp = 20;
        attackPower = 4;
        movementRange = 3;
        break;
    }
}

//custom constructor
Unit::Unit(std::string unitName, int health, int atk, int moveRange, int startX, int startY)
    : name(unitName), hp(health), maxHp(health), attackPower(atk), movementRange(moveRange), position({ startX, startY }) {
}

//getters
std::string Unit::GetName() const { 

    return name; 
}

int Unit::GetHp() const { 
    
    return hp; 
}

int Unit::GetMaxHp() const { 
    
    return maxHp; 
}

int Unit::GetAttackPower() const { 
    
    return attackPower; 
}

int Unit::GetMovementRange() const { 
    
    return movementRange; 
}

bool Unit::IsAlive() const { 

    return hp > 0; 
}

//position methods
std::pair<int, int> Unit::GetPosition() const { 
    
    return position; 
}

void Unit::SetPosition(int x, int y) { 
    
    position = { x, y }; 
}

//combat methods
void Unit::TakeDamage(int amount) {

    //reducing hp
    hp -= amount;

    //checking if hp has fallen below 0
    if (hp < 0) {

        //setting hp to 0
        hp = 0;
    }
}

void Unit::Heal(int amount) {

    //adding to hp
    hp += amount;

    //checking if hpo has gone over maximum
    if (hp > maxHp) {

        //setting hp to max
        hp = maxHp;
    }
}