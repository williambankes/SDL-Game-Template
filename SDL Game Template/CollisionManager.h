#pragma once
#include "GameObject.h"
#include <vector>

class CollisionManager
{
public:
	bool isCollision(SDLGameObject* object1, SDLGameObject* object2);

	void collisionDetection(std::vector<GameObject*> m_gameObjects);
};

