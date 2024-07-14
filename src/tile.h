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
			sand,
			stone
		};
		Type type;
		sb::RGB color;
		//if the tile is sleeping, then update is not called for it
		bool sleep;

		Tile();
		Tile(Type type);

		sb::RGB getColor() const;
		bool isEmpty() const;
		bool isNotEmpty() const;
		void update(int x, int y);


		//STATUS UPDATES
	private:
		//   emptyUpdate();
		void sandUpdate(int x, int y);
		//	 stoneUpdate();
	};
}

#endif //TILE_H