#include "Coord.h"
#include <algorithm>
#include "..\..\..\utils\Log.h"

Coord* Coord::coord = NULL;

Coord::Coord(void){
	x  = 0, y  = 0,
	xp = 0, yp = 0;
}

Coord::~Coord(void){}

Coord* Coord::getInstance(){
	if(!coord){
		coord = new Coord();
	}
	return coord;
}

bool Coord::newEvent(){
	bool result = true;
	if((x == xp) && (y == yp)){
		result = false;
	}
	else{
		xp = x, yp = y;
	}
	return result;
}


void Coord::add(OnCoordListener * obj){
	if(!isRegistered(obj)){
		objects.push_back(obj);
	}
}

void Coord::remuve(OnCoordListener * obj){
	list<OnCoordListener*>::iterator it;
	list<OnCoordListener*>::iterator itDrop;
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

void Coord::notify(){
	list<OnCoordListener*>::iterator it;
	CoordEvent co;
	co.x = x, co.y = y;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnCoordinate(co);
	}
}


void Coord::setEvent(int x, int y){
	this->x = x, this->y = y;
}


bool Coord::isRegistered(OnCoordListener * obj){
	return (find(objects.begin(),
			objects.end(), 
			obj) != objects.end());
}
