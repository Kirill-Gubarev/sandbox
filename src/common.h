#ifndef COMMON_H
#define COMMON_H

#pragma comment (lib, "opengl32.lib")
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <exception>
#include <stdint.h>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <string>
#include <vector>
#include <limits>

#include "utilities/rgb.h"
#include "utilities/vec2.hpp"

namespace sb {
	void init();
	void run();
	void terminate();

	//exit the program in case of an error
	void exitProgram(std::exception& ex);
}

#endif //COMMON_H