#include "GameLevel.h"

using namespace std;



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


void GameLevel::addEntity(GameElement entidad) {
	// TODO @LOG - std::cout << "adding to model" << entidad.getPosition().first << ", " << entidad.getPosition().second << std::endl;
	this->entities.insert(make_pair(entidad.getPosition(),entidad));
}

void GameLevel::setHeight(int h){
	this->levelHeight = h;
}

void GameLevel::setWidth(int w){
	this->levelWidth = w;
}

void GameLevel::removeEntity(GameElement entidad) {
	//TODO
}



bool GameLevel::posicionOcupada(float x, float y){
	//TODO @future - logic for placement
	return false;
}

void GameLevel::entityUpdatePosition(int tileX, int tileY, int id){

}

bool GameLevel::createLevel(GameLevel&){

	//TODO Parse YAML
	//ParserYaml::...;

	// Add entities to the world based on YAML output
	//... i.e.:
	this->addEntity(GameElement(SQUARE,0,0,0));
	this->addEntity(GameElement(PENTAGON,20,20,45));
	this->addEntity(GameElement(CIRCLE,40,40,0));
	this->addEntity(GameElement(TRIANGLE,0,50,10));

	return true;


}


std::multimap<std::pair<float, float>, GameElement> GameLevel::getEntities(){
	return (this->entities);
}


bool GameLevel::checkMapPosition(float x, float y){
	if (x > this->getWidth() || x < 0)
		return false;

	if (y > this->getHeight() || y < 0)
			return false;

	return true;
}




