#include <iostream.h>

double FahrenToCelsius (double fahren)
{
	return 5 * (fahren - 32) / 9;
}

int main (void)
{
	double fahrenheit;

	cout << "Temperature in Fahrenhait: ";
	cin  >> fahrenheit;

	cout << fahrenheit << " degrees Fahrenheit = "
		 << FahrenToCelsius(fahrenheit) << " degrees Celsius\n";
	return 0;
}