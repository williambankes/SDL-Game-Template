#pragma once
#include "GameObject.h"
#include "GameObjectFactory.h"
#include <SDL_scancode.h>

class Player : public SDLGameObject
{
public:

	void draw();
	void update();
	void handleInputs();
	void clean();

	void load(const LoaderParams* pParams);

	Player();


private:

	int m_player;
	SDL_Scancode m_up;
	SDL_Scancode m_down;
};

class PlayerCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const;
};