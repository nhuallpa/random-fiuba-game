#include "Move.h"

Move* Move::move = NULL;

Move::Move(void){}

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

void Move::notify(){
	list<OnMovementListener*>::iterator it;
	MovementEvent m;
	//TODO: ver que le paso
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnMovement(m);
	}
}
