#ifndef AREA_H
#define AREA_H

#include "common.h"
#include "area/tile.h"

namespace sb {
	/// this class manages the game area
	class Area {

	private:
		//data
		static int width;
		static int height;
		static sb::Tile* ptr_tileArray;

	public:
		//an object of this class cannot be created
		Area() = delete;
		Area(const Area&) = delete;
		void operator =(const Area&) = delete;

		//managing this class
		static void init(int width, int height);
		static void terminate();
		static void update();

		//getters
		static int getWidth();
		static int getHeight();
		static sb::Tile& getTile(int x, int y);

		//tiles management
		static void setTile(int x, int y, sb::Tile newTile);
		static void swapTile(int x1, int y1, int x2, int y2);
		static void resetTilesSleepNearby(int x, int y);

		//mouse press
		static void setTileMouseLB();
		static void setTileMouseRB();

		//coordinate management
		static uts::Vec2<int> convertMousePosToAreaPos(uts::Vec2<double> pos);
		static bool isInsideTheArea(uts::Vec2<int> pos);
		static bool isInsideTheArea(int x, int y);

	private:
		//TILE STATUS UPDATES
		static void tileUpdate(Tile& t);
		//			emptyUpdate();
		//			stoneUpdate();
		static void sandUpdate(Tile& t);
		static void waterUpdate(Tile& t);
	};
}

#endif //AREA_H