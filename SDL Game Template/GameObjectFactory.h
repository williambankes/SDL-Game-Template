#pragma once
#include <string>
#include <map>

#include "GameObject.h"

class BaseCreator
{
public:

	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator();
};


class GameObjectFactory
{
public:

	static GameObjectFactory* getInstance();

	bool registerType(std::string typeID, BaseCreator* pCreator);
	GameObject* create(std::string typeID);

private:

	std::map<std::string, BaseCreator*> m_creators;

	//Singleton Implementation:
	GameObjectFactory();
	static GameObjectFactory* s_pInstance;

};


