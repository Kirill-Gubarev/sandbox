#include "area.h"

sb::Area::~Area() {
	std::uint32_t size = width * height;
	for (size_t i = 0; i < size; ++i) {
		if (ptr_tileArray != nullptr)
			delete ptr_tileArray[0];
	}
	delete[] ptr_tileArray;
}
std::uint32_t sb::Area::getWidth() {
	return width;
}
std::uint32_t sb::Area::getHeight() {
	return height;
}
sb::Tile* sb::Area::getTile(std::uint32_t x, std::uint32_t y) {
	sb::Tile* tile = ptr_tileArray[x + y * width];
	return tile;
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
	ptr_tileArray[9000] = new Sand();
	ptr_tileArray[600] = new Sand();
	ptr_tileArray[7922] = new Sand();
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