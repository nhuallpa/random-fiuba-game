#include "GamePlayer.h"
#include "..\..\utils\Util.h"
#include "TerrainProcessor.h"
#include "GamePosition.h"

GamePlayer::GamePlayer(std::string playerID){
	this->playerID = playerID;
}

GamePlayer::~GamePlayer(){}

void GamePlayer::initPlayer(int prefId, int amountWorms,int height, int width){
	GamePosition * gp = GamePosition::getInstance();
	int x, y;
	int i = 0;
	/*height*=10;
	width*=10;*/
	for(int i = 0; i < amountWorms; i++){
		gp->getRandomPosition(&x, &y);
		if((x != -1) && (y != -1)){
			auto puntoTransformado=transformBmpToBox2D(pair<int,int>(x,y),height,width);
			x=puntoTransformado.first;
			y=puntoTransformado.second;
			this->add(new Worm(prefId + i,
							this->playerID,
							 WORM,
							 x,
							 height - y,
							 0, //PREGUNTAR A ARI QUE SETEAR
							 10,//PREGUNTAR A ARI QUE SETEAR
							 10,//PREGUNTAR A ARI QUE SETEAR
							 20,//PREGUNTAR A ARI QUE SETEAR
							 true));//PREGUNTAR A ARI QUE SETEAR
		}
		
		//else{     
  //          x = rand()%500;
  //          y = (rand()%150) + 100; 
  //          //AL WORM LE FALTA EL ESTADO {0:MUERTO, 1:VIVO}
  //          this->add(new Worm(prefId + i, 
		//						this->playerID,
  //                              WORM,
  //                              x,
  //                              y,
  //                              0, //PREGUNTAR A ARI QUE SETEAR
  //                              10,//PREGUNTAR A ARI QUE SETEAR
  //                              10,//PREGUNTAR A ARI QUE SETEAR
  //                              20,//PREGUNTAR A ARI QUE SETEAR
  //                              true));//PREGUNTAR A ARI QUE SETEAR
		//}

						 
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

//	swapea los valores del b2vec
pair<int,int> GamePlayer::transformBmpToBox2D(pair<int,int> vertex, int height, int width)
{
	ParserYaml* aParser = ParserYaml::getInstance();
	pair<int,int> nuevo;
	nuevo.second =vertex.first/10;
	nuevo.first = (height-vertex.second)/10;
	return nuevo;
}