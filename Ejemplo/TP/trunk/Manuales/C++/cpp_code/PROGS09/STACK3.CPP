#include <iostream.h>
#include <string.h>

template <class Type>
class Stack {
public:
			Stack	(int max) :	stack(new Type[max]),
								top(-1), maxSize(max) {}
			~Stack	(void)		{delete [] stack;}
	void	Push	(Type &val);
	void	Pop		(void);
	Type&	Top		(void);
	friend	ostream &operator << (ostream&, Stack&);
private:
	Type		*stack;		// stack array
	int			top;		// index of top stack entry
	const int	maxSize;	// max size of stack
    static Type	dummy;		// dummy entry
};

template <class Type>
void Stack<Type>::Push (Type &val)
{
	if (top+1 < maxSize)
		stack[++top] = val;
}

template <class Type>
void Stack<Type>::Pop (void)
{
	if (top >= 0)
		--top;
}

template <class Type>
Type &Stack<Type>::Top (void)
{
	return top >= 0 ? stack[top] : dummy;

}

template <class Type>
ostream& operator << (ostream& os, Stack<Type>& s)
{
	for (register i = 0; i <= s.top; ++i)
		os << s.stack[i] << " ";
	return os;
}

// template <class Type> Type Stack<Type>::dummy = 0;
int Stack<int>::dummy = 0;

//---------------------------------------
template <class T> void Foo (T&);

template <class T>
class Sample {
	friend Foo<int>;
	friend Stack<int>;

	//...
	friend Foo<T>;
	friend Stack<T>;

	//...
	template <class T> friend Foo;
    template <class T> friend class Stack;
};

int main (void)
{
	Stack<int> s(10);

	cout << s.Top() << '\n';
	s.Push(1);
	s.Push(2);
	s.Push(3);
	cout << s << '\n';
	return 0;
}
