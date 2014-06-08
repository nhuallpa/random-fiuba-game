#pragma once

#ifndef __GAMEDOMAIN_H__
#define __GAMEDOMAIN_H__


#include <string>
#include <vector>
#include <list>

#include "../../utils/Util.h"
#include "../../Servidor/modelo/GameElement.h"





class GameDomain{

	std::string playerID;
	std::map<int,GameElement> domainElements;
	
	// Key: PlayerID, Elem: Pair<State,Color>
	std::map<Player,std::pair<StateConn,unsigned long>> playersPlaying;

public:

	GameDomain();
	 ~GameDomain(void);

	 void setPlayerID(std::string playerID){ this->playerID = playerID; }
	 std::string getPlayerID(){ return this->playerID; }

	 void addElementToDomain(GameElement element)
	 {
			this->domainElements.insert( std::make_pair(element.getId(),element) ); 
	 }

	 std::map<int,GameElement>* getDomainElements() { return &this->domainElements;}

	 void updateElement(int id, float x, float y);
	 void updateElement(int id, float x, float y, Movement action);

	 StateConn getPlayerState(Player p){ return this->playersPlaying[p].first; }
	 unsigned long getPlayerColor(Player p){ return this->playersPlaying[p].second; }
	 void setPlayerState(Player p, StateConn c, unsigned long color);
	 void addPlayer(Player p, StateConn c, unsigned long color){
		this->playersPlaying[p] = std::make_pair(c,color);
	}

	 void updatePlayerStatus(Player p, StateConn st){
		 this->playersPlaying[p] = std::make_pair(st,this->playersPlaying[p].second);
	 }

};

#endif