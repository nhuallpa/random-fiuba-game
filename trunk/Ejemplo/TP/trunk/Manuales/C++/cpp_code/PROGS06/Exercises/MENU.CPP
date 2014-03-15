#include <iostream.h>
#include <string.h>

const int end = -1;		// denotes the end of the list

class Menu {
public:
			Menu	(void)		{first = 0; id = lastId++;}
			~Menu	(void);
	void	Insert	(const char *str, const int pos = end);
	void	Delete	(const int pos = end);
	int		Choose	(void);
    int		ID		(void)		{return id;}

private:

	class Option {
	public:
					Option	(const char*);
					~Option	(void)	{delete name;}
		const char*	Name	(void)	{return name;}
        Option*&	Next	(void)	{return next;}
	private:
		char	*name;	// option name
        Option	*next;	// next option
	};

	Option	*first;		// first option in the menu
    int		id;			// menu ID

    static int	lastId;		// last allocated ID
};

Menu::Option::Option (const char* str)
{
	name = new char [strlen(str) + 1];
	strcpy(name, str);
	next = 0;
}

int Menu::lastId = 0;

Menu::~Menu (void)
{
	Menu::Option *handy, *next;

	for (handy = first; handy != 0; handy = next) {
		next = handy->Next();
		delete handy;
	}
}

void Menu::Insert (const char *str, const int pos)
{
	Menu::Option *option = new Menu::Option(str);
	Menu::Option *handy, *prev = 0;
    int	idx = 0;

	// set prev to point to before the insertion position:
	for (handy = first; handy != 0 && idx++ != pos; handy = handy->Next())
		prev = handy;

    if (prev == 0) {			// empty list
	   option->Next() = first;	// first entry
	   first = option;
	} else { 					// insert
    	option->Next() = handy;
		prev->Next() = option;
	}
}

void Menu::Delete (const int pos)
{
	Menu::Option *handy, *prev = 0;
    int	idx = 0;

	// set prev to point to before the deletion position:
	for (handy = first;
		handy != 0 && handy->Next() != 0 && idx++ != pos;
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

int Menu::Choose (void)
{
	int n, choice;
	Menu::Option *handy = first;

	do {
    	n = 0;
		for (handy = first; handy != 0; handy = handy->Next())
			cout << ++n << ". " << handy->Name() << '\n';
		cout << "Option? ";
		cin >> choice;
	} while (choice <= 0 || choice > n);

	return choice;
}

int main (void)
{
	Menu m;

	m.Insert("Open File");
    m.Insert("Save File");
	m.Insert("Close File");
	m.Insert("Quit");
	m.Insert("----", 1);

    m.Delete();

	cout << m.Choose() << '\n';

	return 0;
}

