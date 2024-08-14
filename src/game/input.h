#ifndef INPUT_H
#define INPUT_H

#include "common.h"

namespace sb {
	/// this class manages the input data
	class Input {
	public:
		//an object of this class cannot be created
		Input() = delete;
		Input(const Input&) = delete;
		void operator =(const Input&) = delete;

		//managing this class
		static void init();
		static void terminate();
		static void update();

		//mouse
		static uts::Vec2<double> getMousePosition();
		//is the left mouse button pressed
		static bool isLBPressed();
		//is the right mouse button pressed
		static bool isRBPressed();
	private:
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};
}

#endif //INPUT_H