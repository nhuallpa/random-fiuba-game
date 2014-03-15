#include <iostream.h>

const minSize = 5;           // minimum number of rows or columns

struct Element {
	short    row, col;
	double   val;
	Element* next;
};

class Matrix {
	short    rows, cols;
	Element* elems;           // linked-list of elements
	double   dummy;
	double& InsertElem (Element* elem,short row,short col);
public:
	        Matrix (short rows,short cols);
	       ~Matrix ();
	short   Rows ()           { return rows; }
	short   Cols ()           { return cols; }
	double& operator () (short row,short col);
	friend  Matrix operator + (Matrix&, Matrix&);
	friend  Matrix operator - (Matrix&, Matrix&);
	friend  Matrix operator * (Matrix&, Matrix&);
	void    Print ();
};

Matrix::Matrix (short rows,short cols)
{
	Matrix::rows = (rows < minSize ? minSize : rows);
	Matrix::cols = (cols < minSize ? minSize : cols);
	elems = 0;   dummy = 0.0;
}

Matrix::~Matrix ()
{
	Element* elem = elems;
	Element* tmp;

	while (elem != 0) {
		tmp = elem;
		elem = elem->next;
		delete tmp;
	}
}

double& Matrix::InsertElem (Element* elem,short row,short col)
{	
	Element* newElem = new Element;
	if (newElem == 0) return dummy;
	newElem->row = row;
	newElem->col = col;
	newElem->val = 0.0;
	if (elem == elems && (elems == 0 || row < elems->row ||
	                      row == elems->row && col < elems->col)) {
	   newElem->next = elems;
	   elems = newElem;
	} else {
	   newElem->next = elem->next;
	   elem->next = newElem;
	}
	return newElem->val;
}

double& Matrix::operator () (short row,short col)
{
	if (row < 1 || row > rows || col < 1 || col > cols)
	   return dummy;
	if (elems == 0 || row < elems->row || 
	    row == elems->row && col < elems->col)
	    return InsertElem(elems,row,col);
	for (Element* elem = elems; elem->next != 0; elem = elem->next)
	     if (row == elem->next->row) {
	        if (col == elem->next->col)
	           return elem->next->val;
	        else if (col < elem->next->col)
	           break;
         } else if (row < elem->next->row)
	        break;
	return InsertElem(elem,row,col);
}

Matrix operator + (Matrix& p,Matrix& q)
{
	Matrix m(p.rows,q.cols);
	for (Element* pe = p.elems; pe != 0; pe = pe->next)  // copy p
	    m(pe->row,pe->col) = pe->val;
	for (Element* qe = q.elems; qe != 0; qe = qe->next)  // add q
	    m(qe->row,qe->col) += qe->val;
	return m;
}

Matrix operator * (Matrix& p,Matrix& q)
{
	Matrix m(p.rows,q.cols);

	for (Element* pe = p.elems; pe != 0; pe = pe->next)
	    for (Element* qe = q.elems; qe != 0; qe = qe->next)
		   if (pe->col == qe->row)
		      m(pe->row,qe->col) += pe->val * qe->val;
	return m;
}

void Matrix::Print ()
{
	Element* elem = elems;
	for (short row = 1; row <= rows; ++row) {
	    for (short col = 1; col <= cols; ++col)
	        if (elem != 0 && elem->row == row && elem->col == col) {
	           cout << form("%5.2f ",elem->val);
	           elem = elem->next;
	        } else
	           cout << form("%5.2f ",0.0);
         cout << "\n";
	}
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
	Matrix r = m + n;
	r.Print();
}
