#include "SBWindow.h"


void sb::SBwindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
	changeTheAspectRatio(width,height);
}
void sb::SBwindow::changeTheAspectRatio(int width,int height) {
	glViewport(0, 0, width, height);
	glLoadIdentity();
	float k = (float)width / (float)height;
	glOrtho(-k, k, -1, 1, -1, 1);
}

GLFWwindow* sb::SBwindow::getGLFWwindow() {
	return ptr_glfwWindow;
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
	changeTheAspectRatio(width, height);
	glfwSetWindowSizeCallback(ptr_glfwWindow, windowSizeCallback);
}

std::shared_ptr<sb::SBwindow> sb::SBwindow::createWindow(int width, int height, const char* title) {
	if (ptr_instance == nullptr) {
		std::shared_ptr<sb::SBwindow> temp(new SBwindow(width,height,title));
		ptr_instance.swap(temp);
	}
	return ptr_instance;
}

std::shared_ptr<sb::SBwindow> sb::SBwindow::getInstance() {
	return ptr_instance;
}