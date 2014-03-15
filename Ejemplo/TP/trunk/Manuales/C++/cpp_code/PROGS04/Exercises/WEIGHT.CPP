#include <iostream.h>

char* CheckWeight (double height, double weight)
{
	if (weight < height/2.5)
		return "Underweight";
	if (height/2.5 <= weight && weight <= height/2.3)
		return "Normal";
	return "Overweight";
}

int main (void)
{
	double height, weight;

	cout << "Person's height (in centimeters): ";
	cin >> height;
	cout << "Person's weight (in kilograms: ";
	cin >> weight;
	cout << CheckWeight(height, weight) << '\n';

	return 0;
}