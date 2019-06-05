#include "MultiState.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "StateParser.h"


const std::string MultiState::s_multiID = "MULTI";

std::string MultiState::getStateID() const {
	return s_multiID;
}

void MultiState::update() {

	if (InputManager::getInstance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::getInstance()->getStateMachine()->
			loadStateChange(PAUSESTATE, PUSH);
	}
	
	collision_Manager.collisionDetection(m_gameObjects);

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MultiState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool MultiState::onEnter()
{
	StateParser stateParser;

	stateParser.parseState("test.xml", s_multiID, &m_gameObjects,
		&m_textureIDList);

	std::cout << "entering MultiState\n";

	return true;
}

bool MultiState::onExit() {
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

	std::cout << "exiting GameOverState\n";

	return true;
}
