#include "TextureManager.h"

bool TextureManager::load(std::string fileName, std::string id,
	SDL_Renderer* pRenderer) {

	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) {
		return false;
	}
	
	SDL_Texture* pTexture =
		SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	return false;
}

int TextureManager::draw(std::string id,
	int x, int y, int width, int height,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect scrRect;
	SDL_Rect destRect;

	scrRect.x = 0;
	scrRect.y = 0;
		
	scrRect.w = destRect.w = width;
	scrRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	//Check id exists in texture map:
	if (check_map(id) == 1)
	{
		return 1;
	}
	else {

		SDL_RenderCopyEx(pRenderer, m_textureMap[id],
			&scrRect, &destRect,
			0, 0, flip);
		return 0;
	}
}

int TextureManager::drawFrame(std::string id,
	int x, int y, int width, int height,
	int currentRow, int currentFrame,
	SDL_Renderer* pRenderer,SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1); //indexed from 1
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	//Check id exists in texture map:
	if (check_map(id) == 1) {
		return 1;
	}
	else
	{
		SDL_RenderCopyEx(pRenderer, m_textureMap[id],
			&srcRect, &destRect, 0, 0, flip);
		return 0;
	}
}

void TextureManager::clearFromTextureMap(std::string id) {
	m_textureMap.erase(id);
}

void clean() {}


int TextureManager::check_map(std::string id) {
	if (m_textureMap[id] == 0)
	{
		std::cout << "Texture Manager error: Unable to find texture " << id << " in m_textureMap"
			<< std::endl;
		return 1;
	}
	else { return 0; }
}

//Singleton Implementation:

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager() {}

TextureManager* TextureManager::getInstance() {
	if (s_pInstance == 0)
	{
		s_pInstance = new TextureManager();
		return s_pInstance;
	}

	return s_pInstance;
}