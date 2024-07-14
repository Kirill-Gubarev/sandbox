#include "game.h"
#include "sbWindow.h"
#include "Input.h"
#include "tile.h"
#include "area.h"

#include <thread>
#include <chrono>

void sb::Game::drawTiles() {

	int areaWidth = ptr_area->getWidth();
	int areaHeight = ptr_area->getHeight();

	for (int x = 0; x < areaWidth; x++) {
		for (int y = areaHeight - 1; y >= 0; y--) {
			sb::Tile* tile = ptr_area->getTile(x, y);
			if (tile == nullptr)
				continue;

			glBegin(GL_TRIANGLE_FAN);

			sb::Game::setColor(tile->getColor());
			glVertex2f(1 + x, 1 + y);
			glVertex2f(1 + x, 0 + y);
			glVertex2f(0 + x, 0 + y);
			glVertex2f(0 + x, 1 + y);
			glEnd();
		}
	}
}
void sb::Game::setColor(sb::RGB color) {
	glColor3ub(color.r, color.g, color.b);
}
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
		glClear(GL_COLOR_BUFFER_BIT);

		drawTiles();

		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
		glColor3ub(150, 150, 150);

		glVertex2f(0, 0);
		glVertex2f(0, ptr_area->getHeight());
		glVertex2f(ptr_area->getWidth(), ptr_area->getHeight());
		glVertex2f(ptr_area->getWidth(), 0);

		glEnd();

		glfwSwapBuffers(glfwWindow);


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