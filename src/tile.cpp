#include "tile.h"
#include "game/area.h"

sb::Tile::Tile():Tile(Type::empty) {

}
sb::Tile::Tile(sb::Tile::Type type) :type(type) {
	switch (type) {

	case Tile::Type::empty:
		color = sb::RGB(0, 0, 0);
		sleep = true; //sleeps forever
		break;

	case Tile::Type::sand:
		color = sb::RGB(255, 255, 0);
		sleep = false;
		break;

	case Tile::Type::stone:
		color = sb::RGB(180, 180, 180);
		sleep = true; //sleeps forever
		break;
		
	default:
		throw std::exception("non-existent tile type");
		break;
	}
}

sb::RGB sb::Tile::getColor() const {
	return color;
}
bool sb::Tile::isEmpty() const {
	return (bool)type;
}
bool sb::Tile::isNotEmpty() const {
	return !(bool)type;
}
void sb::Tile::update(int x, int y) {
	if (sleep)
		return;

	switch (type) {

	case Tile::Type::empty:
		//emptyUpdate();
		break;

	case Tile::Type::sand:
		sandUpdate(x,y);
		break;

	case Tile::Type::stone:
		//stoneUpdate();
		break;

	default:
		throw std::exception("non-existent tile type");
		break;
	}
}


//STATUS UPDATES

//   emptyUpdate(){
// 
// };

void sb::Tile::sandUpdate(int x, int y) {
	if (y == 0) return;

	if (ptr_area->getTile(x, y - 1).isNotEmpty())
		ptr_area->swap(x, y, x, y - 1);
	else if (x != 0 && ptr_area->getTile(x - 1, y - 1).isNotEmpty())
		ptr_area->swap(x, y, x - 1, y - 1);
	else if (x + 1 < ptr_area->getWidth() && ptr_area->getTile(x + 1, y - 1).isNotEmpty())
		ptr_area->swap(x, y, x + 1, y - 1);
	else
		sleep = true;
}

//	 stoneUpdate(){
// 
// };
