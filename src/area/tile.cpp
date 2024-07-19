#include "area/tile.h"
#include "area/area.h"


//constructors
sb::Tile::Tile() :Tile(Type::empty) {

}
sb::Tile::Tile(sb::Tile::Type type)
	:type(type), hasBeenUpdated(false) {

	switch (type) {

	case Tile::Type::empty:
		color = sb::RGB(0, 0, 0);
		sleep = true; //sleeps forever
		density = 0;
		break;

	case Tile::Type::stone:
		color = sb::RGB(180, 180, 180);
		sleep = true; //sleeps forever
		density = 2200;
		break;

	case Tile::Type::sand:
		color = sb::RGB(255, 255, 0);
		sleep = false;
		density = 1700;
		break;

	case Tile::Type::water:
		color = sb::RGB(0, 0, 255);
		sleep = false;
		density = 997;
		break;

	default:
		throw std::exception("non-existent tile type");
		break;
	}
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