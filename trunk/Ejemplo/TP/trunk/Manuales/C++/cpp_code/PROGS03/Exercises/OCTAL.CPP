#include <iostream.h>

int main (void)
{
	int octal, digit;
	int decimal = 0;
    int	power = 1;

	cout << "Input an octal number: ";
	cin >> octal;

	for (int n = octal; n > 0; n /= 10) {	// process each digit
		digit = n % 10;						// right-most digit
		decimal = decimal + power * digit;
		power *= 8;
    }
	cout << "Octal(" << octal << ") = Decimal(" << decimal << ")\n";
	return 0;
}