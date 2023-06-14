#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Player.h"
#include "Tile.h"

using namespace std;
using namespace sf;

// Init ---------------------------------------------------------------------------------------------------

extern class Tile;

// Body ---------------------------------------------------------------------------------------------------

class Grid
{
public:
	Grid();

	void spawnTile(int i, int x, int y, Color c);
	Tile& getTileByIndex(int index);
	vector<Tile>& getGridTiles();
	void setRebuildForNeighbours(int index);
	void mineIncomeTiles(int index, TileName tName, ResourceName rName, int value);
	vector<int> getIndexBuildingTiles();
	vector<Struct2i> getPositionAll();
	vector<Struct2i> getPositionPlus();
	vector<Struct2i> getPositionDiagonal();
	int getIndexTileOffsetByPosition(int index, int offsetX, int offsetY);
	void addBuildingTile(int index);
	void removeBuildingTile(int index);
	void updateTilesEarningsM();
private:
	vector <Tile> tiles;
	vector <int> buildingTiles;

	map<Struct2i, int> tilePositions;
	
	
	vector<Struct2i> neighbourPositionPlus{ {0,-1}, {1,0}, {0,1},{-1,0} };
	vector<Struct2i> neighbourPositionDiagonal{ {-1,-1}, {1,-1}, {1,1}, { -1,1} };
	vector<Struct2i> neighbourPositionAll{ {0,-1}, {1,0}, {0,1},{-1,0},{-1,-1}, {1,-1}, {1,1}, { -1,1} };


};

