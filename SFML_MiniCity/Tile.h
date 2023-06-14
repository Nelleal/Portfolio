#pragma once
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>

#include "Data.h"
#include "Math.h"
#include "Player.h"
#include "Grid.h"

using namespace std;
using namespace sf;

// Init ---------------------------------------------------------------------------------------------------

extern class Grid;
extern class Player;
extern Grid grid;
extern Player player;
extern DT_TileInfo tileInfo;
extern DT_RebuildInfo rebuildInfo;
extern Vector2i windowSize;

// Body ---------------------------------------------------------------------------------------------------


class Tile {

public:

	Sprite sprite;

	Tile();
	Tile(int i, int x, int y, Color c);

	void updateSpawnAnimation(float elapcedTime);
	void changeTile(TileName name);
	void buildTile(TileName name);
	void upgrade();
	void mining();
	void craft(float elapcedTime);
	void income(float elapcedTime);
	void d_ResourceValue();
	void d_TilePosition();
	void select();
	void unSelect();
	bool getIsSpawn();
	int getIndex();
	Struct2i getPosition();
	map<ResourceName, int> getEarningsM();
	void setRebuild();
	TileName getName();
	void mineTile(ResourceName name, int value);
	void setTileBasedPn();
	void initSpawn();
	void updateEarningsM();
	void placeCraftInSlot(int slot, Craft& craft);
	int getUnlokedCraftSlotCount();
	int getMaxCraftSlotCount();
	map<int, Craft> getCurrentCraft();
	map<ResourceName, vector<Craft>>  getCraftInfo();

private:
	// Data =
	int index;
	Struct2i position;
	Color pnValue;
	// Info = 
	TileName name;
	int sizeX;
	int sizeY;
	map<ResourceName, int> currentResourcesValue;

	map<ResourceName, Income> incomeInfo;
	map<ResourceName, float> currentIncomeTime;

	int unlokedCraftSlotCount;
	int maxCraftSlotCount;
	map<ResourceName, vector<Craft>> craftInfo;
	map<int, Craft> currentCraft;
	map<int, float> currentCraftTime;
	
	map<ResourceName, int> earningsM;
	// Spawn = 
	bool isSpawn = false;

	float spawnStartPositionY;
	float spawnEndPositionY;
	float spawnGravityStrengh;
	float spawnTime;
	float spawnCurrentTime;

	void init();
	void setTransform();
	void setOffsetPosition(Texture& texture);
	void subtractMiningValue(ResourceName name, int value);
	int getCountIncome(TileName name);
	Texture* getTexture();
	bool enoughResourcesForBuild(TileName name);
	bool enoughResourcesForCraft(int craftSlot);

	int compareRebuildIndex(int neighbourIndex, int value, bool isSelf);
	int getRebuildIndex();

};


