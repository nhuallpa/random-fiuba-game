#pragma once

#ifndef __HANDLECONTOUR__
#define __HANDLECONTOUR__

#include <list>
#include "Point.h"

using namespace std;
using namespace server_model_point;

namespace server_model_handle{
	class HandleContour{
	public:
		HandleContour();
		~HandleContour();
		list<Point*> rdp(list<Point*> contour, int epsilon);
	private:
		float findPerpendicularDistance(Point* p, Point* p1, Point* p2);
	};
}
#endif /*__HANDLECONTOUR__*/
