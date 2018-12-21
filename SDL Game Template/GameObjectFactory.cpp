#include "GameObjectFactory.h"

BaseCreator::~BaseCreator() {}

bool GameObjectFactory::registerType(std::string typeID,
	BaseCreator* pCreator)
{
	std::map<std::string, BaseCreator*>::iterator it =
		m_creators.find(typeID);

	if (it != m_creators.end())
	{
		delete pCreator;
		return false;
	}

	m_creators[typeID] = pCreator;

	return true;
}

GameObject* GameObjectFactory::create(std::string typeID)
{
	std::map<std::string, BaseCreator*>::iterator it =
		m_creators.find(typeID);

	if (it == m_creators.end())
	{
		std::cout << "could not find type: " << typeID << std::endl;
		return NULL;
	}

	//.second takes the second map element i.e. the BaseCreator*
	BaseCreator* pCreator = (*it).second; 
	return pCreator->createGameObject();
}

//Singleton Implementation:

GameObjectFactory* GameObjectFactory::s_pInstance = 0;

GameObjectFactory::GameObjectFactory() {}

GameObjectFactory* GameObjectFactory::getInstance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new GameObjectFactory();
		return s_pInstance;
	}

	return s_pInstance;
}