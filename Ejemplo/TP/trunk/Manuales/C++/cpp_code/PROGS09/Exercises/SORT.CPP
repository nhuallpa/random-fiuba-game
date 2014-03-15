#include <iostream.h>
#include <string.h>

enum Bool {false, true};

template <class Type>
void BubbleSort (Type *names, const int size)
{
	Bool swapped;

	do {
		swapped = false;
		for (register i = 0; i < size - 1; ++i) {
			if (names[i] > names[i+1]) {
				Type temp = names[i];
				names[i] = names[i+1];
				names[i+1] = temp;
				swapped = true;
			}
		}
	} while (swapped); 
}

// specialization:

void BubbleSort (char **names, const int size)
{
	Bool swapped;

	do {
		swapped = false;
		for (register i = 0; i < size - 1; ++i) {
			if (strcmp(names[i], names[i+1]) > 0 ) {
				char *temp = names[i];
				names[i] = names[i+1];
				names[i+1] = temp;
				swapped = true;
			}
		}
	} while (swapped); 
}

int main (void)
{
    double nums[5] = {1.3, 6.4, 2.9, 11.9, 0.5};
	char *names[5] = {"one", "two", "three", "four", "five"};
    const int size = 5;

    BubbleSort(nums, size);
    BubbleSort(names, size);

    for (register i = 0; i < size; ++i)
    	cout << nums[i] << ' ';
    cout << '\n';

    for (i = 0; i < size; ++i)
    	cout << names[i] << ' ';
    cout << '\n';

    return 0;
}