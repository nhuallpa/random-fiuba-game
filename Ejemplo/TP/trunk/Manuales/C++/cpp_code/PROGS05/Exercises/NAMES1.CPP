#include <iostream.h>
#include <string.h>

enum Bool {false, true};

void ReadNames (char *names[], const int size)
{
	char name[128];

	for (register i = 0; i < size; ++i) {
		cout << "names[" << i << "] = ";
		cin >> name;
		names[i] = new char[strlen(name) + 1];
		strcpy(names[i], name);
	}
}

void WriteNames (char *names[], const int size)
{
	for (register i = 0; i < size; ++i)
		cout << names[i] << '\n';
}

void BubbleSort (char *names[], const int size)
{
	Bool swapped;
	char *temp;

	do {
		swapped = false;
		for (register i = 0; i < size - 1; ++i) {
			if (strcmp(names[i], names[i+1]) > 0 ) {
				temp = names[i];
				names[i] = names[i+1];
				names[i+1] = temp;
				swapped = true;
			}
		}
	} while (swapped); 
}

int main (void)
{
	char *names[5];

	ReadNames(names, 5);
	BubbleSort(names, 5);
	WriteNames(names, 5);

    return 0;
}