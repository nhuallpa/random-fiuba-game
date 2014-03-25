#pragma once

#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include "GameException.h"
class TextureManager
{
private:
	
	// Contains all texture
	std::map<std::string, SDL_Texture*> texture_map;

public:
	
	TextureManager(void);

	static TextureManager & Instance(){
			static TextureManager theTextureManager;
			return theTextureManager;
	}

	bool load(std::string fileName,std::string id, SDL_Renderer* pRenderer);


	void draw(std::string id, int x, int y, 
					SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void draw(std::string id, int x, int y, int width, int
			height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int
					height, int currentRow, int currentFrame, SDL_Renderer*
					pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawBackground(std::string id, SDL_Renderer* pRenderer, 
						SDL_RendererFlip flip = SDL_FLIP_NONE) ;

	~TextureManager(void);
};



#endif /* defined(__TEXTURE_MANAGER__) */