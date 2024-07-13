#ifndef VEC2D_H
#define VEC2D_H

namespace sb {
	template <typename T>
	struct Vec2d {
		T x;
		T y;
		Vec2d() :x(0), y(0) {}
		Vec2d(const T x, const  T y) :x(x), y(y) {}

		template <typename U>
		operator Vec2d<U>(){
			return Vec2d<U>(x,y);
		}
		
	};
}
#endif //VEC2D_H