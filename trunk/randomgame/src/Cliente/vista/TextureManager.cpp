#include "TextureManager.h"


TextureManager::TextureManager(void) {
}

TextureManager::~TextureManager(void)
{
	std::map<std::string, SDL_Texture*>::iterator iter;
	for (iter = texture_map.begin(); iter!=texture_map.end(); ++iter)
	{
		SDL_DestroyTexture(iter->second);
	}
	texture_map.clear();
}


bool TextureManager::load(std::string fileName,std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(pRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	if (newTexture)
	{
		this->texture_map[id]=newTexture;
		return true;
	} 
	else 
	{
		std::stringstream msg;
		msg<<"TextureManager: Imagen NO encontrada: "<<fileName;
		throw GameException(msg.str());
	}
	return false;
}

void TextureManager::draw(std::string id, int x, int y, 
					SDL_Renderer* pRenderer, SDL_RendererFlip flip) 
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	
	SDL_QueryTexture(this->texture_map[id], NULL, NULL,
	&srcRect.w, &srcRect.h);

	srcRect.x = 0;
	srcRect.y = 0;
	
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, this->texture_map[id], &srcRect,&destRect, 0, 0, flip);

}

void TextureManager::draw(std::string id, int x, int y, int width, int
	height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) 
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, this->texture_map[id], &srcRect,&destRect, 0, 0, flip);

}

void TextureManager::drawScrollableBackground(std::string imageId, SDL_Renderer* pRenderer) 
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = this->cam.getX();
	srcRect.y = this->cam.getY();

	destRect.w = srcRect.w = this->cam.getW();
	destRect.h = srcRect.h = this->cam.getH();

	destRect.x = 0;
	destRect.y = 0;

	SDL_RenderCopyEx(pRenderer, this->texture_map[imageId], &srcRect,&destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawBackground(std::string id, SDL_Renderer* pRenderer, SDL_RendererFlip flip) 
{
	SDL_RenderCopy(pRenderer, this->texture_map[id], 0, 0);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int	height, 
								int currentRow, int currentFrame, 
								SDL_Renderer*	pRenderer, SDL_RendererFlip flip) 
{	
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x - this->cam.getX();
	destRect.y = y - this->cam.getY();

	SDL_RenderCopyEx(pRenderer, this->texture_map[id], &srcRect,&destRect, 0, 0, flip);
}

std::pair<int, int> TextureManager::getDimension(std::string imageId)
{
	SDL_Rect rect;
	SDL_QueryTexture(this->texture_map[imageId], NULL, NULL,	&rect.w, &rect.h);
	std::pair<int, int> dimension = std::make_pair(rect.w, rect.h);
	return dimension;
}


void TextureManager::drawCircle(SDL_Renderer * renderer, 
								Sint16 x, 
								Sint16 y, 
								Sint16 r, 
								Uint32 color, 
								Uint32 borderColor)
{
	filledCircleColor(renderer,
						y,
						y,
						r,
						color);

	aacircleColor(renderer,
						y,
						y,
						r,
						borderColor);
}

void TextureManager::drawEllipse(SDL_Renderer * renderer, 
								Sint16 x, 
								Sint16 y, 
								Sint16 rx, 
								Sint16 ry, 
								Uint32 color, 
								Uint32 borderColor)
{
	x = x - this->cam.getX();
	y = y - this->cam.getY();

	filledEllipseColor(renderer,
						x,
						y,
						rx,
						ry,
						color);

	aaellipseColor(renderer,
						x,
						y,
						rx,
						ry,
						borderColor);
}

void TextureManager::drawBox(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color)
{
	x1 = x1 - this->cam.getX();
	y1 = y1 - this->cam.getY();
	x2 = x2 - this->cam.getX();
	y2 = y2 - this->cam.getY();
	boxColor(renderer,
				x1, y1,
				x2, y2, color);
}

void TextureManager::drawPolygon(SDL_Renderer * renderer, 
								Sint16 * vx, 
								Sint16 * vy, 
								int n, 
								Uint32 color, 
								Uint32 borderColor)
{
	int i = 0;
	for (i=0; i<n; i++) 
	{
		vx[i] = vx[i] - this->cam.getX();
		vy[i] = vy[i] - this->cam.getY();
	}

	filledPolygonColor(renderer,
				vx,
				vy,
				n,
				color);

	polygonColor(renderer,
				vx,
				vy,
				n,
				borderColor);
}
