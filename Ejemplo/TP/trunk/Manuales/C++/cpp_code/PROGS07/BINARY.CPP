#include <iostream.h>
#include <string.h>

int const binSize = 16;

class Binary {
public:
				Binary		 (const char*);
				Binary		 (unsigned int);
friend	Binary	operator +	 (const Binary, const Binary);
friend	Binary	operator ++	 (Binary&);
friend	Binary	operator ++	 (Binary&, int);
				operator int (void);	// type conversion
		void	Print		 (void);
friend	ostream& operator << (ostream&, Binary&);
friend	istream& operator >> (istream&, Binary&);
 
private:
		char	bits[binSize];			// binary quantity
};

Binary::Binary (const char *num)
{
	int iSrc = strlen(num) - 1;
	int iDest = binSize - 1;

	while (iSrc >= 0 && iDest >= 0)		// copy bits
	    bits[iDest--] = (num[iSrc--] == '0' ? '0' : '1');
	while (iDest >= 0)					// pad left with zeros
	    bits[iDest--] = '0';
}

Binary::Binary (unsigned int num)
{
	for (register i = binSize - 1; i >= 0; --i) {
	    bits[i] = (num % 2 == 0 ? '0' : '1');
	    num >>= 1;
	}
}

Binary operator + (const Binary n1, const Binary n2)
{
	unsigned carry = 0;
	unsigned value;
	Binary res = "0";

	for (register i = binSize - 1; i >= 0; --i) {
	    value = (n1.bits[i] == '0' ? 0 : 1) +
	            (n2.bits[i] == '0' ? 0 : 1) + carry;
	    res.bits[i] = (value % 2 == 0 ? '0' : '1');
	    carry = value >> 1;
	}
	return res;
}

Binary operator ++ (Binary &n)
{
	return n = n + Binary(1);
}

Binary operator ++ (Binary &n, int)
{
	Binary m = n;
	n = n + Binary(1);
	return m;
}

Binary::operator int ()
{
	unsigned value = 0;

	for (register i = 0; i < binSize; ++i)
	    value = (value << 1) + (bits[i] == '0' ? 0 : 1);
	return value;
}

void Binary::Print (void)
{
	char str[binSize + 1];
	strncpy(str, bits, binSize);
	str[binSize] = '\0';
	cout << str << '\n';
}

ostream& operator << (ostream &os, Binary &n)
{
	char str[binSize + 1];
	strncpy(str, n.bits, binSize);
	str[binSize] = '\0';
	cout << str;
	return os;
}

istream& operator >> (istream &is, Binary &n)
{
	char str[binSize + 1];
	cin >> str;
    n = Binary(str);
	return is;
}

main ()
{
	Binary n1 = "01011";
	Binary n2 = "11010";
	cout << ++n1 << '\n';
	cout << n2++ << '\n';
	cout << n2   << '\n';

	cout << n1 << " + " << n2 << " = " << n1 + n2 << '\n';

	Binary n3 = "";
	cout << "Input Number>"; cin >> n3;
	cout << n3 << '\n';

	n1.Print();
	n2.Print();
	(n1 + n2).Print();
	cout << n1 + Binary(5) << '\n';	// add and then convert to int
	cout << n1 - 5 << '\n';			// convert n2 to int and then subtract
}
