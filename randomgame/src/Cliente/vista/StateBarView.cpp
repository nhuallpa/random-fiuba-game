#include "StateBarView.h"
#define DELAY 10

StateBarView::StateBarView():View(0, 0){
	this->i = 0;
	this->j = 0;
	color.a = 255;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	colorError = 0xFF3300CC;
	colorInfo = 0xFF006633;
	colorMsg = colorError;

	
}

StateBarView::~StateBarView(void)
{

}

void StateBarView::setMsjInfo(std::string msj){
	colorMsg = colorInfo;
	this->label.setText(msj, this->color);
	i=0;
}

void StateBarView::setMsjError(std::string msj){
	colorMsg = colorError;
	this->label.setText(msj, this->color);
	i=0;
}

void StateBarView::setMsj(std::string msj){
	this->label.setText(msj, this->color);
	i=0;
}

void StateBarView::setMessageCenter(std::string msg) {
	this->labelCenter.setText(msg, this->color);
}

void StateBarView::draw(SDLScreen & screen){
	
	int xLabel = (int)(((float)screen.getWidth() / 2) - ((float)this->label.getWidth() / 2));
	int yLabel = screen.getHeight() - this->label.getHeight() - 20;

	SDL_Rect rectAlert = {xLabel, yLabel, this->label.getWidth(), this->label.getHeight()};

	if (i<=300) 
	{
		i++;
		TextureManager::Instance().drawFillRect(screen.getRenderer(), rectAlert,0,255,0,255);
		this->label.draw(screen.getRenderer(), xLabel, yLabel);
	}

	//Fondo Texto
	int posX = screen.getWidth()/2 -
		TextureManager::Instance().getDimension("fondo_msg").first / 2;

	int posY = 40;
	
	TextureManager::Instance().draw("fondo_msg", posX, 0, screen.getRenderer());

	// Texto 
	posX = posX + 30;

	this->labelCenter.draw(screen.getRenderer(), posX, posY);
}