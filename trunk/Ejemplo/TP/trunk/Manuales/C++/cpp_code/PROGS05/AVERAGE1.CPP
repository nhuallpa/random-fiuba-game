#include <iostream.h>

const int size = 3;

double Average (int nums[size])
{
	double average = 0;

	for (register i = 0; i < size; ++i)
		average += nums[i];
	return average/size;
}

main ()
{
	int n[3];
	n[0] = 10;
	n[1] = 20;
	n[2] = 30;
	cout << Average(n) << '\n';

	return 0;
}