#include "matrix.h"

Matrix::Matrix (const short r, const short c) : rows(r), cols(c)
{
	elems = new double[rows * cols];
}

Matrix::Matrix (const Matrix &m) : rows(m.rows), cols(m.cols)
{
	int n = rows * cols;
	elems = new double[n];					// same dimension
	for (register i = 0; i < n; ++i)		// copy elements
		elems[i] = m.elems[i];
}

double& Matrix::operator () (const short row, const short col)
{
	static  double dummy = 0.0;
	return (row >= 1 && row <= rows && col >= 1 && col <= cols)
			? elems[(row - 1)*cols + (col - 1)]
			: dummy;
}

Matrix& Matrix::operator = (const Matrix &m)
{
	if (rows == m.rows && cols == m.cols) {   	// must match
		int n = rows * cols;
		for (register i = 0; i < n; ++i)		// copy elements
			elems[i] = m.elems[i];
	}
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
	Matrix m(p.rows, p.cols);
	if (p.rows == q.rows && p.cols == q.cols)
		for (register r = 1; r <= p.rows; ++r)
			for (register c = 1; c <= p.cols; ++c)
				m(r,c) = p(r,c) + q(r,c);
	return m;
}

Matrix operator - (Matrix &p, Matrix &q)
{
	Matrix m(p.rows, p.cols);
	if (p.rows == q.rows && p.cols == q.cols)
		for (register r = 1; r <= p.rows; ++r)
			for (register c = 1; c <= p.cols; ++c)
				m(r,c) = p(r,c) - q(r,c);
	return m;
}

Matrix operator * (Matrix &p, Matrix &q)
{
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