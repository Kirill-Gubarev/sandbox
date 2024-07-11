#include "common.h"
#include "SBwindow.h"
#include "game.h"
int main(int argc, char* argv[]) {

	try {
		sb::PTR_Game game = sb::Game::createGame();
		game.get()->mainLoop();
	}
	catch (std::exception& ex)
	{
		std::cerr << "EXCEPTION: " << ex.what() << std::endl;
	}

	system("pause");
	return 0;
}

