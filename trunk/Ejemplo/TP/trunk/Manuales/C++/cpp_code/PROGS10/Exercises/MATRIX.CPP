#include <iostream.h>

class DimsDontMatch	{};
class BadDims		{};
class BadRow		{};
class BadCol		{};
class HeapExhausted	{};

class Matrix {
public:
				Matrix		 (const short rows, const short cols);
                Matrix		 (const Matrix&);
				~Matrix		 (void)				{delete elems;}
		double& operator ()  (const short row, const short col);
		Matrix& operator =	 (const Matrix&);

friend ostream& operator <<  (ostream&, Matrix&);
friend  Matrix	operator  +	 (Matrix&, Matrix&);
friend  Matrix	operator  -	 (Matrix&, Matrix&);
friend  Matrix	operator  *	 (Matrix&, Matrix&);
		const short	Rows	 (void)		{return rows;}	   
		const short	Cols	 (void)		{return cols;}

private:
		const short	rows;	  // matrix rows
		const short	cols;	  // matrix columns
		double		*elems;	  // matrix elements
};


Matrix::Matrix (const short r, const short c) : rows(r), cols(c)
{
    if (rows <= 0 || cols <= 0)
    	throw BadDims();
	elems = new double[rows * cols];
    if (elems == 0)
    	throw HeapExhausted();
}

Matrix::Matrix (const Matrix &m) : rows(m.rows), cols(m.cols)
{
	int n = rows * cols;
    if (rows <= 0 || cols <= 0)
    	throw BadDims();
	elems = new double[n];
	if (elems == 0)
		throw HeapExhausted();
	for (register i = 0; i < n; ++i)		// copy elements
		elems[i] = m.elems[i];
}

double& Matrix::operator () (const short row, const short col)
{
	if (row <= 0 || row > rows)
    	throw BadRow();
    if (col <= 0 || col > cols)
    	throw BadCol();
	return elems[(row - 1)*cols + (col - 1)];
}

Matrix& Matrix::operator = (const Matrix &m)
{
	if (rows == m.rows && cols == m.cols) {   	// must match
		int n = rows * cols;
		for (register i = 0; i < n; ++i)		// copy elements
			elems[i] = m.elems[i];
	} else
    	throw DimsDontMatch();
	return *this;
}

ostream& operator << (ostream &os, Matrix &m)
{
	for (register r = 1; r <= m.rows; ++r) {
		for (int c = 1; c <= m.cols; ++c)
			os << m(r,c) << '\t';
		os << '\n';
	}
	return os;
}

Matrix operator + (Matrix &p, Matrix &q)
{
	if (p.rows != q.rows || p.cols != q.cols)
    	throw DimsDontMatch();
	Matrix m(p.rows, p.cols);
	if (p.rows == q.rows && p.cols == q.cols)
		for (register r = 1; r <= p.rows; ++r)
			for (register c = 1; c <= p.cols; ++c)
				m(r,c) = p(r,c) + q(r,c);
	return m;
}

Matrix operator - (Matrix &p, Matrix &q)
{
	if (p.rows != q.rows || p.cols != q.cols)
    	throw DimsDontMatch();
	Matrix m(p.rows, p.cols);
	if (p.rows == q.rows && p.cols == q.cols)
		for (register r = 1; r <= p.rows; ++r)
			for (register c = 1; c <= p.cols; ++c)
				m(r,c) = p(r,c) - q(r,c);
	return m;
}

Matrix operator * (Matrix &p, Matrix &q)
{
	if (p.cols != q.rows)
    	throw DimsDontMatch();
	Matrix m(p.rows, q.cols);
	if (p.cols == q.rows)
		for (register r = 1; r <= p.rows; ++r)
			for (register c = 1; c <= q.cols; ++c) {
				m(r,c) = 0.0;
				for (register i = 1; i <= p.cols; ++i)
					m(r,c) += p(r,c) * q(r,c);
			}
	return m;
}

#ifndef	_NOMAIN_

int main (void)
{
	Matrix m(2,3);

	m(1,1) = 10;	m(1,2) = 20;	m(1,3) = 30;
	m(2,1) = 15;	m(2,2) = 25;	m(2,3) = 35;
	cout << m << '\n';

	Matrix n = m;
	cout << n << '\n';
	return 0;
}

#endif