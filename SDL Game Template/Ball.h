#pragma once
#include "GameObject.h"
#include "GameObjectFactory.h"

class Ball : public SDLGameObject
{
public:
	void draw();
	void update();
	void clean();

	void load(const LoaderParams* pParams);

	Ball();

};

class BallCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const;
};
