#ifndef GAME_H
#define GAME_H

#include "common.h"

namespace sb {
	/// this class manages the main game logic
	class Game {
	private:
		//data
		static const double frameDuration;// 1.0 / 60.0 is 60 FPS
		//but for some reason it turns out to be 66. 
		//I don't know how to fix it yet.

	public:
		//an object of this class cannot be created
		Game() = delete;
		Game(const Game&) = delete;
		void operator =(const Game&) = delete;

		//managing this class
		static void init();
		static void terminate();
		static void mainLoop();
	};
}

#endif //GAME_H