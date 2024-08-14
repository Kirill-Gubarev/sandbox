#include "game/sbWindow.h"
#include "game/render.h"
#include "game/input.h"
#include "area/area.h"

//data
int sb::Area::width = 0;
int sb::Area::height = 0;
sb::Tile* sb::Area::ptr_tileArray = nullptr;

//managing this class
void sb::Area::init(int width, int height) {
	Area::width = width;
	Area::height = height;

	//memory allocation
	int size = width * height;
	ptr_tileArray = new Tile[size];

	//filling an array with empty values
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
 			ptr_tileArray[x + y * width] = Tile(Tile::Type::empty, x, y);

	//creating a stone platform
	for (int y = height / 2; y < height / 2 + 3; ++y)
		for (int x = width / 2 - 10; x < width / 2 + 10; ++x)
			setTile(x, y, Tile(Tile::Type::stone, x, y));
}
void sb::Area::terminate() {
	delete[] ptr_tileArray;
}
void sb::Area::update() {
	//updating tiles
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			tileUpdate(getTile(x,y));

	//resetting status update
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
			getTile(x, y).hasBeenUpdated = false;
}

//getters
int sb::Area::getWidth(){
	return width;
}
int sb::Area::getHeight(){
	return height;
}
sb::Tile& sb::Area::getTile(int x, int y) {
	//exception
	if (!isInsideTheArea(x, y)) {
		std::string message = "CLASS AREA: going beyond the area";
		message += " x: " + std::to_string(x);
		message += " y: " + std::to_string(y);
		throw std::exception(message.c_str());
	}

	return ptr_tileArray[x + y * width];
}

//tiles management
void sb::Area::setTile(int x, int y, sb::Tile newTile) {
	Tile& l_currentTile = getTile(x, y);
	l_currentTile = newTile;
}
void sb::Area::swapTile(int x1, int y1, int x2, int y2) {
	sb::Tile& l_tile1 = getTile(x1, y1);
	sb::Tile& l_tile2 = getTile(x2, y2);

	//swapping
	sb::Tile temp = l_tile1;
	l_tile1.copyWithoutPos(l_tile2);
	l_tile2.copyWithoutPos(temp);

	resetTilesSleepNearby(x2, y2);
}
void sb::Area::resetTilesSleepNearby(int x, int y) {
	//more than 1 current position
	int limitX = x + 1;
	int limitY = y + 1;

	//if go beyond the border, reduce the coordinate
	if (limitX >= width)limitX--;
	//if do not go beyond the border, then can reduce the coordinate
	else if (x > 0) x--;

	//if go beyond the border, reduce the coordinate
	if (limitY >= height)limitY--;
	//if we do not go beyond the border, then we can reduce the coordinate
	else if (y > 0) y--;

	//reset sleep mode
	for (; y < limitY; y++)
		for (; x < limitX; x++)
			getTile(x, y).sleep = false;
}

//mouse press
void sb::Area::setTileMouseLB() {
	uts::Vec2<double> mousePos = sb::Input::getMousePosition();
	uts::Vec2<int> areaPos = convertMousePosToAreaPos(mousePos);

	//creating sand
	if (isInsideTheArea(areaPos)) {
		setTile(areaPos.X, areaPos.Y, Tile(Tile::Type::sand, areaPos.X, areaPos.Y));
		resetTilesSleepNearby(areaPos.X, areaPos.Y);
	}
}
void sb::Area::setTileMouseRB() {
	uts::Vec2<double> mousePos = sb::Input::getMousePosition();
	uts::Vec2<int> areaPos = convertMousePosToAreaPos(mousePos);

	//creating water
	if (isInsideTheArea(areaPos)) {
		setTile(areaPos.X, areaPos.Y, Tile(Tile::Type::water, areaPos.X, areaPos.Y));
		resetTilesSleepNearby(areaPos.X, areaPos.Y);
	}
}

//coordinate management
uts::Vec2<int> sb::Area::convertMousePosToAreaPos(uts::Vec2<double> pos) {
	//type conversion for accurate calculations
	uts::Vec2<double> areaBottomLeft = static_cast<uts::Vec2<double>>(sb::Render::getAreaBottomLeft());
	uts::Vec2<double> areaTopRight = static_cast<uts::Vec2<double>>(sb::Render::getAreaTopRight());

	//shift pos.x
	pos.X = pos.X - sb::Render::getAreaBottomLeft().X;
	//pos.x / (width rendering area / width area)
	pos.X = pos.X / ((areaTopRight.X - areaBottomLeft.X) / static_cast<double>(width));

	//inversion pos.y
	pos.Y = sb::SBWindow::getHeight() - pos.Y;
	//shift pos.y
	pos.Y = pos.Y - sb::Render::getAreaBottomLeft().Y;
	//pos.x / (height rendering area / height area)
	pos.Y = pos.Y / ((areaTopRight.Y - areaBottomLeft.Y) / static_cast<double>(height));

	//type conversion for this class, it works with integers
	return static_cast<uts::Vec2<int>>(pos);
}
bool sb::Area::isInsideTheArea(uts::Vec2<int> pos) {
	return 
		pos.X >= 0 && 
		pos.X < width && 
		pos.Y >= 0 && 
		pos.Y < height;
}
bool sb::Area::isInsideTheArea(int x, int y) {
	return 
		x >= 0 && 
		x < width && 
		y >= 0 && 
		y < height;
}