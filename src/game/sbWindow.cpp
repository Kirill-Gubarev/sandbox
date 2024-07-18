#include "game/SBWindow.h"
#include "area/area.h"


//data
GLFWwindow* sb::SBWindow::ptr_GLFWwindow = nullptr;
int sb::SBWindow::width = 0;
int sb::SBWindow::height = 0;
//Bottom left corner of the output area
sb::Vec2d<int> sb::SBWindow::areaBottomLeft = sb::Vec2d<int>();
//Top right corner of the output area
sb::Vec2d<int> sb::SBWindow::areaTopRight = sb::Vec2d<int>();
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
	changeOutputArea();

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
sb::Vec2d<int> sb::SBWindow::getAreaBottomLeft(){
	return areaBottomLeft;
}
sb::Vec2d<int> sb::SBWindow::getAreaTopRight(){
	return areaTopRight;
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
void sb::SBWindow::changeOutputArea(){

	float numberTilesWidth = sb::Area::getWidth();
	float numberTilesHeight = sb::Area::getHeight();

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

//callbacks
void sb::SBWindow::windowSizeCallback(GLFWwindow* window, int width, int height){
	setWindowSize(width, height);
	changeOutputArea();
}
void sb::SBWindow::windowCloseCallback(GLFWwindow* window){
	windowOpen = false;
}