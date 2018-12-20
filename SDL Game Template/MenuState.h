#pragma once
#include "GameState.h"

#include <iostream>
#include <vector>

//Forward declaration of classes:
class GameObject;
class SDLGameObject;

class MenuState: public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

private:

	static const std::string s_menuID;
	std::vector<GameObject*> m_gameObjects;

	//Button Functionality:
	static void s_menuToPlay();
	static void s_exitFromMenu();
};