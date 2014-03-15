#include "c:\books\cpp\part1\progs09\CList.h"

//---------------------------------------------------------
template <class Type>
List<Type>::~List (void)
{
	ListElem<Type> *handy;
	ListElem<Type> *next;

	for (handy = first; handy != 0; handy = next) {
		next = handy->next;
		delete handy;
	}
}

//---------------------------------------------------------
template <class Type>
void List<Type>::Insert (const Type &elem)
{
	ListElem<Type> *handy = new ListElem<Type>(elem);

	handy->next = first;
	if (first != 0)
		first->prev = handy;
	if (last == 0)
		last = handy;
    first = handy;
}

//---------------------------------------------------------
template <class Type>
void List<Type>::Remove (const Type &val)
{
	ListElem<Type> *handy;

	for (handy = first; handy != 0; handy = handy->next) {
		if (handy->val == val) {                                    
			if (handy->next != 0)
				handy->next->prev = handy->prev;
			else
				last = handy->prev;
			if (handy->prev != 0)
				handy->prev->next = handy->next;
			else
				first = handy->next;
			delete handy;
		}
	}
}

//---------------------------------------------------------
template <class Type>
Bool List<Type>::Member (const Type &val)
{
	ListElem<Type> *handy;

	for (handy = first; handy != 0; handy = handy->next)
		if (handy->val == val)
        	return true;
	return false;
}

//---------------------------------------------------------

template <class Type>
ostream& operator << (ostream &os, ListElem<Type> &elem)
{
	os << elem.Value();
    return os;
}

//---------------------------------------------------------
template <class Type>
ostream& operator << (ostream &os, List<Type> &list)
{
	ListElem<Type> *handy = list.first;

	os << "< ";
	for (; handy != 0; handy = handy->Next())
		os << *handy << " ";
	os << ">";
    return os;
}

//---------------------------------------------------------

#ifndef NOMAIN

/*
int main (void)
{
	List<int>	list;

	list.Insert(30);
	list.Insert(20);
	list.Insert(10);
	cout << "list = " << list << '\n';
	if (list.Member(20)) cout << "20 is in list\n";
	cout << "Removed 20\n";
	list.Remove(20);
	cout << "list = " << list << '\n';
	return 0;
}
*/

int main (void)
{
	Set<int>	set;
	set.Insert(10);
	set.Insert(20);
	set.Insert(10);
	set.Insert(30);
	cout << set << '\n';
	return 0;
}
#endif
