#include <iostream.h>

int main (void)
{
	int n;
	int factorial = 1;

	cout << "Input a positive integer: ";
	cin >> n;

	if (n >= 0) {
		while (n > 0)
			factorial *= n--;
        cout << "Factorial of " << n << " = " << factorial << '\n';
    }
	return 0;
}