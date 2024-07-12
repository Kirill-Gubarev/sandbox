#include "area.h"
#include "../sbWindow.h"
sb::Area::~Area() {
	std::uint32_t size = width * height;
	for (size_t i = 0; i < size; ++i) {
		if (ptr_tileArray[i] != nullptr)
			delete ptr_tileArray[i];
	}
	delete[] ptr_tileArray;
}
std::uint32_t sb::Area::getWidth() {
	return width;
}
std::uint32_t sb::Area::getHeight() {
	return height;
}
sb::Tile*& sb::Area::getTile(std::uint32_t x, std::uint32_t y) {
	return ptr_tileArray[x + y * width];
}
void sb::Area::swap(std::uint32_t x1, std::uint32_t y1, std::uint32_t x2, std::uint32_t y2) {
	sb::Tile* temp = getTile(x1, y1);
	getTile(x1, y1) = getTile(x2, y2);
	getTile(x2, y2) = temp;
}
void sb::Area::update() {
	//left mouse button pressed
	if (sb::SBWindow::getInstance().get()->isLeftButtonPressed())
	{
		Tile*& tile = getTile(width / 2, height - 1);
		//if (tile != nullptr)
			tile = new Sand();
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
sb::Area::Area(std::uint32_t width, std::uint32_t height)
	:width(width), height(height) {
	std::uint32_t size = width * height;
	ptr_tileArray = new Tile * [size];
	for (size_t i = 0; i < size; ++i) {
		ptr_tileArray[i] = nullptr;
	}


	for (std::uint32_t y = height / 2; y < height / 2+3; ++y) {
		for (std::uint32_t x = width / 2 - 10; x < width / 2 + 10; ++x) {
			getTile(x, y) = new Stone();
		}
	}
}
std::shared_ptr<sb::Area> sb::Area::getInstance() {
	return ptr_instance;
}
std::shared_ptr<sb::Area> sb::Area::createInstance(std::uint32_t width, std::uint32_t height) {
	if (ptr_instance == nullptr) {
		ptr_instance.reset(new Area(width, height));
	}
	return ptr_instance;
}