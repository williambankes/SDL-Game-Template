#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputManager.h"


//LoaderParams:
LoaderParams::LoaderParams(int x, int y, int width, int height,
	std::string textureID, int callBackID, int animSpeed) :
	m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID),
m_callBackID(callBackID), m_animSpeed(animSpeed) {}

int LoaderParams::getX() const { return m_x; }
int LoaderParams::getY() const { return m_y; }
int LoaderParams::getWidth() const { return m_width; }
int LoaderParams::getHeight() const { return m_height; }
int LoaderParams::getCallbackID() const { return m_callBackID; }
std::string LoaderParams::getTextureID() const { return m_textureID; }


//GameObject:
GameObject::GameObject() {}
GameObject::~GameObject() {}

//SDLGameObject:
SDLGameObject::SDLGameObject() : GameObject() {}

void SDLGameObject::load(const LoaderParams* pParams)
{
	m_position = Vector2D(pParams->getX(), pParams->getY());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);
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