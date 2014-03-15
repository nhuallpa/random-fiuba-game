#include <iostream.h>

const	maxCard = 100;
enum	Bool {false, true};

class Set {
public:
	void    EmptySet	(void)		{ card = 0; }
	Bool    Member		(const int);
	void	AddElem		(const int);
	void    RmvElem		(const int);
	void    Copy		(Set&);
	Bool    Equal		(Set&);
	void    Intersect	(Set&, Set&);
	void	Union		(Set&, Set&);
	void    Print		(void);
private:
	int		elems[maxCard];			// set elements
	int		card;					// set cardinality
};

Bool Set::Member (const int elem)
{
	for (register i = 0; i < card; ++i)
		if (elems[i] == elem)
			return true;
	return false;
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

void Set::RmvElem (const int elem)
{
	for (register i = 0; i < card; ++i)
		if (elems[i] == elem) {
			for (; i < card-1; ++i)	// shift elements left
				elems[i] = elems[i+1];
			--card;
		}
}

void Set::Copy (Set &set)
{
	for (register i = 0; i < card; ++i)
		set.elems[i] = elems[i];
	set.card = card;
}

Bool Set::Equal (Set &set)
{
	if (card != set.card)
		return false;
	for (register i = 0; i < card; ++i)
		if (!set.Member(elems[i]))
			return false;
	return true;
}

void Set::Intersect (Set &set, Set &res)
{
	res.card = 0;
	for (register i = 0; i < card; ++i)
		if (set.Member(elems[i]))
			res.elems[res.card++] = elems[i];
}

void Set::Union (Set &set, Set &res)
{
	set.Copy(res);
	for (register i = 0; i < card; ++i)
		res.AddElem(elems[i]);
}

void Set::Print (void)
{
	cout << "{";
	for (int i = 0; i < card-1; ++i)
		cout << elems[i] << ",";
	if (card > 0)		// no comma after the last element
		cout << elems[card-1];
	cout << "}\n";
}

int main (void)
{
	Set	s1, s2, s3;

	s1.EmptySet();  s2.EmptySet();  s3.EmptySet();
	s1.AddElem(10); s1.AddElem(20); s1.AddElem(30); s1.AddElem(40);
	s2.AddElem(30); s2.AddElem(50); s2.AddElem(10); s2.AddElem(60);

	cout << "s1 = ";	s1.Print();
	cout << "s2 = ";	s2.Print();

	s2.RmvElem(50);			cout << "s2 - {50} = ";		s2.Print();

	if (s1.Member(20)) cout << "20 is in s1\n";

	s1.Intersect(s2,s3);	cout << "s1 intsec s2 = ";	s3.Print();

	s1.Union(s2,s3);		cout << "s1 union s2 = ";	s3.Print();

	if (!s1.Equal(s2)) cout << "s1 /= s2\n";
	return 0;
}
