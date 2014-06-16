#include "TimerView.h"


TimerView::TimerView(int x, int y)
	: View(x, y)
{
	SDL_Color white;

	white.a = 0xFF;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	this->label.setText("Tiempo", white);
}


TimerView::~TimerView(void)
{
}

void TimerView::update()
{

}


void TimerView::clean()
{

}

void TimerView::draw(SDLScreen & screen){
	
		int margin = 5;
		int margin_left = 10;
		int heightBarProgress = 15;
		SDL_Rect rect;
		rect.x = getX() + margin_left;
		rect.y = getY() + 20;
		rect.w = 100;
		rect.h = heightBarProgress - margin;


		TextureManager::Instance().drawBox(screen.getRenderer(), 
														rect.x, 
														getY(), 
														rect.x + 150,
														rect.y + 50,
														BACK_COLOR_PANEL);



		TextureManager::Instance().drawBox(screen.getRenderer(), 
														rect.x, 
														rect.y, 
														rect.x + rect.w,
														rect.y + rect.h, 
														COLOR_AMARILLO);
		

		this->label.draw(screen.getRenderer(), getX() + margin_left , getY());

}