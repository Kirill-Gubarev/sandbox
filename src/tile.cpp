#include "tile.h"
#include "game/area.h"

sb::Tile::Tile() :sleep(false) {}


sb::Sand::Sand() :Tile() {}
void sb::Sand::update(std::uint32_t x, std::uint32_t y) {
	if (y == 0) return;

	if (ptr_area->getTile(x, y - 1) == nullptr)
		ptr_area->swap(x, y, x, y - 1);
	else if (x != 0 && ptr_area->getTile(x - 1, y - 1) == nullptr)
		ptr_area->swap(x, y, x - 1, y - 1);
	else if (x + 1 < ptr_area->getWidth() && ptr_area->getTile(x + 1, y - 1) == nullptr)
		ptr_area->swap(x, y, x + 1, y - 1);
	else
		sleep = true;
}
sb::RGB sb::Sand::getColor() const {
	return sb::RGB(255, 255, 0);
}



sb::Stone::Stone() :Tile() {
	sleep = true;
}
void sb::Stone::update(std::uint32_t x, std::uint32_t y) {

}
sb::RGB sb::Stone::getColor()const {
	return sb::RGB(200, 200, 200);
}