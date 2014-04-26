#include "GameController.h"

GameController::GameController() {

}

GameController::~GameController() {
}

void GameController::handleState(Contract* c){
	ctx.request(c);
}

bool GameController::isQuit(){
	return ctx.isQuit();
}


void GameController::addListener(OnClickListener* c){
	ctx.addListener(c);
}
void GameController::addListener(OnMovementListener* m){
	ctx.addListener(m);
}
void GameController::addListener(OnScrollListener* s){
	ctx.addListener(s);
}
void GameController::addListener(OnZoomListener* z){
	ctx.addListener(z);
}
void GameController::remuveListener(OnClickListener* c){
	ctx.addListener(c);
}
void GameController::remuveListener(OnMovementListener* m){
	ctx.addListener(m);
}
void GameController::remuveListener(OnScrollListener* s){
	ctx.addListener(s);
}
void GameController::remuveListener(OnZoomListener* z){
	ctx.addListener(z);
}