#ifndef RENDER_H
#define RENDER_H

#include "common.h"
#include "utilities/rgb.h"

namespace sb {
	class Render {
	public:
		void update();
	private:
		void drawTiles();
		void drawArea();
		void setColor(sb::RGB color);

		float areaVertices[8];

		//singleton pattern
	private:
		static std::unique_ptr<sb::Render> ptr_instance;
		Render();
		Render(const Render&) = delete;
		void operator =(const Render&) = delete;
	public:
		static sb::Render* getInstance();
		static sb::Render* createInstance();
	};
	extern sb::Render* ptr_render;
}


#endif //RENDER_H