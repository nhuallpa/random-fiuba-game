#define NOMAIN
#include "c:\sharam\cs_books\cpp\progs07\matrix.cpp"
#include "c:\sharam\cs_books\cpp\progs07\assocvec.cpp"

class Table1 : Matrix, AssocVec  {
public:
			Table1 		(const short entries)
							: Matrix(entries, entries),
				  			  AssocVec(entries)		{}
	double& operator () (const char *src, const char *dest);
};

double& Table1::operator () (const char *src, const char *dest)
{
	return	this->Matrix::operator()(
					this->AssocVec::operator[](src),
					this->AssocVec::operator[](dest)
			);
}

main ()
{
	Table1 tab(3);
	tab("Sydney","Perth") = 12.45;
	cout << "Sydney -> Perth = " << tab("Sydney","Perth") << '\n';
}