#include "Tile.h"

	Tile::Tile() {
		index = -1;
	}

	Tile::Tile(int i, int x, int y, Color c) {

		name = T_STORE;
		index = i;
		position = { x,y };
		pnValue = c;
		setTransform();
		
	};
	
	void Tile::updateSpawnAnimation(float elapcedTime) {
		if (!isSpawn) {
			spawnCurrentTime -= clampFloat(0, spawnCurrentTime, elapcedTime);
			float t = convertTimeToLerpT(spawnCurrentTime,spawnTime);
			float currentPositionY = lerp(spawnStartPositionY,spawnEndPositionY, getLerpQuadraticEaseOut(t));
			sprite.setPosition(sprite.getPosition().x, currentPositionY);
			if (spawnCurrentTime <= 0) {
				isSpawn = true;
			}
		}
	}

	void Tile::setTileBasedPn() {
		if (pnValue.r == 0) {
			TileName n = T_WATER;
			changeTile(n);
		}
		else {
			TileName n = TileName(getRandomIntValue({ T_TREE, T_ROCK, T_CRYSTAL }));
			//TileName n = T_GRASS;
			changeTile(n);

		}
	}

	void Tile::changeTile(TileName name) {
		if (this->name != name) {
			this->name = name;
			Texture& t = *getTexture();
			init();
			setOffsetPosition(t);
		}
	}

	void Tile::buildTile(TileName name) {
		bool canBuild = true;//tileInfo.info[this->name].canBuild;
		if (this->name != name && enoughResourcesForBuild(name) && canBuild) {
			this->name = name;
			Texture& t = *getTexture();
			init();
			setOffsetPosition(t);
			grid.setRebuildForNeighbours(index);
			player.subtractResources(tileInfo.info[name].build);
			grid.updateTilesEarningsM();
			player.updateEarningsM();
		}
	}

	void Tile::upgrade() {
		if (tileInfo.info[name].canIncome) {
			for (auto element : incomeInfo) {
				incomeInfo[element.first].addValue(5);
			}
		}
		unlokedCraftSlotCount += clampInt(0,maxCraftSlotCount,unlokedCraftSlotCount);
	}

	void Tile::mining() {
		bool canMining = tileInfo.info[name].canMining;
		map<ResourceName, Struct2i> info = tileInfo.info[name].mining;
		if (canMining && !info.empty()) {
			for (auto& element : info)
			{
				mineTile(element.first, 5);		// количество ресурсов должно быть == PlayerMiningSTR
			}
		}
	}

	void Tile::income(float elapcedTime) {
		bool canIncome = tileInfo.info[name].canIncome;
		if (canIncome && !incomeInfo.empty()) {
			for (auto& element : incomeInfo)
			{
				currentIncomeTime[element.first] += elapcedTime;
				if (currentIncomeTime[element.first] >= incomeInfo[element.first].time) {
					currentIncomeTime[element.first] = 0;
					grid.mineIncomeTiles(index,incomeInfo[element.first].incomeTile, element.first, incomeInfo[element.first].value);
				}
			}
		}
	}

	void Tile::craft(float elapcedTime) {
		bool canCraft = tileInfo.info[name].canCraft;
		if (canCraft && !currentCraft.empty()) {
			for (int i = 0; i < unlokedCraftSlotCount; i++) {
				if (enoughResourcesForCraft(i) && currentCraft[i].name != R_NONE ) {
					currentCraftTime[i] += elapcedTime;
					if (currentCraftTime[i] >= currentCraft[i].time) {
						currentCraftTime[i] = 0;

						player.addResource(currentCraft[i].name, currentCraft[i].value);

						for (auto element : currentCraft[i].info) {
							player.subtractResource(element.first, element.second);
						}
					}
				}
			}
		}
	}
	
	void Tile::d_ResourceValue() {
		if (!currentResourcesValue.empty()) {
			for (auto element : currentResourcesValue) {
				cout << element.second << endl;
			}
		}
	}

	void Tile::d_TilePosition() {
		cout << position.x << " + " << position.y << endl;
	}

	void Tile::select() {
		sprite.setColor(Color::Red);
		//d_ResourceValue();
		//d_TilePosition();

	}

	void Tile::unSelect() {
		sprite.setColor(Color::White);
	}

	bool Tile::getIsSpawn() {
		return(isSpawn);
	}

	int Tile::getIndex() {
		return(index);
	}

	Struct2i Tile::getPosition() {
		return(position);
	}

	void Tile::setRebuild() {
		Texture& t = *getTexture();
		setOffsetPosition(t);
	}

	TileName Tile::getName() {
		return(name);
	}

	void Tile::mineTile(ResourceName name, int value) {
		cout << currentResourcesValue[name] << endl;
		if (currentResourcesValue[name] == -1) {
			player.addResource(name, value);
		}
		else {
			int v = clampInt(0, currentResourcesValue[name], value);
			subtractMiningValue(name, v);
			player.addResource(name, v);
		}
	}

	map<ResourceName, int> Tile::getEarningsM() {
		return(earningsM);
	}


	void Tile::init() {
		currentIncomeTime.clear();
		currentResourcesValue.clear();
		incomeInfo.clear();
		earningsM.clear();
		craftInfo.clear();
		currentCraft.clear();
		grid.removeBuildingTile(index);

		craftInfo = tileInfo.info[name].craft;
		unlokedCraftSlotCount = tileInfo.info[name].unlokedCraftSlotCount;
		maxCraftSlotCount = tileInfo.info[name].maxCraftSlotCount;
		if (maxCraftSlotCount > 0) {
			for (int i = 0; i < maxCraftSlotCount; i++) {
				currentCraftTime[i] = 0;
				currentCraft[i] = craftInfo[R_NONE][0];
			}
		}

		if (craftInfo.find(R_GOLD) != craftInfo.end()) {
			//placeCraftInSlot(0, craftInfo[R_GOLD][0]);
		}

		incomeInfo = tileInfo.info[name].income;
		if (!incomeInfo.empty()) {
			for (auto element : incomeInfo) {
				currentIncomeTime[element.first] = 0;
			}
		}
		map<ResourceName, Struct2i> miningInfo = tileInfo.info[name].mining;
		if (!miningInfo.empty())
		{
			for (auto element : miningInfo) {
				currentResourcesValue[element.first] = getRandomIntRange(element.second.x, element.second.y);
			}
		}



		if (tileInfo.info[name].canIncome || tileInfo.info[name].canCraft) {
			grid.addBuildingTile(index);
			cout <<  index  << endl;
		}

	}

	void Tile::setTransform() {

		Texture& t = tileInfo.info[name].texture;

		sizeX = t.getSize().x;
		sizeY = t.getSize().y;
		int originX = sizeX / 2 - 4;
		int originY = sizeY - sizeY + 32;

		sprite.setTexture(t);
		sprite.setOrigin(originX, originY);

		int positionX = windowSize.x / 2 + originX * position.x - originX * position.y + originX;
		int positionY = windowSize.y / 8 + originY * position.x + originY * position.y + originY;

		sprite.setPosition(positionX, positionY);

	}

	void Tile::initSpawn(){
		spawnGravityStrengh = 100;
		spawnStartPositionY = sprite.getPosition().y;
		spawnEndPositionY = spawnStartPositionY + spawnGravityStrengh;
		spawnTime = 0.50;
		spawnCurrentTime = spawnTime;
	}

	void Tile::setOffsetPosition(Texture& texture) {
		Texture& t = texture;

		int offsetX = t.getSize().x - sizeX;
		int offsetY = t.getSize().y - sizeY;

		sizeX = t.getSize().x;
		sizeY = t.getSize().y;
		int originX = sizeX / 2 - 2;
		int originY = 32;

		sprite.setTexture(t);
		sprite.setOrigin(originX, originY);

		sprite.setPosition(sprite.getPosition().x - offsetX, sprite.getPosition().y - offsetY);
	}

	void Tile::subtractMiningValue(ResourceName name, int value) {
		currentResourcesValue[name] -= value;
		if (currentResourcesValue[name] <= 0) {
			changeTile(T_GRASS); 
			grid.updateTilesEarningsM();
			player.updateEarningsM();
		}
	}

	void Tile::updateEarningsM() {
		bool canIncome = tileInfo.info[name].canIncome;
		bool canCraft = tileInfo.info[name].canCraft;

		if (canIncome || canCraft) {
			earningsM.clear();
		}

		if (canIncome && !incomeInfo.empty()) {
			for (auto& element : incomeInfo)
			{
				earningsM[element.first] += 60 / element.second.time * getCountIncome(element.second.incomeTile) * element.second.value;
			}
		}

		if (canCraft) {
			for (auto& element : currentCraft)
			{
				if (element.second.name != R_NONE) {
					earningsM[element.second.name] += 60 / element.second.time * element.second.value;
					
					cout << element.second.name << "  =  " << 60 / element.second.time * element.second.value << endl;
					for (auto info : element.second.info) {
						earningsM[info.first] -= 60 / element.second.time * info.second;
					}
				}
			}
		}
	}

	int Tile::getCountIncome(TileName name) {
		int count = 0;
		for (auto element : grid.getPositionAll()) {
			int neighbourIndex = grid.getIndexTileOffsetByPosition(index, element.x, element.y);
			if (neighbourIndex != -1 && grid.getTileByIndex(neighbourIndex).getName() == name) {
				count += 1;
			}
		}
		return count;
	}

	Texture* Tile::getTexture() {
		if (!tileInfo.info[name].canRebuildPlus && !tileInfo.info[name].canRebuildDiagonal) {
			Texture& t = tileInfo.info[name].texture;
			return(&t);
		}

		int i = getRebuildIndex();

		Texture& t = rebuildInfo.rebuildTexture[name][i];
		return(&t);
	}

	int Tile::getRebuildIndex() {
		int i = 0;
		int value;
		int neighbourIndex;

		if (tileInfo.info[name].canRebuildPlus) {
			value = 1;
			for (auto element : grid.getPositionPlus()) {
				neighbourIndex = grid.getIndexTileOffsetByPosition(index, element.x, element.y);
				i += compareRebuildIndex(neighbourIndex, value, true);
				value *= 10;
			}
		}

		if (tileInfo.info[name].canRebuildDiagonal) {
			value = 10000;
			for (auto element : grid.getPositionDiagonal()) {
				neighbourIndex = grid.getIndexTileOffsetByPosition(index, element.x, element.y);
				i += compareRebuildIndex(neighbourIndex, value, false);
				value *= 10;
			}
		}

		return(i);
	}

	int Tile::compareRebuildIndex(int neighbourIndex, int value, bool isSelf) {

		if (neighbourIndex == -1) {
			return(0);
		}

		TileName neigbourName = grid.getTileByIndex(neighbourIndex).getName();

		if (isSelf) {
			if (name == neigbourName) {
				return(value);
			}
			else {
				return(0);
			}
		}

		if (!isSelf) {
			if (name != neigbourName) {
				return(value);
			}
			else {
				return(0);
			}
		}
	}

	bool Tile::enoughResourcesForBuild(TileName name) {
		map<ResourceName, int> buildCost = tileInfo.info[name].build;
		for (auto element : buildCost) {
			if (player.getResourceValue(element.first) < element.second) {
				return false ;
			}
		}
		return true;
	}

	bool Tile::enoughResourcesForCraft(int craftSlot) {
		for (auto element : currentCraft[craftSlot].info) {
			if (player.getResourceValue(element.first) < element.second) {
				return false;
			}
		}
		return true;
	}
	
	void Tile::placeCraftInSlot(int slot, Craft& craft) {
		currentCraftTime[slot] = 0;
		currentCraft[slot] = craft;
	}

	int Tile::getUnlokedCraftSlotCount() {
		return unlokedCraftSlotCount;
	}
	int Tile::getMaxCraftSlotCount() {
		return maxCraftSlotCount;
	}
	map<int, Craft> Tile::getCurrentCraft() {
		return currentCraft;
	}

	map<ResourceName, vector<Craft>>  Tile::getCraftInfo() {
		return craftInfo;
	}
