#ifndef VEC2D_HPP
#define VEC2D_HPP

#include "common.h"

namespace sb {
	template <typename T>
	//this struct stores coordinates
	struct Vec2d {
		T x;
		T y;
		Vec2d() :x(0), y(0) {}
		Vec2d(const T x, const  T y) :x(x), y(y) {}
		template <typename U>
		Vec2d(Vec2d<U> vec) : x(vec.x), y(vec.y) {}

		template <typename U>
		operator Vec2d<U>() {
			return Vec2d<U>(x, y);
		}

	};
}
#endif //VEC2D_HPP