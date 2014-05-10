#ifndef __GAMEPOSITION__
#define __GAMEPOSITION__
#include <map>
#include <list>
#include "..\..\utils\Constantes\Constantes.h"

using namespace std;

class GamePosition{
public:
	static GamePosition* getInstance();
	void generate(int supreme);
	void validPosition(list<pair<int,int>>* terrain);
	void getRandomPosition(int* x, int* y);
private:
	GamePosition();
	~GamePosition();
	int getX(list<int>* listX);
	int supreme, deltaX, deltaY;
	list<pair<int, int>> terrain;
	map<int, list<int>> positions;
	static GamePosition* gp;

};
#endif
