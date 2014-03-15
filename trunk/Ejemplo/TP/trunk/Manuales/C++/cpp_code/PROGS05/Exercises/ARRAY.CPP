#include <iostream.h>

void ReadArray (double nums[], const int size)
{
	for (register i = 0; i < size; ++i) {
		cout << "nums[" << i << "] = ";
		cin >> nums[i];
	}
}

void WriteArray (double nums[], const int size)
{
	for (register i = 0; i < size; ++i)
		cout << nums[i] << '\n';
}

void Reverse (double nums[], const int size)
{
	double temp;

	for (register i = 0; i < size/2; ++i) {
		temp = nums[i];
		nums[i] = nums[size - i - 1];
		nums[size - i - 1] = temp;
	}
}

int main (void)
{
	double v[5];

	ReadArray(v, 5);
	Reverse(v, 5);
	WriteArray(v, 5);

    return 0;
}