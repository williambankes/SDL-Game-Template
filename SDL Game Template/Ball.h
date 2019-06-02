#pragma once
#include "GameObject.h"
#include "GameObjectFactory.h"
#include <SDL.h>

class Ball : public SDLGameObject
{
public:
	void draw();
	void update();
	void clean();

	void load(const LoaderParams* pParams);

	void oncollision(GameObject* col);

	Ball();


};

class BallCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const;
};
