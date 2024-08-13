#include "game/input.h"
#include "game/sbWindow.h"
#include "area/area.h"
#include "game/GUI.h"
#include "game/Element.h"

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
	double x, y;
	glfwGetCursorPos(sb::SBWindow::getGLFWwindow(), &x, &y);
	sb::GUI::ptr_element->mouseAction(
		x, y,
		static_cast<sb::GUI::MouseButton>(button),
		static_cast<sb::GUI::MouseAction>(action)
	);
}