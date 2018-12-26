#pragma once
#include "GameObject.h"
#include "tinyxml/tinyxml.h"

#include <vector>
#include <iostream>

class StateParser
{
public:
	StateParser();

	bool parseState(const char* stateFile, std::string stateID,
		std::vector<GameObject*> *pObjects,
		std::vector<std::string> *pTextureIDs);

private:

	void parseObject(TiXmlElement* pStateRoot,
		std::vector<GameObject*> *pObject);
	void parseTextures(TiXmlElement* pStateRoot,
		std::vector<std::string> *pTextureIDs);
		
};

