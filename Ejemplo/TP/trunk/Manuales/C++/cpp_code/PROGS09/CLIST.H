#include <iostream.h>

enum  Bool {false, true};
template <class Type> class List;	// forward declaration

template <class Type>
class ListElem {
public:
				ListElem	(const Type elem) : val(elem)
							{prev = next = 0;}
	Type		&Value		(void)		{return val;}
	ListElem	*Prev		(void)		{return prev;}
    ListElem	*Next		(void)		{return next;}
	friend class List<Type>;
protected:
	Type		val;		// the element value
	ListElem	*prev;		// previous element in the list
	ListElem	*next;		// next element in the list
};
//---------------------------------------------------------
template <class Type>
class List {
public:
					List	(void)	{first = last = 0;}
					~List	(void);
	virtual	void	Insert	(const Type&);
	virtual	void	Remove	(const Type&);
	virtual	Bool	Member	(const Type&);
	friend	ostream& operator <<	(ostream&, List&);
protected:
	ListElem<Type>	*first;	// first element in the list
	ListElem<Type>	*last;	// last element in the list
};
//---------------------------------------------------------
template <class Type>
class Set : public List<Type> {
public:
	virtual	void	Insert	(const Type &val)
					{if (!Member(val)) List<Type>::Insert(val);}
};
