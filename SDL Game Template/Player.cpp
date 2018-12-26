#include "Player.h"
#include "InputManager.h"

Player::Player() : SDLGameObject() {}


void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	handleInputs();
	SDLGameObject::update();
}

void Player::handleInputs()
{
	Vector2D* target = InputManager::getInstance()->getMousePosition();

	m_velocity = *target - m_position;

	m_velocity /= 50;
}

void Player::clean() {}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);
}