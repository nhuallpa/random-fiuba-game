#include "GameController.h"
#include "..\..\utils\Log.h"

GameController::GameController(){
	rg = RunGame::getInstance();
}
GameController::~GameController(){}

void GameController::handlerEvent(){
	rg->addCallFromSDL();
	rg->addCallFromOver();
	rg->call();
}

bool GameController::isQuit(){
	return rg->isQuit();
}


void GameController::destroy(){
	rg->destroy();
}

void GameController::addListener(OnClickListener* c){
	Click* ck = Click::getInstance();
	ck->add(c);
}
void GameController::addListener(OnMovementListener* m){
	Move* mv = Move::getInstance();
	mv->add(m);
}
void GameController::addListener(OnScrollListener* s){
	Over* o = Over::getInstance();
	o->add(s);
}
void GameController::addListener(OnZoomListener* z){
	Zoom* zm = Zoom::getInstance();
	zm->add(z);
}
void GameController::remuveListener(OnClickListener* c){
	Click* ck = Click::getInstance();
	ck->remuve(c);
}
void GameController::remuveListener(OnMovementListener* m){
	Move* mv = Move::getInstance();
	mv->remuve(m);
}
void GameController::remuveListener(OnScrollListener* s){
	Over* o = Over::getInstance();
	o->remuve(s);
}
void GameController::remuveListener(OnZoomListener* z){
	Zoom* zm = Zoom::getInstance();
	zm->remuve(z);
}
