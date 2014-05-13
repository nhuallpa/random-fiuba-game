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
    std::pair<int,int> puntoTransformado;
	printf("\n Height %d, width %d ",height,width);

	puntoTransformado = transformBmpToBox2D(pair<int,int>(0,0),height,width);
	printf("\n Transformo el 0,0: %d,%d",puntoTransformado.first, puntoTransformado.second);

	puntoTransformado = transformBmpToBox2D(pair<int,int>(0,height),height,width);
	printf("\n Transformo el 0,HEIGHT: %d,%d",puntoTransformado.first, puntoTransformado.second);

	puntoTransformado = transformBmpToBox2D(pair<int,int>(width,height),height,width);
	printf("\n Transformo el WIDTH,HEIGHT: %d,%d",puntoTransformado.first, puntoTransformado.second);

	puntoTransformado = transformBmpToBox2D(pair<int,int>(width,0),height,width);
	printf("\n Transformo el WIDTH,0: %d,%d",puntoTransformado.first, puntoTransformado.second);

	puntoTransformado = transformBmpToBox2D(pair<int,int>(30,960),height,width);
	printf("\n Transformo el WIDTH/2,HEIGHT/2: %d,%d",puntoTransformado.first, puntoTransformado.second);
	//for ( int z; i < 200 ; i++){
	//	gp->getRandomPosition(&x, &y);
	//	printf("\nPosicion libre: %d,%d",x,y);
	//}

	


	for(int i = 0; i < amountWorms; i++){
		gp->getRandomPosition(&x, &y);
		if((x != -1) && (y != -1)){
			printf("Posicion libre a transformar %d,%d",x,y);
			puntoTransformado = transformBmpToBox2D(pair<int,int>(x,y),height,width);
			x=puntoTransformado.first;
			y=puntoTransformado.second;
			this->add(new Worm(prefId + i,
							this->playerID,
							 WORM,
							 x/10.0,
							 y/10.0,
							 0, //PREGUNTAR A ARI QUE SETEAR
							 3,//PREGUNTAR A ARI QUE SETEAR
							 3,//PREGUNTAR A ARI QUE SETEAR
							 20,//PREGUNTAR A ARI QUE SETEAR
							 true));//PREGUNTAR A ARI QUE SETEAR
		}
		
		else{     
			printf("\n Como no confio en Erik creo a mano esto\n");
            x = rand()%500;
            y = (rand()%150) + 100; 
            //AL WORM LE FALTA EL ESTADO {0:MUERTO, 1:VIVO}
            this->add(new Worm(prefId + i, 
								this->playerID,
                                WORM,
                                x/ESCALA_UL2PX,
                                y/ESCALA_UL2PX,
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

//	swapea los valores del b2vec
pair<int,int> GamePlayer::transformBmpToBox2D(pair<int,int> vertex, int height, int width)
{
	ParserYaml* aParser = ParserYaml::getInstance();
	pair<int,int> nuevo;
	//nuevo.second =vertex.first;
	//nuevo.first = (height-vertex.second);
	nuevo.second = height-vertex.first;
	nuevo.first = vertex.second;

	/*nuevo.y =((-1*vertex.x)+height-1)*(atoi((aParser->getEscenarioAltoU()).c_str() ) / (float)height);
	nuevo.x = (vertex.y)*(atoi((aParser->getEscenarioAnchoU()).c_str() ) / (float)width);*/
	return nuevo;
}