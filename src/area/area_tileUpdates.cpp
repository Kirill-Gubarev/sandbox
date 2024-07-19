#include "area.h"


//STATUS UPDATES
void sb::Area::tileUpdate(int x, int y) {
	Tile& l_tile = getTile(x,y);
	//if the tile is sleeping, then update is not called for it
	if (l_tile.sleep)
		return;

	//if the tile has been updated, don't need to do it twice
	if (l_tile.hasBeenUpdated)
		return;
	l_tile.hasBeenUpdated = true;

	switch (l_tile.type) {

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
//   emptyUpdate();
//	 stoneUpdate();
void sb::Area::sandUpdate(int x, int y) {
	Tile& l_tile = getTile(x, y);
	//bottom area
	if (y == 0) {
		l_tile.sleep = true;
		return;
	}

	//bottom tile
	if (sb::Area::getTile(x, y - 1).isTheDensityLess(l_tile.density)) {
		sb::Area::swapTile(x, y, x, y - 1);
		return;
	}

	bool moveLeft = false;
	bool moveRight = false;

	//bottom left tile
	if (x > 0 && sb::Area::getTile(x - 1, y - 1).isTheDensityLess(l_tile.density))
		moveLeft = true;

	//bottom right tile
	if (x + 1 < sb::Area::getWidth() && sb::Area::getTile(x + 1, y - 1).isTheDensityLess(l_tile.density))
		moveRight = true;

	if (moveLeft && moveRight) {
		// the probability is 50%
		if (rand() % 2) { sb::Area::swapTile(x, y, x - 1, y - 1);	return; }
		else { sb::Area::swapTile(x, y, x + 1, y - 1);	return; }
	}
	else if (moveLeft) { sb::Area::swapTile(x, y, x - 1, y - 1);	return; }
	else if (moveRight) { sb::Area::swapTile(x, y, x + 1, y - 1);	return; }

	//if "return" was not called
	l_tile.sleep = true;
}
void sb::Area::waterUpdate(int x, int y) {
	Tile& l_tile = getTile(x, y);
	//bottom tile
	if (y > 0 && sb::Area::getTile(x, y - 1).isTheDensityLess(l_tile.density)) {
		sb::Area::swapTile(x, y, x, y - 1);
		return;
	}

	bool moveLeft = false;
	bool moveRight = false;

	//bottom left tile
	if (y > 0 && x > 0 && sb::Area::getTile(x - 1, y - 1).isTheDensityLess(l_tile.density))
		moveLeft = true;

	//bottom right tile
	if (y > 0 && x + 1 < sb::Area::getWidth() && sb::Area::getTile(x + 1, y - 1).isTheDensityLess(l_tile.density))
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
	if (x > 0 && sb::Area::getTile(x - 1, y).isTheDensityLess(l_tile.density))
		moveLeft = true;

	//right tile
	if (x + 1 < sb::Area::getWidth() && sb::Area::getTile(x + 1, y).isTheDensityLess(l_tile.density))
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