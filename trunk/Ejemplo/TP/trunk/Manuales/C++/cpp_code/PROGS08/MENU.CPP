#include <iostream.h>

class Rect {
	int x;
};

class Widget {
	int x;
public:
	Widget (int y)	{x=y;}
};
class List {int x;};
class Port {int x;};

class OptionList : virtual public Widget, List {
public:
	OptionList	(int n);
	~OptionList	(void);
	void	Highlight	(int part)		{}
	//...
};

class Window : virtual public Widget, Port {
public:
	Window	(Rect &bounds);
    Window	(Window&) :Widget(0)	{}
	~Window	(void);
	void	Highlight	(int part)		{}
	//...
};

class Menu : public OptionList, public Window {
public:
	Menu	(int n, Rect &bounds);
	Menu	(Window&);

	~Menu	(void);
	void	Highlight	(int part)
			{OptionList::Highlight(part);
			 Window::Highlight(part);}
	//...
};

OptionList::OptionList (int n) : Widget(n)
{
	cout << "OptionList::OptionList invoked\n";
}

OptionList::~OptionList (void)
{
	cout << "OptionList::~OptionList invoked\n";
}

Window::Window (Rect&) : Widget(0)
{
	cout << "Window::Window invoked\n";
}

Window::~Window (void)
{
	cout << "Window::~Window invoked\n";
}

Menu::Menu (int n, Rect &bounds) : Widget(n), OptionList(n), Window(bounds)
{
	//...
}

Menu::Menu (Window &win) : Widget(0), OptionList(0), Window(win)
{
	//...
}

Menu::~Menu (void)
{
	cout << "Menu::~Menu invoked\n";
}

int main (void)
{
	Rect	r;
	Menu	menu(0,r);

	Window	win = menu;
	Window	&wRef = menu;
	Window	*wPtr = &menu;

	menu = (Menu) win;		// illegal
	Menu	&mRef = (Menu&) win;
	Menu	*mPtr = (Menu*) &win;

	menu.Highlight(0);
	return 0;
}