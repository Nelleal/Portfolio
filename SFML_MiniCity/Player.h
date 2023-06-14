#pragma once
#include <iostream>
#include <map>
#include "Data.h"
#include "Math.h"
#include "Grid.h"

using namespace std;
using namespace sf;
// Init ---------------------------------------------------------------------------------------------------

extern class Grid;
extern Grid grid;
extern DT_ResourceInfo resourseInfo;

// body ---------------------------------------------------------------------------------------------------

class Player {
public:
	Player();
	void addResource(ResourceName name, int value);
	void addAllResources(int value);
	void subtractResource(ResourceName name, int value);
	void subtractResources(map<ResourceName, int> resourceValue);
	int getResourceValue(ResourceName name);
	int getEarningsMValue(ResourceName name);
	int getMiningStrenghValue(ResourceName name);
	void updateEarningsM();
private:
	map<ResourceName, int> resources;
	map<ResourceName, int> earningsM;
	map<ResourceName, int> miningStrengh;
};