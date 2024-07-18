#ifndef TILE_H
#define TILE_H


#include "common.h"
#include "utilities/rgb.h"


namespace sb {
	//the main unit
	struct Tile {
	public:
		enum class Type : std::uint32_t{
			empty,
			stone,
			sand,
			water
		};

		Type type;
		bool isEmpty() const;
		bool isNotEmpty() const;

		sb::RGB color;

		//if the tile is sleeping, then update is not called for it
		bool sleep;
		void resetSleep();

		//if the tile has been updated, don't need to do it twice
		bool hasBeenUpdated;
		void resetUpdate();

		//dense particles sink to the bottom
		float density; //kg / m^3
		bool isTheDensityLess(float density);
		bool isTheDensityGreater(float density);

		void swap();

		Tile();
		Tile(Type type);
		void update(int x, int y);


		//STATUS UPDATES
	private:
		//   emptyUpdate();
		//	 stoneUpdate();
		void sandUpdate(int x, int y);
		void waterUpdate(int x, int y);
	};
}


#endif //TILE_H