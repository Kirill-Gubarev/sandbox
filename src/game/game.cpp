#include "game.h"
#include "sbWindow.h"
#include "Input.h"
#include "tile.h"
#include "area.h"
#include "render.h"

void sb::Game::mainLoop() {
	GLFWwindow* glfwWindow = ptr_sbWindow->getGLFWwindow();

	double now = glfwGetTime();
	double previousTime = now;

	double fpsCounter = 0;
	double previousCounterTime = now;

	while (sb::ptr_sbWindow->isWindowOpen()) {
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
		glfwPollEvents();
		ptr_input->update();

		//render
		sb::ptr_render->update();

		//physics
		ptr_area->update();
	}
	glfwTerminate();
}



//singleton pattern
sb::Game* sb::ptr_game = nullptr;
std::unique_ptr<sb::Game> sb::Game::ptr_instance(nullptr);
sb::Game::Game() :frameDuration(1.0 / 60.0) {

}
sb::Game* sb::Game::getInstance() {
	return ptr_instance.get();
}
sb::Game* sb::Game::createInstance() {
	if (ptr_instance == nullptr) {
		ptr_instance.reset(new Game());
		sb::ptr_game = ptr_instance.get();
	}
	return ptr_instance.get();
}