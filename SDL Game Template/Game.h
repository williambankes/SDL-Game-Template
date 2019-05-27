#pragma once
#include "SDL.h"
#include "GameStateMachine.h"

#include <vector>
#include <iostream>

class Game
{

public:
		
	static Game* getInstance();


	//Game functions:
	bool init(const char* title, 
		int xpos, int ypos,
		int height, int width,
		int flags);

	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();
	
	GameStateMachine* getStateMachine();

	SDL_Renderer* getRenderer() const {return m_pRenderer; }
	bool running() { return m_brunning; }

	

private:

	bool m_brunning;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	SDL_Texture* m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;
	
	GameStateMachine* m_pGameStateMachine;

	
	//Singleton Implementation:
	Game();
	static Game* s_pInstance;
};

