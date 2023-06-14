#include "Data.h"


Craft::Craft() {}
Craft::Craft(ResourceName name, int value, float time, map<ResourceName, int> info){
	this->name = name;
	this->value = value;
	this->time = time;
	this->info = info;
}
Craft& Craft::operator=(const Craft& other)
{
	this->name = other.name;
	this->value = other.value;
	this->time = other.time;
	this->info = other.info;
	return *this;
}

// Income ---------------------------------------------------------------------------------------------------

Income::Income() {}
Income::Income(TileName incomeTile, int value, float time) {
	this->value = value;
	this->time = time;
	this->incomeTile = incomeTile;
}
Income& Income::operator=(const Income& other)
{
	this->value = other.value;
	this->time = other.time;
	this->incomeTile = other.incomeTile;
	return *this;
}
void Income::addValue(int value) {
	this->value += value;
}

// Struct2i ---------------------------------------------------------------------------------------------------

Struct2i::Struct2i() {}
Struct2i::Struct2i(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
Struct2i& Struct2i::operator=(const Struct2i& other)
{
	x = other.x;
	y = other.y;
	return *this;
}
bool Struct2i::operator<(const Struct2i& other) const
{
	if (x < other.x) {
		return true;
	}
	else if (other.x < x) {
		return false;
	}
	else {
		return (y < other.y);
	}
}
bool Struct2i::operator==(const Struct2i& other) const
{
	if (x == other.x && y == other.y)
	{
		return true;
	}
	else {
		return false;
	}
}

// UiInfo ---------------------------------------------------------------------------------------------------

UiInfo::UiInfo() {}
UiInfo::UiInfo(string fileName) {
	Collision::CreateTextureAndBitmask(texture, fileName);
}

// ResourceInfo ---------------------------------------------------------------------------------------------------

ResourceInfo::ResourceInfo() {}
ResourceInfo::ResourceInfo(string fileName) {
	Collision::CreateTextureAndBitmask(texture, fileName);
}

// ButtonInfo ---------------------------------------------------------------------------------------------------

ButtonInfo::ButtonInfo() {}
ButtonInfo::ButtonInfo(string fileName) {
	Collision::CreateTextureAndBitmask(texture, fileName);
}

// TileInfo ---------------------------------------------------------------------------------------------------

TileInfo::TileInfo() {}

TileInfo::TileInfo(string fileName, TileType type, bool canRebuildPlus, bool canRebuildDiagonal, bool canBuild, map<ResourceName, int> buildInfo, bool canMining, map<ResourceName, Struct2i> miningInfo, bool canIncome, map<ResourceName, Income> incomeInfo, bool canCraft, int unlokedCraftSlotCount, int maxCraftSlotCount, map<ResourceName, vector<Craft>> craftInfo)
{
	Collision::CreateTextureAndBitmask(texture, fileName);
	this->type = type;
	this->canRebuildPlus = canRebuildPlus;
	this->canRebuildDiagonal = canRebuildDiagonal;

	this->canBuild = canBuild;
	this->canMining = canMining;
	this->canIncome = canIncome;

	this->build = buildInfo;
	this->mining = miningInfo;
	this->income = incomeInfo;

	this->canCraft = canCraft;
	
	this->unlokedCraftSlotCount = unlokedCraftSlotCount;
	this->maxCraftSlotCount = maxCraftSlotCount;
	this->craft = craftInfo;
	
	init();

}

void TileInfo::init() {
	craft[R_NONE].push_back({ R_NONE, 0, 0, { {R_NONE,0} } });
}

// DT_UiInfo ---------------------------------------------------------------------------------------------------

DT_UiInfo::DT_UiInfo() {
	addElemet(U_YELLOWCLOUD, "Sprite/UI/S_Cloud_01.png");
	addElemet(U_LOKED, "Sprite/UI/S_Loked.png");
	addElemet(U_UNLOKED, "Sprite/UI/S_Unloked.png");
	addElemet(U_UPGRADE, "Sprite/UI/S_Upgrade.png");
	addElemet(U_DESTROY, "Sprite/UI/S_Destroy.png");
}
void DT_UiInfo::addElemet(UiName name, string fileName) {
	UiInfo info(fileName);
	this->info[name] = info;
}

// DT_ResourceInfo ---------------------------------------------------------------------------------------------------

DT_ResourceInfo::DT_ResourceInfo() {
	addElemet(R_WOOD, "Sprite/Resource/Ic_Wood.png");
	addElemet(R_ROCK, "Sprite/Resource/Ic_Rock.png");
	addElemet(R_CRYSTAL, "Sprite/Resource/Ic_Crystal.png");
	addElemet(R_GOLD, "Sprite/Resource/Ic_Gold.png");
}
void DT_ResourceInfo::addElemet(ResourceName name, string fileName) {
	ResourceInfo info(fileName);
	this->info[name] = info;
}

// DT_ButtonInfo ---------------------------------------------------------------------------------------------------

DT_ButtonInfo::DT_ButtonInfo() {
	addElemet(T_GRASS, "Sprite/UI/S_BluePanel.png");
	addElemet(T_WATER, "Sprite/UI/S_BluePanel.png");
	addElemet(T_ROAD, "Sprite/UI/S_BluePanel.png");
	addElemet(T_TREE, "Sprite/UI/S_GreenPanel.png");
	addElemet(T_ROCK, "Sprite/UI/S_GreenPanel.png");
	addElemet(T_CRYSTAL, "Sprite/UI/S_GreenPanel.png");
	addElemet(T_STORE, "Sprite/UI/S_OrangePanel.png");
	addElemet(T_MINE, "Sprite/UI/S_OrangePanel.png");
	addElemet(T_FORESTERHOUSE, "Sprite/UI/S_OrangePanel.png");
	addElemet(T_QUARRY, "Sprite/UI/S_OrangePanel.png");
}
void DT_ButtonInfo::addElemet(TileName name, string fileName) {
	ButtonInfo info(fileName);
	this->info[name] = info;
}

// DT_TileInfo ---------------------------------------------------------------------------------------------------

DT_TileInfo::DT_TileInfo() {

	addElement(T_GRASS, TY_TILE, "Sprite/Tiles/S_Grass_01.png", false, false, true, {}, false, {}, false, {}, false, 0, 0, {});
	addElement(T_WATER, TY_TILE, "Sprite/Tiles/S_Water_00.png", true, true, false, {}, false, { {R_GOLD,{-1,-1}} }, false, {}, false,0, 0, {});
	addElement(T_ROAD, TY_TILE, "Sprite/Tiles/S_Road_00.png", true, false, false, { {R_GOLD,10} }, false, {}, false, {}, false, 0, 0, {});
	addElement(T_TREE, TY_RESOURCE, "Sprite/Objects/S_Tree_01.png", false, false, false, {}, true, { {R_WOOD,{100,500}} }, false, {}, false, 0, 0, {});
	addElement(T_ROCK, TY_RESOURCE, "Sprite/Objects/S_Rock_01.png", false, false, false, {}, true, { {R_ROCK,{250,1000}} }, false, {}, false, 0, 0, {});
	addElement(T_CRYSTAL, TY_RESOURCE, "Sprite/Objects/S_Crystal_01.png", false, false, false, {}, true, { {R_CRYSTAL,{1000,10000}} }, false, {}, false, 0, 0, {});
	addElement(T_MINE, TY_BUILDING, "Sprite/Buildings/S_Mine_01.png", false, false, false, { {R_GOLD,100}, {R_WOOD,5}, {R_ROCK,25} }, false, {}, true, { {R_CRYSTAL, {T_CRYSTAL,1,5} } }, false, 0, 0, {});
	addElement(T_FORESTERHOUSE, TY_BUILDING, "Sprite/Buildings/S_ForesterHouse_01.png", false, false, false, { {R_GOLD,100}, {R_ROCK,50} }, false, {}, true, { {R_WOOD, {T_TREE,5,1} } }, false, 0, 0, {});
	addElement(T_QUARRY, TY_BUILDING, "Sprite/Buildings/S_Quarry_01.png", false, false, false, { {R_GOLD,100}, {R_WOOD,50} }, false, {}, true, { {R_ROCK, {T_ROCK,3,3} } }, false, 0, 0, {});
	addElement(T_STORE, TY_RESOURCE, "Sprite/Buildings/S_Store_01.png", false, false, false, { {R_WOOD,15}, {R_ROCK,25}, {R_CRYSTAL,5} }, false, {}, true, {}, true, 1,3, { {R_GOLD,{{R_GOLD,1,5,{{R_WOOD,10}}},{R_GOLD,1,3,{{R_ROCK,10}}},{R_GOLD,5,20,{{R_CRYSTAL,1}}}}} });
}
void DT_TileInfo::addElement(TileName name, TileType type, string fileName, bool canRebuildPlus, bool canRebuildDiagonal, bool canBuild, map<ResourceName, int> buildInfo, bool canMining, map<ResourceName, Struct2i> miningInfo, bool canIncome, map<ResourceName, Income> incomeInfo, bool canCraft, int unlokedCraftSlotCount, int maxCraftSlotCount, map<ResourceName, vector<Craft>> craftInfo)
{
	TileInfo info(fileName, type, canRebuildPlus, canRebuildDiagonal, canBuild, buildInfo, canMining, miningInfo, canIncome, incomeInfo, canCraft, unlokedCraftSlotCount, maxCraftSlotCount, craftInfo);
	this->info[name] = info;
}



// DT_RebuildInfo ---------------------------------------------------------------------------------------------------

DT_RebuildInfo::DT_RebuildInfo() {
	addElement(T_ROAD, 0, "Sprite/Tiles/S_Road_00.png");
	addElement(T_ROAD, 1, "Sprite/Tiles/S_Road_01.png");
	addElement(T_ROAD, 10, "Sprite/Tiles/S_Road_02.png");
	addElement(T_ROAD, 100, "Sprite/Tiles/S_Road_03.png");
	addElement(T_ROAD, 1000, "Sprite/Tiles/S_Road_04.png");
	addElement(T_ROAD, 101, "Sprite/Tiles/S_Road_05.png");
	addElement(T_ROAD, 1010, "Sprite/Tiles/S_Road_06.png");
	addElement(T_ROAD, 110, "Sprite/Tiles/S_Road_07.png");
	addElement(T_ROAD, 1100, "Sprite/Tiles/S_Road_08.png");
	addElement(T_ROAD, 1001, "Sprite/Tiles/S_Road_09.png");
	addElement(T_ROAD, 11, "Sprite/Tiles/S_Road_10.png");
	addElement(T_ROAD, 1011, "Sprite/Tiles/S_Road_11.png");
	addElement(T_ROAD, 111, "Sprite/Tiles/S_Road_12.png");
	addElement(T_ROAD, 1110, "Sprite/Tiles/S_Road_13.png");
	addElement(T_ROAD, 1101, "Sprite/Tiles/S_Road_14.png");
	addElement(T_ROAD, 1111, "Sprite/Tiles/S_Road_15.png");

	addElements(T_WATER, diagonalPosition, 0, "Sprite/Tiles/S_Water_00.png");
	addElements(T_WATER, diagonalPosition, 1, "Sprite/Tiles/S_Water_01.png");
	addElements(T_WATER, diagonalPosition, 10, "Sprite/Tiles/S_Water_02.png");
	addElements(T_WATER, diagonalPosition, 100, "Sprite/Tiles/S_Water_03.png");
	addElements(T_WATER, diagonalPosition, 1000, "Sprite/Tiles/S_Water_04.png");
	addElements(T_WATER, diagonalPosition, 101, "Sprite/Tiles/S_Water_05.png");
	addElements(T_WATER, diagonalPosition, 1010, "Sprite/Tiles/S_Water_06.png");

	addElements(T_WATER, v7, 110, "Sprite/Tiles/S_Water_07.png");
	addElements(T_WATER, v8, 1100, "Sprite/Tiles/S_Water_08.png");
	addElements(T_WATER, v9, 1001, "Sprite/Tiles/S_Water_09.png");
	addElements(T_WATER, v10, 11, "Sprite/Tiles/S_Water_10.png");
	addElements(T_WATER, v11, 1011, "Sprite/Tiles/S_Water_11.png");
	addElements(T_WATER, v12, 111, "Sprite/Tiles/S_Water_12.png");
	addElements(T_WATER, v13, 1110, "Sprite/Tiles/S_Water_13.png");
	addElements(T_WATER, v14, 1101, "Sprite/Tiles/S_Water_14.png");
	addElements(T_WATER, v16, 110, "Sprite/Tiles/S_Water_16.png");
	addElements(T_WATER, v17, 1100, "Sprite/Tiles/S_Water_17.png");
	addElements(T_WATER, v18, 1001, "Sprite/Tiles/S_Water_18.png");
	addElements(T_WATER, v19, 11, "Sprite/Tiles/S_Water_19.png");
	addElements(T_WATER, v20, 1011, "Sprite/Tiles/S_Water_20.png");
	addElements(T_WATER, v21, 1011, "Sprite/Tiles/S_Water_21.png");
	addElements(T_WATER, v22, 1011, "Sprite/Tiles/S_Water_22.png");
	addElements(T_WATER, v23, 111, "Sprite/Tiles/S_Water_23.png");
	addElements(T_WATER, v24, 111, "Sprite/Tiles/S_Water_24.png");
	addElements(T_WATER, v25, 111, "Sprite/Tiles/S_Water_25.png");
	addElements(T_WATER, v26, 1110, "Sprite/Tiles/S_Water_26.png");
	addElements(T_WATER, v27, 1110, "Sprite/Tiles/S_Water_27.png");
	addElements(T_WATER, v28, 1110, "Sprite/Tiles/S_Water_28.png");
	addElements(T_WATER, v29, 1101, "Sprite/Tiles/S_Water_29.png");
	addElements(T_WATER, v30, 1101, "Sprite/Tiles/S_Water_30.png");
	addElements(T_WATER, v31, 1101, "Sprite/Tiles/S_Water_31.png");

	addElement(T_WATER, 1111, "Sprite/Tiles/S_Water_15.png");
	addElement(T_WATER, 1001111, "Sprite/Tiles/S_Water_32.png");
	addElement(T_WATER, 101111, "Sprite/Tiles/S_Water_33.png");
	addElement(T_WATER, 10001111, "Sprite/Tiles/S_Water_34.png");
	addElement(T_WATER, 11111, "Sprite/Tiles/S_Water_35.png");
	addElement(T_WATER, 11001111, "Sprite/Tiles/S_Water_36.png");
	addElement(T_WATER, 1101111, "Sprite/Tiles/S_Water_37.png");
	addElement(T_WATER, 111111, "Sprite/Tiles/S_Water_38.png");
	addElement(T_WATER, 10101111, "Sprite/Tiles/S_Water_39.png");
	addElement(T_WATER, 1011111, "Sprite/Tiles/S_Water_40.png");
	addElement(T_WATER, 10011111, "Sprite/Tiles/S_Water_41.png");
	addElement(T_WATER, 11101111, "Sprite/Tiles/S_Water_42.png");
	addElement(T_WATER, 1111111, "Sprite/Tiles/S_Water_43.png");
	addElement(T_WATER, 10111111, "Sprite/Tiles/S_Water_44.png");
	addElement(T_WATER, 11011111, "Sprite/Tiles/S_Water_45.png");
	addElement(T_WATER, 11111111, "Sprite/Tiles/S_Water_46.png");
	};
void DT_RebuildInfo::addElements(TileName name, vector<int> vi, int i, string fileName) {
	for (auto element : vi) {
		Collision::CreateTextureAndBitmask(rebuildTexture[name][element + i], fileName);
	}
}
void DT_RebuildInfo::addElement(TileName name, int i, string fileName) {
	Collision::CreateTextureAndBitmask(rebuildTexture[name][i], fileName);
}