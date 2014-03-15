#include <iostream.h>
const int rows		= 3;
const int columns	= 4;

int seasonTemp[rows][columns] = {
	{26, 34, 22, 17},
	{24, 32, 19, 13},
	{28, 38, 25, 20}
};

int HighestTemp (const int *temp, const int rows, const int columns)
{
	int	highest = 0;

	for (register i = 0; i < rows; ++i)
    	for (register j = 0; j < columns; ++j)
			if (*(temp + i * columns + j) > highest)
				highest = *(temp + i * columns + j);
	return highest;
}

main ()
{
	cout << HighestTemp((const int*) seasonTemp, rows, columns) << '\n';

	return 0;
}