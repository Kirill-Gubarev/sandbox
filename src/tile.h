#ifndef TILE_H
#define TILE_H

#include "common.h"

namespace sb {
	class Tile {
	public:
		virtual void update() = 0;
		virtual void setColor() = 0;
	};
	class Sand : public Tile {
	public:
		void update() override;
		void setColor() override;
	};
}

#endif //TILE_H