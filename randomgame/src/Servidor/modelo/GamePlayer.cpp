#include "GamePlayer.h"
#include "..\..\utils\Util.h"
#include "TerrainProcessor.h"
#include "GamePosition.h"

GamePlayer::GamePlayer(std::string playerID){
	this->playerID = playerID;
}

GamePlayer::~GamePlayer(){}

void GamePlayer::initPlayer(int prefId, int amountWorms){
	GamePosition * gp = GamePosition::getInstance();
	int x, y;
	for(int i = 0; i < amountWorms; i++){
		gp->getRandomPosition(&x, &y);

		//AL WORM LE FALTA EL ESTADO {0:MUERTO, 1:VIVO}
		if((x != -1) && (y != -1)){
			this->add(new Worm(prefId + i,
							this->playerID,
							 WORM,
							 x,
							 y,
							 0, //PREGUNTAR A ARI QUE SETEAR
							 10,//PREGUNTAR A ARI QUE SETEAR
							 10,//PREGUNTAR A ARI QUE SETEAR
							 20,//PREGUNTAR A ARI QUE SETEAR
							 true));//PREGUNTAR A ARI QUE SETEAR
		}
						 
	}

}

GamePlayer* GamePlayer::NewPlayerFactory(int prefId, int amountWorms){
	//deprecated
	GamePlayer* gp = new GamePlayer("player");
	//gp->state = CONNECTED;
	//int x, y;
	//for(int i = 0; i < amountWorms; i++){
	//	TerrainProcessor::getRandomPosition(&x, &y);
	//	//AL WORM LE FALTA EL ESTADO {0:MUERTO, 1:VIVO}
	//	gp->add(new Worm(prefId + i, 
	//					 WORM,
	//					 x,
	//					 y,
	//					 0, //PREGUNTAR A ARI QUE SETEAR
	//					 10,//PREGUNTAR A ARI QUE SETEAR
	//					 10,//PREGUNTAR A ARI QUE SETEAR
	//					 20,//PREGUNTAR A ARI QUE SETEAR
	//					 true));//PREGUNTAR A ARI QUE SETEAR
	//}
	return gp;
}

void GamePlayer::setStateConn(StateConn sc){
	this->state = sc;
}

void GamePlayer::add(Worm* w){
	worms.push_back(w);
}
