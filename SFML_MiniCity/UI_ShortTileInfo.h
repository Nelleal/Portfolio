#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "Data.h"
#include "Grid.h"
#include "Math.h"

using namespace std;
using namespace sf;

// init ---------------------------------------------------------------------------------------------------

//extern class Tile;
extern class Grid;
extern Grid grid;
extern struct DT_UiInfo;
extern DT_UiInfo uiInfo;
extern struct DT_ResourceInfo;
extern DT_ResourceInfo resourseInfo;
extern struct Craft;
extern RenderWindow win;

// body ---------------------------------------------------------------------------------------------------

class UI_ShortTileInfo
{
public:

	UI_ShortTileInfo();
	void open(int tileIndex);
	void close();
	bool getIsOpen();
	void update();
	void setTransform(int pX, int pY, int unlokedSlotCount, int maxSlotCount, map<int, Craft> crafts);
	void targeting(Sprite& pointer);

private:
	bool isOpen = false;
	//Tile tile;
	int tileIndex;
	Sprite sDestroy;
	Sprite sUpgrade;
	vector <Sprite> sCraftSlots;

	void setSprite(Sprite& s,Texture& t,float scale);
};

