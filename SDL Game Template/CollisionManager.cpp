#include "CollisionManager.h"


bool CollisionManager::isCollision(SDLGameObject* object1, SDLGameObject* object2)
{
	if (object1->get_position().getX() > 
		(object2->get_position().getX() + object2->get_width()))
	{ return false;	}
	if ((object1->get_position().getX() + object1->get_width()) < 
		object2->get_position().getX())
	{return false; }
	if (object1->get_position().getY() >
		(object2->get_position().getY() + object2->get_height()))
	{return false; }
	if ((object1->get_position().getY() + object1->get_height()) <
		object2->get_position().getY())
	{return false; }

	return true;
}

void CollisionManager::collisionDetection(std::vector<GameObject*> m_gameObjects)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		for (int j = 0; j < m_gameObjects.size(); j++)
		{
			if (i == j) {}
			else if (isCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[i]),
				dynamic_cast<SDLGameObject*>(m_gameObjects[j])))
			{
				std::cout << "Collision" << std::endl;
				m_gameObjects[i]->oncollision();
			}
		}
	}
}