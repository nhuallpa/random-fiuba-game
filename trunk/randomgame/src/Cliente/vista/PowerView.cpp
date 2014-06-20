#include "PowerView.h"


PowerView::PowerView(int x, int y)
	: View(x, y)
{
	SDL_Color white;

	white.a = 0xFF;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	this->label.setText("Poder", white);
}


PowerView::~PowerView(void)
{
}

void PowerView::update()
{

}


void PowerView::clean()
{

}

void PowerView::draw(SDLScreen & screen){
	
		int margin = 5;
		int heightBarProgress = 15;
		SDL_Rect rect;
		rect.x = getX();
		rect.y = getY() + 20;
		rect.w = 100;
		rect.h = heightBarProgress - margin;


		TextureManager::Instance().drawFillRect(screen.getRenderer(), rect, 0,0,255, 255);

		this->label.draw(screen.getRenderer(), getX() , getY());

}