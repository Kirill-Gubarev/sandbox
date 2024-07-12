#ifndef GAME_H
#define GAME_H

#include "../common.h"

namespace sb {
	class Game {
	private:
		void drawTiles();
	public:
		void mainLoop();

		//singleton pattern
	private:
		static std::shared_ptr<sb::Game> ptr_instance;
	public:
		Game();
		Game(const Game&) = delete;
		void operator =(const Game&) = delete;
		static std::shared_ptr<sb::Game> getInstance();
		static std::shared_ptr<sb::Game> createInstance();
	};
	typedef std::shared_ptr<sb::Game> PTR_Game;
}

#endif //GAME_H