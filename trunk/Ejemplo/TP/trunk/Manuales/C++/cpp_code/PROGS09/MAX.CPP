#include <iostream.h>

template <class T>
T Max (T val1, T val2)
{
	return val1 > val2 ? val1 : val2;
}

template <class T>
T Max (T *vals, int n)
{
	T max = vals[0];
	for (register i = 1; i < n; ++i)
		if (vals[i] > max)
			max = vals[i];
	return max;
}

#include <string.h>
char *Max (char *str1, char *str2)
{
	return strcmp(str1,str2) > 0 ? str1 : str2;
}

int main (void)
{
	cout << Max(19, 5) << " "
		 << Max(10.5, 20.3) << " "
		 << Max('a','b') << '\n';

    unsigned n = 4;
	int vals[] = {10, 20, 30, 40};
	cout << Max(vals, int(n)) << '\n';
	cout << Max("Day", "Night") << '\n';
	return 0;
}