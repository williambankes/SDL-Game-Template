#include "Ball.h"
#include "Game.h"


Ball::Ball() : SDLGameObject() {}

void Ball::draw()
{
	SDLGameObject:: draw();
}


void Ball::update()
{	
	//Edge collision logic:

	//Top and bottom:
	if (m_position.getY() < 0) {
		m_velocity.setY(2);
	}
	if (m_position.getY() > 768 - m_height) {
		m_velocity.setY(-2);
	}

	//Left and right:

	if (m_position.getX() < 0) {
		Game::getInstance()->getStateMachine()->loadStateChange(GAMEOVERSTATE, CHANGE);
	}
	if (m_position.getX() > 1366 - m_width) {
		Game::getInstance()->getStateMachine()->loadStateChange(GAMEOVERSTATE, CHANGE);
	}

	//collision code goes here:
	SDLGameObject::update();
}

void Ball::clean() {}

void Ball::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
	m_velocity.setX(2);
	m_velocity.setY(2);
}

void Ball::oncollision(GameObject* col)
{
	std::cout << "entered correct" << std::endl;

	//check edges 
	//if(m_position.getX() > col->get_position().getX())


	if (m_velocity.getX() > 0)
	{
		m_velocity.setX(-2);
	}
	else
	{
		m_velocity.setX(2);
	}
}


GameObject* BallCreator::createGameObject() const
{
	return new Ball();
}
