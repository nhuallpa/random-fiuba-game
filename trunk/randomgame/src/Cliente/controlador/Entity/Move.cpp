#include "Move.h"

Move* Move::move = NULL;

Move::Move(void){
	x  = 0, y  = 0,
	xp = 0, yp = 0;
	shoot = 0, shootp = 0;
}

Move::~Move(void){}

Move* Move::getInstance(){
	if(!move){
		move = new Move();
	}
	return move;
}

void Move::add(OnMovementListener* obj){
	objects.push_back(obj);
}

void Move::remuve(OnMovementListener* obj){
	list<OnMovementListener*>::iterator it;
	list<OnMovementListener*>::iterator itDrop;
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

bool Move::newEvent(){
	bool result = true;
	if((x == xp) && (y == yp) && (shoot == shootp)){
		result = false;
	}
	else{
		if((x == xp) && (y == yp) && (shoot == 0)){
			result = false;
		}
		xp = x, yp = y, shootp = shoot;

	}
	return result;
}

void Move::notify(){
	list<OnMovementListener*>::iterator it;
	MovementEvent m;
	m.x = this->x, m.y = this->y;
	m.shoot = this->shoot;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnMovement(m);
	}
	//Log::i("(x,y,z)=(%d,%d,%d)",m.x,m.y,m.shoot);
}
