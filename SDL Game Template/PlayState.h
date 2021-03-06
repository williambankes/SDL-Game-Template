#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "CollisionManager.h"

#include <iostream>
#include <vector>

class PlayState: public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

private:

	static const std::string s_playID;

	CollisionManager collision_manager;

	std::vector<GameObject*> m_gameObjects;
};

