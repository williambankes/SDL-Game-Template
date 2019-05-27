#include "PlayState.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Game.h"
#include "Player.h"
#include "StateParser.h"

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

	collision_manager.collisionDetection(m_gameObjects);

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
	StateParser stateParser;

	stateParser.parseState("test.xml", s_playID, &m_gameObjects,
		&m_textureIDList);

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
	

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		TextureManager::getInstance()->
			clearFromTextureMap(m_textureIDList[i]);
	}

	m_textureIDList.clear();

	std::cout << "exiting PlayState \n";
	return false;
}
