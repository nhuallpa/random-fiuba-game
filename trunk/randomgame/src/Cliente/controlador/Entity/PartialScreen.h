#pragma once
#ifndef __PSCREEN__
#define __PSCREEN__

#include <list>
#include <map>
using namespace std;

enum Side {S_UP,
           S_DOWN,
           S_LEFT,
           S_RIGHT,
           S_NONE};

class PartialScreen
{
public:
	PartialScreen(void);
	~PartialScreen(void);
	PartialScreen* Inside(int x, int y, Side s);
	PartialScreen* Inside(int x, int y);
	void addRelationScreen(PartialScreen *s);
	int xFrom, xTo,
		yFrom, yTo;
	int id;
	map<int, Side> dir;
private:
	list<PartialScreen*> screens;
	bool sharedDir(int id, Side s);
};

#endif