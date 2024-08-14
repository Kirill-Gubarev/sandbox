#include "area/tile.h"
#include "area/area.h"

//constructors
sb::Tile::Tile() :Tile(Type::empty, -1, -1) {

}
sb::Tile::Tile(int x, int y) :Tile(Type::empty, x, y) {

}
sb::Tile::Tile(sb::Tile::Type type, int x, int y)
	:x(x), y(y), type(type),  hasBeenUpdated(false) {

	switch (type) {

	case Tile::Type::empty:
		color = uts::RGB(0, 0, 0);
		sleep = true; //sleeps forever
		density = 0;
		break;

	case Tile::Type::stone:
		color = uts::RGB(180, 180, 180);
		sleep = true; //sleeps forever
		density = 2200;
		break;

	case Tile::Type::sand:
		color = uts::RGB(255, 255, 0);
		sleep = false;
		density = 1700;
		break;

	case Tile::Type::water:
		color = uts::RGB(0, 0, 255);
		sleep = false;
		density = 997;
		break;

	default:
		throw std::exception("non-existent tile type");
		break;
	}
}
void sb::Tile::copyWithoutPos(const Tile& l_tile){
	//without x, y
	type = l_tile.type;
	color = l_tile.color;
	density = l_tile.density;
	sleep = l_tile.sleep;
	hasBeenUpdated = l_tile.hasBeenUpdated;
}
//getters
bool sb::Tile::isEmpty() const {
	// !0 = true - yes, it is empty
	return !static_cast<bool>(type);
}
bool sb::Tile::isNotEmpty() const {
	// something = true - yes, it isn't empty
	return static_cast<bool>(type);
}
bool sb::Tile::isTheDensityLess(float density) {
	return this->density < density;
}
bool sb::Tile::isTheDensityGreater(float density) {
	return this->density > density;
}