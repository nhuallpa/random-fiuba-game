#include <iostream.h>

const	maxCard = 100;
enum	Bool {false, true};

class Set {
public:
				Set			(void)		{ card = 0; }
	friend Bool operator &  (const int, Set&);	// membership
	friend Bool operator == (Set&, Set&);		// equality
	friend Bool operator != (Set&, Set&);		// inequality
	friend Set  operator *  (Set&, Set&);		// intersection
	friend Set  operator +  (Set&, Set&);		// union
	//...
    friend	ostream&	operator << (ostream&, Set&);
    friend	istream&	operator >>	(istream&, Set&);

	void	AddElem (const int elem);
	void	Copy	(Set &set);
    void	Print	(void);
private:
	int		elems[maxCard];				// set elements
	int		card;						// set cardinality
};

ostream& operator << (ostream &os, Set &set)
{
	os << '{';
	for (int i = 0; i < card - 1; ++i)
		os << elems[i] << ',';
	if (card > 0)		// no comma after the last element
		os << elems[card-1];
	os << '}';
    return os;
}

istream& operator >> (istream &is, Set &set)
{
	return is;
}

Bool operator & (const int elem, Set &set)
{
	for (register i = 0; i < set.card; ++i)
		if (elem == set.elems[i])
			return true;
	return false;
}

Bool operator == (Set &set1, Set &set2)
{
	if (set1.card != set2.card)
		return false;
	for (register i = 0; i < set1.card; ++i)
		if (!(set1.elems[i] & set2))
			return false;
	return true;
}

Bool operator != (Set &set1, Set &set2)
{
	return !(set1 == set2);
}

Set operator * (Set &set1, Set &set2)
{
	Set res;

	for (register i = 0; i < set1.card; ++i)
		if (set1.elems[i] & set2)
			res.elems[res.card++] = set1.elems[i];
    return res;
}

Set operator + (Set &set1, Set &set2)
{
	Set res;

	set1.Copy(res);
	for (register i = 0; i < set2.card; ++i)
		res.AddElem(set2.elems[i]);
	return res;
}

void Set::AddElem (const int elem)
{
	for (register i = 0; i < card; ++i)
		if (elems[i] == elem)
			return;
	if (card < maxCard)
		elems[card++] = elem;
	else
    	cout << "Set overflow\n";
}

void Set::Copy (Set &set)
{
	for (register i = 0; i < card; ++i)
		set.elems[i] = elems[i];
	set.card = card;
}

int main (void)
{
	Set	s1, s2, s3;

	s1.AddElem(10); s1.AddElem(20); s1.AddElem(30); s1.AddElem(40);
	s2.AddElem(30); s2.AddElem(50); s2.AddElem(10); s2.AddElem(60);

	cout << "s1 = ";	s1.Print();
	cout << "s2 = ";	s2.Print();

	if (20 & s1) cout << "20 is in s1\n";

	cout << "s1 intsec s2 = ";	(s1 * s2).Print();
	cout << "s1 union s2 = ";	(s1 + s2).Print();

	if (s1 != s2) cout << "s1 /= s2\n";
	return 0;
}
