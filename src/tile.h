#ifndef TILE_H
#define TILE_H

#include "common.h"

namespace sb {

	class Tile {
	public:
		bool sleep;
		Tile();
		virtual void update(std::uint32_t x, std::uint32_t y) = 0;
		virtual void setColor() = 0;
	};

	class Sand : public Tile {
	public:
		Sand();
		void update(std::uint32_t x, std::uint32_t y) override;
		void setColor() override;
	};

	class Stone : public Tile {
	public:
		Stone();
		void update(std::uint32_t x, std::uint32_t y) override;
		void setColor() override;
	};

}

#endif //TILE_H