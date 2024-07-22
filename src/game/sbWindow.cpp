#include "game/sbWindow.h"
#include "game/render.h"
#include "area/area.h"


//data
GLFWwindow* sb::SBWindow::ptr_GLFWwindow = nullptr;
int sb::SBWindow::width = 0;
int sb::SBWindow::height = 0;
bool sb::SBWindow::windowOpen = false;

//managing this class
void sb::SBWindow::init(int width, int height, const char* title){
	sb::SBWindow::width = width;
	sb::SBWindow::height = height;

	if (!glfwInit()) 
		throw std::exception("failed to init glfw");

	ptr_GLFWwindow = glfwCreateWindow(width, height, title, NULL, NULL);

	if (ptr_GLFWwindow == nullptr){
		glfwTerminate();
		throw std::exception("failed to create a window");
	}
	glfwMakeContextCurrent(ptr_GLFWwindow);
	windowOpen = true;

	//setting output area
	sb::Render::changeOutputArea();

	//setting callbacks
	glfwSetWindowSizeCallback(ptr_GLFWwindow, windowSizeCallback);
	glfwSetWindowCloseCallback(ptr_GLFWwindow, windowCloseCallback);
}
void sb::SBWindow::terminate(){

}

//getters
int sb::SBWindow::getWidth(){
	return width;
}
int sb::SBWindow::getHeight(){
	return height;
}
GLFWwindow* sb::SBWindow::getGLFWwindow(){
	return ptr_GLFWwindow;
}
bool sb::SBWindow::isWindowOpen(){
	return windowOpen;
}

//window
void sb::SBWindow::setWindowSize(int width, int height){
	sb::SBWindow::width = width;
	sb::SBWindow::height = height;
}


//callbacks
void sb::SBWindow::windowSizeCallback(GLFWwindow* window, int width, int height){
	setWindowSize(width, height);
	sb::Render::changeOutputArea();
}
void sb::SBWindow::windowCloseCallback(GLFWwindow* window){
	windowOpen = false;
}