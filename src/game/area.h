#ifndef AREA_H
#define AREA_H

#include "common.h"
#include "tile.h"
#include "utilities/vec2d.hpp"

namespace sb {
	//this class manages the game area
	class Area {
		//basic game logic
	public:
		void mouseLeftButtonSetTile();
		void mouseRightButtonSetTile();
		void setTile(int x, int y,sb::Tile newTile);
		void tileSwap(int x1, int y1, int x2, int y2);
		void update();
		sb::Vec2d<int> convertMousePosToAreaPos(sb::Vec2d<double> pos) const;
		sb::Tile& getTile(int x, int y) const;

		bool isInsideTheArea(sb::Vec2d<int> pos) const;
		bool isInsideTheArea(int x, int y) const;

		void resetTilesSleepNearby(int x,int y);
		//data
	private:
		int width;
		int height;
		sb::Tile* ptr_tileArray;
	public:
		int getWidth() const;
		int getHeight() const;

		~Area();


		//singleton pattern
	private:
		static std::unique_ptr<sb::Area> ptr_instance;
		Area(int width, int height);
		Area(const Area&) = delete;
		void operator =(const Area&) = delete;
	public:
		static sb::Area* getInstance();
		static sb::Area* createInstance(int width, int height);
	};
	extern  sb::Area* ptr_area;
}

#endif //AREA_H