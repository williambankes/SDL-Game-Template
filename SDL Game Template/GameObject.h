#pragma once
#include <string>

#include "Vector.h"

class LoaderParams {

public:

	LoaderParams(int x, int y, int width, int height,
		std::string textureID);

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	std::string getTextureID() const;


private:

	int m_x;
	int m_y;

	int m_width;
	int m_height;

	std::string m_textureID;

};

class GameObject {

public:
		
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	

protected:
	
	GameObject(const LoaderParams* pParams);
	virtual ~GameObject();
};

class SDLGameObject : public GameObject {

public:

	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;

};

class Player : public SDLGameObject
{
public:

	void draw();
	void update();
	void handleInputs();
	void clean();

	Player(const LoaderParams* pParams);
};