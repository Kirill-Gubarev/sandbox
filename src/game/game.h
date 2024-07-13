#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "utilities/rgb.h"

namespace sb {
	//this class manages the main game logic
	class Game {
	private:
		void drawTiles();
		void setColor(sb::RGB color);
	public:
		void mainLoop();


		//singleton pattern
	private:
		static std::unique_ptr<sb::Game> ptr_instance;
		Game();
		Game(const Game&) = delete;
		void operator =(const Game&) = delete;
	public:
		static sb::Game* getInstance();
		static sb::Game* createInstance();
	};
	extern sb::Game* ptr_game;
}

#endif //GAME_H