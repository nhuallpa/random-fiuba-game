int Power (int base, int exponent)	// assumes exponent > 0
{
	int	result = 1;

	for (int i = 0; i < exponent; ++i)
		result *= base;
	return result;
}

#include <iostream.h>

main (void)
{
	cout << "2 ^ 8 = " << Power(2,8) << '\n';
}