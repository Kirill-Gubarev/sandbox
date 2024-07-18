#ifndef RENDER_H
#define RENDER_H


#include "common.h"
#include "utilities/rgb.h"


namespace sb {
	/// <summary>
	/// this class renders the game
	/// </summary>
	class Render {
	private:
		//data
		static float areaVertices[8];

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
	};
}


#endif //RENDER_H