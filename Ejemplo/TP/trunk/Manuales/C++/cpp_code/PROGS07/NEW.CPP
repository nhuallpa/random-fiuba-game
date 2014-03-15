#include <stddef.h>
#include <iostream.h>

const int  maxPoints = 512;

class Point {
public:
		 Point (int x, int y)	{xVal = x; yVal = y;}
	void *operator new		(size_t bytes);
	void  operator delete	(void *ptr, size_t bytes);
private:
	int xVal, yVal;

	static union Block {
		int	  xy[2];
		Block *next;
    }			 *blocks;
	static Block *freeList;		// free list of linked blocks
	static int	 used;			// blocks used so far
};

Point::Block *Point::blocks = new Block[maxPoints];
Point::Block *Point::freeList = 0;
int 		  Point::used = 0;

void *Point::operator new (size_t bytes)
{
	Block *res = freeList;
cout << "my new called\n";
	return used < maxPoints
			   ? &(blocks[used++])
			   : (res == 0	? 0 
							: (freeList = freeList->next, res));
}

void
Point::operator delete (void *ptr, size_t bytes)
{
cout << "my delete called\n";
	((Block*) ptr)->next = freeList;
	freeList = (Block*) ptr;
}

int main (void)
{
	Point *pt = new Point(1,1);		// calls Point::operator new
	char  *str = new char[10];		// calls ::operator new
	delete pt;						// calls Point::operator delete
	delete str;						// calls ::operator delete
	return 0;
}