#include "game/game.h"
#include "game/sbWindow.h"
#include "game/input.h"
#include "game/render.h"

#include "area/tile.h"
#include "area/area.h"

//data
const double sb::Game::frameDuration = 1.0/60.0;// 1.0 / 60.0 is 60 FPS
//but for some reason it turns out to be 66. 
//I don't know how to fix it yet.

//managing this class
void sb::Game::init() {

}
void sb::Game::terminate(){

}
void sb::Game::mainLoop(){
	GLFWwindow* glfwWindow = sb::SBWindow::getGLFWwindow();

	double now = glfwGetTime();
	double previousTime = now;

	double fpsCounter = 0;
	double previousCounterTime = now;

	while (sb::SBWindow::isWindowOpen()) {
		//FPS controller
		now = glfwGetTime();
		double sleepTime = frameDuration - (now - previousTime);
		previousTime = now;

		if (sleepTime > 0) {
			std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
		}

		//FPS counter
		fpsCounter++;
		if ((now - previousCounterTime) >= 1.0) {
			std::cout << "FPS: " << fpsCounter << std::endl;
			fpsCounter = 0;
			previousCounterTime = now;
		}

		//input
		sb::Input::update();

		//render
		sb::Render::update();

		//physics
		sb::Area::update();
	}
	glfwTerminate();
}