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
	this->entities.insert(std::make_pair(entidad->getId(), entidad ));
	


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

bool GameLevel::createLevel(GameLevel&){
	//ToDo: crear nivel a partir de yaml persistido
	//ParserYaml* aParser = ParserYaml::getInstance();

	//if ( aParser->getDefault() == false ){
	//for(int i=0;i<1;i++){
	//	//std::cout<<"elementos:"<< aParser->getCantElem(i) << "\n\t\t";
	//	for(int j=0;j<aParser->getCantElem(i);j++){
	//		//std::cout<<"tipo: "<< aParser->getElemNombre(i,j)<<"\n\t\t";
	//		//std::cout<<"x: "<< aParser->getElemX(i,j)<<"\n\t\t";
	//		//std::cout<<"y: "<< aParser->getElemY(i,j)<<"\n\t\t";
	//		//std::cout<<"angulo: "<< aParser->getElemAngulo(i,j)<<"\n\t\t";

	//		this->addEntity(GameElement(
	//							aParser->getElementPosition(aParser->getElemNombre(i,j)),
	//							//nearest(boost::lexical_cast<float>( (aParser->getElemX(i,j)).c_str() )),
	//							//nearest(boost::lexical_cast<float>( (aParser->getElemY(i,j)).c_str() )),
	//							0.0,
	//							0.0,
	//							atoi( (aParser->getElemAngulo(i,j)).c_str()) ));

	//		//std::cout<<"added one at " <<  nearest(boost::lexical_cast<float>((aParser->getElemX(i,j)).c_str()))  << ", " << nearest(boost::lexical_cast<float>(((aParser->getElemY(i,j)).c_str()))) << std::endl;
	//	}
	//}
	//}
	
	//ToDo @aliguo: Agrego hardcoded un cuadrado
	this->addEntity(new GameElement(1,SQUARE,100.0,200.0,0.0,20,20,60.0, false));
	this->addEntity(new GameElement(2, 65.0, 150.0, 10.0, 1.0, 60.0, false));
	this->addEntity(new GameElement(3, HEXAGON, 65.0, 150.0, 1.0, 15.0, 0.0, false));

	//ToDo @aliguo: aca podria vincularlo directamente con Box2D si se complica la separacion (idea)
	return true;
}

std::map<int,GameElement> GameLevel::getModelElements(){
	std::map<int, GameElement*>::iterator it = this->entities.begin();

	//todo arreglar para que se actualicen los vertices
	//for ( ; it != this->entities.end(); it++){
	//	this->modelElements.insert(std::make_pair(it->second->getId(),
	//	GameElement(it->second->getId(), it->second->getType(), it->second->getPosition().first,
	//	it->second->getPosition().second, it->second->getRotation(), it->second->getHeight(), 
	//	it->second->getWidth(), it->second->getMass() ) ) );

	//}
	
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




