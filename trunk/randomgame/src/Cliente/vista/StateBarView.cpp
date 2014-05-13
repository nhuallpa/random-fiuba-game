#include "StateBarView.h"
#define DELAY 10

StateBarView::StateBarView():View(0, 0){
	this->i = 0;
	this->j = 0;
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

void StateBarView::setMsj(std::string msj){
	/*state aState;
	std::vector<state>::iterator it;
	aState.msj = msj;
	aState.j = this->i;
	it = this->stateV.begin();
	this->stateV.insert(it,aState);
	*/
	this->msj.assign(msj);
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
		TextureManager::Instance().drawText(screen.getRenderer(), 
										TextureManager::Instance().getCamera().getX(),
										10 + TextureManager::Instance().getCamera().getY(), 
										msj.c_str(),
										0xFFFFFFFF);
	}
	

}