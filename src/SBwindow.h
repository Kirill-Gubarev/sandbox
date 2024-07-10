#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <memory>
#pragma comment (lib, "opengl32.lib")
#include <GLFW/glfw3.h>
namespace sb {
	class SBwindow {

	private:
		GLFWwindow* ptr_glfwWindow;
		static void windowSizeCallback(GLFWwindow* window, int width, int height);
		static void changeTheAspectRatio(int width, int height);
	public:
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