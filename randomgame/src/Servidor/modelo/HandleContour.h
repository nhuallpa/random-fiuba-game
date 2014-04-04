#pragma once

#ifndef __HANDLECONTOUR__
#define __HANDLECONTOUR__

#include <list>
#include <Box2D.h>
#include <vector>

using namespace std;

namespace server_model_handle{
	class HandleContour{
	public:
		HandleContour();
		~HandleContour();
		list<b2Vec2*> rdp(list<b2Vec2*> contour, int epsilon);
		vector<vector<b2Vec2>> getPolygonConvex(list<b2Vec2*> contour);
	private:
		float findPerpendicularDistance(b2Vec2* p, b2Vec2* p1, b2Vec2* p2);
	};
}
#endif /*__HANDLECONTOUR__*/
