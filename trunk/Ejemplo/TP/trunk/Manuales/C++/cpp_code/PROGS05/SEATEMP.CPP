#include <iostream.h>
const int rows		= 3;
const int columns	= 4;

int seasonTemp[rows][columns] = {
	{26, 34, 22, 17},
	{24, 32, 19, 13},
	{28, 38, 25, 20}
};

int HighestTemp (int temp[rows][columns])
{
	int	highest = 0;

	for (register i = 0; i < rows; ++i)
    	for (register j = 0; j < columns; ++j)
			if (temp[i][j] > highest)
            	highest = temp[i][j];
	return highest;
}

main ()
{
	cout << HighestTemp(seasonTemp) << "\n";
}