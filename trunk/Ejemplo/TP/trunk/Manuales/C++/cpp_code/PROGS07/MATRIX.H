#include <iostream.h>

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

