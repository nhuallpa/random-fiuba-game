#include <iostream.h>
#include <string.h>

enum Bool {false, true};
typedef unsigned char uchar;

class BitVec {
public:
			 BitVec			(const short dim);
			 BitVec			(const char* bits);
			 BitVec			(const BitVec&);
			 ~BitVec		(void)	{ delete vec; }
	BitVec& operator =		(const BitVec&);
	BitVec& operator &=		(const BitVec&);
	BitVec& operator |=		(const BitVec&);
	BitVec& operator ^=		(const BitVec&);
	BitVec& operator <<=	(const short);
	BitVec& operator >>=	(const short);
	int		 operator [] 	(const short idx);
	void	 Set			(const short idx);
	void	 Reset			(const short idx);

	BitVec  operator ~		();
	BitVec  operator &		(const BitVec&);
	BitVec  operator |		(const BitVec&);
	BitVec  operator ^		(const BitVec&);
	BitVec  operator <<		(const short n);
	BitVec  operator >>		(const short n);
	Bool	 operator ==	(const BitVec&);
	Bool	 operator !=	(const BitVec&);

friend	ostream& operator << (ostream&, BitVec&);

protected:
	uchar	*vec;			// vector of 8*bytes bits
	short	 bytes;			// bytes in the vector

};

// set the bit denoted by idx to 1
inline void BitVec::Set (const short idx)
{
	vec[idx/8] |= (1 << idx%8);
}

// reset the bit denoted by idx to 0
inline void BitVec::Reset (const short idx)
{
	vec[idx/8] &= ~(1 << idx%8);
}

inline BitVec& BitVec::operator &= (const BitVec &v)
{
	return (*this) = (*this) & v;
}

inline BitVec& BitVec::operator |= (const BitVec &v)
{
	return (*this) = (*this) | v;
}

inline BitVec& BitVec::operator ^= (const BitVec &v)
{
	return (*this) = (*this) ^ v;
}

inline BitVec& BitVec::operator <<= (const short n)
{
	return (*this) = (*this) << n;
}

inline BitVec& BitVec::operator >>= (const short n)
{
	return (*this) = (*this) >> n;
}

// return the bit denoted by idx
inline int BitVec::operator [] (const short idx)
{
	return vec[idx/8] & (1 << idx%8) ? true : false;
}

inline Bool BitVec::operator != (const BitVec &v)
{
	return *this == v ? false : true;
}

