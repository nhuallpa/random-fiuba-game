#include <iostream.h>
#include <string.h>

class AssocVec {
public:
			AssocVec	(const int dim);
			~AssocVec	(void);
	int&	operator [] (const char *idx);
private:
	struct VecElem {
		char	*index;
		int		value;
	}	*elems;			// vector elements
	int dim;			// vector dimension
	int used;			// elements used so far
};

AssocVec::AssocVec (const int dim)
{
	AssocVec::dim = dim;
	used = 0;
	elems = new VecElem[dim];
}

AssocVec::~AssocVec (void)
{
	for (register i = 0; i < used; ++i)
		delete elems[i].index;
	delete [] elems;
}

int& AssocVec::operator [] (const char *idx)
{
	for (register i = 0; i < used; ++i)	// search existing elements
		if (strcmp(idx,elems[i].index) == 0)
			return elems[i].value;

	if (used < dim &&	                // create new element
	    (elems[used].index = new char[strlen(idx)+1]) != 0) {
		strcpy(elems[used].index,idx);
		elems[used].value = used + 1;
		return elems[used++].value;
	}
	static int dummy = 0;
	return dummy;
}

#ifndef	NOMAIN

int main (void)
{
	AssocVec count(5);
	count["apple"] = 5;
	count["orange"] = 10;
	count["fruit"] = count["apple"] + count["orange"];

	cout << count["apple"] << " , " << count["orange"]
						   << " , " << count["fruit"] << '\n';
	return 0;
}

#endif