#include <iostream.h>

enum Bool {false, true};

void Primes (unsigned int n)
{
	Bool isPrime;

	for (register num = 2; num <= n; ++num) {
    	isPrime = true;
		for (register i = 2; i < num/2; ++i)
			if (num%i == 0) {
            	isPrime = false;
				break;
			}
		if (isPrime)
        	cout << num << '\n';

    }
}

int main (void)
{
	Primes(50);

	return 0;
}