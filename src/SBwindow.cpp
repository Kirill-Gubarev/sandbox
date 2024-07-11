#include "SBWindow.h"
#include "game.h"
void sb::SBwindow::setWindowSize(int windowWidth, int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}
void sb::SBwindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
	ptr_instance.get()->setWindowSize(width, height);
	ptr_instance.get()->changeTheAspectRatio();
}
void sb::SBwindow::changeTheAspectRatio() {

	sb::PTR_Game game = sb::Game::getInstance();

	float numberTilesWidth = game.get()->getNumberTilesWidth();
	float numberTilesHeight = game.get()->getNumberTilesHeight();

	float tileWidth = (float)windowWidth / numberTilesWidth;
	float tileHeight = (float)windowHeight / numberTilesHeight;

	float width;
	float height;
	float tileSize;

	glLoadIdentity();
	if (tileWidth < tileHeight) {
		float ratio = numberTilesWidth / numberTilesHeight;

		width = numberTilesWidth;
		height = tileHeight / tileWidth * numberTilesWidth * ratio  ;
		tileSize = tileWidth;

	}
	else {

		width = tileWidth / tileHeight * numberTilesWidth;
		height = numberTilesHeight;
		tileSize = tileHeight;

	}
	glViewport(windowWidth / 2 - tileSize * numberTilesWidth / 2, 0, windowWidth, windowHeight);
	glOrtho(0, width, 0, height, -1, 1);
}

GLFWwindow* sb::SBwindow::getGLFWwindow() {
	return ptr_glfwWindow;
}

void sb::SBwindow::init() {
	changeTheAspectRatio();
	glfwSetWindowSizeCallback(ptr_glfwWindow, windowSizeCallback);
}

//singleton pattern
std::shared_ptr<sb::SBwindow> sb::SBwindow::ptr_instance(nullptr);

sb::SBwindow::SBwindow(int width, int height, const char* title) {
	ptr_glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

	if (ptr_glfwWindow == nullptr)
	{
		glfwTerminate();
		throw std::exception("failed to create a window");
	}
	glfwMakeContextCurrent(ptr_glfwWindow);
	windowWidth = width;
	windowHeight = height;
}

std::shared_ptr<sb::SBwindow> sb::SBwindow::createWindow(int width, int height, const char* title) {
	if (ptr_instance == nullptr) {
		std::shared_ptr<sb::SBwindow> temp(new SBwindow(width, height, title));
		ptr_instance.swap(temp);
	}
	return ptr_instance;
}

std::shared_ptr<sb::SBwindow> sb::SBwindow::getInstance() {
	return ptr_instance;
}