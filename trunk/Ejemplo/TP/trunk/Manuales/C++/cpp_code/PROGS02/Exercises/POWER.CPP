#include <iostream.h>

int main (void)
{
	long n;

	cout << "What is the value of n? ";
	cin  >> n;
	cout << "2 to the power of " << n << " = " << (1L << n) << '\n';
	return 0;
}