#include "MainMenuState.h"
#include "Game.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "TextureManager.h"




std::string MainMenuState::getStateID() const {
	return s_menuID;
}

const std::string MainMenuState::s_menuID = "MAINMENU";

void MainMenuState::update()
{
	for (int i = 0; i < int(m_gameObjects.size()); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MainMenuState::render()
{
	for (int i = 0; i < int(m_gameObjects.size()); i++)
	{
		m_gameObjects[i]->draw();
	}
}

//Loads Textures and objects:
bool MainMenuState::onEnter() {
	
	StateParser stateParser;
	stateParser.parseState("test.xml", s_menuID, &m_gameObjects,
		&m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);
	m_callbacks.push_back(s_menuToMulti);

	setCallbacks(m_callbacks);

	std::cout << "entering MainMenuState\n";

	return true;
}

bool MainMenuState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::getInstance()->
			clearFromTextureMap(m_textureIDList[i]);
	}
	m_textureIDList.clear();

	std::cout << "exiting MainMenuState\n";

	return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//if they are of type Menubutton then assign a callback;
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton =
				dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void MainMenuState::s_menuToPlay()
{
	Game::getInstance()->getStateMachine()->
		loadStateChange(PLAYSTATE, CHANGE);
	std::cout << "Play button clicked \n";
}

void MainMenuState::s_exitFromMenu()
{
	Game::getInstance()->quit();
	std::cout << "Exit button clicked \n";
}

void MainMenuState::s_menuToMulti()
{
	Game::getInstance()->getStateMachine()->
		loadStateChange(MULTISTATE, CHANGE);
	std::cout << "Multi button clicked \n";
}