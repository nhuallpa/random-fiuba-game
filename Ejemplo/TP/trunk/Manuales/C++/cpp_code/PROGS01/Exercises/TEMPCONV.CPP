#include <iostream.h>

int main (void)
{
	double fahrenheit;
	double celsius;

	cout << "Temperature in Fahrenhait: ";
	cin  >> fahrenheit;

	celsius = 5 * (fahrenheit - 32) / 9;

	cout << fahrenheit << " degrees Fahrenheit = "
		 << celsius << " degrees Celsius\n";
	return 0;
}