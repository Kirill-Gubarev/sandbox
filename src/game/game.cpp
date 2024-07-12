#include "game.h"
#include "../sbWindow.h"
#include "../tile.h"
#include "area.h"

void sb::Game::drawTiles() {

	sb::Area* ptr_area = sb::Area::getInstance().get();

	std::uint32_t areaWidth = ptr_area->getWidth();
	std::uint32_t areaHeight = ptr_area->getHeight();

	for (int x = 0; x < areaWidth; x++) {
		for (int y = areaHeight - 1; y >= 0; y--) {
			sb::Tile* tile = ptr_area->getTile(x, y);
			if (tile == nullptr)
				continue;

			glBegin(GL_TRIANGLE_FAN);
			
			tile->setColor();
			glVertex2f(1 + x, 1 + y);
			glVertex2f(1 + x, 0 + y);
			glVertex2f(0 + x, 0 + y);
			glVertex2f(0 + x, 1 + y);
			glEnd();
		}
	}


}

void sb::Game::mainLoop() {
	sb::SBWindow* ptr_sbWindow = sb::SBWindow::getInstance().get();
	sb::Area* area = sb::Area::getInstance().get();
	ptr_sbWindow->init();
	GLFWwindow* glfwWindow = ptr_sbWindow->getGLFWwindow();
	while (!glfwWindowShouldClose(glfwWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		drawTiles();

		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
		glColor3ub(150, 150, 150);

		glVertex2f(0, 0);
		glVertex2f(0, area->getHeight());
		glVertex2f(area->getWidth(), area->getHeight());
		glVertex2f(area->getWidth(), 0);

		glEnd();

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}
	glfwTerminate();
}


//singleton pattern
std::shared_ptr<sb::Game> sb::Game::ptr_instance(nullptr);
sb::Game::Game() {
	
}
std::shared_ptr<sb::Game> sb::Game::getInstance() {
	return ptr_instance;
}
std::shared_ptr<sb::Game> sb::Game::createInstance() {
	if (ptr_instance == nullptr) {
		ptr_instance.reset(new Game());
	}
	return ptr_instance;
}