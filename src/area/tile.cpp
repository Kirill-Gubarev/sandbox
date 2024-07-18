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

void sb::Tile::update(int x, int y) {

	//if the tile is sleeping, then update is not called for it
	if (sleep)
		return;

	//if the tile has been updated, don't need to do it twice
	if (hasBeenUpdated)
		return;
	hasBeenUpdated = true;

	switch (type) {

	case Tile::Type::empty:
		//emptyUpdate();
		break;

	case Tile::Type::stone:
		//stoneUpdate();
		break;

	case Tile::Type::sand:
		sandUpdate(x, y);
		break;

	case Tile::Type::water:
		waterUpdate(x, y);
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

//resetters
void sb::Tile::resetSleep() {
	sleep = false;
}
void sb::Tile::resetUpdate() {
	hasBeenUpdated = false;
}

//STATUS UPDATES
//   emptyUpdate();
//	 stoneUpdate();
void sb::Tile::sandUpdate(int x, int y) {

	//bottom area
	if (y == 0) {
		sleep = true;
		return;
	}
	type;

	//bottom tile
	bool b = sb::Area::getTile(x, y - 1).isTheDensityLess(density);
	if (b) {
		sb::Area::swapTile(x, y, x, y - 1);
		return;
	}

	bool moveLeft = false;
	bool moveRight = false;

	//bottom left tile
	if (x > 0 && sb::Area::getTile(x - 1, y - 1).isTheDensityLess(density))
		moveLeft = true;

	//bottom right tile
	if (x + 1 < sb::Area::getWidth() && sb::Area::getTile(x + 1, y - 1).isTheDensityLess(density))
		moveRight = true;

	if (moveLeft && moveRight) {
		// the probability is 50%
		if (rand() % 2) { sb::Area::swapTile(x, y, x - 1, y - 1);	return; }
		else { sb::Area::swapTile(x, y, x + 1, y - 1);	return; }
	}
	else if (moveLeft) { sb::Area::swapTile(x, y, x - 1, y - 1);	return; }
	else if (moveRight) { sb::Area::swapTile(x, y, x + 1, y - 1);	return; }

	//if "return" was not called
	sleep = true;
}
void sb::Tile::waterUpdate(int x, int y) {

	//bottom tile
	if (y > 0 && sb::Area::getTile(x, y - 1).isTheDensityLess(density)) {
		sb::Area::swapTile(x, y, x, y - 1);
		return;
	}

	bool moveLeft = false;
	bool moveRight = false;

	//bottom left tile
	if (y > 0 && x > 0 && sb::Area::getTile(x - 1, y - 1).isTheDensityLess(density))
		moveLeft = true;

	//bottom right tile
	if (y > 0 && x + 1 < sb::Area::getWidth() && sb::Area::getTile(x + 1, y - 1).isTheDensityLess(density))
		moveRight = true;

	if (moveLeft && moveRight) {
		// the probability is 50%
		if (rand() % 2) { sb::Area::swapTile(x, y, x - 1, y - 1);	return; }
		else { sb::Area::swapTile(x, y, x + 1, y - 1);	return; }
	}
	else if (moveLeft) { sb::Area::swapTile(x, y, x - 1, y - 1);	return; }
	else if (moveRight) { sb::Area::swapTile(x, y, x + 1, y - 1);	return; }

	//reset
	moveLeft = false;
	moveRight = false;

	//left tile
	if (x > 0 && sb::Area::getTile(x - 1, y).isTheDensityLess(density))
		moveLeft = true;

	//right tile
	if (x + 1 < sb::Area::getWidth() && sb::Area::getTile(x + 1, y).isTheDensityLess(density))
		moveRight = true;

	if (moveLeft && moveRight) {
		// the probability is 50%
		if (rand() % 2) { sb::Area::swapTile(x, y, x - 1, y);	return; }
		else { sb::Area::swapTile(x, y, x + 1, y);	return; }
	}
	else if (moveLeft) { sb::Area::swapTile(x, y, x - 1, y);	return; }
	else if (moveRight) { sb::Area::swapTile(x, y, x + 1, y);	return; }

	//if "return" was not called
	//the water breaks when add this, I don't know how to fix it yet
	//sleep = true;
}