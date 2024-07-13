#ifndef AREA_H
#define AREA_H

#include "../common.h"
#include "../tile.h"

namespace sb {
	class Area {
	private:
		int width;
		int height;
		sb::Tile** ptr_tileArray;
	public:
		int getWidth();
		int getHeight();
		sb::Tile*& getTile(int x, int y);
		void update();
		void swap(int x1, int y1, int x2, int y2);

		~Area();
		//singleton pattern
	private:
		static std::shared_ptr<sb::Area> ptr_instance;
	public:
		Area(int width, int height);
		Area(const Area&) = delete;
		void operator =(const Area&) = delete;
		static std::shared_ptr<sb::Area> getInstance();
		static std::shared_ptr<sb::Area> createInstance(int width, int height);
	}; 
	typedef std::shared_ptr<sb::Area> PTR_Area;
}

#endif //AREA_H