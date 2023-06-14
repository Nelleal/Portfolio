#include "Player.h"

Player::Player() {
	for (auto element : resourseInfo.info) {
		resources[element.first] = 0;
	}
	for (auto element : miningStrengh) {
		miningStrengh[element.first] = getRandomIntRange(1, 10);
	}
}

void Player::addResource(ResourceName name, int value) {
	resources[name] += value;
}

void Player::addAllResources(int value) {
	for (auto element : resources) {
		addResource(element.first, value);
	}
}

void Player::subtractResource(ResourceName name, int value) {
	resources[name] -= value;
}

void Player::subtractResources(map<ResourceName, int> resourceValue) {
	for (auto element : resourceValue) {
		subtractResource(element.first, element.second);
	}
}

int Player::getResourceValue(ResourceName name) {
	return (resources[name]);
}

int Player::getEarningsMValue(ResourceName name) {
	return (earningsM[name]);
}

int Player::getMiningStrenghValue(ResourceName name) {
	return (miningStrengh[name]);
}

void Player::updateEarningsM() {
	earningsM.clear();
	for (auto& element : grid.getGridTiles()) {
		for (auto info : element.getEarningsM()) {
			earningsM[info.first] += info.second;
		}
	}
	cout << " player " << endl;
}

