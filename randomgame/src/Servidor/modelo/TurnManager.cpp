#include "TurnManager.h"

TurnManager::TurnManager(int nrPlayers):
	maxPlayers(nrPlayers){

	this->indicator = NOT_YET_ASSIGNED;

}



void TurnManager::addPlayer(std::string player){
	this->players.push_back(player);
}

void TurnManager::removePlayer(std::string player){

	for ( std::vector<std::string>::iterator it = this->players.begin(); it != this->players.end(); ++it){
		if ( !it->compare(player) ){
			this->players.erase(it);
		}
	}

}



std::string TurnManager::getNextPlayerTurn(){
	if ( this->indicator == NOT_YET_ASSIGNED ){
		this->indicator = rand() % this->maxPlayers;
		return this->players[indicator];
	}
	int newPos = this->indicator + 1;
	this->indicator = newPos % this->maxPlayers;
	return this->players[indicator];
}


TurnManager::TurnManager(){

}

TurnManager::~TurnManager(){

}


