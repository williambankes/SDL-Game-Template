#pragma once
#include "GameObject.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject
{
public:

	void draw();
	void update();
	void handleInputs();
	void clean();

	void load(const LoaderParams* pParams);

	Player();
};

class PlayerCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const;
};