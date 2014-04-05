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
		//vector<b2Vec2> change(list<b2Vec2*> contour, int scale);
		/*vector<vector<b2Vec2>> getPolygonConvex(vector<b2Vec2> contour,float epsilon, b2Separator* sep);
		vector<vector<b2Vec2>> split(vector<b2Vec2> contour);
		vector<b2Vec2> getItems(vector<b2Vec2>* contour, int cant);
		*/
	};
}
#endif /*__HANDLECONTOUR__*/
