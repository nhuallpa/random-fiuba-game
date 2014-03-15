class Rectangle {			// a nested class
public:
			Rectangle (int, int, int, int);
	//..
private:
	class Point {
	public:
				Point	(int, int);
		void	OffsetPt(int, int);
    private:
		int x, y;
	};

	Point	topLeft, botRight;
};

Rectangle::Point::Point (int x, int y)
{
	//...
}

typedef int Image;

void Render (Image &image)
{
	class ColorTable {
    public:
		ColorTable	(void)					{ /* ... */ }
		AddEntry	(int r, int g, int b)	{ /* ... */ }
		//...
	};

	ColorTable colors;
	//...
}

int main (void)
{
	Rectangle::Point p(1,1);

	return 0;
}

