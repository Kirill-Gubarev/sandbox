#ifndef RENDER_H
#define RENDER_H

#include "common.h"
#include "GUI/GUI.h"

namespace sb {
	/// this class renders the game
	class Render {
	private:
		//data
		static float areaVertices[8];
		static float squareVertices[8];

		//Bottom left corner of the output area
		static uts::Vec2<int> areaBottomLeft;
		//Top right corner of the output area
		static uts::Vec2<int> areaTopRight;
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
		static void drawElement(const gui::GUI::Element* ptr_element);
		static void setColor(uts::RGB color);

		static uts::Vec2<int> getAreaBottomLeft();
		static uts::Vec2<int> getAreaTopRight();

		static void updateOutputArea();
	};
}

#endif //RENDER_H