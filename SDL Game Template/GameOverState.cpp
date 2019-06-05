#include "GameOverState.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "Game.h"
#include "StateParser.h"


const std::string GameOverState::s_overID = "OVER";

std::string GameOverState::getStateID() const {
	return s_overID;
}

void GameOverState::update() {

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onEnter()
{
	StateParser stateParser;

	stateParser.parseState("test.xml", s_overID, &m_gameObjects,
		&m_textureIDList);

	//Set button callback
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_overtoMain);

	setCallbacks(m_callbacks);

	std::cout << "entering GameOverState\n";

	return true;
}

bool GameOverState::onExit() {
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

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton =
				dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

//Button Functionality:

void GameOverState::s_overtoMain()
{
	Game::getInstance()->getStateMachine()->
		loadStateChange(MAINMENU, CHANGE);
}