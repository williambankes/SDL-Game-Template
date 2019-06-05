#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "MenuState.h"

#include <iostream>
#include <vector>

class GameOverState : public MenuState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_overtoMain();

	static const std::string s_overID;
	
	std::vector<GameObject*> m_gameObjects;

};

