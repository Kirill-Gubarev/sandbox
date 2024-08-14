#include "area.h"

//STATUS UPDATES
void sb::Area::tileUpdate(Tile& t) {

	//if the tile is sleeping, then update is not called for it
	if (t.sleep)
		return;

	//if the tile has been updated, don't need to do it twice
	if (t.hasBeenUpdated)
		return;
	t.hasBeenUpdated = true;

	switch (t.type) {

	case Tile::Type::empty:
		//emptyUpdate();
		break;

	case Tile::Type::stone:
		//stoneUpdate();
		break;

	case Tile::Type::sand:
		sandUpdate(t);
		break;

	case Tile::Type::water:
		waterUpdate(t);
		break;

	default:
		throw std::exception("non-existent tile type");
		break;
	}
}
//   emptyUpdate();
//	 stoneUpdate();
void sb::Area::sandUpdate(Tile& t) {

	//bottom area
	if (t.y == 0) {
		t.sleep = true;
		return;
	}

	//bottom tile
	if (sb::Area::getTile(t.x, t.y - 1).isTheDensityLess(t.density)) {
		sb::Area::swapTile(t.x, t.y, t.x, t.y - 1);
		return;
	}

	bool moveLeft = false;
	bool moveRight = false;

	//bottom left tile
	if (t.x > 0 && sb::Area::getTile(t.x - 1, t.y - 1).isTheDensityLess(t.density))
		moveLeft = true;

	//bottom right tile
	if (t.x + 1 < sb::Area::getWidth() && sb::Area::getTile(t.x + 1, t.y - 1).isTheDensityLess(t.density))
		moveRight = true;

	if (moveLeft && moveRight) {
		// the probability is 50%
		if (rand() % 2) { sb::Area::swapTile(t.x, t.y, t.x - 1, t.y - 1);	return; }
		else			{ sb::Area::swapTile(t.x, t.y, t.x + 1, t.y - 1);	return; }
	}
	else if (moveLeft)	{ sb::Area::swapTile(t.x, t.y, t.x - 1, t.y - 1);	return; }
	else if (moveRight) { sb::Area::swapTile(t.x, t.y, t.x + 1, t.y - 1);	return; }

	//if "return" was not called
	t.sleep = true;
}
void sb::Area::waterUpdate(Tile& t) {

	//bottom tile
	if (t.y > 0 && sb::Area::getTile(t.x, t.y - 1).isTheDensityLess(t.density)) {
		sb::Area::swapTile(t.x, t.y, t.x, t.y - 1);
		return;
	}

	bool moveLeft = false;
	bool moveRight = false;

	//bottom left tile
	if (t.y > 0 && t.x > 0 && 
		sb::Area::getTile(t.x - 1, t.y - 1).isTheDensityLess(t.density))
		moveLeft = true;

	//bottom right tile
	if (t.y > 0 && t.x + 1 < sb::Area::getWidth() 
		&& sb::Area::getTile(t.x + 1, t.y - 1).isTheDensityLess(t.density))
		moveRight = true;

	if (moveLeft && moveRight) {
		// the probability is 50%
		if (rand() % 2)	{	sb::Area::swapTile(t.x, t.y, t.x - 1, t.y - 1);	return; }
		else			{	sb::Area::swapTile(t.x, t.y, t.x + 1, t.y - 1);	return; }
	}
	else if (moveLeft)	{	sb::Area::swapTile(t.x, t.y, t.x - 1, t.y - 1);	return; }
	else if (moveRight) {	sb::Area::swapTile(t.x, t.y, t.x + 1, t.y - 1);	return; }

	//reset
	moveLeft = false;
	moveRight = false;

	//left tile
	if (t.x > 0 && sb::Area::getTile(t.x - 1, t.y).isTheDensityLess(t.density))
		moveLeft = true;

	//right tile
	if (t.x + 1 < sb::Area::getWidth() 
		&& sb::Area::getTile(t.x + 1, t.y).isTheDensityLess(t.density))
		moveRight = true;

	if (moveLeft && moveRight) {
		// the probability is 50%
		if (rand() % 2) {	sb::Area::swapTile(t.x, t.y, t.x - 1, t.y);	return;	}
		else			{	sb::Area::swapTile(t.x, t.y, t.x + 1, t.y);	return;	}
	}
	else if (moveLeft)	{	sb::Area::swapTile(t.x, t.y, t.x - 1, t.y);	return;	}
	else if (moveRight) {	sb::Area::swapTile(t.x, t.y, t.x + 1, t.y);	return;	}

	//if "return" was not called
	//the water breaks when add this, I don't know how to fix it yet
	//sleep = true;
}