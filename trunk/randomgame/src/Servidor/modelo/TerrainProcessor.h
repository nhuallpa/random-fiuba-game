#pragma once

#ifndef TerrainProcessor_H_
#define TerrainProcessor_H_

#include "HandlerBmp/ContourBmp.h"
#include "HandleContour.h"
#include "../../libs/Box2D/Box2D.h"
#include <cstdio>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace server_model_handle;
using namespace std;

class TerrainProcessor
{
private:
	b2Vec2 transformBmpToBox2D(b2Vec2 vertex, int height);
	list< list< pair<float,float> > >* aListOfPolygons;

public:
	TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale);
	list< list< pair<float,float> > > * getListOfPolygons();
	~TerrainProcessor(void);
};

#endif