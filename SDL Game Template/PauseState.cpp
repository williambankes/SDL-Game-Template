#include "PauseState.h"
#include "Game.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "StateParser.h"

const std::string PauseState::s_pauseID = "PAUSE";

std::string PauseState::getStateID() const
{
	return s_pauseID;
}

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("test.xml", s_pauseID, &m_gameObjects,
		&m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_resumePlay);
	m_callbacks.push_back(s_pauseToMain);

	setCallbacks(m_callbacks);

	std::cout << "entering PauseState \n";

	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TextureManager::getInstance()->clearFromTextureMap("resumebutton");
	TextureManager::getInstance()->clearFromTextureMap("mainbutton");

	InputManager::getInstance()->reset();

	std::cout << "exiting PauseState \n";
	return true;
}


void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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


//Button Functionality:
void PauseState::s_resumePlay()
{
	Game::getInstance()->getStateMachine()->
		loadStateChange(NOSTATE, POP);
}

void PauseState::s_pauseToMain()
{
	Game::getInstance()->getStateMachine()->
		loadStateChange(MENUSTATE, CHANGE);
}