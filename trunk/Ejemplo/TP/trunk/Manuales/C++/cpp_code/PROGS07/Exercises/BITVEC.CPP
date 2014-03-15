#include "bitvec.h"

BitVec::BitVec (const short dim)
{
	bytes = dim / 8 + (dim % 8 == 0 ? 0 : 1);
	vec = new uchar[bytes];

	for (register i = 0; i < bytes; ++i)
		vec[i] = 0;					// all bits are initially zero
}

BitVec::BitVec (const char *bits)
{
	int len = strlen(bits);
	bytes = len / 8 + (len % 8 == 0 ? 0 : 1);
	vec = new uchar[bytes];

	for (register i = 0; i < bytes; ++i)
		vec[i] = 0;					// initialize all bits to zero

	for (i = len - 1; i >= 0; --i)
		if (*bits++ == '1')			// set the 1 bits
			vec[i/8] |= (1 << (i%8));
}

BitVec::BitVec (const BitVec &v)
{
	bytes = v.bytes;
	vec = new uchar[bytes];
	for (register i = 0; i < bytes; ++i)	// copy bytes
		vec[i] = v.vec[i];
}

BitVec& BitVec::operator = (const BitVec& v)
{
	for (register i = 0; i < (v.bytes < bytes ? v.bytes : bytes); ++i)
		vec[i] = v.vec[i];			// copy bytes
	for (; i < bytes; ++i)			// extra bytes in *this
		vec[i] = 0;
	return *this;
}

// bitwise COMPLEMENT
BitVec BitVec::operator ~ (void)
{
	BitVec r(bytes * 8);
	for (register i = 0; i < bytes; ++i)
		r.vec[i] = ~vec[i];
	return r;
}

// bitwise AND
BitVec BitVec::operator & (const BitVec &v)
{
	BitVec r((bytes > v.bytes ? bytes : v.bytes) * 8);
	for (register i = 0; i < (bytes < v.bytes ? bytes : v.bytes); ++i)
		r.vec[i] = vec[i] & v.vec[i];
	return r;
}

// bitwise OR
BitVec BitVec::operator | (const BitVec &v)
{
	BitVec r((bytes > v.bytes ? bytes : v.bytes) * 8);
	for (register i = 0; i < (bytes < v.bytes ? bytes : v.bytes); ++i)
		r.vec[i] = vec[i] | v.vec[i];
	return r;
}

// bitwise exclusive-OR
BitVec BitVec::operator ^ (const BitVec &v)
{
	BitVec r((bytes > v.bytes ? bytes : v.bytes) * 8);
	for (register i = 0; i < (bytes < v.bytes ? bytes : v.bytes); ++i)
		r.vec[i] = vec[i] ^ v.vec[i];
	return r;
}

// SHIFT LEFT by n bits
BitVec BitVec::operator << (const short n)
{
	BitVec r(bytes * 8);
	int		zeros = n / 8;	// bytes on the left to become zero
	int		shift = n % 8;	// left shift for remaining bytes
	register i;

	for (i = bytes - 1; i >= zeros; --i)	// shift bytes left
		r.vec[i] = vec[i - zeros];

	for (; i >= 0; --i)						// zero left bytes
		r.vec[i] = 0;
	unsigned char prev = 0;

	for (i = zeros; i < r.bytes; ++i) {		// shift bits left
		r.vec[i] = (r.vec[i] << shift) | prev;
		prev = vec[i - zeros] >> (8 - shift);
	}
	return r;
}

// SHIFT RIGHT by n bits
BitVec BitVec::operator >> (const short n)
{
	BitVec r(bytes * 8);
	int 	zeros = n / 8;			// bytes on the right to become zero
	int 	shift = n % 8;			// right shift for remaining bytes
	register i;

	for (i = 0; i < bytes - zeros; ++i)		// shift bytes right
		r.vec[i] = vec[i + zeros];
	for (; i < bytes; ++i)					// zero right bytes
		r.vec[i] = 0;

	uchar prev = 0;
	for (i = r.bytes - zeros - 1; i >= 0; --i) {	// shift bits right
		r.vec[i] = (r.vec[i] >> shift) | prev;
		prev = vec[i + zeros] << (8 - shift);
	}
	return r;
}

Bool BitVec::operator ==  (const BitVec &v)
{
	int 	smaller = bytes < v.bytes ? bytes : v.bytes;
	register i;

	for (i = 0; i < smaller; ++i)		// compare bytes
		if (vec[i] != v.vec[i])
			return false;
	for (i = smaller; i < bytes; ++i)	// extra bytes in first operand
		if (vec[i] != 0)
			return false;
	for (i = smaller; i < v.bytes; ++i)	// extra bytes in second operand
		if (v.vec[i] != 0)
			return false;
	return true;
}

ostream& operator << (ostream &os, BitVec &v)
{
	const int maxBytes = 256;
	char  buf[maxBytes * 8 + 1];
    char  *str = buf;
	int	  n = v.bytes > maxBytes ? maxBytes : v.bytes;

	for (register i = n-1; i >= 0; --i)
		for (register j = 7; j >= 0; --j)
			*str++ = v.vec[i] & (1 << j) ? '1' : '0';
    *str = '\0';
	os << buf;
	return os;
}

#ifndef _NOMAIN_

int main (void)
{
	BitVec v("1011011101111");

	cout << v << endl;
	return 0;
}

#endif