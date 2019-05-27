#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "CollisionManager.h"

#include <iostream>
#include <vector>


class MultiState: public GameState
{
public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const;

private:

	static const std::string s_multiID;

	CollisionManager collision_Manager;

	std::vector<GameObject*> m_gameObjects;
};

