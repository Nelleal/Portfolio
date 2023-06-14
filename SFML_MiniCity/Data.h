#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "Collision.hpp"
#include <string>

using namespace std;
using namespace sf;

// Init ---------------------------------------------------------------------------------------------------

struct Craft;
struct Income;
struct Struct2i;
struct UiInfo;
struct ResourceInfo;
struct ButtonInfo;
struct TileInfo;
struct DT_UiInfo;
struct DT_ResourceInfo;
struct DT_ButtonInfo;
struct DT_TilesInfo;
struct DT_RebuildInfo;

extern vector <Font> fonts;
extern map<Struct2i, int> tilePositions;

// Global ---------------------------------------------------------------------------------------------------

enum TileName { T_GRASS, T_ROAD, T_TREE, T_ROCK, T_CRYSTAL, T_STORE, T_WATER, T_MINE, T_FORESTERHOUSE, T_QUARRY };
enum ResourceName { R_NONE, R_WOOD, R_ROCK, R_CRYSTAL, R_GOLD };
enum PlayerAction { A_NONE, A_BUILD, A_UPGRADE };
enum UiName { U_YELLOWCLOUD, U_UNLOKED, U_LOKED, U_DESTROY, U_UPGRADE};
enum TileType {TY_TILE, TY_BUILDING, TY_RESOURCE };

// struct ---------------------------------------------------------------------------------------------------

struct Craft {
	ResourceName name;
	int value;
	float time;
	map<ResourceName, int> info;

	Craft();
	Craft(ResourceName name, int value,float time,map<ResourceName, int> info);
	Craft& operator = (const Craft& other);
};

struct Income {
	int value;
	float time;
	TileName incomeTile;
	Income();
	Income(TileName incomeTile, int value, float time);
	Income& operator = (const Income& other);
	void addValue(int value);
};

struct Struct2i {
	int x;
	int y;
	Struct2i();
	Struct2i(int x, int y);
	Struct2i& operator=(const Struct2i& other);
	bool operator<(const Struct2i& other) const;
	bool operator==(const Struct2i& other) const;
};

struct UiInfo {
	Texture texture;
	UiInfo();
	UiInfo(string fileName);
};

struct ResourceInfo {
	Texture texture;
	ResourceInfo();
	ResourceInfo(string fileName);
};

struct ButtonInfo {
	Texture texture;
	ButtonInfo();
	ButtonInfo(string fileName);
};

struct TileInfo
{
public:
	Texture texture;
	TileType type;

	bool canRebuildPlus;
	bool canRebuildDiagonal;

	bool canBuild;
	map<ResourceName, int> build;

	bool canMining;
	map<ResourceName, Struct2i> mining;

	bool canIncome;
	map<ResourceName, Income> income;

	bool canCraft;
	int unlokedCraftSlotCount;
	int maxCraftSlotCount;
	map<ResourceName, vector<Craft>> craft;


	TileInfo();
	TileInfo(string fileName, TileType type, bool canRebuildPlus, bool canRebuildDiagonal, bool canBuild, map<ResourceName, int> buildInfo, bool canMining, map<ResourceName, Struct2i> miningInfo, bool canIncome, map<ResourceName,Income> incomeInfo, bool canCraft, int unlokedCraftSlotCount, int maxCraftSlotCount, map<ResourceName, vector<Craft>> craftInfo);
private:
	void init();
};

// DataTable ---------------------------------------------------------------------------------------------------

struct DT_UiInfo {
	map <UiName, UiInfo> info;
	DT_UiInfo();
private:
	void addElemet(UiName name, string fileName);
};

struct DT_ResourceInfo {
	map<ResourceName, ResourceInfo> info;
	DT_ResourceInfo();
private:
	void addElemet(ResourceName name, string fileName);
};

struct DT_ButtonInfo {
	map<TileName, ButtonInfo> info;
	DT_ButtonInfo();
private:
	void addElemet(TileName name, string fileName);
};

struct DT_TileInfo
{
	map<TileName, TileInfo> info; 
	DT_TileInfo();
private:
	void addElement(TileName name, TileType type, string fileName, bool canRebuildPlus, bool canRebuildDiagonal, bool canBuild, map<ResourceName,int> buildInfo, bool canMining, map<ResourceName, Struct2i> miningInfo, bool canIncome, map<ResourceName, Income> incomeInfo, bool canCraft, int unlokedCraftSlotCount, int maxCraftSlotCount, map<ResourceName, vector<Craft>> craftInfo);
};

struct DT_RebuildInfo
{
	map<TileName, map<int, Texture>> rebuildTexture;
	DT_RebuildInfo();
private:
	vector<int> diagonalPosition{ 0,10000000,1000000,100000,10000,11000000,10100000,10010000,110000,1100000,1010000,11100000,1110000,10110000,11010000,11110000 };

	vector<int> v7{ 0,10000000,100000,10000,10100000,10010000,110000,10110000 };
	vector<int> v8{ 0,1000000,100000,10000,1100000,1010000,110000,1110000 };
	vector<int> v9{ 0,10000000,1000000,100000,11000000,1100000,10100000,11100000 };
	vector<int> v10{ 0,10000000,1000000,10000,11000000,10010000,1010000,11010000 };

	vector<int> v16{ 1000000,11000000,1100000,1010000,11100000,11010000,1110000,11110000 };
	vector<int> v17{ 10000000,11000000,10100000,10010000,11100000,10110000,11010000,11110000, };
	vector<int> v18{ 10000,10010000,1010000,110000,11010000,1110000,10110000,11110000 };
	vector<int> v19{ 100000,10100000,1100000,110000,11100000,10110000,1110000,11110000 };

	vector<int> v11{ 0,10000000,1000000,11000000 };
	vector<int> v20{ 10000,10010000,1010000,11010000 };
	vector<int> v21{ 100000,10100000,1100000,11100000 };
	vector<int> v22{ 110000,10110000,1110000,11110000 };

	vector<int> v12{ 0,10000000,10000,10010000 };
	vector<int> v23{ 1000000,11000000,11010000,1010000 };
	vector<int> v24{ 100000,10100000,110000,10110000 };
	vector<int> v25{ 1100000,11100000,1110000,11110000 };

	vector<int> v13{ 0,100000,10000,110000 };
	vector<int> v26{ 10000000,10100000,10010000,10110000, };
	vector<int> v27{ 1000000,1100000,1010000,1110000 };
	vector<int> v28{ 11000000,11100000,11010000,11110000 };

	vector<int> v14{ 0,1000000,100000,1100000 };
	vector<int> v29{ 10000000,11000000,10100000,11100000 };
	vector<int> v30{ 10000,1010000,110000,1110000 };
	vector<int> v31{ 10010000,11010000,10110000,11110000 };

	void addElements(TileName name, vector<int> vi, int i, string fileName);
	void addElement(TileName name, int i, string fileName);
};

