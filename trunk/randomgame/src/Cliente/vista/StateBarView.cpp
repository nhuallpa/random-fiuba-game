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
	
	int xLabel = TextureManager::Instance().getCamera().getX();
	int yLabel = 10 + TextureManager::Instance().getCamera().getY();

	float lastScaleX=0;
	float lastScaleY=0;

	if (i<=300) 
	{
		i++;
	
		TextureManager::Instance().drawBox(screen.getRenderer(), 
											xLabel,
											yLabel,
											xLabel + this->label.getWidth(),
											yLabel + this->label.getHeight(),
											colorMsg);

		/*this->label.draw(screen.getRenderer(), 
			TextureManager::Instance().getCamera().getX(),
			10 + TextureManager::Instance().getCamera().getY());*/

		this->label.draw(screen.getRenderer(), 0, 10);

	}	
	
	

	//Fondo Texto
	int posX = TextureManager::Instance().getCamera().getW()/2 -
		TextureManager::Instance().getDimension("fondo_msg").first / 2;

	int posY = 30;
	
	TextureManager::Instance().drawScale("fondo_msg", posX, 0, 1, screen.getRenderer());

	// Texto 
	posX = posX + 30;

	this->labelCenter.draw(screen.getRenderer(), posX, posY);
}