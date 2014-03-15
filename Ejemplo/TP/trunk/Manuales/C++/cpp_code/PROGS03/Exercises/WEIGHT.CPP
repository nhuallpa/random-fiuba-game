#include <iostream.h>

int main (void)
{
	double height, weight;

	cout << "Person's height (in centimeters): ";
	cin >> height;
	cout << "Person's weight (in kilograms: ";
	cin >> weight;

	if (weight < height/2.5)
		cout << "Underweight\n";
	else if (height/2.5 <= weight && weight <= height/2.3)
		cout << "Normal\n";
	else
		cout << "Overweight\n";

	return 0;
}