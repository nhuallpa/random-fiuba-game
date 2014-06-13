#include "Change.h"
#include <algorithm>
#include "..\..\..\utils\Log.h"

Change* Change::change = NULL;

Change::Change(void){
	x  = 0, y  = 0,
	xp = 0, yp = 0;
}

Change::~Change(void){}

Change* Change::getInstance(){
	if(!change){
		change = new Change();
	}
	return change;
}

bool Change::newEvent(){
	bool result = true;
	if((x == xp) && (y == yp)){
		result = false;
	}
	else{
		xp = x, yp = y;
	}
	return result;
}


void Change::add(OnChangeListener * obj){
	if(!isRegistered(obj)){
		objects.push_back(obj);
	}
}

void Change::remuve(OnChangeListener * obj){
	list<OnChangeListener*>::iterator it;
	list<OnChangeListener*>::iterator itDrop;
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

void Change::notify(){
	list<OnChangeListener*>::iterator it;
	ChangeEvent co;
	co.x = x, co.y = y;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnChange(co);
	}
}


void Change::setEvent(int x, int y){
	this->x = x, this->y = y;
}


bool Change::isRegistered(OnChangeListener * obj){
	return (find(objects.begin(),
			objects.end(), 
			obj) != objects.end());
}
