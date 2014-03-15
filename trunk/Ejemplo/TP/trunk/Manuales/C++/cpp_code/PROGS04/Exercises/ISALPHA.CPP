#include <iostream.h>

inline int IsAlpha (char ch)
{
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

int main (void)
{
	cout << IsAlpha('K') << '\n';

	return 0;
}