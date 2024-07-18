#include "common.h"

#include "game/game.h"
#include "game/sbWindow.h"
#include "game/render.h"
#include "game/input.h"

#include "area/area.h"


void sb::init() {
	try {
		sb::Area::createInstance(100, 150);
		sb::Game::createInstance();
		sb::SBWindow::createInstance(900, 500, "sandbox");
		sb::Input::createInstance();
		sb::Render::createInstance();
		srand(time(nullptr));
	}
	catch (std::exception& ex) {
		sb::exitProgram(ex);
	}
}
void sb::start() {
	try {
		sb::Game::getInstance()->mainLoop();
	}
	catch (std::exception& ex) {
		sb::exitProgram(ex);
	}
}
void sb::exitProgram(std::exception& ex) {
	std::cerr << "EXCEPTION: " << ex.what() << std::endl;
	system("pause");
	exit(0);
}