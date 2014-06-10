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
	this->stateV.clear();

}

void StateBarView::cutVect(){
	int lon = this->stateV.size();
	time_t ttime = time(NULL);
	if (lon>0){
		if ((this->i - this->stateV[lon-1].j ) > (DELAY * 100)) this->stateV.pop_back();		
	}
	if (lon == 6) this->stateV.pop_back();
	
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

		this->label.draw(screen.getRenderer(), TextureManager::Instance().getCamera().getX(),
												10 + TextureManager::Instance().getCamera().getY());

	}	
	
	int posX = TextureManager::Instance().getCamera().getX() + 
					TextureManager::Instance().getCamera().getW()/2 - 
						this->labelCenter.getWidth() / 2;
	int posY = TextureManager::Instance().getCamera().getY() + 10;
	this->labelCenter.draw(screen.getRenderer(), posX, posY);

	// pichaba ... ver 
	color.r = 255;
	color.g = 255;
	color.b = 255;
	TextManager::Instance().write(Arial16,60, 50,"hola,anda un monton",this->color);
	this->color.r=0;
	this->color.b=0;
	TextManager::Instance().write(Arial12,60, 70,"y hasta le puedo cambiar el color",this->color);
}