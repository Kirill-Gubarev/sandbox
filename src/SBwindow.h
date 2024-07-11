#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"

namespace sb {
	class SBwindow {

	private:
		GLFWwindow* ptr_glfwWindow;
		int windowWidth, windowHeight;
		void setWindowSize(int windowWidth,int windowHeight);
		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		void changeTheAspectRatio();
	public:
		void init();
		GLFWwindow* getGLFWwindow();


		//singleton pattern
	private:
		static std::shared_ptr<sb::SBwindow> ptr_instance;
		SBwindow(int width, int height, const char*);
		SBwindow(const SBwindow &) = delete;
		void operator=(const SBwindow &) = delete;
	public:
		static std::shared_ptr<sb::SBwindow> getInstance();
		static std::shared_ptr<sb::SBwindow> createWindow(int width, int height, const char*);
	};
	typedef std::shared_ptr<sb::SBwindow> PTR_SBWindow;
}
#endif //WINDOW_H