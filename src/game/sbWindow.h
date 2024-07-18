#ifndef SBWINDOW_H
#define SBWINDOW_H


#include "common.h"
#include "utilities/vec2d.hpp"


namespace sb {
	/// <summary>
	/// this class is the wrapper for GLFWwindow
	/// </summary>
	class SBWindow {

		//data
	private:
		static GLFWwindow* ptr_GLFWwindow;
		static int width;
		static int height;
		//Bottom left corner of the output area
		static sb::Vec2d<int> areaBottomLeft;
		//Top right corner of the output area
		static sb::Vec2d<int> areaTopRight;
		static bool windowOpen;

	public:
		//an object of this class cannot be created
		SBWindow() = delete;
		SBWindow(const SBWindow&) = delete;
		void operator =(const SBWindow&) = delete;

		//managing this class
		static void init(int width, int height, const char* title);
		static void terminate();

		//getters
		static int getWidth();
		static int getHeight();
		static sb::Vec2d<int> getAreaBottomLeft();
		static sb::Vec2d<int> getAreaTopRight();
		static GLFWwindow* getGLFWwindow();
		static bool isWindowOpen();

	private:
		//window
		static void setWindowSize(int width, int height);
		static void changeOutputArea();

		//callbacks
		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		static void windowCloseCallback(GLFWwindow* window);
	};
}


#endif //SBWINDOW_H