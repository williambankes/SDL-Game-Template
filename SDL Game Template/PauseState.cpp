#include "PauseState.h"
#include "Game.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "InputHandler.h"

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

	if (!TextureManager::getInstance()->load("assets/resume.png",
		"resumebutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	if (!TextureManager::getInstance()->load("assets/mainmenu.png",
		"mainbutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(100, 100,
		200,100, "resumebutton"), s_resumePlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 300,
		200, 100, "mainbutton"), s_pauseToMain);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

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

	InputHandler::getInstance()->reset();

	std::cout << "exiting PauseState \n";
	return true;
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