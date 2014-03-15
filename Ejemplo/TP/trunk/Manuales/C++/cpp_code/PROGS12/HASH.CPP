#include <iostream.h>

#define CheckPtr(ptr)	if ((ptr) == 0) cout << #ptr << " is zero!\n"
#define test ptr##man

int main (void)
{
	double *numPtr = 0;
	CheckPtr(numPtr);
	cout << test;
	return 0;
}