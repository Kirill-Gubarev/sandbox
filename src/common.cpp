#include "common.h"

#include "game/game.h"
#include "game/sbWindow.h"
#include "game/render.h"
#include "game/input.h"
#include "game/GUI.h"

#include "area/area.h"


void sb::init() {
	try {
		sb::Area::init(200, 100);
		sb::SBWindow::init(900, 500, "sandbox");
		sb::Render::init();
		sb::Input::init();
		sb::GUI::init();
		sb::Game::init();
		
		//random initialization
		srand(time(nullptr));
	}
	catch (std::exception& ex) {
		sb::exitProgram(ex);
	}
}
void sb::run() {
	try {
		sb::Game::mainLoop();
	}
	catch (std::exception& ex) {
		sb::exitProgram(ex);
	}
}
void sb::terminate() {
	try {
		sb::Game::terminate();
		sb::GUI::terminate();
		sb::Input::terminate();
		sb::Render::terminate();
		sb::SBWindow::terminate();
		sb::Area::terminate();
	}
	catch (std::exception& ex) {
		sb::exitProgram(ex);
	}
}
void sb::exitProgram(std::exception& ex) {
	std::cerr << "EXCEPTION: " << ex.what() << std::endl;
	system("pause");
	exit(-1);
}