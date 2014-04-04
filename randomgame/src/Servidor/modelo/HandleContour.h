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
		vector<vector<b2Vec2>> getPolygonConvex(list<b2Vec2*> contour, int scale);
	private:
		list<b2Vec2*> rdp(list<b2Vec2*> contour, int epsilon);
		float findPerpendicularDistance(b2Vec2* p, b2Vec2* p1, b2Vec2* p2);
		vector<b2Vec2> change(list<b2Vec2*> contour, int scale);
		
	};
}
#endif /*__HANDLECONTOUR__*/
