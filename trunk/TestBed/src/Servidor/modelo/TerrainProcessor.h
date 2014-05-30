#pragma once

#ifndef TerrainProcessor_H_
#define TerrainProcessor_H_

#include "HandlerBmp/ContourBmp.h"
#include "HandleContour.h"
#include "../../libs/Box2D/Box2D.h"
#include"../../utils/ParserYaml.h"

#include <cstdio>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

struct Shape
{
	enum Category
	{
		normal	     = (1 << 0),
		destructible = (1 << 1)
	};
};


class TerrainProcessor
{
private:
	b2Vec2 transformBmpToBox2D(b2Vec2 vertex, int height, int width);
	list< list< pair<float,float> > >* aListOfPolygons;
	void makeDefaultTerrain(b2World* m_world,int waterLevel);
	list<pair<int,int>> * rangeTerrainOverWater;
	pair<int,int> maxPointTerrain;
	int height;
	int width;
	

public:
	TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale, int waterLevel);
		TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale, int waterLevel, bool chained, std::vector<b2Body*>* myTerrain);
	TerrainProcessor(b2World* m_world, char* path,float epsilon);
	list< list< pair<float,float> > > * getListOfPolygons();
	~TerrainProcessor(void);

	vector<b2Vec2> getChains(vector<b2Vec2> lista, float epsilon, int scale, int &height, int& width, int waterLevel);

	vector<vector<b2Vec2>> 
	    getPolygonConvex(vector<b2Vec2> contour, float epsilon, int scale, int& height, int& width,int waterLevel);
	static void getRandomPosition(int* x,int* y);
	list<pair<int,int>> * getRangeTerrainOverWater();
	pair<int,int> getMaxPointTerrain();
	int getHeight();
	int getWidth();
	std::vector<Position> rdp(std::vector<Position> contourVec, float epsilon);
};

#endif