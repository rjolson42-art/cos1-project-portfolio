#pragma once

#ifndef BATTLEGRID_H
#define BATTLEGRID_H

#include <vector>
#include "Tile.h"

//forward declaration for Unit class
class Unit;

class BattleGrid
{

private:

	//members
	int width;
	int height;

	//2D vector for battle grid
	std::vector<std::vector<Tile>> grid;

public:

	//constructors
	BattleGrid();
	BattleGrid(int gridWidth, int gridHeight);

	//getters
	int GetWidth() const;
	int GetHeight() const;

	//methods for placement and bounds
	bool isValidPosition(int x, int y) const;
	bool placeUnit(Unit* unit, int targetX, int targetY);
	bool removeUnit(int x, int y);

	//tile getters
	Tile* getTile(int x, int y);
	const Tile* getTile(int x, int y) const;

	//display method
	void displayGrid() const;
};

#endif // BATTLEGRID_H

