#pragma once

#ifndef __POINT__
#define __POINT__

namespace server_model_point{

	class Point{
	public:
		Point();
		Point(double y, double x);
		~Point();
		double distance(Point* p);
		double diffY(double y);
		double diffX(double x);
	private:
		double y;
		double x;
	
	};

}

#endif /*__POINT__*/
