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
	this->finished = true;
	this->timerP = 0.0;
	this->index = 0;
}


TimerView::~TimerView(void)
{
}

void TimerView::setTimer(float t){
	this->timerP = t;
}

void TimerView::update()
{
	float tim = this->timmer.elapsed();
	if(this->timerP < tim){
		this->finished = true;
	}
}


void TimerView::clean()
{

}

void TimerView::start(){
	this->timmer.start();
	this->finished = false;
}

void TimerView::reset(){
	this->start();
}

bool TimerView::isFinished(){
	return this->finished;
}

void TimerView::draw(SDLScreen & screen){
	

		this->update();
		int margin = 5;
		int margin_left = 10;
		int padding_left = 10;
		int heightBarProgress = 15;
		SDL_Rect rect;
		rect.x = getX() + margin_left;
		rect.y = getY() + 20;
		rect.w = 140;
		rect.h = heightBarProgress - margin;

		if(!this->isFinished()){
			this->index++;
		}
		else{
			this->index = 0;
		}
		int w_bar = rect.w	- this->index;
		
		
		SDL_Rect rectBar;
		rectBar.x = rect.x + padding_left;
		rectBar.y = rect.y;
		rectBar.w = w_bar;
		rectBar.h = rect.h;

		TextureManager::Instance().drawFillRect(screen.getRenderer(), rectBar, 200, 200, 200, 200);
		
		this->label.draw(screen.getRenderer(), getX() + margin_left , getY());

}