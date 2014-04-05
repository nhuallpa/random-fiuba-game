#pragma once

#ifndef __HANDLECONTOUR__
#define __HANDLECONTOUR__

#include <Box2D.h>
#include <vector>
#include "b2Separator.h"

using namespace std;

namespace server_model_handle{
	class HandleContour{
	public:
		HandleContour();
		~HandleContour();
		vector<vector<b2Vec2>> getPolygonConvex(vector<b2Vec2> contour,
			                                    float epsilon, 
												int scale);
	private:
		
		vector<b2Vec2> rdp(vector<b2Vec2> contour, float epsilon);
		float findPerpendicularDistance(b2Vec2 p, b2Vec2 p1, b2Vec2 p2);
		vector<vector<b2Vec2>> split(vector<b2Vec2> contour);
	};
}
#endif /*__HANDLECONTOUR__*/
