#ifndef RENDER_H
#define RENDER_H


#include "common.h"
#include "utilities/rgb.h"
#include "utilities/vec2d.hpp"


namespace sb {
	/// <summary>
	/// this class renders the game
	/// </summary>
	class Render {
	private:
		//data
		static float areaVertices[8];
		static float squareVertices[8];

		//Bottom left corner of the output area
		static sb::Vec2d<int> areaBottomLeft;
		//Top right corner of the output area
		static sb::Vec2d<int> areaTopRight;
	public:
		//an object of this class cannot be created
		Render() = delete;
		Render(const Render&) = delete;
		void operator =(const Render&) = delete;

		//managing this class
		static void init();
		static void terminate();
		static void update();

		//drawing
		static void drawTiles();
		static void drawArea();
		static void setColor(sb::RGB color);

		static sb::Vec2d<int> getAreaBottomLeft();
		static sb::Vec2d<int> getAreaTopRight();

		static void changeOutputArea();
		static void changeOutputArea2();
	};
}


#endif //RENDER_H