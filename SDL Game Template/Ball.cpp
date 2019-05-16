#include "Ball.h"



Ball::Ball() : SDLGameObject() {}

void Ball::draw()
{
	SDLGameObject:: draw();
}


void Ball::update()
{
	//collision code goes here:
	SDLGameObject::update();
}

void Ball::clean() {}

void Ball::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}


GameObject* BallCreator::createGameObject() const
{
	return new Ball();
}
