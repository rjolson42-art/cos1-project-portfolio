#include "../h Files/Tile.h"

//default constructor
Tile::Tile() : x(0), y(0), traversable(true), occupant(nullptr) {}

//overload constructor
Tile::Tile(int tileX, int tileY, bool isTraversable)
    : x(tileX), y(tileY), traversable(isTraversable), occupant(nullptr) {
}