#pragma once
#include "SDL.h"
#include "SDL_image.h"

#include <string>
#include <map>
#include <iostream>

class TextureManager {

public:

	static TextureManager* getInstance();

	//Load textures into texture map:
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	//Draw functions:
	int draw(std::string id,
		int x, int y, int width, int height,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int drawFrame(std::string id,
		int x, int y, int width, int height,
		int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void clearFromTextureMap(std::string id);

	void clean();

private:
	
	std::map<std::string, SDL_Texture*> m_textureMap;

	int check_map(std::string id);

	//Singleton Implementation:
	TextureManager();
	static TextureManager* s_pInstance;

};