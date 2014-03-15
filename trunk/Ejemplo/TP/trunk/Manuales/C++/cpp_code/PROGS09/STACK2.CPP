#include <iostream.h>

template <class Type, int maxSize>
class Stack {
public:
			Stack	(void) :	stack(new Type[maxSize]), top(-1) {}
			~Stack	(void)		{delete [] stack;}
	void	Push	(Type &val);
	void	Pop		(void)		{if (top >= 0) --top;}
	Type&	Top		(void)		{return stack[top];}
//	friend	ostream& operator << (ostream&, Stack&);
private:
	Type		*stack;		// stack array
	int			top;		// index of top stack entry
//	const int	maxSize;	// max size of stack
};

template <class Type, int maxSize>
void Stack<Type, maxSize>::Push (Type &val)
{
	if (top+1 < maxSize)
		stack[++top] = val;
}

/*
template <class Type, int size>
ostream& operator << (ostream& os, Stack<Type,0>& s)
{
	for (register i = 0; i <= s.top; ++i)
		os << s.stack[i] << " ";
	return os;
}
*/

int main (void)
{
	Stack<int, 10> s;

	s.Push(10);
	s.Push(20);
	s.Push(30);
//	cout << s << '\n';
	return 0;
}
