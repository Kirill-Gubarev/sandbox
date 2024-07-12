#include "SBWindow.h"
#include "game/game.h"
#include "game/area.h"
void sb::SBWindow::setWindowSize(int windowWidth, int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}
void sb::SBWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
	ptr_instance.get()->setWindowSize(width, height);
	ptr_instance.get()->changeTheAspectRatio();
}
void sb::SBWindow::changeTheAspectRatio() {

	Area* area = sb::Area::getInstance().get();

	float numberTilesWidth = area->getWidth();
	float numberTilesHeight = area->getHeight();

	float tileWidth = (float)windowWidth / numberTilesWidth;
	float tileHeight = (float)windowHeight / numberTilesHeight;

	float width;
	float height;
	float tileSize;

	glLoadIdentity();
	if (tileWidth < tileHeight) {
		float ratio = numberTilesWidth / numberTilesHeight;
		tileSize = tileWidth;
		width = numberTilesWidth;
		height = tileHeight / tileSize * numberTilesWidth / ratio;
	}
	else {
		tileSize = tileHeight;
		width = tileWidth / tileSize * numberTilesWidth;
		height = numberTilesHeight;
	}
	glViewport(windowWidth / 2 - tileSize * numberTilesWidth / 2, 0, windowWidth, windowHeight);
	glOrtho(0, width, 0, height, -1, 1);
}

GLFWwindow* sb::SBWindow::getGLFWwindow() {
	return ptr_glfwWindow;
}

void sb::SBWindow::init() {
	changeTheAspectRatio();
	glfwSetWindowSizeCallback(ptr_glfwWindow, windowSizeCallback);
}

//singleton pattern
std::shared_ptr<sb::SBWindow> PTR_SBWindow(nullptr);
std::shared_ptr<sb::SBWindow> sb::SBWindow::ptr_instance(nullptr);

sb::SBWindow::SBWindow(int width, int height, const char* title)
:windowWidth(width), windowHeight(height){
	if (!glfwInit()) {
		throw std::exception("failed to init glfw");
	}

	ptr_glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

	if (ptr_glfwWindow == nullptr)
	{
		glfwTerminate();
		throw std::exception("failed to create a window");
	}
	glfwMakeContextCurrent(ptr_glfwWindow);
}

std::shared_ptr<sb::SBWindow> sb::SBWindow::createInstance(int width, int height, const char* title) {
	if (ptr_instance == nullptr) {
		ptr_instance.reset(new sb::SBWindow(width, height, title));
	}
	return ptr_instance;
}

std::shared_ptr<sb::SBWindow> sb::SBWindow::getInstance() {
	return ptr_instance;
}