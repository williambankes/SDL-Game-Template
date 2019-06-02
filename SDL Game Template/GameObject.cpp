#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputManager.h"


//LoaderParams:
LoaderParams::LoaderParams(int x, int y, int width, int height,
	std::string textureID, int callBackID, int animSpeed, int player) :
	m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID),
m_callBackID(callBackID), m_animSpeed(animSpeed), m_player(player) {}

int LoaderParams::getX() const { return m_x; }
int LoaderParams::getY() const { return m_y; }
int LoaderParams::getWidth() const { return m_width; }
int LoaderParams::getHeight() const { return m_height; }
int LoaderParams::getCallbackID() const { return m_callBackID; }
int LoaderParams::getPlayer() const { return m_player; }
std::string LoaderParams::getTextureID() const { return m_textureID; }


//GameObject:
GameObject::GameObject() {}
GameObject::~GameObject() {}
void GameObject::oncollision(GameObject* col) {}

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
	m_currentFrame = 0;

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

void SDLGameObject::oncollision(GameObject* col) {}

Vector2D SDLGameObject::get_position() { return m_position; }
Vector2D SDLGameObject::get_velocity() { return m_velocity; }
int SDLGameObject::get_width() { return m_width; }
int SDLGameObject::get_height() { return m_height; }