#include "GamePosition.h"
#include "..\..\utils\ParserYaml.h"
#include "..\..\utils\Util.h"

GamePosition* GamePosition::gp = NULL;

GamePosition::GamePosition(){
	//TODO: Aca trasformar a WORM_WIDTH = 30, WORM_HEIGHT = 30
	deltaY = WORM_WIDTH;
	deltaX = WORM_HEIGHT;
	supreme = -1;
}

void GamePosition::generate(int supreme){
	ParserYaml* py = ParserYaml::getInstance();
	list<int> listX;
	int value = 0;
	
	int countWidth = (int)(Util::string2int(py->getEscenarioAnchoP()) / 
		deltaX);
	int countHight =(int)(supreme / deltaY);

	for(int i = 0; i < countHight; i++){
		listX.push_back(value);
		value += deltaX;
	}
	value = 0;
	for(int i = 0; i < countWidth; i++){
		positions.insert(pair<int, list<int>>(value, listX));
		value += deltaY;
	}

}

void GamePosition::validPosition(list<pair<int,int>>* terrain){
	list<map<int, list<int>>::iterator> remuve;
	list<map<int, list<int>>::iterator>::iterator rt;
	map<int, list<int>>::iterator it;
	map<int, list<int>>::iterator itAux;
	list<pair<int,int>>::iterator iit;
	itAux = positions.begin();
	iit = terrain->begin();
	int yMin = 0, yMax = 0, size = 0;
	
	
	for(; iit != terrain->end(); iit++){
		yMin = iit->first;
		yMax = iit->second;
		for(it = itAux; it != positions.end(); it++){
			if( it->first < yMin	){
				remuve.push_back(it);
			}
			else if(it->first > yMax	){
				itAux = it;
				break;
			}
		}
	}

	//elimino los que estan sobre el agua
	for(rt = remuve.begin() ; 
		rt != remuve.end(); 
		rt++){
			positions.erase((*rt));
	}

	//elimino los que tienen 0 epacios
	remuve.clear();
	for(it = positions.begin(); 
		it != positions.end(); 
		it++){
		size = it->second.size();
		if(!size){
			remuve.push_back(it);
		}
	}

	//elimino los que no tiene casilleros
	for(rt = remuve.begin() ; 
		rt != remuve.end(); 
		rt++){
			positions.erase((*rt));
	}
}


void GamePosition::getRandomPosition(int* x, int* y){
	map<int, list<int>>::iterator it;
	pair<int, list<int>> result;

	int size = positions.size();
	int index = 0;
	if(size){
		index = Util::getRandom(1, size);
		for(it = positions.begin();
			it != positions.end();
			it++){
			--index;
			if(!index){
				break;
			}
		}
		*y = it->first;
		*x = getX(&it->second);
		size = it->second.size();
		if(!size){
			positions.erase(it);
		}
	}else{
		*x = -1;
		*y = -1;	
	}
}

int GamePosition::getX(list<int>* listX){
	list<int>::iterator it;
	int size = listX->size();
	int index = 0, result = 0;
	if(size){
		index = Util::getRandom(1, size);
		for(it = listX->begin();
			it != listX->end();
			it++){
			--index;
			if(!index){
				break;
			}
		}
		result = *it;
		listX->erase(it);
	}
	else{
		//Para que esto no ocurra necesito chequearlo antes
	
	}
	return result;
}

GamePosition::~GamePosition(){
}

GamePosition* GamePosition::getInstance(){
	if(!gp){
		gp = new GamePosition();
	}
	return gp;
}

