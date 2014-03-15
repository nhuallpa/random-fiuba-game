#include <iostream.h>

const int 	maxCard = 10;
enum  Bool	{false, true};


class Set {
public:
			Set			(void)		{ first = 0; }
            ~Set		(void);
	int		Card		(void);
	Bool    Member		(const int)	const;
	void	AddElem		(const int);
	void    RmvElem		(const int);
	void    Copy		(Set&);
	Bool    Equal		(Set&);
	void    Intersect	(Set&, Set&);
	void	Union		(Set&, Set&);
	void    Print		(void);

private:

	class Element {
	public:
					Element	(const int val)	{value = val; next = 0;}
		int			Value	(void)			{return value;}
		Element*&	Next	(void)			{return next;}
	private:
		int			value;	// element value
		Element		*next;	// next element
	};

	Element	*first;			// first element in the list
};

Set::~Set (void)
{
	Set::Element *handy, *next;

	for (handy = first; handy != 0; handy = next) {
		next = handy->Next();
		delete handy;
	}
}

int Set::Card (void)
{
	Set::Element *handy;
    int	card = 0;

	for (handy = first; handy != 0; handy = handy->Next())
		++card;
	return card;
}

Bool Set::Member (const int elem) const
{
	Set::Element *handy;

	for (handy = first; handy != 0; handy = handy->Next())
		if (handy->Value() == elem)
			return true;
	return false;
}

void Set::AddElem (const int elem)
{
	if (!Member(elem)) {
		Set::Element *option = new Set::Element(elem);
		option->Next() = first;		// prepend
		first = option;
    }
}

void Set::RmvElem (const int elem)
{
	Set::Element *handy, *prev = 0;
    int	idx = 0;

	// set prev to point to before the deletion position:
	for (handy = first;
		handy != 0 && handy->Next() != 0 && handy->Value() != elem;
		handy = handy->Next())
		prev = handy;

	if (handy != 0) {
		if (prev == 0)				// it's the first entry
			first = handy->Next();
		else						// it's not the first
			prev->Next() = handy->Next();
		delete handy;
	}
}

void Set::Copy (Set &set)
{
	Set::Element *handy;

	for (handy = first; handy != 0; handy = handy->Next())
		set.AddElem(handy->Value());
}

Bool Set::Equal (Set &set)
{
	Set::Element *handy;

	if (Card() != set.Card())
		return false;
	for (handy = first; handy != 0; handy = handy->Next())
		if (!set.Member(handy->Value()))
			return false;
	return true;
}

void Set::Intersect (Set &set, Set &res)
{
	Set::Element *handy;

	for (handy = first; handy != 0; handy = handy->Next())
		if (set.Member(handy->Value()))
			res.AddElem(handy->Value());
}

void Set::Union (Set &set, Set &res)
{
	Copy(res);
	set.Copy(res);
}

void Set::Print (void)
{
	Set::Element *handy;

	cout << '{';
	for (handy = first; handy != 0; handy = handy->Next()) {
    	cout << handy->Value();
        if (handy->Next() != 0)
        	cout << ',';
    }
	cout << "}\n";
}

int main (void)
{
	Set	s1, s2, s3;

	s1.AddElem(10); s1.AddElem(20); s1.AddElem(30); s1.AddElem(40);
	s2.AddElem(30); s2.AddElem(50); s2.AddElem(10); s2.AddElem(60);

	cout << "s1 = ";	s1.Print();
	cout << "s2 = ";	s2.Print();

	s2.RmvElem(50);			cout << "s2 - {50} = ";		s2.Print();

	if (s1.Member(20)) cout << "20 is in s1\n";

	s1.Intersect(s2,s3);	cout << "s1 intsec s2 = ";	s3.Print();

	s1.Union(s2,s3);		cout << "s1 union s2 = ";	s3.Print();

	if (!s1.Equal(s2)) cout << "s1 /= s2\n";

	const Set s4;
	s4.AddElem(10);
	s4.Member(10);

	return 0;
}
