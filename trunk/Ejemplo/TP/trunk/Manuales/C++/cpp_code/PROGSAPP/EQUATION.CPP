#include <iostream.h>

class LinEqns : public Matrix {
     int     nEqns;          // number of equations
     double* solution;       // the solution vector
public:
          LinEqns (int n,double* soln);
         ~LinEqns ()                     { delete solution; }
     void Generate (int coef);
     void Solve ();
};

LinEqns::LinEqns (int n,double* soln) : Matrix(n,n+1)
{
	nEqns = n;
	solution = new double[n];
	for (int i = 0; i < n; ++i)
		solution[i] = soln[i];
}

void
LinEqns::Generate (int coef)
{
	int mid = coef / 2;
	srandom((int) time(0));			// set random seed
	for (int r = 1; r <= nEqns; ++r) {
		(*this)(r,nEqns+1) = 0.0;		// right-hand side
		for (int c = 1; c <= nEqns; ++c) {
			(*this)(r,c) = (double) (mid - random() % coef);
			(*this)(r,nEqns+1) += (*this)(r,c) * solution[c-1];
		}
	}
}

void
LinEqns::Solve ()
{
	double const epsilon = 1e-5;
	double temp;
	int diag, piv, r, c;

	for (diag = 1; diag <= nEqns; ++diag) {
		piv = diag;
		for (r = diag+1; r <= nEqns; ++r)
			if (abs((*this)(piv,diag)) < abs((*this)(r,diag)))
				piv = r;
		// make sure there is a unique solution:
		if (abs((*this)(piv,diag)) < epsilon) {
			if (abs((*this)(diag,nEqns+1)) < epsilon)
				cout << "infinite solutions\n";
			else
				cout << "no solution\n";
			return;
		}
		if (piv != diag)
			for (c = 1; c <= nEqns+1; ++c) {
				temp = (*this)(diag,c);
				(*this)(diag,c) = (*this)(piv,c);
				(*this)(piv,c) = temp;
			}

		// normalise diag row so that m[diag,diag] = 1:
		temp = (*this)(diag,diag);
		(*this)(diag,diag) = 1.0;
		for (c = diag+1; c <= nEqns+1; ++c)
			(*this)(diag,c) = (*this)(diag,c) / temp;

		// now eliminate entries below the pivot:
		for (r = diag+1; r <= nEqns; ++r) {
			double factor = (*this)(r,diag);
			(*this)(r,diag) = 0.0;
			for (c = diag+1; c <= nEqns+1; ++c)
				(*this)(r,c) -= (*this)(diag,c) * factor;
		}
		cout << "eliminated below pivot in column " << diag << "\n";
		Print();
	}

	// back substitute:
	double* soln = new double[nEqns];
	soln[nEqns-1] = (*this)(nEqns,nEqns+1);		// the last unknown

	for (r = nEqns-1; r >= 1; --r) {		// the rest
		double sum = 0.0;
		for (diag = r+1; diag <= nEqns; ++diag)
			sum += (*this)(r,diag) * soln[diag-1];
		soln[r-1] = (*this)(r,nEqns+1) - sum;
	}
	for (r = 1; r <= nEqns; ++r)
		cout << "	 x[" << r << "] = " << soln[r-1] << "\n";
	delete soln;
}
