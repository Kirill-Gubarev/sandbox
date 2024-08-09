#ifndef RENDER_H
#define RENDER_H


#include "common.h"
#include "utilities/rgb.h"
#include "utilities/vec2d.hpp"
#include "game/GUI.h"


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
		static void drawGameArea();
		static void drawElement(const sb::GUI::Element* ptr_element);
		static void setColor(sb::RGB color);

		static sb::Vec2d<int> getAreaBottomLeft();
		static sb::Vec2d<int> getAreaTopRight();

		static void updateOutputArea();
	};
}


#endif //RENDER_H