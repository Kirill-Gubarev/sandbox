#ifndef AREA_H
#define AREA_H

#include "../common.h"
#include "../tile.h"

namespace sb {
	class Area {
	private:
		std::uint32_t width;
		std::uint32_t height;
		sb::Tile** ptr_tileArray;
	public:
		std::uint32_t getWidth();
		std::uint32_t getHeight();
		sb::Tile*& getTile(std::uint32_t x, std::uint32_t y);
		void update();
		void swap(std::uint32_t x1, std::uint32_t y1, std::uint32_t x2, std::uint32_t y2);

		~Area();
		//singleton pattern
	private:
		static std::shared_ptr<sb::Area> ptr_instance;
	public:
		Area(std::uint32_t width, std::uint32_t height);
		Area(const Area&) = delete;
		void operator =(const Area&) = delete;
		static std::shared_ptr<sb::Area> getInstance();
		static std::shared_ptr<sb::Area> createInstance(std::uint32_t width, std::uint32_t height);
	}; 
	typedef std::shared_ptr<sb::Area> PTR_Area;
}

#endif //AREA_H