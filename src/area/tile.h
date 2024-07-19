#ifndef TILE_H
#define TILE_H


#include "common.h"
#include "utilities/rgb.h"


namespace sb {
	/// <summary>
	/// the main unit
	/// </summary>
	struct Tile {

	public:
		//the type of this class
		enum class Type : std::uint32_t { 
			empty,
			stone,
			sand,
			water
		};

		//data
		Type type;
		sb::RGB color;
		//if the tile is sleeping, then update is not called for it
		bool sleep;
		//if the tile has been updated, don't need to do it twice
		bool hasBeenUpdated;
		//dense particles sink to the bottom (kg / m^3)
		float density;

		//constructors
		Tile();
		Tile(Type type);

		//getters
		bool isEmpty() const;
		bool isNotEmpty() const;
		bool isTheDensityLess(float density);
		bool isTheDensityGreater(float density);
	};
}


#endif //TILE_H