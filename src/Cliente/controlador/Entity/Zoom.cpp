#include "Zoom.h"


Zoom* Zoom::zoom = NULL;

Zoom::Zoom(void){}

Zoom::~Zoom(void){}

Zoom* Zoom::getInstance(){
	if(!zoom){
		zoom = new Zoom();
	}
	return zoom;
}

void Zoom::add(OnZoomListener* obj){
	objects.push_back(obj);
}

void Zoom::remuve(OnZoomListener* obj){
	list<OnZoomListener*>::iterator it;
	list<OnZoomListener*>::iterator itDrop;
	it = objects.begin();
	itDrop = objects.end();
	for(; it != objects.end(); it++){
		if((*it) == obj){
			itDrop = it;
			break;
		}
	}
	if(itDrop != objects.end()){
		objects.erase(itDrop);
	}
}

void Zoom::notify(){
	list<OnZoomListener*>::iterator it;
	ZoomEvent z;
	z.y = this->y;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnZoom(z);
	}
}

void Zoom::setEvent(int y){
	this->y = y;
}

