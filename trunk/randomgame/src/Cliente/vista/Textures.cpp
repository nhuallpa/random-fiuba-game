/*
 * Textures.cpp
 *
 *  Created on: 09/09/2013
 *      Author: ALiguori
 */

#include "Textures.h"
#include "Screen.h"
#include "../../utils/Log.h"

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
		Log::e( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{

		//SDL_Surface* formattedSurface = SDL_ConvertSurface( loadedSurface, SDL_GetWindowSurface( Screen::getInstance()->getWindow() )->format, NULL );

		//if( formattedSurface == NULL )
		//{
		//	printf( "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError() );
		//}


		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( this->tRenderer, loadedSurface );
		//newTexture = SDL_CreateTexture( this->tRenderer, SDL_GetWindowPixelFormat( Screen::getInstance()->getWindow() ), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );
		if( newTexture == NULL )
		{
			Log::e( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//SDL_LockSurface(loadedSurface);
			//memcpy(mPixels,loadedSurface->pixels,loadedSurface->pitch*loadedSurface->h);
			//this->mPixels = loadedSurface->pixels;
			//SDL_UnlockSurface(loadedSurface);
			this->mPitch = loadedSurface->pitch;
			//this->fmt = loadedSurface->format;
			std::cout << "image: " << path << ", bpp: " << static_cast<int>(loadedSurface->format->BitsPerPixel) << std::endl;
			//SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );
			//Copy loaded/formatted surface pixels
			//memcpy( mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

			//Unlock texture to update
			//SDL_UnlockTexture( newTexture );

			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
			//mPixels = NULL;
		}
		//SDL_FreeSurface( formattedSurface );

			mPixels = malloc(loadedSurface->pitch * loadedSurface->h);
			//fmt = (SDL_PixelFormat*)malloc(sizeof(loadedSurface->format));
			SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );
			memcpy( mPixels, loadedSurface->pixels, loadedSurface->pitch * loadedSurface->h );
			//memcpy(&fmt,loadedSurface->format,sizeof(loadedSurface->format));

	fmt.Ashift = loadedSurface->format->Ashift;
	fmt.Amask = loadedSurface->format->Amask;
	fmt.Aloss = loadedSurface->format->Aloss;
	fmt.BitsPerPixel = loadedSurface->format->BitsPerPixel;
			SDL_UnlockTexture( newTexture );
			//std::cout << "dsp memcpy, bpp: " << static_cast<int>(fmt.BitsPerPixel) << std::endl;
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;

	return mTexture != NULL;
}

void* Textures::getPixels(){
	return this->mPixels;
}

int Textures::getPitch(){
	return this->mPitch;
}

#ifdef _SDL_TTF_H
bool Textures::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *gFont )
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		Log::e( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( this->tRenderer, textSurface );
		if( mTexture == NULL )
		{
			Log::e( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
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

	if (mWidth > Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*3) - (15*4)){
		renderQuad.w = (Screen::getInstance()->getWidth() - MENU_WIDTH - (SPRITES_WIDTH*3) - (15*5));
	}

	//Render to screen
	SDL_RenderCopyEx( this->tRenderer, this->mTexture, clip, &renderQuad, angle, center, flip );
}

bool Textures::isAlphaPixel(int x, int y){

	Uint32* pixels = (Uint32*)this->mPixels;
	float factorX = ELEM_WIDTH * Screen::getInstance()->getLogic2PixelsFactor().first / this->getWidth();
	float factorY = ELEM_HEIGHT * Screen::getInstance()->getLogic2PixelsFactor().second / this->getHeight();
	int xpos, ypos;
	if (factorX >= 1){
		xpos = (int)floor(x/factorX);
	}else
		xpos = (int)ceil(x*factorX);

	if (factorY >= 1){
		ypos = (int)floor(y/factorY);
	}else
		ypos = (int)ceil(y*factorY);

	Uint32 aPixel = pixels[(this->getWidth()* ypos )+ xpos - 1];
	Uint8 r,g,b,alpha;
	Uint32 temp;
	bool tr = false;

	temp = aPixel & this->fmt.Amask;  /* Isolate alpha component */
	temp = temp >> this->fmt.Ashift; /* Shift it down to 8-bit */
	temp = temp << this->fmt.Aloss;  /* Expand to a full 8-bit number */
	alpha = (Uint8)temp;

	std::cout << "pixel alpha: " << static_cast<int>(alpha )<< std::endl;

	if ( static_cast<int>(alpha )== 0 )
		return true;
	return false;
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


bool Textures::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if( mPixels != NULL )
	{
		printf( "Texture is already locked!\n" );
		success = false;
	}
	//Lock texture
	else
	{
		if( SDL_LockTexture( mTexture, NULL, &mPixels, &mPitch ) != 0 )
		{
			printf( "Unable to lock texture! %s\n", SDL_GetError() );
			success = false;
		}
	}
	return success;
}

bool Textures::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if( mPixels == NULL )
	{
		printf( "Texture is not locked!\n" );
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture( mTexture );
		mPixels = NULL;
		mPitch = 0;
	}
	return success;
}