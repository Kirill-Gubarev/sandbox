#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include <utilities/vec2d.hpp>
namespace sb {
	//this class manages the input data
	class Input {
	public:
		void update();
		//mouse
	private:
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	public:
		sb::Vec2d<double> getMousePosition() const;
		bool isLeftButtonPressed() const;


		//singleton pattern
	private:
		static std::unique_ptr<sb::Input> ptr_instance;
		Input();
		Input(const sb::Input&) = delete;
		void operator =(const sb::Input&) = delete;
	public:
		static sb::Input* getInstance();
		static sb::Input* createInstance();
	};
	extern sb::Input* ptr_input;
}

#endif