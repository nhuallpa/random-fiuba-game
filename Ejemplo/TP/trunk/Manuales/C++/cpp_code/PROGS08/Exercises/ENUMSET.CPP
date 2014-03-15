#define _NOMAIN_

#include "..\..\progs07\exers\bitvec.cpp"

class EnumSet : public BitVec {
public:
	        EnumSet (const short maxCard) : BitVec(maxCard) {}
	        EnumSet (BitVec& v) : BitVec(v)  {*this = (EnumSet&)v;}
	friend  EnumSet  operator +  (EnumSet &s, EnumSet &t);
	friend  EnumSet  operator -  (EnumSet &s, EnumSet &t);
	friend  EnumSet  operator *  (EnumSet &s, EnumSet &t);
	friend  Bool     operator %  (const short elem, EnumSet &s);
	friend  Bool     operator <= (EnumSet &s, EnumSet &t);
	friend  Bool     operator >= (EnumSet &s, EnumSet &t);
	friend  EnumSet& operator << (EnumSet &s, const short elem);
	friend  EnumSet& operator >> (EnumSet &s, const short elem);
};

inline EnumSet operator + (EnumSet &s, EnumSet &t)	// union
{
	return s | t;
}

inline EnumSet operator - (EnumSet &s, EnumSet &t)	// difference
{
	return s & ~t;
}

inline EnumSet operator * (EnumSet &s, EnumSet &t)	// intersection
{
	return s & t;
}

inline Bool operator % (const short elem, EnumSet &t)
{
	return t[elem];
}

inline Bool operator <= (EnumSet &s, EnumSet &t)
{
	return (t & s) == s;
}

inline Bool operator >= (EnumSet &s, EnumSet &t)
{
	return (t & s) == t;
}

EnumSet& operator << (EnumSet &s, const short elem)
{
	s.Set(elem);
	return s;
}

EnumSet& operator >> (EnumSet &s, const short elem)
{
	s.Reset(elem);
	return s;
}

int main (void)
{
	EnumSet s(60);

    s << 10 << 20 << 24;
    cout << s << '\n';
}
