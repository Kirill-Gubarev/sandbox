#include "common.h"
#include "sbWindow.h"
#include "game/game.h"
#include "game/area.h"
void sb::init() {
	try {
		sb::Area::createInstance(100, 150);
		sb::Game::createInstance();
		sb::SBWindow::createInstance(900, 500, "sandbox");
	}
	catch (std::exception& ex)
	{
		std::cerr << "EXCEPTION: " << ex.what() << std::endl;
	}
}
void sb::start() {
	sb::Game::getInstance().get()->mainLoop();
}