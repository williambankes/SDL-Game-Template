#include "PlayState.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Game.h"

const std::string PlayState::s_playID = "PLAY";

std::string PlayState::getStateID() const {
	return s_playID;
}

void PlayState::update() 
{
	if (InputManager::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::getInstance()->getStateMachine()->
			loadStateChange(PAUSESTATE, PUSH);
	}
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}	
}

void PlayState::render() 
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TextureManager::getInstance()->load("assets/paddle-anim.bmp",
		"paddle", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	GameObject* player = new Player(new LoaderParams(100, 100, 50, 50,
		"paddle"));

	m_gameObjects.push_back(player);

	std::cout << "entering PlayState \n";
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	
	m_gameObjects.clear();
	TextureManager::getInstance()->clearFromTextureMap("helicopter");

	std::cout << "exiting PlayState \n";
	return false;
}
