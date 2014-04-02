#pragma once

#ifndef __POINT__
#define __POINT__

namespace server_model_point{

	class Point{
	public:
		Point();
		Point(float y, float x);
		~Point();
		float getY();
		float getX();
	private:
		float y;
		float x;
	
	};

}

#endif /*__POINT__*/
