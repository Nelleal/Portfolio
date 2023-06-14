#include "Grid.h"

Grid::Grid() {

}

void Grid::spawnTile(int i, int x, int y, Color c) {
	tilePositions[{x, y}] = i;
	tiles.push_back(Tile(i,x,y,c));
	tiles[i].setTileBasedPn();
	setRebuildForNeighbours(i);
	tiles[i].initSpawn();
}

Tile& Grid::getTileByIndex(int index) {
	return(tiles[index]);
}

vector<Tile>& Grid::getGridTiles() {
	return(tiles);
}
vector<Struct2i> Grid::getPositionAll() {
	return neighbourPositionAll;
}
vector<Struct2i> Grid::getPositionPlus() {
	return neighbourPositionPlus;
}
vector<Struct2i> Grid::getPositionDiagonal() {
	return neighbourPositionDiagonal;
}

int Grid::getIndexTileOffsetByPosition(int index, int offsetX, int offsetY) {

	int x = tiles[index].getPosition().x + offsetX;
	int y = tiles[index].getPosition().y + offsetY;
	Struct2i s2i(x, y);
	auto it = tilePositions.find(s2i);

	if (it == tilePositions.end()) {
		return(-1);
	}
	else {
		return(tilePositions[s2i]);
	}  

}

void Grid::setRebuildForNeighbours(int index) {
	for (auto element : neighbourPositionAll) {
		int neighbourIndex = getIndexTileOffsetByPosition(index, element.x, element.y);
		if ( neighbourIndex != -1) {
			tiles[neighbourIndex].setRebuild();
		}
	}
}

void Grid::mineIncomeTiles(int index, TileName tName, ResourceName rName, int value) {
	for (auto element : neighbourPositionAll) {
		int neighbourIndex = getIndexTileOffsetByPosition(index, element.x, element.y);
		if (neighbourIndex != -1 && tiles[neighbourIndex].getName() == tName) {
			tiles[neighbourIndex].mineTile(rName, value);
		}
	}
}

void Grid::addBuildingTile(int index) {
	buildingTiles.push_back(index);
}

void Grid::removeBuildingTile(int index) {
	remove(buildingTiles.begin(),buildingTiles.end(),index);
}

vector<int> Grid::getIndexBuildingTiles() {
	return buildingTiles;
}

void Grid::updateTilesEarningsM() {
	for (auto index : buildingTiles) {
		tiles[index].updateEarningsM();
	}
}