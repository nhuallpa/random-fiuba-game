#include "GameDomain.h"

GameDomain::GameDomain(){
}
		
GameDomain::~GameDomain(void){
	//TODO: Liberar game element?
}

void GameDomain::updateElement(int id, float posX, float posY){
	this->domainElements[id].setPosition(std::make_pair(posX,posY));
}

void GameDomain::updateElement(int id, float posX, float posY, Movement action){
	this->domainElements[id].setPosition(std::make_pair(posX,posY));
	this->domainElements[id].setAction(action);
}

void GameDomain::setPlayerState(Player p, StateConn c, unsigned long color){
	this->playersPlaying[p] = std::make_pair(c,color);
}