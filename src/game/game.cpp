#include "game.h"

void sb::Game::drawTile() {
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(255, 255, 0);
	glVertex2f(1, 1);
	glVertex2f(1, 0);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glEnd();
}

int sb::Game::getNumberTilesWidth() {
	return numberTilesWidth;
}
int sb::Game::getNumberTilesHeight() {
	return numberTilesHeight;
}

void sb::Game::mainLoop() {
	
	sbWindow.get()->init();
	GLFWwindow* glfwWindow = sbWindow.get()->getGLFWwindow();
	while (!glfwWindowShouldClose(glfwWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		drawTile();

		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
		glColor3ub(150, 150, 150);

		glVertex2f(0, 0);
		glVertex2f(0, numberTilesHeight);
		glVertex2f(numberTilesWidth , numberTilesHeight);
		glVertex2f(numberTilesWidth , 0);

		glEnd();

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}
	glfwTerminate();
}


//singleton pattern
std::shared_ptr<sb::Game> sb::Game::ptr_instance(nullptr);
sb::Game::Game() {
	if (!glfwInit()) {
		throw std::exception("failed to init glfw");
		return;
	}
	numberTilesWidth = 30;
	numberTilesHeight = 30;
	sbWindow = sb::SBwindow::createWindow(700, 500, "Sandbox");
};
std::shared_ptr<sb::Game> sb::Game::getInstance() {
	return ptr_instance;
}
std::shared_ptr<sb::Game> sb::Game::createGame() {
	if (ptr_instance == nullptr) {
		std::shared_ptr<sb::Game> temp(new Game());
		ptr_instance.swap(temp);
	}
	return ptr_instance;
}