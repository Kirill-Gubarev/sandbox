#include "game/input.h"
#include "game/sbWindow.h"
#include "area/area.h"
#include "GUI/GUI.h"
#include "GUI/Element.h"

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
uts::Vec2<double> sb::Input::getMousePosition() {
	double x, y;
	glfwGetCursorPos(sb::SBWindow::getGLFWwindow(), &x, &y);
	return uts::Vec2<double>(x, y);
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
	gui::GUI::ptr_element->mouseAction(
		gui::Point2D(x, sb::SBWindow::getHeight() - y),
		static_cast<gui::GUI::MouseButton>(button),
		static_cast<gui::GUI::MouseAction>(action)
	);
}