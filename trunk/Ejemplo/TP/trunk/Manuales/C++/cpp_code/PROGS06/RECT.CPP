#include <iostream.h>

class Point {
public:
		Point (int x = 0, int y = 0) {xVal = x; yVal = y;}
private:
	int	xVal, yVal;
};

class Rectangle {
public:
			Rectangle	(int left, int top, int right, int bottom);
			//...
private:
	Point	topLeft;
	Point	botRight;
};

Rectangle::Rectangle (int left, int top, int right, int bottom)
	: topLeft(left,top), botRight(right,bottom)
{
}

int main (void)
{
	Rectangle r(1,2,3,4);

	return 0;
}