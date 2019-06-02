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

	//Screen collisions
	if (m_velocity.getY() < 0 && m_position.getY() < 0) {
		m_velocity.setY(0);
	}
	if (m_velocity.getY() > 0 && (m_position.getY() + m_height) > 768) {
		m_velocity.setY(0);
	}

	SDLGameObject::update();  //handles basic physics e.g. vel += acc etc...
}


void Player::handleInputs()
{
	if (InputManager::getInstance()->isKeyDown(m_up))
	{
		m_velocity.setY(-3);
	}
	if (InputManager::getInstance()->isKeyDown(m_down))
	{
		m_velocity.setY(3);
	}
	if (!InputManager::getInstance()->isKeyDown(m_down) &&
		!InputManager::getInstance()->isKeyDown(m_up))
	{
		m_velocity.setY(0);
	}
}

void Player::clean() {}

void Player::load(const LoaderParams* pParams)
{
	SDLGameObject::load(pParams);

	m_player = pParams->getPlayer();

	//Set different controls for the different players
	
	if (m_player == 1 || m_player == 0)
	{
		m_up = SDL_SCANCODE_W;
		m_down = SDL_SCANCODE_S;
	}
	else if (m_player == 2)
	{
		m_up = SDL_SCANCODE_UP;
		m_down = SDL_SCANCODE_DOWN;
	}
}

GameObject* PlayerCreator::createGameObject() const
{
	return new Player();
}