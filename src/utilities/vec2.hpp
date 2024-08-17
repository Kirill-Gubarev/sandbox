#ifndef VEC2D_HPP
#define VEC2D_HPP

namespace uts {
	/// this struct stores coordinates
	template <typename T>
	struct Vec2 {
	public:
		//data
		union { T X, width; };
		union { T Y, height; };

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

		//operators
		Vec2 operator+(const Vec2 other) const { return Vec2(X + other.X, Y + other.Y); }
		Vec2 operator-(const Vec2 other) const { return Vec2(X - other.X, Y - other.Y); }
		Vec2 operator*(const Vec2 other) const { return Vec2(X * other.X, Y * other.Y); }
		Vec2 operator/(const Vec2 other) const { return Vec2(X / other.X, Y / other.Y); }

		Vec2 operator+(const T value) const { return Vec2(X + value, Y + value); }
		Vec2 operator-(const T value) const { return Vec2(X - value, Y - value); }
		Vec2 operator*(const T value) const { return Vec2(X * value, Y * value); }
		Vec2 operator/(const T value) const { return Vec2(X / value, Y / value); }

		Vec2& operator+=(const Vec2 other) {
			X += other.X;
			Y += other.Y;
			return *this;
		}
		Vec2& operator-=(const Vec2 other) {
			X -= other.X;
			Y -= other.Y;
			return *this;
		}
		Vec2& operator*=(const Vec2 other) {
			X *= other.X;
			Y *= other.Y;
			return *this;
		}
		Vec2& operator/=(const Vec2 other) {
			X /= other.X;
			Y /= other.Y;
			return *this;
		}
	};
}

#endif //VEC2D_HPP