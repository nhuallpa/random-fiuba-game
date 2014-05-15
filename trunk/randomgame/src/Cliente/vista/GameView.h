#pragma once

#ifndef __VIEW_H__
#define __VIEW_H__
#include <list>
#include "ViewGroup.h"
#include "FigureView.h"
#include "EartView.h"
#include "SkyView.h"
#include "WaterView.h"
#include "TerrainView.h"
#include "StateBarView.h"
#include "WormView.h"
#include <map>
#include <string>
using std::map;
using std::string;
class GameView : 	public ViewGroup
{
private:
	map<int, FigureView*> figures;
	map<int, WormView*> worms;
	EartView* eart;
	SkyView* sky;
	WaterView* water;
	TerrainView* terrain;
	StateBarView* stateBar;

public:
	GameView(int x, int y, int width, int height);

	void putFigure(int id, FigureView* figure);
	void putWorm(int id, WormView* worm);
	void setEart(EartView* eart);
	void setSky(SkyView* sky);
	void setWater(WaterView* water);
	void setTerrain(TerrainView* terrain);
	void setStateBar(StateBarView* stateBar);

	StateBarView* getStateBar() { return this->stateBar;}

	FigureView* findFigureById(int idElement);
	WormView* findWormById(int idElement);

	~GameView(void);
};


#endif /** __VIEW_GROUP_H__ */