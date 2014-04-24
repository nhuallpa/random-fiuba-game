#pragma once

#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <map>
#include "GameException.h"
#include "../../utils/Log.h"

enum ImgOper 
{
	NONE,
	REVERT
};

class TextureManager
{
private:
	
	// Contains all texture
	std::map<std::string, SDL_Texture*> texture_map;

	/**
	* @param  surface A SDL_Surface to flip. Only works with image with channel alpha (32 bits)
	* @return flipped A copy of surface flipped horizontaly
	*/
	SDL_Surface* flipSurface(SDL_Surface* surface);
	
	Uint32 getPixel32( SDL_Surface *surface, int x, int y );

	void putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );

public:
	
	TextureManager(void);

	static TextureManager & Instance(){
			static TextureManager theTextureManager;
			return theTextureManager;
	}

	/**
	* Load image. Allow png, jpg, gif, bmp
	* @param fileName	The file name of image
	* @param id			The id image using to retrive later
	* @param pRenderer	The renderer which is used to load image
	* @param oper		The aditional operation on image
	*/
	bool load(std::string fileName,std::string id, SDL_Renderer* pRenderer, ImgOper oper = NONE);


	void draw(std::string id, int x, int y, 
					SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void draw(std::string id, int x, int y, int width, int
			height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	
	/**
	* Draw a frame from sprite
	*
	* @param id Id de imagen 
	* @param x  Position in axis x
	* @param y  Position in axis y
	* @param width Width of frame 
	* @param height Height of frame
	* @param currentRow row to draw. Beginning since 1
	* @param currentFrame frame to draw. Beginning since 0
	* @param pRenderer Render to draw
	* @param flip SDL flip
	* 
	**/
	void drawFrame(std::string id, int x, int y, int width, int
					height, int currentRow, int currentFrame, SDL_Renderer*
					pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);


	void drawBackground(std::string id, SDL_Renderer* pRenderer, 
						SDL_RendererFlip flip = SDL_FLIP_NONE) ;

	~TextureManager(void);
};



#endif /* defined(__TEXTURE_MANAGER__) */