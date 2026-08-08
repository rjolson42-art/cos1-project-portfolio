#pragma once

#ifndef TILE_H
#define TILE_H

class Unit;

class Tile
{

private:

	//members
	int x;
	int y;
	bool traversable;
	Unit* occupant;

public:

	//constructors
	Tile();
	Tile(int tileX, int tileY, bool isTraversable = true);

	//getters
	int GetX() const;
	int GetY() const;
	bool IsTraversable() const;
	bool IsOccupied() const;
	Unit* GetOccupant() const;

	//setters
	void SetOccupant(Unit* unit);
	void RemoveOccupant();
};

#endif // TILE_H

