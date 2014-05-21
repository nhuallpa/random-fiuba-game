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

void StateBarView::draw(SDLScreen & screen){
	/*std::vector<state>::iterator it;
	this->cutVect();
	int i=0;
	this->i++;
	for (it=this->stateV.begin(); it<this->stateV.end(); it++){
		char *cstr = new char[it->msj.size() +1];
		strcpy(cstr, it->msj.c_str());	
		TextureManager::Instance().drawText(screen.getRenderer(),0+TextureManager::Instance().getCamera().getX(),0+(i*10)+TextureManager::Instance().getCamera().getY(),cstr,0xFFFFFFFF);
		i++;
	}
	
	*/
	if (i<=300) 
	{
		i++;
		/*TextureManager::Instance().drawText(screen.getRenderer(), 
										TextureManager::Instance().getCamera().getX(),
										10 + TextureManager::Instance().getCamera().getY(), 
										msj,
										0xFFFFFFFF);
		*/
		int xLabel = TextureManager::Instance().getCamera().getX();
		int yLabel = 10 + TextureManager::Instance().getCamera().getY();
		TextureManager::Instance().drawBox(screen.getRenderer(), 
											xLabel,
											yLabel,
											xLabel + this->label.getWidth(),
											yLabel + this->label.getHeight(),
											colorMsg);

		this->label.draw(screen.getRenderer(), TextureManager::Instance().getCamera().getX(),
												10 + TextureManager::Instance().getCamera().getY());
	}
	

}