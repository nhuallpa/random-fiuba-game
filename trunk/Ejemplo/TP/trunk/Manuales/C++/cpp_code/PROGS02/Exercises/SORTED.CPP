#include <iostream.h>

int main (void)
{
	double n1, n2, n3;

	cout << "Input three numbers: ";
	cin  >> n1 >> n2 >> n3;
	cout << (n1 <= n2 && n2 <= n3 ? "Sorted" : "Not sorted") << '\n';
	return 0;
}