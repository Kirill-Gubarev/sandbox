#ifndef VEC2D_HPP
#define VEC2D_HPP

namespace uts {
	/// this struct stores coordinates
	template <typename T>
	struct Vec2 {
	public:
		//data
		T X, Y;
		
		//constructors
		Vec2() :X(0), Y(0) {}
		Vec2(const T x, const  T y) :X(x), Y(y) {}

		//type conversion constructor
		template <typename U>
		Vec2(Vec2<U> vec) : X(vec.X), Y(vec.Y) {}

		//type conversion
		template <typename U>
		operator Vec2<U>() {
			return Vec2<U>(X, Y);
		}
	};
}

#endif //VEC2D_HPP