#define NOMAIN
#include "c:\sharam\cs_books\cpp\progs07\matrix.cpp"
#include "c:\sharam\cs_books\cpp\progs07\assocvec.cpp"

class Table3 : Matrix {
public:
			Table3		(const short rows, const short cols)
							: Matrix(rows,cols),
							  rowIdx(rows),
							  colIdx(cols) {}
	double& operator () (const char *src, const char *dest);

private:
	AssocVec rowIdx;	// row index
	AssocVec colIdx;	// column index
};

double& Table3::operator () (const char *src, const char *dest)
{
	return this->Matrix::operator()(rowIdx[src], colIdx[dest]);
}
