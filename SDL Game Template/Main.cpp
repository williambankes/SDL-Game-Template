#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = int(1000.0f / FPS);

int main(int argc, char* argv[]) {

	Uint32 frameStart, frameTime;

	std::cout << "game init attempt ..." << std::endl;

	if (Game::getInstance()->init("Pong", 100, 100, 640, 480, false))
	{
		std::cout << "game init success!" << std::endl;
		while (Game::getInstance()->running())
		{
			frameStart = SDL_GetTicks();

			Game::getInstance()->handleEvents();
			Game::getInstance()->update();
			Game::getInstance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)DELAY_TIME - frameTime);
			}
		}
	}
	else {
		std::cout << "game init failure: " << SDL_GetError() << std::endl;
		return -1;
	}

	std::cout << "game closing ..." << std::endl;
	Game::getInstance()->clean();
	return 0;
}

