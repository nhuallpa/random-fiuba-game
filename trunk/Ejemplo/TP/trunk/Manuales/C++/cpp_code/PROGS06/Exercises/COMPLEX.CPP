#include <iostream.h>

class Complex {
public:
			Complex	(double r = 0, double i = 0)
					{real = r; imag = i;}
	Complex	Add		(Complex &c);
	Complex	Subtract(Complex &c);
	Complex Multiply(Complex &c);
    void	Print	(void);
private:
	double	real;	// real part
    double	imag;	// imaginary part
};

Complex Complex::Add (Complex &c)
{
	return Complex(real + c.real, imag + c.imag);
}

Complex Complex::Subtract (Complex &c)
{
	return Complex(real - c.real, imag - c.imag);
}

Complex Complex::Multiply (Complex &c)
{
	return Complex(	real * c.real - imag * c.imag,
					imag * c.real + real * c.imag);
}

void Complex::Print (void)
{
	cout << real << " + i" << imag << '\n';
}

int main (void)
{
	Complex x(2,5);
	Complex y(3,4);

	x.Print();
	y.Print();
	x.Add(y).Print();
	x.Subtract(y).Print();
	x.Multiply(y).Print();

	return 0;
}