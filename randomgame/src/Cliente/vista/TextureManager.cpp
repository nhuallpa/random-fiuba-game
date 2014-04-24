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


bool TextureManager::load(std::string fileName,std::string id, SDL_Renderer* pRenderer, ImgOper oper)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());
	SDL_Surface* proccecedSurface = NULL;
	if (oper == REVERT) 
	{
		proccecedSurface = flipSurface(tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
	else
	{
		proccecedSurface = tmpSurface;
	}

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(pRenderer, proccecedSurface);
	SDL_FreeSurface(proccecedSurface);

	if (newTexture)
	{
		this->texture_map[id]=newTexture;
		return true;
	} else 
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

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, this->texture_map[id], &srcRect,&destRect, 0, 0, flip);
}


SDL_Surface* TextureManager::flipSurface(SDL_Surface* surface)
{
	SDL_Surface *flipped = NULL;
	flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, 
									surface->w, 
									surface->h, 
									surface->format->BitsPerPixel, 
									surface->format->Rmask, 
									surface->format->Gmask, 
									surface->format->Bmask, 
									surface->format->Amask );
	if (flipped==NULL) {
		std::stringstream msg;
		msg<<"TextureManager: Error al voltear un imagen ";
		throw GameException(msg.str());
	}
	if( SDL_MUSTLOCK( surface ) )
    {
        SDL_LockSurface( surface );
    }
	// read in one direction and write in others
	int x = 0;
	int rx = flipped->w-1;
	int y = 0;
	int ry = flipped->h-1;
	Log::i("		Ancho %d    alto %d", surface->w, surface->h);
	Log::i("		Ancho dest %d    alto dest %d", flipped->w, flipped->h);
	for (x = 0; x < surface->w; x++) // columns
	{
		ry = flipped->h-1;
		Log::i("Colmna %d", x);
		for (y = 0; y < surface->h; y++) // rows
		{
			Log::i("		Fila %d", y);
			Uint32 pixel = getPixel32(surface, x, y);
			putPixel32(flipped, rx, y, pixel);				// flip horizontal
			ry--;
		}

		rx--;
	}

	if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }

	return flipped;
}

Uint32 TextureManager::getPixel32( SDL_Surface *surface, int x, int y )
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[ ( y * surface->w ) + x ];
}

void TextureManager::putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    Uint32 *pixels = (Uint32 *)surface->pixels;   
    pixels[ ( y * surface->w ) + x ] = pixel;
}