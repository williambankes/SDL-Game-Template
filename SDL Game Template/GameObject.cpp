#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"


//LoaderParams:
LoaderParams::LoaderParams(int x, int y, int width, int height,
	std::string textureID) : m_x(x), m_y(y), m_width(width), m_height(height),
	m_textureID(textureID) {}

int LoaderParams::getX() const { return m_x; }
int LoaderParams::getY() const { return m_y; }
int LoaderParams::getWidth() const { return m_width; }
int LoaderParams::getHeight() const { return m_height; }
std::string LoaderParams::getTextureID() const { return m_textureID; }

//GameObject:
GameObject::GameObject(const LoaderParams* pParams) {}
GameObject::~GameObject() {}

//SDLGameObject:
SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
	GameObject(pParams), m_position(pParams->getX(), pParams-> getY()),
	m_velocity(0, 0), m_acceleration(0, 0) {

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw() {
	TextureManager::getInstance()->drawFrame(m_textureID,
		(int)m_position.getX(), (int)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame,
		Game::getInstance()->getRenderer());
}

void SDLGameObject::clean() {}

void SDLGameObject::update() {
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

Player::Player(const LoaderParams* pParams) :
	SDLGameObject(pParams)	{}


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
	Vector2D* target = InputHandler::getInstance()->getMousePosition();

	m_velocity = *target - m_position;

	m_velocity /= 50;
}

void Player::clean() {}
