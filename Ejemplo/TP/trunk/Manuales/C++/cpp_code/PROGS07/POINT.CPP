#include <iostream.h>

/*
class Point {
public:
	Point (int x, int y)		{Point::x = x; Point::y = y;}
	Point operator + (Point &p)	{return Point(x + p.x,y + p.y);}
	Point operator - (Point &p)	{return Point(x - p.x,y - p.y);}
private:
	int x, y;
};
*/

class Point {
public:
	Point (int x, int y)		{Point::x = x; Point::y = y;}
	Point (int x)				{Point::x = Point::y = x;}

	friend Point operator + (Point &p, Point &q)
								{return Point(p.x + q.x,p.y + q.y);}
	friend Point operator - (Point &p, Point &q) 
								{return Point(p.x - q.x,p.y - q.y);}
	void Print (void) {cout<<"("<<x<<","<<y<<")";}
private:
	int x, y;
};

class Rectangle {
public:
	Rectangle (int left, int top, int right, int bottom);
    Rectangle (Point &p, Point &q) :  topLeft(p), botRight(q) {}
	Rectangle (Point &p) : topLeft(p), botRight(p) {}

    operator Point ()	{return botRight - topLeft;}
	friend Rectangle operator + (Rectangle &r, Rectangle &t)
			{return Rectangle(r.topLeft + t.topLeft, r.botRight + t.botRight);}
	friend Rectangle operator - (Rectangle &r, Rectangle &t);
	void Print (void) {topLeft.Print();botRight.Print();}
private:
	Point	topLeft;
	Point	botRight;
};

Rectangle::Rectangle (int left, int top, int right, int bottom)
	: topLeft(left,top), botRight(right,bottom)
{
}

main ()
{
	Point p(10,10), q(20,20);
	(p+q).Print();		cout<<'\n';
	(p + 10).Print();	cout<<'\n';
	Rectangle r(10,10,20,30);
	q = r + p;
}