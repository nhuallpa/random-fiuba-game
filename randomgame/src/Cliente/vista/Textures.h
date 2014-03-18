/*
 * Textures.h
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */
#pragma once

#ifndef TEXTURES_H_
#define TEXTURES_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "../../utils/Constantes/Constantes.h"
#include <math.h>
/*
 *
 */

class Textures {
	public:
		Textures();
		Textures(SDL_Renderer* tRenderer);

		virtual ~Textures();
		bool loadFromFile( std::string path );


		#ifdef _SDL_TTF_H
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *gFont );
		#endif

		void free();

		//Renders textures
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		void renderFixSize( int x, int y, int width, int height, float degree );
		void renderFonts( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getWidth();
		int getHeight();
		SDL_Renderer* getRenderer();

		void* getPixels();
		int getPitch();

		SDL_Texture* getTexture();
		void setRenderer(SDL_Renderer* tRenderer);
		bool isAlphaPixel(int x, int y);
		bool unlockTexture();
		bool lockTexture();

	private:

		SDL_Texture* mTexture;
		SDL_Renderer* tRenderer;
		SDL_PixelFormat fmt;
		void* mPixels;
		int mPitch;
		int mWidth;
		int mHeight;


};

#endif /* TEXTURES_H_ */
