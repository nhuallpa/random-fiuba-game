#include <iostream.h>
#include <stdarg.h>

double Sum (int n, double val ...)
{
	va_list args;				// argument list
	double	sum = 0;

	va_start(args, val);		// initialize args

	while (n-- > 0) {
		sum += val;
		val = va_arg(args, double);
    }
	va_end(args);				// clean up args
	return sum;

}

int main (void)
{
	cout << Sum(4, 10.4, 2.0, 5.3, 6.9) << '\n';
	cout << Sum(1, 10.5) << '\n';

	return 0;
}