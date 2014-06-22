#include "TimerView.h"


TimerView::TimerView(int x, int y)
	: View(x, y)
{
	SDL_Color white;
	this->beforeTimer = 0.0;
	this->timerView = 60;
	white.a = 0xFF;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	this->finished = true;
	this->timerP = 0.0;
	this->index = 0;
	this->i = 1.0;
	this->label.setText("Tiempo", white);
	this->updateTime();
}


TimerView::~TimerView(void)
{
}

void TimerView::setTimer(float t){
	this->timerP = t;
}


void TimerView::update()
{
	if(!this->finished){
		float tim = this->timmer.elapsed();
		if(this->timerP < tim){
			this->finished = true;
			this->i = 1.0;
			this->beforeTimer = 0.0;
			this->timerView = 60;
			this->updateTime();
		}

		if((tim - this->beforeTimer)> i){
			this->beforeTimer = this->i* 1.5;
			this->i += 1.0;
			this->updateTime();
		}
	}
	else{
	}

}

void TimerView::updateTime(){
	SDL_Color white;	
	white.a = 0xFF;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	int val = this->timerView
		- this->beforeTimer;
	stgTimerView = Util::int2string(val);
	this->numberLabel.setText(stgTimerView, white);
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
	
		int margin_left = 10;
		//this->update();
		/*int margin = 5;
		int margin_left = 10;
		int padding_left = 10;
		int heightBarProgress = 15;
		SDL_Rect rect;
		rect.x = getX() + margin_left;
		rect.y = getY() + 20;
		rect.w = 140;
		rect.h = heightBarProgress - margin;*/

		TextureManager::Instance().draw("reloj", 5, 5, screen.getRenderer());

		/*if(!this->isFinished()){
			this->index++;
		}
		else{
			this->index = 0;
		}
		int w_bar = rect.w	- this->index;*/
		
		
		/*SDL_Rect rectBar;
		rectBar.x = rect.x + padding_left;
		rectBar.y = rect.y;
		rectBar.w = w_bar;
		rectBar.h = rect.h;

		TextureManager::Instance().drawFillRect(screen.getRenderer(), rectBar, 200, 200, 200, 200);*/
		
		this->label.draw(screen.getRenderer(), getX() + margin_left , getY());

		this->numberLabel.draw(screen.getRenderer(), getX() + margin_left + 20, getY() + 30);

}