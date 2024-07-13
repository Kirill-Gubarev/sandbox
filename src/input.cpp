#include "input.h"
#include "sbWindow.h"
#include "game/area.h"


void sb::Input::update() {
	if (isLeftButtonPressed())
	{
		sb::ptr_area->mouseSetTile();
	}
}


//mouse
void sb::Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		std::cout << "left button press" << std::endl;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		std::cout << "right button press" << std::endl;
}
sb::Vec2d<double> sb::Input::getMousePosition() const {
	double x, y;
	glfwGetCursorPos(sb::ptr_sbWindow->getGLFWwindow(), &x, &y);
	return Vec2d<double>(x, y);
}
bool sb::Input::isLeftButtonPressed() const {
	int state = glfwGetMouseButton(sb::ptr_sbWindow->getGLFWwindow(), GLFW_MOUSE_BUTTON_LEFT);
	return state == GLFW_PRESS;
}


//singleton
sb::Input* sb::ptr_input = nullptr;
std::unique_ptr<sb::Input> sb::Input::ptr_instance(nullptr);
sb::Input::Input() {
	glfwSetMouseButtonCallback(sb::ptr_sbWindow->getGLFWwindow(), mouseButtonCallback);
}
sb::Input* sb::Input::getInstance() {
	return ptr_instance.get();
}
sb::Input* sb::Input::createInstance() {
	if (ptr_instance == nullptr) {
		ptr_instance.reset(new Input());
		sb::ptr_input = ptr_instance.get();
	}
	return ptr_instance.get();
}