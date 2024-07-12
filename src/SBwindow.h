#ifndef SBWINDOW_H
#define SBWINDOW_H

#include "common.h"

namespace sb {
	class SBWindow {

	private:
		GLFWwindow* ptr_glfwWindow;
		int windowWidth, windowHeight;
		void setWindowSize(int windowWidth,int windowHeight);


		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		void changeTheAspectRatio();

		//mouse
	private:
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	public:
		sb::Vec2d getMousePosition();
		bool isLeftButtonPressed();

	public:
		void init();
		GLFWwindow* getGLFWwindow();


		//singleton pattern
	private:
		static std::shared_ptr<sb::SBWindow> ptr_instance;
		SBWindow(int width, int height, const char*);
		SBWindow(const SBWindow &) = delete;
		void operator=(const SBWindow &) = delete;
	public:
		static std::shared_ptr<sb::SBWindow> getInstance();
		static std::shared_ptr<sb::SBWindow> createInstance(int width, int height, const char*);
	};
	typedef std::shared_ptr<sb::SBWindow> PTR_SBWindow;
}
#endif //SBWINDOW_H