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
	bool IsValidPosition(int x, int y) const;
	bool PlaceUnit(Unit* unit, int targetX, int targetY);
	bool RemoveUnit(int x, int y);

	//tile getters
	Tile* GetTile(int x, int y);
	const Tile* GetTile(int x, int y) const;

	//display method
	void DisplayGrid() const;
};

#endif // BATTLEGRID_H

