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

	SDLGameObject * coll = dynamic_cast<SDLGameObject*>(col);
	
	//Declare important object positions
	int bx = m_position.getX();
	int bxw = bx + m_width;
	int by = m_position.getY();
	int byh = by + m_height;
	   	 
	int cx = coll->get_position().getX();
	int cxw = cx + coll->get_width();
	int cy = coll->get_position().getY();
	int cyh = cy + coll->get_height();

	//Insert extra conditions on collisions here:
	//Ball left on coll right:
	if (bx <= cxw && bxw > cxw && (byh - cy) > m_moveValue)
	{
		m_velocity.setX(m_moveValue);
	}
	//Ball right on coll left:
	if (bxw > cx && bx < cx && (byh - cy) > m_moveValue)
	{
		m_velocity.setX(-1 * m_moveValue);
	}
	//Ball top on coll bottom:
	if (by < cyh && byh > cyh && (bxw - cx) > m_moveValue)
	{
		m_velocity.setY(m_moveValue);
	}
	//Ball bottom on coll top:
	if (by < cy && byh > cy && (bxw - cx) > m_moveValue)
	{
		m_velocity.setY(-1 * m_moveValue);
	}
	/*
	if (m_velocity.getX() > 0)
	{
		m_velocity.setX(-2);
	}
	else
	{
		m_velocity.setX(2);
	}
	*/
}


GameObject* BallCreator::createGameObject() const
{
	return new Ball();
}
