#include <iostream.h>

main ()
{
	unsigned char x = '\011';
	unsigned char y = '\027';

	cout << "x = " << oct << short(x) << '\n';
	cout << "y = " << oct << short(y) << '\n';
	cout << "~x = " << oct << (short)(~x) << '\n';
	cout << "x & y = " << oct << (short)(x & y) << '\n';
	cout << "x | y = " << oct << (short)(x | y) << '\n';
	cout << "x ^ y = " << oct << (short)(x ^ y) << '\n';
	cout << "x << 2 = " << oct << (short)(x << 2) << '\n';
	cout << "x >> 2 = " << oct << (short)(x >> 2) << '\n';
}