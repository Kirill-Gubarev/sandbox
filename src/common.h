#ifndef COMMON_H
#define COMMON_H

#pragma comment (lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <exception>
#include <stdint.h>

#include "vec2d.hpp"

namespace sb {
	void init();
	void start();
}


#endif //COMMON_H
