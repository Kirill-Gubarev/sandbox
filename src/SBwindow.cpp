#include "SBWindow.h"
#include "game/area.h"


void sb::SBWindow::setWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
}


int sb::SBWindow::getWidth() const {
	return width;
}
int sb::SBWindow::getHeight() const {
	return height;
}
sb::Vec2d<int> sb::SBWindow::getAreaBottomLeft() const {
	return areaBottomLeft;
}
sb::Vec2d<int> sb::SBWindow::getAreaTopRight() const {
	return areaTopRight;
}
GLFWwindow* sb::SBWindow::getGLFWwindow() const {
	return ptr_glfwWindow;
}


void sb::SBWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
	ptr_sbWindow->setWindowSize(width, height);
	ptr_sbWindow->changeOutputArea();
}
void sb::SBWindow::windowCloseCallback(GLFWwindow* window) {
	ptr_sbWindow->windowOpen = false;
	std::cout << "windowCloseCallback();" << std::endl;
}
bool sb::SBWindow::isWindowOpen() const {
	return windowOpen;
}
void sb::SBWindow::changeOutputArea() {

	float numberTilesWidth = sb::ptr_area->getWidth();
	float numberTilesHeight = sb::ptr_area->getHeight();

	float tileWidth = (float)width / numberTilesWidth;
	float tileHeight = (float)height / numberTilesHeight;
	float tileSize;

	float drawWidth;
	float drawHeight;


	if (tileWidth < tileHeight) {
		float ratio = numberTilesWidth / numberTilesHeight;
		tileSize = tileWidth;
		drawWidth = numberTilesWidth;
		drawHeight = tileHeight / tileSize * numberTilesWidth / ratio;
	}
	else {
		tileSize = tileHeight;
		drawWidth = tileWidth / tileSize * numberTilesWidth;
		drawHeight = numberTilesHeight;
	}


	areaBottomLeft.x = width / 2 - tileSize * numberTilesWidth / 2;
	areaBottomLeft.y = 0;
	areaTopRight.x = width / 2 + tileSize * numberTilesWidth / 2;
	areaTopRight.y = tileSize * numberTilesHeight;


	glLoadIdentity();
	glViewport(areaBottomLeft.x, areaBottomLeft.y, width, height);
	glOrtho(0, drawWidth, 0, drawHeight, -1, 1);
}



//singleton pattern
sb::SBWindow* sb::ptr_sbWindow = nullptr;
std::unique_ptr<sb::SBWindow> sb::SBWindow::ptr_instance(nullptr);
sb::SBWindow::SBWindow(int width, int height, const char* title)
	:width(width), height(height), areaBottomLeft(), areaTopRight() {
	if (!glfwInit()) {
		throw std::exception("failed to init glfw");
	}

	ptr_glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

	if (ptr_glfwWindow == nullptr)
	{
		glfwTerminate();
		throw std::exception("failed to create a window");
	}
	windowOpen = true;
	glfwMakeContextCurrent(ptr_glfwWindow);

	changeOutputArea();
	glfwSetWindowSizeCallback(ptr_glfwWindow, windowSizeCallback);
	glfwSetWindowCloseCallback(ptr_glfwWindow, windowCloseCallback);
}
sb::SBWindow* sb::SBWindow::createInstance(int width, int height, const char* title) {
	if (ptr_instance == nullptr) {
		ptr_instance.reset(new sb::SBWindow(width, height, title));
		sb::ptr_sbWindow = ptr_instance.get();
	}
	return ptr_instance.get();
}
sb::SBWindow* sb::SBWindow::getInstance() {
	return ptr_instance.get();
}