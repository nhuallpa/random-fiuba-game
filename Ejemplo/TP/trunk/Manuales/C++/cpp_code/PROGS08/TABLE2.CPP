#define NOMAIN
#include "c:\sharam\cs_books\cpp\progs07\matrix.cpp"
#include "c:\sharam\cs_books\cpp\progs07\assocvec.cpp"

class Table2 : Matrix  {
public:
			Table2		(const short entries)
							: Matrix(entries, entries),
				  			  index(entries)	{}
	double& operator () (const char *src, const char *dest);
private:
	AssocVec index;		// row and column index
};

double& Table2::operator () (const char *src, const char *dest)
{
	return	this->Matrix::operator()(index[src], index[dest]);
}

main ()
{
	Table2 tab(3);
	tab("Sydney","Perth") = 12.45;
	cout << "Sydney -> Perth = " << tab("Sydney","Perth") << '\n';
}