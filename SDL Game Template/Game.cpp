#pragma once
#include "Game.h"

//GameObjects:
#include "GameObjectFactory.h"
#include "MenuButton.h"

//GameStates:
#include "PlayState.h"
#include "MenuState.h"

//Managers:
#include "InputManager.h"


bool Game::init(const char* title,
	int xpos, int ypos,
	int height, int width,
	int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		std::cout << "SDL_Init successful" << std::endl;

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (m_pWindow != 0) {
			std::cout << "SDL_CreateWindow successful" << std::endl;

			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) {
				std::cout << "SDL_CreateRenderer successful" << std::endl;

				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
				
			}
			else {
				std::cout << "SDL_CreateRenderer failed" << std::endl;
				return false;
			}
		}
		else {
			std::cout << "SDL_CreateWindow failed" << std::endl;
			return false;
		}

	}
	else {
		std::cout << "SDL_Init failed" << std::endl;
	}
		
	//Register 
	GameObjectFactory::getInstance()->
		registerType("MenuButton", new MenuButtonCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->loadStateChange(MENUSTATE, CHANGE);

	m_brunning = true;
	
	return true;
}


void Game::render() {
	SDL_RenderClear(m_pRenderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {

	//Add class clean functions here:
	InputManager::getInstance()->clean();
	
	//clean the base game class:
	std::cout << "Cleaning Game" << std::endl;
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents() {
	
	InputManager::getInstance()->update();
}

void Game::update() {
		
	if (!InputManager::getInstance()->getRunning())
	{
		m_brunning = false;
	}
	m_pGameStateMachine->update();
}

void Game::quit() {
	m_brunning = false;
}

GameStateMachine* Game::getStateMachine()
{
	return m_pGameStateMachine;
}


//Singleton Implementation:

Game* Game::s_pInstance = 0;

Game::Game() {}

Game* Game::getInstance() {
	if (s_pInstance == 0)
	{
		s_pInstance = new Game();
		return s_pInstance;
	}

	return s_pInstance;
}