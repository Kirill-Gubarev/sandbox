#ifndef VEC2D_HPP
#define VEC2D_HPP


#include "common.h"


namespace sb {
	/// <summary>
	/// this struct stores coordinates
	/// </summary>
	template <typename T>
	struct Vec2d {

	public:
		//data
		T x, y;
		
		//constructors
		Vec2d() :x(0), y(0) {}
		Vec2d(const T x, const  T y) :x(x), y(y) {}

		//type conversion constructor
		template <typename U>
		Vec2d(Vec2d<U> vec) : x(vec.x), y(vec.y) {}

		//type conversion
		template <typename U>
		operator Vec2d<U>() {
			return Vec2d<U>(x, y);
		}
	};
}


#endif //VEC2D_HPP