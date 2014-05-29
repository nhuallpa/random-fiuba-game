#include "GameDomain.h"

GameDomain::GameDomain(){
}
		
GameDomain::~GameDomain(void){
	//TODO: Liberar game element?
}

void GameDomain::updateElement(int id, float posX, float posY){
	std::map<int,GameElement>::iterator it;

	it = this->domainElements.find(id);
	if ( it != this->domainElements.end() ){
		this->domainElements[id].setPosition(std::make_pair(posX,posY));
	}
}

void GameDomain::updateElement(int id, float posX, float posY, Movement action){
	std::map<int,GameElement>::iterator it;

	it = this->domainElements.find(id);

	if ( it != this->domainElements.end() ){
		this->domainElements[id].setPosition(std::make_pair(posX,posY));
		this->domainElements[id].setAction(action);
	} else {
		Log::e("GameDomain::updateElement: No se pudo actualizar el worm id %d", id);
	}

}

void GameDomain::setPlayerState(Player p, StateConn c, unsigned long color){
	this->playersPlaying[p] = std::make_pair(c,color);
}

