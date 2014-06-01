#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <map>
#include "GameException.h"
#include "Camera.h"
#include <SDL_rect.h>
#include "../../utils/Log.h"
#include <SDL2_gfxPrimitives.h>

class TextureManager
{
private:

	

	Camera cam;
	
	// Contains all texture
	std::map<std::string, SDL_Texture*> texture_map;
	std::map<std::string, SDL_Surface*> surface_map;

	int screenWidth;
	int screenHeight;

	bool firstTime;

	/**
	* @param  surface A SDL_Surface to flip. Only works with image with channel alpha (32 bits)
	* @return flipped A copy of surface flipped horizontaly
	*/
	SDL_Surface* flipSurface(SDL_Surface* surface);
	
	

	

public:
	
	TextureManager(void);

	
	static TextureManager & Instance(){
			static TextureManager theTextureManager;
			return theTextureManager;
	}

	void init(int w, int h);

	void setScreenSize(int w, int h);

	int getScreenWidth() { return this->screenWidth;}
	int getScreenHeight() { return this->screenHeight;}

	/**
	* Load image. Allow png, jpg, gif, bmp
	* @param fileName	The file name of image
	* @param id			The id image using to retrive later
	* @param pRenderer	The renderer which is used to load image
	* @param oper		The aditional operation on image
	*/
	bool load(std::string fileName,std::string id, SDL_Renderer* pRenderer);

	void loadImages(std::map<std::string, std::string> map_images, SDL_Renderer * renderer);

	bool loadStream(std::string fileName,std::string id, SDL_Renderer* pRenderer);

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
					pRenderer,bool grey, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawScrollableBackground(std::string imageId, SDL_Renderer* pRenderer);

	void drawBackground(std::string id, SDL_Renderer* pRenderer, 
						SDL_RendererFlip flip = SDL_FLIP_NONE) ;

	/**
	*
	*/
	void drawImageOffset(std::string id,
								int x, int y, int widthCamera, int heightCamera,
								SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/*
	* Gets the dimension of an image
	* @param imageId The image id
	* @return Dimension width and height
	**/
	std::pair<int, int> getDimension(std::string imageId);

	
	Camera & getCamera() {return cam;}

	/** Draw circle on renderer*/
	void drawCircle(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 r, Uint32 color, Uint32 borderColor);
	/** Draw ellipse on renderer*/
	void drawEllipse(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color, Uint32 borderColor);
	/** Draw polygon on renderer*/
	void drawPolygon(SDL_Renderer * renderer, Sint16 * vx, Sint16 * vy, int n, Uint32 color, Uint32 borderColor);
	/** Draw Box on renderer*/
	void drawBox(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);

	void drawText(SDL_Renderer * renderer,Sint16 x, Sint16 y, std::string text , Uint32 color);

	SDL_Point convertPointScreen2SDL(int x, int y);

	tPoint convertPointUL2PXSDL(float x, float y);

	~TextureManager(void);

	SDL_Texture * getTexture(std::string imageId);

	SDL_Surface* getSurface(std::string imageId);

	/* one in two*/
	bool intersectRects(SDL_Rect one, SDL_Rect two);

	void drawCircleOn(SDL_Surface *surface, int centerX, int centerY, int radius, Uint32 pixel);

	void fillCircleOn(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);

	void putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
};



#endif /* defined(__TEXTURE_MANAGER__) */