#include "StateParser.h"

#include "GameObjectFactory.h"
#include "TextureManager.h"
#include "Game.h"



StateParser::StateParser()
{}


bool StateParser::parseState(const char *stateFile, std::string stateID,
	std::vector<GameObject*> *pObjects,
	std::vector<std::string> *pTextureIDs)
{
	//create the XML document
	TiXmlDocument xmlDoc;

	//load the state file
	if (!xmlDoc.LoadFile(stateFile))
	{
		std::cerr << xmlDoc.ErrorDesc() << std::endl;
		return false;
	}

	//get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();

	//pre declaration of state root nodes:
	TiXmlElement* pStateRoot = 0;
	//get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement();
		e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;
		}
	}

	//pre decalaration of texture root:
	TiXmlElement* pTextureRoot = 0;

	//get the root of the texture elements:
	for (TiXmlElement* e = pStateRoot->FirstChildElement();
		e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("TEXTURES"))
		{
			pTextureRoot = e;
		}
	}

	//now parse the Textures:
	parseTextures(pTextureRoot, pTextureIDs);

	//pre declaration of the object root node:
	TiXmlElement* pObjectRoot = 0;

	//get the root node and assign it to pObjectRoot:
	for (TiXmlElement* e = pStateRoot->FirstChildElement();
		e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("OBJECTS"))
		{
			pObjectRoot = e;
		}
	}

	//now parse the objects:
	parseObject(pObjectRoot, pObjects);
}

void StateParser::parseTextures(TiXmlElement* pStateRoot,
	std::vector<std::string> *pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement())
	{
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute);

		TextureManager::getInstance()->load(filenameAttribute,
			idAttribute, Game::getInstance()->getRenderer());
	}
}

void parseObject(TiXmlElement* pStateRoot,
	std::vector<GameObject*> *pObject)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;

		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callBackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);

		textureID = e->Attribute("textureID");

		GameObject* pGameObject = GameObjectFactory::getInstance()->
			create(e->Attribute("type"));
		pGameObject->load(new LoaderParams(
			x, y, width, height, textureID, callbackID, animSpeed));
		pObject->push_back(pGameObject);		
	}
}