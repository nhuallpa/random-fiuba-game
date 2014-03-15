#include <iostream.h>

class Matrix {
public:
				Matrix		(const int rows, const int cols);
                Matrix		(const Matrix&);
				~Matrix		(void);
		double&	operator ()	(const int row, const int col);
		Matrix&	operator =	(const Matrix&);

friend ostream&	operator << (ostream&, Matrix&);
friend  Matrix	operator + 	(Matrix&, Matrix&);
friend  Matrix	operator -	(Matrix&, Matrix&);
friend  Matrix	operator *	(Matrix&, Matrix&);
		int   	Rows 		(void)	{return rows;}
		int   	Cols 		(void)	{return cols;}
protected:
		class Element {			// nonzero element
        public:
        				Element	(const int row, const int col, double);
        	const int	Row		(void)	{return row;}
			const int	Col		(void)	{return col;}
			double&		Value	(void)	{return value;}
			Element*& 	Next	(void)	{return next;}
            Element* 	CopyList(Element *list);
            void		DeleteList	(Element *list);
        private:
			const int	row, col;	// row and column of element
			double		value;		// element value
			Element		*next;		// pointer to next element
		};

		double&	InsertElem	(Element *elem, const int row, const int col);

		int  	rows, cols;	// matrix dimensions
		Element	*elems;		// linked-list of elements
};

Matrix::Element::Element (const int r, const int c, double val)
		   : row(r), col(c)
{
	value = val;
    next = 0;
}

Matrix::Element* Matrix::Element::CopyList (Element *list)
{
	Element *prev = 0;
    Element *first = 0;
    Element *copy;

	for (; list != 0; list = list->Next()) {
    	copy = new Element(list->Row(), list->Col(), list->Value());
        if (prev == 0)
        	first = copy;
        else
        	prev->Next() = copy;
        prev = copy;
    }
    return first;
}

void Matrix::Element::DeleteList (Element *list)
{
	Element *next;

	for (; list != 0; list = next) {
		next = list->Next();
		delete list;
	}
}

// InsertElem creates a new element and inserts it before
// or after the element denoted by elem.

double& Matrix::InsertElem (Element *elem, const int row, const int col)
{	
	Element* newElem = new Element(row, col, 0.0);

	if (elem == elems && (elems == 0 || row < elems->Row() ||
						 row == elems->Row() && col < elems->Col())) {
		// insert in front of the list:
		newElem->Next() = elems;
		elems = newElem;
	} else {
    	// insert after elem:
		newElem->Next() = elem->Next();
		elem->Next() = newElem;
	}
	return newElem->Value();
}

Matrix::Matrix (const int rows, const int cols)
{
	Matrix::rows = rows;
	Matrix::cols = cols;
	elems = 0;
}

Matrix::Matrix (const Matrix &m)
{
	rows = m.rows;
    cols = m.cols;
	elems = m.elems->CopyList(m.elems);
}

Matrix::~Matrix (void)
{
	elems->DeleteList(elems);
}

Matrix& Matrix::operator = (const Matrix &m)
{
	elems->DeleteList(elems);
    rows = m.rows;
    cols = m.cols;
	elems = m.elems->CopyList(m.elems);
	return *this;
}

double& Matrix::operator () (const int row, const int col)
{
	if (elems == 0 || row < elems->Row() ||
		row == elems->Row() && col < elems->Col())
        // create an element and insert in front:
		return InsertElem(elems, row, col);

	// check if it's the first element in the list:
    if (row == elems->Row() && col == elems->Col())
    	return elems->Value();

	// search the rest of the list:
	for (Element *elem = elems; elem->Next() != 0; elem = elem->Next())
		if (row == elem->Next()->Row()) {
			if (col == elem->Next()->Col())
				return elem->Next()->Value();	// found it!
			else if (col < elem->Next()->Col())
				break;							// doesn't exist
		} else if (row < elem->Next()->Row())
			break;								// doesn't exist
    // create new element and insert just after elem:
	return InsertElem(elem, row, col);
}

ostream& operator << (ostream &os, Matrix &m)
{
	Matrix::Element *elem = m.elems;

	for (register row = 1; row <= m.rows; ++row) {
		for (register col = 1; col <= m.cols; ++col)
			if (elem != 0 && elem->Row() == row && elem->Col() == col) {
				os << elem->Value() << '\t';
				elem = elem->Next();
			} else
				os << 0.0 << '\t';
		os << '\n';
	}
    return os;
}

Matrix operator + (Matrix &p, Matrix &q)
{
	Matrix m(p.rows, q.cols);

    // copy p:
	for (Matrix::Element *pe = p.elems; pe != 0; pe = pe->Next())
	    m(pe->Row(), pe->Col()) = pe->Value();
    // add q:
	for (Matrix::Element *qe = q.elems; qe != 0; qe = qe->Next())
	    m(qe->Row(), qe->Col()) += qe->Value();
	return m;
}

Matrix operator - (Matrix &p, Matrix &q)
{
	Matrix m(p.rows, q.cols);

    // copy p:
	for (Element *pe = p.elems; pe != 0; pe = pe->Next())
	    m(pe->Row(), pe->Col()) = pe->Value();
    // subtract q:
	for (Element *qe = q.elems; qe != 0; qe = qe->Next())
	    m(qe->Row(), qe->Col()) -= qe->Value();
	return m;
}

Matrix operator * (Matrix &p, Matrix &q)
{
	Matrix m(p.rows, q.cols);

	for (Element *pe = p.elems; pe != 0; pe = pe->Next())
	    for (Element *qe = q.elems; qe != 0; qe = qe->Next())
		   if (pe->Col() == qe->Row())
		      m(pe->Row(),qe->Col()) += pe->Value() * qe->Value();
	return m;
}

main ()
{
	Matrix m(5,5);
	Matrix n(5,5);
	m(2,2) = 1.0;	m(3,3) = 2.0;
	m(4,4) = 3.0;	m(1,1) = 4.0;
	m(1,5) = 5.0;	m(1,3) = 6.0;
	n(2,2) = 10.0;	n(3,3) = 20.0;
	n(3,5) = 30.0;	n(5,2) = 40.0;
    cout << m << '\n';
    cout << n << '\n';
	cout << (m + n) << '\n';
	cout << (m * n) << '\n';
}
