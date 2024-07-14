#include "common.h"
#include "sbWindow.h"
#include "game/game.h"
#include "game/area.h"
#include "input.h"
#include "render.h"


void sb::init() {
	try {
		sb::Area::createInstance(100, 150);
		sb::Game::createInstance();
		sb::SBWindow::createInstance(900, 500, "sandbox");
		sb::Input::createInstance();
		sb::Render::createInstance();
	}
	catch (std::exception& ex)
	{
		sb::exitProgram(ex);
	}
}
void sb::start() {
	sb::Game::getInstance()->mainLoop();
}
void sb::exitProgram(std::exception& ex) {
	std::cerr << "EXCEPTION: " << ex.what() << std::endl;
	system("pause");
	exit(0);
}