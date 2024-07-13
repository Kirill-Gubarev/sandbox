#include "area.h"
#include "../sbWindow.h"
sb::Area::~Area() {
	int size = width * height;
	for (size_t i = 0; i < size; ++i) {
		if (ptr_tileArray[i] != nullptr)
			delete ptr_tileArray[i];
	}
	delete[] ptr_tileArray;
}
int sb::Area::getWidth() {
	return width;
}
int sb::Area::getHeight() {
	return height;
}
sb::Tile*& sb::Area::getTile(int x, int y) {
	if (x < 0 || x >= width) throw std::exception("going beyond the width of the area");
	if (y < 0 || y >= height) throw std::exception("going beyond the height of the area");
	return ptr_tileArray[x + y * width];
}
void sb::Area::swap(int x1, int y1, int x2, int y2) {
	sb::Tile* temp = getTile(x1, y1);
	getTile(x1, y1) = getTile(x2, y2);
	getTile(x2, y2) = temp;
}
void sb::Area::update() {
	sb::SBWindow* sbWindow = sb::SBWindow::getInstance().get();
	//left mouse button pressed
	if (sbWindow->isLeftButtonPressed())
	{
		sb::Vec2d<float> pos = sbWindow->getMousePosition();
		sb::Vec2d<float> outputLeftBottom = static_cast<sb::Vec2d<float>>(sbWindow->getOutputLeftBottom());
		sb::Vec2d<float> outputRightTop = static_cast<sb::Vec2d<float>>(sbWindow->getOutputRightTop());

		pos.x = pos.x - sbWindow->getOutputLeftBottom().x;
		pos.x = pos.x / ((outputRightTop.x - outputLeftBottom.x) / static_cast<float>(width));
		pos.y = sbWindow->getHeight() - pos.y;
		pos.y = pos.y / ((outputRightTop.y - outputLeftBottom.y) / static_cast<float>(height));

		int x = static_cast<int>(pos.x);
		int y = static_cast<int>(pos.y);

		std::cout << x << " " << y << std::endl;



		if (x >= 0 && x < width &&y>=0&&y<height) {
			Tile*& tile = getTile(x, y);
			if (tile == nullptr)
				tile = new Sand();
		}

	}
	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			Tile*& tile = getTile(x, y);
			if (tile != nullptr && !tile->sleep)
				tile->update(x, y);
		}
	}
}
//singleton pattern
std::shared_ptr<sb::Area> sb::Area::ptr_instance(nullptr);
sb::Area::Area(int width, int height)
	:width(width), height(height) {
	int size = width * height;
	ptr_tileArray = new Tile * [size];
	for (size_t i = 0; i < size; ++i) {
		ptr_tileArray[i] = nullptr;
	}


	for (int y = height / 2; y < height / 2 + 3; ++y) {
		for (int x = width / 2 - 10; x < width / 2 + 10; ++x) {
			getTile(x, y) = new Stone();
		}
	}
}
std::shared_ptr<sb::Area> sb::Area::getInstance() {
	return ptr_instance;
}
std::shared_ptr<sb::Area> sb::Area::createInstance(int width, int height) {
	if (ptr_instance == nullptr) {
		ptr_instance.reset(new Area(width, height));
	}
	return ptr_instance;
}