#include "UI_ShortTileInfo.h"


UI_ShortTileInfo::UI_ShortTileInfo() {
	setSprite(sDestroy, uiInfo.info[U_DESTROY].texture,0.75);
	setSprite(sUpgrade, uiInfo.info[U_UPGRADE].texture,0.75);
}

void UI_ShortTileInfo::open(int tileIndex) {
	this->tileIndex = tileIndex;
	isOpen = true;
	Tile& tile = grid.getTileByIndex(tileIndex);
	setTransform(tile.sprite.getPosition().x, tile.sprite.getPosition().y, tile.getUnlokedCraftSlotCount(), tile.getMaxCraftSlotCount(), tile.getCurrentCraft());
}

void UI_ShortTileInfo::close() {
	isOpen = false;
}

bool UI_ShortTileInfo::getIsOpen() {
	return isOpen;
}

void UI_ShortTileInfo::update() {
	if (isOpen) {
		win.draw(sDestroy);
		win.draw(sUpgrade);
		if (!sCraftSlots.empty()) {
			for (auto element : sCraftSlots) {
				win.draw(element);
			}
		}
	}
}

void UI_ShortTileInfo::setTransform(int pX, int pY, int unlokedSlotCount, int maxSlotCount, map<int,Craft> crafts) {

	sCraftSlots.clear();
	int paddingX = 10;
	int offsetY = 115;
	int startX = sUpgrade.getOrigin().x / 2;
	int offsetX = sUpgrade.getOrigin().x + paddingX;
	
	sUpgrade.setPosition(pX - startX - offsetX, pY - offsetY);
	sDestroy.setPosition(pX - startX + offsetX, pY - offsetY);

	if (maxSlotCount > 0) {
		sCraftSlots.resize(maxSlotCount);
		for (int i = 0; i < maxSlotCount; i++)
		{
			if (i < unlokedSlotCount) {
				if (crafts[i].name != R_NONE) {
					setSprite(sCraftSlots[i], resourseInfo.info[crafts[i].name].texture, 0.75);
				}
				else {
					setSprite(sCraftSlots[i], uiInfo.info[U_UNLOKED].texture, 0.75);
				}
			}
			else {
				setSprite(sCraftSlots[i], uiInfo.info[U_LOKED].texture, 0.75);
				sCraftSlots[i].setColor(Color::Color(100,100,100));
			}
			startX = getOffsetSprites(maxSlotCount,sCraftSlots[i].getGlobalBounds().width,paddingX);
			offsetX = (sCraftSlots[i].getGlobalBounds().width + paddingX) * i;
			sCraftSlots[i].setPosition(pX - startX + offsetX, pY + offsetY);
		}
	}
}


void UI_ShortTileInfo::setSprite(Sprite& s, Texture& t, float scale) {
	s.setTexture(t);
	s.setScale(scale,scale);
	s.setOrigin(s.getGlobalBounds().width/2, s.getGlobalBounds().height/2);
}

void UI_ShortTileInfo::targeting(Sprite& pointer) {
	if (!isOpen) { return; }

	Tile& tile = grid.getTileByIndex(tileIndex);

	if (Collision::PixelPerfectTest(sUpgrade, pointer))
	{
		tile.upgrade();
		setTransform(tile.sprite.getPosition().x, tile.sprite.getPosition().y, tile.getUnlokedCraftSlotCount(), tile.getMaxCraftSlotCount(), tile.getCurrentCraft());
		grid.updateTilesEarningsM();
		player.updateEarningsM();
		return;
	}

	if (Collision::PixelPerfectTest(sDestroy, pointer))
	{
		tile.changeTile(T_GRASS);
		close();
		grid.updateTilesEarningsM();
		player.updateEarningsM();
		return;
	}

	if (!sCraftSlots.empty()) {
		for (int i = 0; i < sCraftSlots.size(); i++)
		{
			if (Collision::PixelPerfectTest(sCraftSlots[i], pointer))
			{
				if (i < tile.getUnlokedCraftSlotCount()) {
					if (tile.getCurrentCraft()[i].name != R_NONE) {
						tile.placeCraftInSlot(i, tile.getCraftInfo()[R_NONE][0]); // доработать, чтобы можно было выбриать рецепты из списка рецептов
						setTransform(tile.sprite.getPosition().x, tile.sprite.getPosition().y, tile.getUnlokedCraftSlotCount(), tile.getMaxCraftSlotCount(), tile.getCurrentCraft());
						grid.updateTilesEarningsM();
						player.updateEarningsM();
						return;
					}
					else {
						tile.placeCraftInSlot(i, tile.getCraftInfo()[R_GOLD][0]); // доработать, чтобы можно было выбриать рецепты из списка рецептов
						setTransform(tile.sprite.getPosition().x, tile.sprite.getPosition().y, tile.getUnlokedCraftSlotCount(), tile.getMaxCraftSlotCount(), tile.getCurrentCraft());
						grid.updateTilesEarningsM();
						player.updateEarningsM();
						return;
					}
				}
			}
		}
	}
}