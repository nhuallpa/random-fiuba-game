#include <iostream.h>
#include <stdlib.h>

int main (int argc, const char *argv[])
{
	double sum = 0;

	for (int i = 1; i < argc; ++i)
    	sum += atof(argv[i]);
	cout << sum << '\n';
	return 0;
}