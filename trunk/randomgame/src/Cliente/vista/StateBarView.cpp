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
	//this->label.setText(msj, this->color);
	i=0;
}

void StateBarView::setMsjError(std::string msj){
	colorMsg = colorError;
	//this->label.setText(msj, this->color);
	i=0;
}

void StateBarView::setMsj(std::string msj){
	//this->label.setText(msj, this->color);
	i=0;
}

void StateBarView::draw(SDLScreen & screen){
	
	int xLabel = TextureManager::Instance().getCamera().getX();
	int yLabel = 10 + TextureManager::Instance().getCamera().getY();

	SDL_Rect canvas;
	canvas.x = xLabel;
	canvas.y = yLabel;
	canvas.h = this->label.getHeight();
	canvas.w = this->label.getWidth();

	float lastScaleX=0;
	float lastScaleY=0;

	if (i<=300) 
	{
		i++;
		
		/*SDL_RenderGetScale(screen.getRenderer(), &lastScaleX, &lastScaleY);

		SDL_Texture* auxtexture = SDL_CreateTexture(screen.getRenderer(), 
										SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, canvas.w, canvas.h);
		SDL_SetTextureBlendMode(auxtexture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(screen.getRenderer(), auxtexture);
		SDL_RenderSetScale(screen.getRenderer(),1,1);
		*/
		TextureManager::Instance().drawBox(screen.getRenderer(), 
											xLabel,
											yLabel,
											xLabel + this->label.getWidth(),
											yLabel + this->label.getHeight(),
											colorMsg);

		this->label.draw(screen.getRenderer(), TextureManager::Instance().getCamera().getX(),
												10 + TextureManager::Instance().getCamera().getY());


		/*
		SDL_SetRenderTarget(screen.getRenderer(), NULL);
		SDL_RenderCopy(screen.getRenderer(), auxtexture, NULL, &canvas);
		SDL_DestroyTexture(auxtexture);*/
	}	
	

}