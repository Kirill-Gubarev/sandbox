#include "SBWindow.h"
#include "game/game.h"
#include "game/area.h"
void sb::SBWindow::setWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
}

int sb::SBWindow::getWidth() {
	return width;
}
int sb::SBWindow::getHeight(){
	return height;
}
sb::Vec2d<int> sb::SBWindow::getOutputLeftBottom() {
	return outputLeftBottom;
}
sb::Vec2d<int> sb::SBWindow::getOutputRightTop() {
	return outputRightTop;
}
void sb::SBWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
	ptr_instance.get()->setWindowSize(width, height);
	ptr_instance.get()->changeOutputArea();
}
void sb::SBWindow::changeOutputArea() {

	Area* area = sb::Area::getInstance().get();

	float numberTilesWidth = area->getWidth();
	float numberTilesHeight = area->getHeight();

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
	glLoadIdentity();
	outputLeftBottom.x = width / 2 - tileSize * numberTilesWidth / 2;
	outputLeftBottom.y = 0;
	outputRightTop.x = width / 2 + tileSize * numberTilesWidth / 2;
	outputRightTop.y = tileSize * numberTilesHeight;

	std::cout
		<< "LB x: " << outputLeftBottom.x
		<< " LB y: " << outputLeftBottom.y
		<< " RT x: " << outputRightTop.x
		<< " RT y: " << outputRightTop.y
		<< std::endl;

	glViewport(outputLeftBottom.x, outputLeftBottom.y, width, height);
	glOrtho(0, drawWidth, 0, drawHeight, -1, 1);
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
sb::Vec2d<float> sb::SBWindow::getMousePosition() {
	double x, y;
	glfwGetCursorPos(ptr_glfwWindow, &x, &y);
	return Vec2d<float>(x,y);
}
bool sb::SBWindow::isLeftButtonPressed() {
	int state = glfwGetMouseButton(ptr_glfwWindow, GLFW_MOUSE_BUTTON_LEFT);
	return state == GLFW_PRESS;
}


GLFWwindow* sb::SBWindow::getGLFWwindow() {
	return ptr_glfwWindow;
}

void sb::SBWindow::init() {
	changeOutputArea();
	glfwSetWindowSizeCallback(ptr_glfwWindow, windowSizeCallback);
	glfwSetMouseButtonCallback(ptr_glfwWindow, mouseButtonCallback);
}

//singleton pattern
std::shared_ptr<sb::SBWindow> PTR_SBWindow(nullptr);
std::shared_ptr<sb::SBWindow> sb::SBWindow::ptr_instance(nullptr);

sb::SBWindow::SBWindow(int width, int height, const char* title)
	:width(width), height(height),outputLeftBottom(),outputRightTop () {
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