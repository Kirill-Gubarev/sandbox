#include "area.h"
#include "sbWindow.h"
#include "input.h"


sb::Vec2d<int> sb::Area::convertMousePosToAreaPos(sb::Vec2d<double> pos) const {

	//type conversion for accurate calculations
	sb::Vec2d<double> areaBottomLeft = static_cast<sb::Vec2d<double>>(ptr_sbWindow->getAreaBottomLeft());
	sb::Vec2d<double> areaTopRight = static_cast<sb::Vec2d<double>>(ptr_sbWindow->getAreaTopRight());

	//shift pos.x
	pos.x = pos.x - ptr_sbWindow->getAreaBottomLeft().x;
	//pos.x / (width rendering area / width area)
	pos.x = pos.x / ((areaTopRight.x - areaBottomLeft.x) / static_cast<double>(width));

	//inversion pos.y
	pos.y = ptr_sbWindow->getHeight() - pos.y;
	//pos.x / (height rendering area / height area)
	pos.y = pos.y / ((areaTopRight.y - areaBottomLeft.y) / static_cast<double>(height));

	//type conversion for this class, it works with integers
	return static_cast<sb::Vec2d<int>>(pos);
}
void sb::Area::mouseSetTile() {
	sb::Vec2d<double> mousePos = sb::ptr_input->getMousePosition();
	sb::Vec2d<int> areaPos = convertMousePosToAreaPos(mousePos);

	if (isInsideTheArea(areaPos))
		setTile(areaPos.x, areaPos.y, Tile(Tile::Type::sand));
}
void sb::Area::update() {
	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
				getTile(x,y).update(x,y);
		}
	}
}
bool sb::Area::isInsideTheArea(sb::Vec2d<int> pos) const {
	return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}
bool sb::Area::isInsideTheArea(int x, int y) const {
	return x >= 0 && x < width && y >= 0 && y < height;
}


void sb::Area::swap(int x1, int y1, int x2, int y2) {
	sb::Tile temp = getTile(x1, y1);
	getTile(x1, y1) = getTile(x2, y2);
	getTile(x2, y2) = temp;
}
sb::Tile& sb::Area::getTile(int x, int y) const {
	if (!isInsideTheArea(x, y)) throw std::exception("CLASS AREA: going beyond the area");
	return ptr_tileArray[x + y * width];
}
void sb::Area::setTile(int x, int y, sb::Tile newTile) {
	Tile& currentTile = getTile(x, y);
	currentTile = newTile;
}


sb::Area::~Area() {
	delete[] ptr_tileArray;
}
int sb::Area::getWidth() const {
	return width;
}
int sb::Area::getHeight() const {
	return height;
}


//singleton pattern
sb::Area* sb::ptr_area = nullptr;
std::unique_ptr<sb::Area> sb::Area::ptr_instance(nullptr);
sb::Area::Area(int width, int height)
	:width(width), height(height) {

	int size = width * height;
	ptr_tileArray = new Tile[size];

	for (int y = height / 2; y < height / 2 + 3; ++y) {
		for (int x = width / 2 - 10; x < width / 2 + 10; ++x) {
			setTile(x, y, Tile(Tile::Type::stone) );
		}
	}
}
sb::Area* sb::Area::getInstance() {
	return ptr_instance.get();
}
sb::Area* sb::Area::createInstance(int width, int height) {
	if (ptr_instance == nullptr) {
		ptr_instance.reset(new Area(width, height));
		ptr_area = ptr_instance.get();
	}
	return ptr_instance.get();
}