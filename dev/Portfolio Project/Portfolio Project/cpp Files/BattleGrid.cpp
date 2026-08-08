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
