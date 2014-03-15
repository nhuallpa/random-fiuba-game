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
	Type&	Top		(void)		{return stack[top];}
	friend	ostream& operator << (ostream&, Stack&);
private:
	Type		*stack;		// stack array
	int			top;		// index of top stack entry
	const int	maxSize;	// max size of stack
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
ostream& operator << (ostream& os, Stack<Type>& s)
{
	for (register i = 0; i <= s.top; ++i)
		os << s.stack[i] << " ";
	return os;
}

typedef char* Str;

class Stack<Str> {
public:
			Stack<Str>::Stack	(int max) :	stack(new Str[max]),
								top(-1), maxSize(max) {}
			~Stack	(void)		{delete [] stack;}
	void	Push	(Str val);
	void	Pop		(void);
	Str		Top		(void)		{return stack[top];}
	friend	ostream& operator << (ostream&, Stack<Str>&);
private:
	Str			*stack;		// stack array
	int			top;		// index of top stack entry
	const int	maxSize;	// max size of stack
};

void Stack<Str>::Push (char* val)
{
	if (top+1 < maxSize) {
		stack[++top] = new char[strlen(val) + 1];
		strcpy(stack[top], val);
    }
}

void Stack<Str>::Pop (void)
{
	if (top >= 0)
		delete stack[top--];
}

int main (void)
{
	Stack<Str> s(10);

	s.Push("one");
	s.Push("two");
	s.Push("three");
	cout << s << '\n';
	return 0;
}
