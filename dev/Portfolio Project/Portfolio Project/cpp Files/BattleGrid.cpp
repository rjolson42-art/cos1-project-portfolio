#include "../h Files/BattleGrid.h"
#include "../h Files/Unit.h"
#include <iostream>

//default constructor
BattleGrid::BattleGrid() : width(10), height(10) {

	//resizing grid
	grid.resize(height, std::vector<Tile>(width));

	//adding Tiles to grid
	for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			grid[r][c] = Tile(c, r);
		}
	}
}

//overload constructor
BattleGrid::BattleGrid(int gridWidth, int gridHeight) : width(gridWidth), height(gridHeight) {

	//resizing grid
	grid.resize(height, std::vector<Tile>(width));

	//adding Tiles to grid
	for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			grid[r][c] = Tile(c, r);
		}
	}
}

//getters
int BattleGrid::GetWidth() const {

	return width;
}

int BattleGrid::GetHeight() const {

	return height;
}

//class methods
bool BattleGrid::isValidPosition(int x, int y) const {

	//returning true if position is within bounds
	return (x >= 0 && x < width && y >= 0 && y < height);
}

bool BattleGrid::placeUnit(Unit* unit, int targetX, int targetY) {

    //checking if position is in bounds
    if (!isValidPosition(targetX, targetY)) {

        //alerting user that the position is out of bounds
        std::cout << "[Grid Error] Target position (" << targetX << ", " << targetY << ") is out of bounds!\n";
        return false;
    }

    //checking if position is occipied
    if (grid[targetY][targetX].IsOccupied()) {

        //alerting user that the position is occupied
        std::cout << "[Grid Error] Tile (" << targetX << ", " << targetY << ") is already occupied!\n";
        return false;
    }

    //storing units current position
    std::pair<int, int> currentPos = unit->GetPosition();

    //checking if unit is being moved from another valid position
    if (isValidPosition(currentPos.first, currentPos.second)) {

        //checking if unit is actually at the position being moved from
        if (grid[currentPos.second][currentPos.first].GetOccupant() == unit) {

            //removing unit from the Tile
            grid[currentPos.second][currentPos.first].RemoveOccupant();
        }
    }

    //adding unit to the Tile
    grid[targetY][targetX].SetOccupant(unit);

    //setting units new postion
    unit->SetPosition(targetX, targetY);

    return true;
}