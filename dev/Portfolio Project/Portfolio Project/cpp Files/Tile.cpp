#include "../h Files/Tile.h"

//default constructor
Tile::Tile() : x(0), y(0), traversable(true), occupant(nullptr) {}

//overload constructor
Tile::Tile(int tileX, int tileY, bool isTraversable)
    : x(tileX), y(tileY), traversable(isTraversable), occupant(nullptr) {}

//getters
int Tile::GetX() const { 
    
    return x; 
}

int Tile::GetY() const { 
    
    return y; 
}

//methods
bool Tile::IsTraversable() const {

    //returning true if Tile is both traversable and unoccupied
    return traversable && occupant == nullptr;
}

bool Tile::IsOccupied() const {

    //returning true if Tile is unoccupied
    return occupant != nullptr;
}

Unit* Tile::GetOccupant() const {

    //returning occupant
    return occupant;
}

void Tile::SetOccupant(Unit* unit) {

    //setting occupant
    occupant = unit;
}

void Tile::RemoveOccupant() {

    //setting occupant to nullptr
    occupant = nullptr;
}