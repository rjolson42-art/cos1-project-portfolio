#include "../h Files/BattleGrid.h"
#include "../h Files/Unit.h"
#include <iostream>

//default constructor
BattleGrid::BattleGrid() : width(10), height(10) {

	//resizing grid
	grid.resize(height, std::vector<Tile>(width));

	//adding coordinates to each Tile of grid
}