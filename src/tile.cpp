#include "tile.h"
#include "game/area.h"

sb::Tile::Tile():sleep(false) {}
sb::Sand::Sand() :Tile() {}
void sb::Sand::update(std::uint32_t x, std::uint32_t y) {
	if (y == 0) return;
	sb::Area* area = sb::Area::getInstance().get();
	
	if (area->getTile(x, y - 1) == nullptr)
		area->swap(x, y, x, y - 1);
	else if (x != 0 && area->getTile(x - 1, y - 1) == nullptr)
		area->swap(x, y, x - 1, y - 1);
	else if (x+1 < area->getWidth() && area->getTile(x + 1, y - 1) == nullptr)
		area->swap(x, y, x + 1, y - 1);
	else
		sleep = true;
}
void sb::Sand::setColor() {
	glColor3ub(255, 255, 0);
}

sb::Stone::Stone() :Tile() { 
	sleep = true; 
}
void sb::Stone::update(std::uint32_t x, std::uint32_t y) {};
void sb::Stone::setColor() {
	glColor3ub(200, 200, 200);
};