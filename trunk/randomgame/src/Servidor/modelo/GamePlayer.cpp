#include "GamePlayer.h"
#include "..\..\utils\Util.h"
#include "TerrainProcessor.h"

GamePlayer::GamePlayer(){}

GamePlayer::~GamePlayer(){}

void GamePlayer::initPlayer(int prefId, int amountWorms){

	int x, y;
	for(int i = 0; i < amountWorms; i++){
		TerrainProcessor::getRandomPosition(&x, &y);
		
		x = rand()%500;
		y = (rand()%150) + 100; 
		//AL WORM LE FALTA EL ESTADO {0:MUERTO, 1:VIVO}
		this->add(new Worm(prefId + i, 
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

GamePlayer* GamePlayer::NewPlayerFactory(int prefId, int amountWorms){
	GamePlayer* gp = new GamePlayer();
	gp->state = CONNECTED;
	int x, y;
	for(int i = 0; i < amountWorms; i++){
		TerrainProcessor::getRandomPosition(&x, &y);
		//AL WORM LE FALTA EL ESTADO {0:MUERTO, 1:VIVO}
		gp->add(new Worm(prefId + i, 
						 WORM,
						 x,
						 y,
						 0, //PREGUNTAR A ARI QUE SETEAR
						 10,//PREGUNTAR A ARI QUE SETEAR
						 10,//PREGUNTAR A ARI QUE SETEAR
						 20,//PREGUNTAR A ARI QUE SETEAR
						 true));//PREGUNTAR A ARI QUE SETEAR
	}
	return gp;
}

void GamePlayer::setStateConn(StateConn sc){
	this->state = sc;
}

void GamePlayer::add(Worm* w){
	worms.push_back(w);
}
