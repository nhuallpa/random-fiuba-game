#include "GameLevel.h"
#include "../../utils/Log.h"
#include "GamePosition.h"

#define MAXPLAYER 1
#define ERRPLAYER 2

using namespace std;


GameLevel::GameLevel() {

	ParserYaml* aParser = ParserYaml::getInstance();
	this->levelHeight = 100;
	this->levelWidth = 100;
	this->amountUser = Util::string2int(aParser->getMetaMaxPlay()); 
	this->amountWorms = Util::string2int(aParser->getMetaMaxPj());
	this->idUnique = 1;

}

GameLevel::~GameLevel() {

}

int GameLevel::getHeight() {
	return this->levelHeight;
}

int GameLevel::getWidth() {
	return this->levelWidth;
}

void GameLevel::addUserIntoLevel(string user){
	GamePlayer* player = NULL;
	try{
		player = getPlayer(user);
		if(player == NULL){
			this->addPlayer(user, 
				GamePlayer::NewPlayerFactory(this->idUnique,
				                             this->amountWorms));
			(this->idUnique)++;
		}
		else{
			player->setStateConn(CONNECTED);
		}
	}
	catch(PlayerExp pe){
		throw pe;
	}
	catch(...){
		throw PlayerExp(ERRPLAYER);
	}
}

GamePlayer* GameLevel::getPlayer(string user){
	map<string, GamePlayer*>::iterator it;
	it = players.find(user);
	if(it != players.end())
		return (*it).second;
	else
		return NULL;
}

void GameLevel::addPlayer(string user, GamePlayer *pg){
	if(players.size() == this->amountUser){
		throw PlayerExp(MAXPLAYER);
	}
	this->players.insert(
		pair<string, GamePlayer*>(user,pg));
}


//float nearest(float f){
//	return floorf(f * 100 + 0.5) / 100; 
//}

void GameLevel::addEntity(GameElement *entidad) {
	//this->entities.insert(std::make_pair(entidad->getId(), entidad ));
	this->entities[entidad->getId()] = entidad;
	
	// TODO reflect to modelEntities (the one used for pass data) //future
	//this->modelElements[entidad->getId()] = *entidad;


}

void GameLevel::setHeight(int h){
	this->levelHeight = h;
}

void GameLevel::setWidth(int w){
	this->levelWidth = w;
}

void GameLevel::setTerrain( b2World* mworld, char* path,float epsilon, int scale,int waterLevel )
{
	GamePosition * gp = GamePosition::getInstance();
	TerrainProcessor* aNewTerrain = new TerrainProcessor();
	aNewTerrain->process(mworld, path, epsilon, scale, waterLevel, true, &this->myTerrain, this->myPol);
 
	if(!gp->isCompleted()){
		list<pair<int,int>> *l =aNewTerrain->getRangeTerrainOverWater();
		
		gp->generate(aNewTerrain->getMaxPointTerrain().first, aNewTerrain->getWidth());
		gp->validPosition(l);
	}
	this->aTerrainProcessor = aNewTerrain;
}

void GameLevel::removeEntity(int id) {

	std::map<int, GameElement*>::iterator it = this->entities.begin();
	it = this->entities.find(id);
	if ( it != this->entities.end() ){
		this->entities.erase(it);
	}

	//std::map<int, GameElement>::iterator it2 = this->modelElements.begin();
	//it2 = this->modelElements.find(id);
	//if ( it2 != this->modelElements.end() ){
	//	this->modelElements.erase(it2);
	//}
}



bool GameLevel::posicionOcupada(float x, float y){
	//TODO @future - logic for placement / El modelo lo rechaza antes que Box2D
	//Chequear en base a radio/distancia del centro. Recibe pos central y tiene h, w


	return false;
}

bool GameLevel::validElementPosition(int j){

	ParserYaml* aParser = ParserYaml::getInstance();
	//Log::t("Validando elemento: %d",j);
	// Chequeo si esta mas alla del ancho/alto del sistema en UL
	if ((Util::string2float(aParser->getElemX(j)) >
		Util::string2float(aParser->getEscenarioAnchoU())) ||
		(Util::string2float(aParser->getElemY(j)) >
		Util::string2float(aParser->getEscenarioAltoU()))  ||
		(Util::string2float(aParser->getElemX(j))<0) ||
		(Util::string2float(aParser->getElemY(j))<0) )
			Log::i("Elemento id: %d se encuentra fuera de los limites del escenario", 
					Util::string2int(aParser->getElemId(j)) );
	//		return false;
	//}
	return true;
}

bool GameLevel::createLevel(GameLevel* gl){

	ParserYaml* aParser = ParserYaml::getInstance();
	//Deprecated at TP2
	//for (unsigned j=0;j<aParser->getCantElem();j++){
	//		std::string tipo = aParser->getElemTipo(j);

	//		if (!this->validElementPosition(j))
	//				continue;

	//		Log::i("Agregando: %d", Util::string2int(aParser->getElemId(j)));
	//		if (tipo.compare("rec") == 0)
	//		{
	//			this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
	//											SQUARE,
	//											Util::string2float(aParser->getElemX(j)),
	//											Util::string2float(aParser->getElemY(j)),
	//											Util::string2float(aParser->getElemRot(j)),
	//											Util::string2int(aParser->getElemAlto(j)),
	//											Util::string2int(aParser->getElemAncho(j)),
	//											Util::string2float(aParser->getElemMasa(j)), 
	//											Util::string2bool(aParser->getElemEstatico(j))));
	//		} 
	//		else if (tipo.compare("circ") == 0)
	//		{
	//			this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
	//											Util::string2float(aParser->getElemX(j)),
	//											Util::string2float(aParser->getElemY(j)),
	//											Util::string2float(aParser->getElemRadio(j)),
	//											Util::string2float(aParser->getElemEscala(j)),
	//											Util::string2float(aParser->getElemMasa(j)), 
	//											Util::string2bool(aParser->getElemEstatico(j))));
	//		}
	//		else if (tipo.compare("tri") == 0)
	//		{
	//			this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
	//											TRIANGLE,
	//											Util::string2float(aParser->getElemX(j)),
	//											Util::string2float(aParser->getElemY(j)),
	//											Util::string2float(aParser->getElemEscala(j)),
	//											Util::string2float(aParser->getElemRot(j)),
	//											Util::string2float(aParser->getElemMasa(j)), 
	//											Util::string2bool(aParser->getElemEstatico(j))));
	//		}
	//		else if (tipo.compare("pent") == 0)
	//		{
	//			 this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
	//											PENTA,
	//											Util::string2float(aParser->getElemX(j)),
	//											Util::string2float(aParser->getElemY(j)),
	//											Util::string2float(aParser->getElemEscala(j)),
	//											Util::string2float(aParser->getElemRot(j)),
	//											Util::string2float(aParser->getElemMasa(j)), 
	//											Util::string2bool(aParser->getElemEstatico(j))));
	//		}
	//		else if (tipo.compare("hexa") == 0)
	//		{
	//			this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
	//											HEXAGON,
	//											Util::string2float(aParser->getElemX(j)),
	//											Util::string2float(aParser->getElemY(j)),
	//											Util::string2float(aParser->getElemEscala(j)),
	//											Util::string2float(aParser->getElemRot(j)),
	//											Util::string2float(aParser->getElemMasa(j)), 
	//											Util::string2bool(aParser->getElemEstatico(j))));
	//		}
	//}


	//ToDo chequear el nivel de agua no mayor al alto
	gl->setWaterLevel(Util::string2float(aParser->getEscenarioAgua() ) );


	return true;
}

std::map<int,GameElement> GameLevel::getModelElements(){
	return this->modelElements;
}


std::map<int, GameElement*> GameLevel::getEntities(){
	return (this->entities);
}

TerrainProcessor* GameLevel::getTerrain()
{
	return this->aTerrainProcessor;
}

void GameLevel::destroyEntities(){
	std::map<int, GameElement*>::iterator it = this->entities.begin();
	for ( ; it != this->entities.end(); it++){
		delete (*it).second;
	}
}


// Chequea posiciones dentro del mapa
bool GameLevel::checkMapPosition(float x, float y){
	//std::cout << "validando: " << x << ", " << y << std::endl;
	if (x > this->getWidth() || x < 0)
		return false;

	if (y > this->getHeight() || y < 0)
			return false;

	return true;
}

void GameLevel::updateElementPosition(int pos, int id, float x, float y, float angle){

	Log::t("Examinando elemento: %d", pos);


	if ( this->validElementPosition(pos) && this->entities.count(id)){

		std::map<int,GameElement*>::iterator it;
		it=	this->entities.find(id);
		it->second->setPosition(std::make_pair<float,float>(x,y));
		it->second->setAngle(angle);
	}
}


PlayerAccounting GameLevel::acceptPlayer(std::string playerID){

	map<string, GamePlayer*>::iterator it;
	it=this->players.find(playerID);

	if ( it != this->players.end() ){
		
		//Si ya esta conectado lo rechazo
		if ( it->second->getStatus() == CONNECTED || it->second->getStatus() == RECONNECTED )
			return PLAYER_NOT_ALLOWED;

		// Esta en la lista de jugadores del nivel, lo seteo como conectado y lo acepto
		it->second->setStateConn(RECONNECTED);
		
		//Update all their worms has connected
		this->connectWormsFromPlayer(playerID);
		
		return EXISTING_PLAYER;
	}

	if ( this->players.size() < this->amountUser ){
		// No esta en la lista pero lo acepto porque entra
	
		GamePlayer* gp = new GamePlayer(playerID);
		int height = aTerrainProcessor->getHeight();
		int width = aTerrainProcessor->getWidth();
		gp->initPlayer(this->idUnique,this->amountWorms,height,width);
		this->idUnique += this->amountWorms;
		gp->setStateConn(CONNECTED);

		this->players.insert(std::make_pair(playerID,gp));

		//Agrego los worms del jugador al nivel
		std::vector<Worm*> copy = gp->getWorms();
		for (std::vector<Worm*>::const_iterator itW = copy.begin() ; itW != copy.end(); itW++){
			this->addEntity( (*itW) );
		}

		this->connectWormsFromPlayer(playerID);
		return NEW_PLAYER;
	}

	return PLAYER_NOT_ALLOWED;

}

void GameLevel::disconnectPlayer(std::string playerID){

	map<string, GamePlayer*>::iterator it;
	it=this->players.find(playerID);

	if ( it != this->players.end() ){
		
		it->second->setStateConn(DISCONNECTED);
	}

}

StateConn GameLevel::getPlayerStatus(std::string playerID){

	map<string, GamePlayer*>::iterator it;
	it=this->players.find(playerID);

	if ( it != this->players.end() ){
		
		return it->second->getStatus();
	}

	return DISCONNECTED;
		
}



int GameLevel::getWormsFromPlayer(std::string playerId, Playable* p){

	map<string, GamePlayer*>::iterator it;
	it=this->players.find(playerId);
	int i=0;

	if ( it != this->players.end() ){
		

		std::vector<Worm*> copy = it->second->getWorms();
		for ( std::vector<Worm*>::const_iterator itW = copy.begin() ; itW != copy.end(); itW++, i++){
			
			p[i].wormid = (*itW)->getId();
			p[i].x = (*itW)->getPosition().first;
			p[i].y = (*itW)->getPosition().second;
			p[i].action = (*itW)->getAction();

		}


	}

	return i;

}


void GameLevel::disconnectWormsFromPlayer(std::string playerId){

	map<string, GamePlayer*>::iterator it;
	it=this->players.find(playerId);

	if ( it != this->players.end() ){
		std::vector<Worm*> copy = it->second->getWorms();
		for ( std::vector<Worm*>::const_iterator itW = copy.begin() ; itW != copy.end(); itW++){
			if ( (*itW)->getAction() == MOVE_LEFT || (*itW)->getAction() == MOVELESS_LEFT)
			{
				(*itW)->myLastAction=NOT_CONNECTED_LEFT;
				(*itW)->setAction(NOT_CONNECTED_LEFT);
			}
			else 	if ( (*itW)->getAction() == MOVE_RIGHT || (*itW)->getAction() == MOVELESS_RIGHT)
			{
				(*itW)->myLastAction=NOT_CONNECTED_RIGHT;
				(*itW)->setAction(NOT_CONNECTED_RIGHT);
			}
			else
			{
				(*itW)->myLastAction=NOT_CONNECTED;
				(*itW)->setAction(NOT_CONNECTED);
			}
				
		}
	}
}

void GameLevel::connectWormsFromPlayer(std::string playerId){

	map<string, GamePlayer*>::iterator it;
	it=this->players.find(playerId);

	if ( it != this->players.end() ){

		std::vector<Worm*> copy = it->second->getWorms();

		for ( std::vector<Worm*>::const_iterator itW = copy.begin() ; itW != copy.end(); itW++){
			if ( (*itW)->getAction() == MOVE_RIGHT || (*itW)->getAction() == NOT_CONNECTED_RIGHT || (*itW)->getAction() == MOVELESS_RIGHT ){
				(*itW)->setAction(MOVELESS_RIGHT);
			} else if ( (*itW)->getAction() == MOVE_LEFT || (*itW)->getAction() == NOT_CONNECTED_LEFT || (*itW)->getAction() == MOVELESS_LEFT ) {
				(*itW)->setAction(MOVELESS_LEFT);
			}else
				(*itW)->setAction(MOVELESS);
		}

	}

}


poly_t GameLevel::makeConvexRing(b2Vec2 position, float radius, int vertices)
{
	poly_t convexRing;
	const float theta = boost::math::constants::two_pi<float>() / static_cast<float>(vertices);

	float c = std::cos(theta);
	float s = std::sin(theta);

	float t = 0.0f;
	float y = 0.0f;
	float x = radius;
	for (float i = 0; i < vertices; i++)
	{
		float v_x = x + position.x;
		float v_y = y + position.y;
		bg::append(convexRing, point(v_x, v_y));

		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}

	return convexRing;
}


void GameLevel::doExplosion(b2Vec2 removalPosition, int removalRadius, b2World* mundo){

	poly_t* explosion = new poly_t();
	*explosion = this->makeConvexRing(removalPosition, removalRadius, 16);
			
	list <poly_t*>* afterExplode = new list<poly_t*>();
	for(list<poly_t*>::iterator it = this->myPol->begin(); it != this->myPol->end(); it++){
		list <poly_t>* output = new list<poly_t>();
		boost::geometry::difference(*(*it), *explosion, *output);
		for(list<poly_t>::iterator it2 = output->begin(); it2 != output->end(); it2++){
				afterExplode->push_back(&(*it2));
		}
	}
	this->myPol->clear();
	this->myPol = afterExplode;

	for(std::vector<b2Body*>::iterator it = myTerrain.begin(); it != myTerrain.end(); it++){
			mundo->DestroyBody(*it);
	}

	myTerrain.clear();

	for(std::list<poly_t*>::iterator it = afterExplode->begin(); it != afterExplode->end(); it++){
		b2BodyDef* bd = new b2BodyDef();
		b2Vec2* vs = new b2Vec2[(*it)->outer().size()];
		int vertexCount = 0;
		for(vector<point>::iterator it2 = (*it)->outer().begin(); it2 != (*it)->outer().end(); it2++){
				vs[vertexCount].Set((*it2).get<0>(),(*it2).get<1>());
				vertexCount++;
		}

		b2ChainShape shape;
		shape.CreateChain(vs, vertexCount);

		bd->type = b2_staticBody; //this will be a static body
		b2Body* newTerrainBody = mundo->CreateBody(bd);

		b2FixtureDef myFixtureDef;
		myFixtureDef.friction = 0.999;
		myFixtureDef.userData = ( (void*)2 );
		myFixtureDef.shape = &shape; //change the shape of the fixture
		newTerrainBody->CreateFixture(&myFixtureDef);	
		
		myTerrain.push_back(newTerrainBody);
	}

}










