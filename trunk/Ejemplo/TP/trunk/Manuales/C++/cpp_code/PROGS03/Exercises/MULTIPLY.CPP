#include <iostream.h>

int main (void)
{
	for (register i = 1; i <= 9; ++i)
		for (register j = 1; j <= 9; ++j)
			cout << i << " x " << j << " = " << i*j << '\n';

	return 0;
}