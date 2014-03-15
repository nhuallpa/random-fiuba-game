#include <iostream.h>

double contents[][4] = {
	{ 12, 25, 16, 0.4 },
	{ 22,  4,  8, 0.3 },
	{ 28,  5,  9, 0.5 },
	{ 32,  7,  2, 0.2 }
};

void WriteContents (const double *contents, const int rows, const int cols)
{
	for (register i = 0; i < rows; ++i) {
		for (register j = 0; j < cols; ++j)
			cout << *(contents + i * rows + j) << ' ';
		cout << '\n';
	}
}

int main (void)
{
	WriteContents((const double*) contents, 4, 4);

    return 0;
}