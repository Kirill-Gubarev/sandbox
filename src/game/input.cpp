#include "game/input.h"
#include "game/sbWindow.h"
#include "area/area.h"


//managing this class
void sb::Input::init() {
	glfwSetMouseButtonCallback(sb::SBWindow::getGLFWwindow(), mouseButtonCallback);
}
void sb::Input::terminate() {

}
void sb::Input::update() {
	glfwPollEvents();
	if (isLBPressed())
		sb::Area::setTileMouseLB();
	if (isRBPressed())
		sb::Area::setTileMouseRB();
}

//mouse
sb::Vec2d<double> sb::Input::getMousePosition() {
	double x, y;
	glfwGetCursorPos(sb::SBWindow::getGLFWwindow(), &x, &y);
	return Vec2d<double>(x, y);
}
bool sb::Input::isLBPressed() {
	int state = glfwGetMouseButton(sb::SBWindow::getGLFWwindow(), GLFW_MOUSE_BUTTON_LEFT);
	return state == GLFW_PRESS;
}
bool sb::Input::isRBPressed() {
	int state = glfwGetMouseButton(sb::SBWindow::getGLFWwindow(), GLFW_MOUSE_BUTTON_RIGHT);
	return state == GLFW_PRESS;
}
void sb::Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		std::cout << "left button press" << std::endl;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		std::cout << "right button press" << std::endl;
}