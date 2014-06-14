#include "ChangeEvent.h"

ChangeEvent::ChangeEvent(void){}
ChangeEvent::~ChangeEvent(void){}



bool ChangeEvent::isStateBar(){
	return stateBar;
}


bool ChangeEvent::isCoordenate(){
	return coordenate;
}

void ChangeEvent::setFactor(int factor){
	this->factor = factor;
}



void ChangeEvent::setStateBar(bool stateBar){
	this->stateBar = stateBar;
}

void ChangeEvent::setCoordenate(bool coordenate){
	this->coordenate = coordenate;
}
