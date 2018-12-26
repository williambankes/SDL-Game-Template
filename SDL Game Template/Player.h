#pragma once
#include "GameObject.h"

class Player : public SDLGameObject
{
public:

	void draw();
	void update();
	void handleInputs();
	void clean();

	void load(const LoaderParams* pParams);

	Player();
};