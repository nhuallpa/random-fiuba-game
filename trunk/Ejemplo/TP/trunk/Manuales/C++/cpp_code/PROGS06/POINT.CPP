#include <iostream.h>

class Point {
public:
	void SetPt		(int, int);
	void OffsetPt	(int, int);
    void Print		(void);
private:
	int	 xVal, yVal;
};

void Point::SetPt (int x, int y)
{
	xVal = x;
	yVal = y;
}

void Point::OffsetPt (int x, int y)
{
	xVal += x;
	yVal += y;
}

void Point::Print (void)
{
	cout << '(' << xVal << ',' << yVal << ")\n";
}

int main (void)
{
	Point pt;
	pt.SetPt(10,20);
    pt.Print();
	pt.OffsetPt(2,2);
	pt.Print();

	return 0;
}