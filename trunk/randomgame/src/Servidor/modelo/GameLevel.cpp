#include "GameLevel.h"
#include "../../utils/Log.h"


using namespace std;


//ToDo @aliguo: crear nivel a partir de UL de YAML
GameLevel::GameLevel() {
	this->levelHeight = 100;
	this->levelWidth = 100;
}

GameLevel::~GameLevel() {

}

int GameLevel::getHeight() {
	return this->levelHeight;
}

int GameLevel::getWidth() {
	return this->levelWidth;
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

void GameLevel::setTerrain(TerrainProcessor* aNewTerrain)
{
	this->aTerrainProcessor=aNewTerrain;
}

void GameLevel::removeEntity(int id) {

	std::map<int, GameElement*>::iterator it = this->entities.begin();
	it = this->entities.find(id);
	if ( it != this->entities.end() ){
		this->entities.erase(it);
	}

	std::map<int, GameElement>::iterator it2 = this->modelElements.begin();
	it2 = this->modelElements.find(id);
	if ( it2 != this->modelElements.end() ){
		this->modelElements.erase(it2);
	}
}



bool GameLevel::posicionOcupada(float x, float y){
	//TODO @future - logic for placement / El modelo lo rechaza antes que Box2D
	//Chequear en base a radio/distancia del centro. Recibe pos central y tiene h, w


	return false;
}

bool GameLevel::validElementPosition(int j){

	ParserYaml* aParser = ParserYaml::getInstance();
	Log::t("Validando elemento: %d",j);
	// Chequeo si esta mas alla del ancho/alto del sistema en UL
	if ((Util::string2float(aParser->getElemX(j)) >
		Util::string2float(aParser->getEscenarioAnchoU())) ||
		(Util::string2float(aParser->getElemY(j)) >
		Util::string2float(aParser->getEscenarioAltoU()))  ||
		(Util::string2float(aParser->getElemX(j))<0) ||
		(Util::string2float(aParser->getElemY(j))<0) ){
			Log::i("Descartando elemento de id: %d por encontrarse fuera \
					de los limites del escenario", 
					Util::string2int(aParser->getElemId(j)) );
			return false;
	}
	return true;
}

bool GameLevel::createLevel(GameLevel&){

	ParserYaml* aParser = ParserYaml::getInstance();
	for (unsigned j=0;j<aParser->getCantElem();j++){
			std::string tipo = aParser->getElemTipo(j);

			if (!this->validElementPosition(j))
					continue;

			Log::i("Agregando: %d", Util::string2int(aParser->getElemId(j)));
			if (tipo.compare("rec") == 0)
			{
				this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
												SQUARE,
												Util::string2float(aParser->getElemX(j)),
												Util::string2float(aParser->getElemY(j)),
												Util::string2float(aParser->getElemRot(j)),
												Util::string2int(aParser->getElemAlto(j)),
												Util::string2int(aParser->getElemAncho(j)),
												Util::string2float(aParser->getElemMasa(j)), 
												Util::string2bool(aParser->getElemEstatico(j))));
			} 
			else if (tipo.compare("circ") == 0)
			{
				this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
												Util::string2float(aParser->getElemX(j)),
												Util::string2float(aParser->getElemY(j)),
												Util::string2float(aParser->getElemRadio(j)),
												Util::string2float(aParser->getElemEscala(j)),
												Util::string2float(aParser->getElemMasa(j)), 
												Util::string2bool(aParser->getElemEstatico(j))));
			}
			else if (tipo.compare("tri") == 0)
			{
				this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
												TRIANGLE,
												Util::string2float(aParser->getElemX(j)),
												Util::string2float(aParser->getElemY(j)),
												Util::string2float(aParser->getElemEscala(j)),
												Util::string2float(aParser->getElemRot(j)),
												Util::string2float(aParser->getElemMasa(j)), 
												Util::string2bool(aParser->getElemEstatico(j))));
			}
			else if (tipo.compare("pent") == 0)
			{
				 this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
												PENTA,
												Util::string2float(aParser->getElemX(j)),
												Util::string2float(aParser->getElemY(j)),
												Util::string2float(aParser->getElemEscala(j)),
												Util::string2float(aParser->getElemRot(j)),
												Util::string2float(aParser->getElemMasa(j)), 
												Util::string2bool(aParser->getElemEstatico(j))));
			}
			else if (tipo.compare("hexa") == 0)
			{
				this->addEntity(new GameElement(Util::string2int(aParser->getElemId(j)),
												HEXAGON,
												Util::string2float(aParser->getElemX(j)),
												Util::string2float(aParser->getElemY(j)),
												Util::string2float(aParser->getElemEscala(j)),
												Util::string2float(aParser->getElemRot(j)),
												Util::string2float(aParser->getElemMasa(j)), 
												Util::string2bool(aParser->getElemEstatico(j))));
			}
	}


	//ToDo chequear el nivel de agua no mayor al alto
	this->setWaterLevel(Util::string2float(aParser->getEscenarioAgua() ) );


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
	if ( this->validElementPosition(pos) ){

		std::map<int,GameElement*>::iterator it;
		it=	this->entities.find(id);
		it->second->setPosition(std::make_pair<float,float>(x,y));
		it->second->setAngle(angle);
	}
}


