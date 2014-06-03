#include "EartView.h"


EartView::EartView(std::string imageId):View(0, 0), imageId(imageId)
{
	this->counter = 0;
}


EartView::~EartView(void)
{

}

void EartView::draw(SDLScreen & screen)
{
	/*if (this->counter > 100)
	{
		this->counter = 0;
		this->drawExplotion(200, 200, 30);
	}
	this->counter++;*/
	TextureManager::Instance().drawScrollableBackground(imageId, screen.getRenderer());
}

void EartView::drawExplotion(int x, int y, int radius)
{
	Uint32 pixel = 0x00000000;
	void* pixels;
	/*Bytes between rows*/
	int pitch;
	SDL_Texture* texture = TextureManager::Instance().getTexture(this->imageId);
	std::pair<int,int> dim = TextureManager::Instance().getDimension(this->imageId);
	SDL_Surface * surface = TextureManager::Instance().getSurface(this->imageId);

	TextureManager::Instance().fillCircleOn(surface, x, y, radius, pixel);

	SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);

}
