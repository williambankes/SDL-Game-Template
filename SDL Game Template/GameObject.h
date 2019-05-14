#pragma once
#include <string>

#include "Vector.h"

class LoaderParams {

public:

	LoaderParams(int x, int y, int width, int height,
		std::string textureID, int callBackID = 0, int animSpeed = 0,
		int player = 0);

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	int getCallbackID() const;
	int getPlayer() const;
	std::string getTextureID() const;

private:

	int m_x;
	int m_y;

	int m_width;
	int m_height;

	std::string m_textureID;

	int m_callBackID;
	int m_animSpeed;
	int m_player;
};

class GameObject {

public:
		
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void load(const LoaderParams* pParams) = 0;
	

protected:
	
	GameObject();
	virtual ~GameObject();
};

class SDLGameObject : public GameObject {

public:

	SDLGameObject();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);
	

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