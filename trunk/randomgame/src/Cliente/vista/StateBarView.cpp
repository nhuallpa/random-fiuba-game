#include "StateBarView.h"


StateBarView::StateBarView(int msjs):View(0, 0){
	this->msjs = msjs;
}


void StateBarView::cutVect(){
	int lon = this->stateV.size();
	
	if (difftime(this->stateV[lon-1].ttime,time(NULL))>5) this->stateV.pop_back();
	if (lon == 6) this->stateV.pop_back();
	
}

void StateBarView::setMsj(std::string msj){
	state aState;
	std::vector<state>::iterator it;
	aState.msj = msj;
	aState.ttime = time(NULL);
	it = this->stateV.begin();
	this->stateV.insert(it,aState);
}

void StateBarView::draw(SDLScreen & screen){
	std::vector<state>::iterator it;
	this->cutVect();
	for (int i=0;i<6;i++){
		char *cstr = new char[this->stateV[i].msj.length() + 1];
		strcpy(cstr, this->stateV[i].msj.c_str());
		TextureManager::Instance().drawText(screen.getRenderer(),0,0+(i*3),cstr,0xFFFFFFFF);
	}
}