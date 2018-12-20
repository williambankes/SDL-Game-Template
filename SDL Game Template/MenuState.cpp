#pragma once
#include "MenuState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "PlayState.h"


std::string MenuState::getStateID() const {
	return s_menuID;
}

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() 
{
	for (int i = 0; i < int(m_gameObjects.size()); i++)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render() 
{
	for (int i = 0; i < int(m_gameObjects.size()); i++)
	{
		m_gameObjects[i]->draw();
	}
}

//Loads Textures and objects:
bool MenuState::onEnter() {	

	if (!TextureManager::getInstance()->load("assets/play.png",
		"playbutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}
	if (!TextureManager::getInstance()->load("assets/exit.png",
		"exitbutton", Game::getInstance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(
		new LoaderParams(100, 100, 200, 100, "playbutton"),s_menuToPlay);
	GameObject* button2 = new MenuButton(
		new LoaderParams(100, 300, 200, 100, "exitbutton"),s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering MenuState \n";
	return true;
}

bool MenuState::onExit() {

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TextureManager::getInstance()->clearFromTextureMap("playbutton");
	TextureManager::getInstance()->clearFromTextureMap("exitbutton");

	std::cout << "Exiting MenuState \n";
	return true;
}

void MenuState::s_menuToPlay()
{	
	Game::getInstance()->getInstance()->getStateMachine()->
		loadStateChange(PLAYSTATE, CHANGE);
	std::cout << "Play button clicked \n";
}

void MenuState::s_exitFromMenu()
{
	Game::getInstance()->quit();
	std::cout << "Exit button clicked \n";
}