#include <iostream.h>

class Point {
public:
		Point (int x = 0, int y = 0) {xVal = x; yVal = y;}
private:
	int	xVal, yVal;
};

Point pentagon[5] = {
	Point(10,20), Point(10,30), Point(20,30), Point(30,20)
};

int main (void)
{
	return 0;
}