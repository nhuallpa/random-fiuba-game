#define _NOMAIN_

#include <stdlib.h>
#include <time.h>
#include "..\..\progs07\matrix.cpp"

inline double Abs(double n)	{return n >= 0 ? n : -n;}

class LinEqns : public Matrix {
public:
			LinEqns		(const int n, double *soln);
	void	Generate	(const int coef);
	void	Solve		(void);
private:
	Matrix	solution;
};

LinEqns::LinEqns (const int n, double* soln)
		: Matrix(n, n+1), solution(n, 1)
{
	for (register r = 1; r <= n; ++r)
    	solution(r, 1) = soln[r - 1];
}

void LinEqns::Generate (const int coef)
{
	int mid = coef / 2;

	srand((unsigned int) time(0));	// set random seed

	for (register r = 1; r <= Rows(); ++r) {
		(*this)(r, Cols()) = 0.0;	// initialize right-hand side

        // generate equations whose coefficients
        // do not exceed coef:

		for (register c = 1; c < Cols(); ++c) {
			(*this)(r, c) = (double) (mid - random(1000) % coef);
			(*this)(r, Cols()) += (*this)(r, c) * solution(c, 1);
		}
	}
}

// solve equations using Gaussian elimination

void LinEqns::Solve (void)
{
	double const epsilon = 1e-5;	// 'almost zero' quantity
	double temp;
	int diag, piv, r, c;

	for (diag = 1; diag <= Rows(); ++diag) {	// diagonal
		piv = diag;								// pivot
		for (r = diag + 1; r <= Rows(); ++r)	// upper triangle
			if (Abs((*this)(piv, diag)) < Abs((*this)(r, diag)))
				piv = r;						// choose new pivot

		// make sure there is a unique solution:
		if (Abs((*this)(piv, diag)) < epsilon) {
			if (Abs((*this)(diag, Cols())) < epsilon)
				cout << "infinite solutions\n";
			else
				cout << "no solution\n";
			return;
		}
		if (piv != diag) {
        	// swap pivit with diagonal:
			for (c = 1; c <= Cols(); ++c) {
				temp = (*this)(diag, c);
				(*this)(diag, c) = (*this)(piv, c);
				(*this)(piv, c) = temp;
			}
        }
		// normalise diag row so that m[diag, diag] = 1:
		temp = (*this)(diag, diag);
		(*this)(diag, diag) = 1.0;
		for (c = diag + 1; c <= Cols(); ++c)
			(*this)(diag, c) = (*this)(diag, c) / temp;

		// now eliminate entries below the pivot:
		for (r = diag + 1; r <= Rows(); ++r) {
			double factor = (*this)(r, diag);
			(*this)(r, diag) = 0.0;
			for (c = diag + 1; c <= Cols(); ++c)
				(*this)(r, c) -= (*this)(diag, c) * factor;
		}
        // display elimination step:
		cout << "eliminated below pivot in column " << diag << '\n';
		cout << *this;
	}

	// back substitute:
	Matrix soln(Rows(), 1);
	soln(Rows(), 1) = (*this)(Rows(), Cols());	// the last unknown

	for (r = Rows() - 1; r >= 1; --r) {				// the rest
		double sum = 0.0;
		for (diag = r + 1; diag <= Rows(); ++diag)
			sum += (*this)(r, diag) * soln(diag, 1);
		soln(r, 1) = (*this)(r, Cols()) - sum;
	}
	cout << "solution:\n";
    cout << soln;
}

int main (void)
{
	static double s3[] = {2.0,4.5,1.2};
	LinEqns eqn(3, s3);

	eqn.Generate(10);
	cout << eqn;
	eqn.Solve();

    return 0;
}