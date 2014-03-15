#include <iostream.h>
#include <string.h>

const int Max (const int x, const int y)
{
	return x >= y ? x : y;
}

const double Max (const double x, const double y)
{
	return x >= y ? x : y;
}

const char*	Max (const char *x, const char *y)
{
	return strcmp(x,y) >= 0 ? x : y;
}

int main (void)
{
	cout << Max(10, 20) << '\n';
    cout << Max(20.4, 3.9) << '\n';
    cout << Max("Hello", "Bye") << '\n';
    return 0;
}


