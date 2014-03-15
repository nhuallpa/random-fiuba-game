#include <iostream.h>
#include <string.h>

typedef int (*Compare)(const char*, const char*);

int BinSearch (char *item, char *table[], int n, Compare comp)
{
	int bot = 0;
	int top = n - 1;
	int mid, cmp;

	while (bot <= top) {
		mid = (bot + top) / 2;
		if ((cmp = comp(item,table[mid])) == 0)
			return mid;				// return item index
		else if (cmp < 0)
			top = mid - 1;			// restrict search to lower half
		else
			bot = mid + 1;			// restrict search to upper half
	}
	return -1;						// not found
}

char *cities[] = {"Boston", "London", "Sydney", "Tokyo"};

main ()
{
	cout << BinSearch("Sydney", cities, 4, strcmp) << '\n';

	return 0;
}