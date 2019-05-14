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
	SDLGameObject::update();  //handles basic physics e.g. vel += acc etc...
}

//This is written badly to adjust for different control settings for different players.
void Player::handleInputs()
{
	if (InputManager::getInstance()->isKeyDown(m_up))
	{
		m_velocity.setY(-1);
	}
	if (InputManager::getInstance()->isKeyDown(m_down))
	{
		m_velocity.setY(1);
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