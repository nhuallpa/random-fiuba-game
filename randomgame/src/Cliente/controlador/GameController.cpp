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
