#include "GameLevel.h"
#include "../../utils/Log.h"


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

float nearest(float f){
	return floorf(f * 100 + 0.5) / 100; 
}

void GameLevel::addEntity(GameElement entidad) {

	//if ( entidad.getPosition().first < 0 )
	//	entidad.setPosition( std::make_pair(0,entidad.getPosition().second) );
	//if ( entidad.getPosition().first > this->getWidth() )
	//	entidad.setPosition( std::make_pair(this->getWidth(),entidad.getPosition().second) );
	//if ( entidad.getPosition().second < 0 )
	//	entidad.setPosition( std::make_pair(entidad.getPosition().first,0) );
	//if ( entidad.getPosition().second > this->getHeight() )
	//	entidad.setPosition( std::make_pair(entidad.getPosition().first,this->getHeight()) );
	// Log::d("Adding to model %d, %d", entidad.getPosition().first, entidad.getPosition().second);
	this->entities.insert(std::make_pair( entidad.getPosition(), entidad ));
}

void GameLevel::setHeight(int h){
	this->levelHeight = h;
}

void GameLevel::setWidth(int w){
	this->levelWidth = w;
}

void GameLevel::removeEntity(std::pair<float,float> pos) {
	std::pair<float,float> pos2 = std::make_pair((float)pos.first,(float)pos.second);
	//std::cout << "removiendo: "<< pos2.first << ", " << pos2.second << std::endl;
	std::multimap<std::pair<float, float>, GameElement>::iterator it = this->entities.begin();
	//for ( ; it != this->entities.end(); it++)
	//	std::cout << "elem: " << (*it).first.first << ", " << (*it).first.second << std::endl;
	it = this->entities.find(pos2);
	if ( it != this->entities.end() ){
		//std::cout << "encontrado: " << (*it).first.first << ", " << (*it).first.second << std::endl;
		this->entities.erase(it);
	}
}



bool GameLevel::posicionOcupada(float x, float y){
	//TODO @future - logic for placement / El modelo lo rechaza antes que Box2D
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
	this->addEntity(GameElement(SQUARE,10.0,10.0,45,3,4,15.0));

	//ToDo @aliguo: aca podria vincularlo directamente con Box2D si se complica la separacion (idea)

	return true;


}


std::multimap<std::pair<float, float>, GameElement> GameLevel::getEntities(){
	return (this->entities);
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




