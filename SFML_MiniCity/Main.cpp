#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Collision.hpp"
#include "Grid.h"
#include "UI_ShortTileInfo.h"

using namespace std;
using namespace sf;

// init ---------------------------------------------------------------------------------------------------

class Resource;
class Button;

// global ---------------------------------------------------------------------------------------------------

Vector2i windowSize(1920, 1080);
RenderWindow win(VideoMode(windowSize.x, windowSize.y), "SFML_Window"/*,Style::None*/);
Clock globalClk;
float globalElapcedTime;
int gridSizeX = 8;
int gridSizeY = 8;
int gridSize = gridSizeX * gridSizeY;

Texture texturePointer;
Sprite pointer;

int targetedTile = -1;
int targetedButton = -1;
TileName selectedTile;
PlayerAction playerAction = A_NONE;

vector <Button> buttons;
vector <Resource> resources;

vector <Font> fonts;

DT_UiInfo uiInfo;
DT_ButtonInfo buttonInfo;
DT_TileInfo tileInfo;
DT_RebuildInfo rebuildInfo;
DT_ResourceInfo resourseInfo;

Player player;
Grid grid;
UI_ShortTileInfo shortTileInfo;

// class ---------------------------------------------------------------------------------------------------

class Resource {
public:

	Resource(ResourceName name) {
		this->name = name;
		statCount = 3;
		index = resources.size();
		setTransform();
		setText();
	}

	
	void update() {
		int value = player.getResourceValue(name);
		int earningsM = player.getEarningsMValue(name);
		int playerStrengh = player.getMiningStrenghValue(name);

		statsText[0].setString(to_string(value));
		statsText[1].setString(to_string(earningsM) + " / min");
		statsText[2].setString(to_string(playerStrengh));


		if (earningsM == 0) {
			statsText[1].setFillColor(Color::White);
		}
		else if (earningsM > 0) {
			statsText[1].setFillColor(Color::Green);
		}
		else {
			statsText[1].setFillColor(Color::Red);
		}



		for (int i = 0; i < statCount; i++)
		{
			statsText[i].setPosition(statsText[i].getPosition().x - statsText[i].getLocalBounds().width / 2, statsText[i].getPosition().y);
			win.draw(statsCloud[i]);
			win.draw(statsText[i]);
		}

		win.draw(sprite);
	}

private:
	ResourceName name;
	Sprite sprite;
	vector<Sprite> statsCloud;
	vector<Text> statsText;
	int index;
	int statCount;

	void setTransform() {
		Texture& t = resourseInfo.info[name].texture;
		Texture& cloud = uiInfo.info[U_YELLOWCLOUD].texture;
		Sprite s;
		s.setTexture(cloud);

		int	originX = t.getSize().x / 2;
		int originY = t.getSize().y / 2;
		int paddingX = 5;
		int paddingY = 5;
		int offsetX = t.getSize().x + paddingX;
		int offsetY = 0;
		int startPositionX = windowSize.x - originX - paddingX;
		int startPositionY = originY + paddingY;

		sprite.setTexture(t);
		sprite.setOrigin(originX, originY);
		sprite.setPosition(startPositionX - offsetX * index, startPositionY);

		for (int i = 0; i < statCount; i++)
		{
			originX = t.getSize().x / 2;
			originY = t.getSize().y / 2;
			paddingX = 0;
			paddingY = 3;
			offsetX = 0;
			offsetY = cloud.getSize().y + paddingY;
			startPositionX = sprite.getPosition().x;
			startPositionY = sprite.getPosition().y + t.getSize().y + paddingY;

			statsCloud.push_back(s);
			statsCloud[i].setOrigin(originX, originY);
			statsCloud[i].setPosition(startPositionX, startPositionY + offsetY * i);
		}
	}

	void setText() {
		statsText.resize(3);
		for (int i = 0; i < statCount; i++)
		{
			int positionX = statsCloud[i].getPosition().x;// -statsCloud[i].getOrigin().x;
			int positionY = statsCloud[i].getPosition().y - statsCloud[i].getOrigin().y;
			setTextValue(statsText[i], 16, positionX, positionY);
		}
	}

	void setTextValue(Text &text, int fontSize, int positionX, int positionY) {
		Font &font = fonts[0];

		text.setFont(font);
		text.setCharacterSize(fontSize);
		text.setStyle(Text::Bold);
		text.setFillColor(Color::White);
		text.setOutlineThickness(2);
		text.setOutlineColor(Color::Black);

		text.setPosition(positionX, positionY);
		
	}

};

class Button {

public:

	Sprite sprite;

	Button(TileName name) {
		this->name = name;
		index = buttons.size();
		setTransform();
	};

	int getButtonIndex() {
		return(index);
	}

	TileName getName() {
		return(name);
	}

	void select() {
		sprite.setColor(Color::Red);
	}

	void unSelect() {
		sprite.setColor(Color::White);
	}

private:
	int sizeX;
	int sizeY;
	int centreX;
	int centreY;
	int index;
	int offsetX;
	int offsetY;
	TileName name;

	void setTransform() {
		Texture& t = buttonInfo.info[name].texture;

		sizeX = t.getSize().x;
		sizeY = t.getSize().y;
		centreX = sizeX / 2;
		centreY = sizeY / 2;
		offsetX = 5;
		offsetY = 5;

		sprite.setTexture(t);
		sprite.setOrigin(centreX, centreY);

		sprite.setPosition((sizeX + offsetX) * index + centreX + offsetX, offsetY + centreY);
	}
};

// body ---------------------------------------------------------------------------------------------------

void createWorld() {

	cout << "createWorld" << endl;
	Font font;
	font.loadFromFile("Sprite/Fonts/arial.ttf");
	fonts.push_back(font);
	Image image;
	image.loadFromFile("Sprite/RenderTarget/RT_World_16x16_01.png");
	Color c;
	Clock clk;
	int i = 0;
	int x = 0;
	int y = 0;
	float time = 0.1;
	win.setFramerateLimit(60);
	globalClk.restart();


	// Pointer =

	texturePointer.loadFromFile("Sprite/Other/S_Pointer.png");
	pointer.setTexture(texturePointer);

	// buttons =

	buttons.push_back(Button(T_GRASS));
	buttons.push_back(Button(T_WATER));
	buttons.push_back(Button(T_ROAD));
	buttons.push_back(Button(T_TREE));
	buttons.push_back(Button(T_ROCK));
	buttons.push_back(Button(T_CRYSTAL));
	buttons.push_back(Button(T_STORE));
	buttons.push_back(Button(T_QUARRY));
	buttons.push_back(Button(T_FORESTERHOUSE));
	buttons.push_back(Button(T_MINE));

	// resources =

	resources.push_back(Resource(R_WOOD));
	resources.push_back(Resource(R_ROCK));
	resources.push_back(Resource(R_CRYSTAL));
	resources.push_back(Resource(R_GOLD));
	player.addAllResources(999);

	// tiles =

	while (win.isOpen()) {
		Event ev;	
		globalElapcedTime = globalClk.restart().asSeconds();
		while (win.pollEvent(ev)) {

			if (ev.type == Event::Closed) {
				win.close();
			}

		}

		// spawn =

		if (clk.getElapsedTime().asSeconds() >= time && i < gridSize) {

			if (x < image.getSize().x && y < image.getSize().y) {
				c = image.getPixel(x, y);
			}
			else {
				c = Color::White;
			}

			grid.spawnTile(i, x, y, c);
			i++;
			x++;

			if (x == gridSizeX) {
				x = 0;
				y++;
			}

			clk.restart();
			
		}

		// update =

		win.clear();

		for (int j = 0; j < i; j++) {
			grid.getTileByIndex(j).updateSpawnAnimation(globalElapcedTime);
			win.draw(grid.getTileByIndex(j).sprite);
		}

		win.display();

		// eixt =

		if (clk.getElapsedTime().asSeconds() >= time && i == gridSize) {

			if (i == gridSize && grid.getTileByIndex(i-1).getIsSpawn() == true) {

				cout << "continue" << endl;

				break;
			}
		}
	}

}

void draw() {

	win.clear();

	win.draw(pointer);

	for (auto& element : grid.getGridTiles()) {
		element.income(globalElapcedTime);
		element.craft(globalElapcedTime);
		win.draw(element.sprite);
	}

	for (auto element : buttons)
	{
		win.draw(element.sprite);
	}

	for (auto element : resources)
	{
		element.update();
	}

	shortTileInfo.update();

	win.display();

}

void update() {

	cout << "update" << endl;

	while (win.isOpen()) {
		Event ev; 
		globalElapcedTime = globalClk.restart().asSeconds();
		while (win.pollEvent(ev)) {

			if (ev.type == Event::Closed) {
				win.close();
			}
			
			// body -----------------------------------------------------------------------------------------------------------

			Vector2i mousePositionOnWindow = Mouse::getPosition(win);					// получаем координаты относительно экрана
			Vector2f mousePositionInGame = win.mapPixelToCoords(mousePositionOnWindow);	// конвертируем их в координаты относительно игры
			pointer.setPosition(mousePositionInGame.x, mousePositionInGame.y);

			//// check if the sprites have actually collided using pixel perfect collision detection
			if (targetedTile != -1) {
				grid.getTileByIndex(targetedTile).unSelect();
				targetedTile = -1;
			}
			if (targetedButton != -1) {
				buttons[targetedButton].unSelect();
				targetedButton = -1;
			}

			for (auto it = grid.getGridTiles().rbegin(); it != grid.getGridTiles().rend(); it++) {
				if (Collision::PixelPerfectTest((*it).sprite, pointer))
				{
					targetedTile = (*it).getIndex();
					(*it).select();
					break;
				}
			}

			for (auto element : buttons) {
				if (Collision::PixelPerfectTest(element.sprite, pointer))
				{
					targetedButton = element.getButtonIndex();
					element.select();
					break;
				}
			}

			if (Mouse::isButtonPressed(Mouse::Right)) {
				playerAction = A_NONE;
				shortTileInfo.close();
			}

			if (ev.type == Event::MouseButtonReleased)
				{

				for (vector<Tile>::reverse_iterator i = grid.getGridTiles().rbegin(); i != grid.getGridTiles().rend(); i++) {

					if (Collision::PixelPerfectTest((*i).sprite, pointer)) {

						switch (playerAction) {
						case A_NONE:
							//(*i).mining();
							shortTileInfo.open((*i).getIndex()); // проверка на тип постройки, можно ли открывать шорт»нфо
							break;
						case A_UPGRADE:
							(*i).upgrade();
							break;
						case A_BUILD:
							(*i).buildTile(selectedTile);
							break;
						}
						break;
					}
				}

				shortTileInfo.targeting(pointer);
				
				for (auto element : buttons) {
					if (Collision::PixelPerfectTest(element.sprite, pointer))
					{
						selectedTile = element.getName();
						playerAction = A_BUILD;
						break;
					}
				}
			}
		}
		draw();
	}
}


// main ---------------------------------------------------------------------------------------------------

int main() {

	srand(time(NULL));

	createWorld();
	
	update();

	return(0);

}
