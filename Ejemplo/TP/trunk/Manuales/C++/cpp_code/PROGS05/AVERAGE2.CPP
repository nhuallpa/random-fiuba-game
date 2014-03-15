#include <iostream.h>

double Average (int nums[], int size)
{
	double average = 0;

	for (register i = 0; i < size; ++i)
		average += nums[i];
	return average/size;
}

main ()
{
	int n[3];
	n[0] = 10; n[1] = 20; n[2] = 30;
	cout << Average(n, 3) << '\n';

    return 0;
}