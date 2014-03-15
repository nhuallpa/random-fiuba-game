/*
 * Textures.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "Textures.h"
#include "Screen.h"

Textures::Textures()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	tRenderer = NULL;
}

Textures::Textures(SDL_Renderer* tRenderer){

	this->tRenderer = tRenderer;
	this->mTexture = NULL;
	this->mWidth = 0;
	this->mHeight = 0;
}

Textures::~Textures()
{
	free();
}

bool Textures::loadFromFile( std::string path )
{
	free();
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( this->tRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			// TODO @LOG
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool Textures::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *gFont )
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		// TODO @LOG
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( this->tRenderer, textSurface );
		if( mTexture == NULL )
		{
			// TODO @LOG
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}

	return mTexture != NULL;
}
#endif

void Textures::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Textures::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x,
							y,
							ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first,
							ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second};

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( this->tRenderer, this->mTexture, clip, &renderQuad, angle, center, flip );
}


void Textures::renderFixSize( int x, int y, int width, int height,float degree)
{
	SDL_Rect renderQuad = { x,
							y,
							width,
							height};

	//Render to screen
	SDL_RenderCopyEx( this->tRenderer, this->mTexture, NULL, &renderQuad, degree, NULL, SDL_FLIP_NONE);
}


void Textures::renderFonts( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x,
							y,
							mWidth,
							mHeight};

	if (mWidth > Screen::getInstance()->getWidth() - MENU_WIDTH - 160){
		renderQuad.w = (Screen::getInstance()->getWidth() - MENU_WIDTH - 160);
	}

	//Render to screen
	SDL_RenderCopyEx( this->tRenderer, this->mTexture, clip, &renderQuad, angle, center, flip );
}


int Textures::getWidth()
{
	return mWidth;
}

int Textures::getHeight()
{
	return mHeight;
}


void Textures::setRenderer(SDL_Renderer* tRenderer){
	this->tRenderer = tRenderer;
}


SDL_Renderer* Textures::getRenderer(){
	return this->tRenderer;
}

SDL_Texture* Textures::getTexture(){
	return this->mTexture;
}
