#pragma once

#ifndef __HANDLECONTOUR__
#define __HANDLECONTOUR__

#include <list>
#include "Point.h"
#include <Box2D.h>

using namespace std;
using namespace server_model_point;

namespace server_model_handle{
	class HandleContour{
	public:
		HandleContour();
		~HandleContour();
		list<Point*> rdp(list<Point*> contour, int epsilon);
		int Validate(list<b2Vec2*> l);
	private:
		float findPerpendicularDistance(Point* p, Point* p1, Point* p2);
		float det(float x1,float y1,
			      float x2,float y2,
				  float x3,float y3);
		b2Vec2* hitSegment(float x1,float y1,
						  float x2,float y2,
						  float x3,float y3,
						  float x4,float y4);
		bool isOnSegment(float px,float py,
			             float x1,float y1,
			             float x2,float y2);
		bool isOnLine(float px,float py,
			          float x1,float y1,
			          float x2,float y2);
		list<b2Vec2*> calcShapes(list<b2Vec2*> l);
	};
}
#endif /*__HANDLECONTOUR__*/
