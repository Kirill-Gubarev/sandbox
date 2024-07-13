#ifndef SBWINDOW_H
#define SBWINDOW_H

#include "common.h"
#include "utilities/vec2d.hpp"
namespace sb {
	//this class is the wrapper for GLFWwindow
	class SBWindow {

	private:
		GLFWwindow* ptr_glfwWindow;

		//Bottom left corner of the area
		sb::Vec2d<int> areaBottomLeft;
		//Top right corner of the area
		sb::Vec2d<int> areaTopRight;

		int width;
		int height;
		void setWindowSize(int width, int height);
	public:
		int getWidth() const;
		int getHeight() const;
		sb::Vec2d<int> getAreaBottomLeft() const;
		sb::Vec2d<int> getAreaTopRight() const;
		GLFWwindow* getGLFWwindow() const;
	private:
		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		void changeOutputArea();


		//singleton
	private:
		static std::unique_ptr<sb::SBWindow> ptr_instance;
		SBWindow(int width, int height, const char*);
		SBWindow(const SBWindow&) = delete;
		void operator=(const SBWindow&) = delete;
	public:
		static sb::SBWindow* getInstance();
		static sb::SBWindow* createInstance(int width, int height, const char*);
	};
	extern sb::SBWindow* ptr_sbWindow;
}
#endif //SBWINDOW_H