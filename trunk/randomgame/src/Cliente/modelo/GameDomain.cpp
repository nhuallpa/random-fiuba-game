#include "GameDomain.h"

GameDomain::GameDomain(){
	
}
		
GameDomain::~GameDomain(void){
	
}

void GameDomain::updateElement(int id){

}

void GameDomain::setPlayerState(Player p, StateConn c, unsigned long color){
	this->playersPlaying[p] = std::make_pair(c,color);
}