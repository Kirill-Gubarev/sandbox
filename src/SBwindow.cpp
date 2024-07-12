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
	glLoadIdentity();
	glViewport(windowWidth / 2 - tileSize * numberTilesWidth / 2, 0, windowWidth, windowHeight);
	glOrtho(0, width, 0, height, -1, 1);
}

//mouse
void sb::SBWindow::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		std::cout << "left button press" << std::endl;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		std::cout << "right button press" << std::endl;
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
}
sb::Vec2d sb::SBWindow::getMousePosition() {
	double x, y;
	glfwGetCursorPos(ptr_glfwWindow, &x, &y);
	return Vec2d(x,y);
}
bool sb::SBWindow::isLeftButtonPressed() {
	int state = glfwGetMouseButton(ptr_glfwWindow, GLFW_MOUSE_BUTTON_LEFT);
	return state == GLFW_PRESS;
}


GLFWwindow* sb::SBWindow::getGLFWwindow() {
	return ptr_glfwWindow;
}

void sb::SBWindow::init() {
	changeTheAspectRatio();
	glfwSetWindowSizeCallback(ptr_glfwWindow, windowSizeCallback);
	glfwSetMouseButtonCallback(ptr_glfwWindow, mouseButtonCallback);
}

//singleton pattern
std::shared_ptr<sb::SBWindow> PTR_SBWindow(nullptr);
std::shared_ptr<sb::SBWindow> sb::SBWindow::ptr_instance(nullptr);

sb::SBWindow::SBWindow(int width, int height, const char* title)
	:windowWidth(width), windowHeight(height) {
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