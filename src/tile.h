#ifndef TILE_H
#define TILE_H

#include "common.h"
#include "utilities/rgb.h"
namespace sb {

	//the main unit
	class Tile {
	public:
		bool sleep;
		Tile();
		virtual void update(std::uint32_t x, std::uint32_t y) = 0;
		virtual sb::RGB getColor() const = 0;
	};

	class Sand : public Tile {
	public:
		Sand();
		void update(std::uint32_t x, std::uint32_t y) override;
		sb::RGB getColor() const override;
	};

	class Stone : public Tile {
	public:
		Stone();
		void update(std::uint32_t x, std::uint32_t y) override;
		sb::RGB getColor() const  override;
	};

}

#endif //TILE_H