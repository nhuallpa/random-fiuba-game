#include <iostream.h>
#include <string.h>

const int end = -1;		// denotes the end of the list
class Option;

class Menu {
public:
			Menu	(void)		{first = 0; id = lastId++;}
			~Menu	(void);
	void	Insert	(const char *str, const Menu *submenu, const int pos = end);
	void	Delete	(const int pos = end);
    int		Print	(void);
	int		Choose	(void)	const;
    int		ID		(void)		{return id;}

private:

	class Option {
	public:
					Option	(const char*, const Menu* = 0);
					~Option	(void);
		const char*	Name	(void)	{return name;}
        const Menu*	Submenu	(void)	{return submenu;}
        Option*&	Next	(void)	{return next;}
        void		Print	(void);
        int			Choose	(void)	const;
	private:
		char		*name;		// option name
		const Menu	*submenu;	// submenu
        Option		*next;		// next option
	};

	Option	*first;				// first option in the menu
    int		id;					// menu ID

    static int	lastId;			// last allocated ID
};

Menu::Option::Option (const char *str, const Menu *menu) : submenu(menu)
{
	name = new char [strlen(str) + 1];
	strcpy(name, str);
	next = 0;
}

Menu::Option::~Option (void)
{
	delete name;
	delete submenu;
}

void Menu::Option::Print (void)
{
    cout << name;
    if (submenu != 0)
    	cout << " ->";
    cout << '\n';
}

int Menu::Option::Choose (void) const
{
    if (submenu == 0)
    	return 0;
    else
	   	return submenu->Choose();
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

void Menu::Insert (const char *str, const Menu *submenu, const int pos)
{
	Menu::Option *option = new Option(str, submenu);
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

int Menu::Print (void)
{
    int n = 0;
	Menu::Option *handy = first;

	for (handy = first; handy != 0; handy = handy->Next()) {
		cout << ++n << ". ";
		handy->Print();
    }
    return n;
}

int Menu::Choose (void) const
{
	int choice, n;

	do {
    	n = Print();
		cout << "Option? ";
		cin >> choice;
	} while (choice <= 0 || choice > n);

	Menu::Option *handy = first;
    n = 1;

    // move to the chosen option:
	for (handy = first; n != choice && handy != 0; handy = handy->Next())
		++n;
	// choose the option:
    n = handy->Choose();

	return (n == 0 ? choice : n);

}

int main (void)
{
	Menu m;
    Menu *n = new Menu();

    n->Insert("Save Workspace", 0);
    n->Insert("Save Rulers", 0);
    n->Insert("Save just Data", 0);

	m.Insert("Open File", 0);
    m.Insert("Save File", n);
	m.Insert("Close File", 0);
	m.Insert("Quit", 0);
	m.Insert("----", 0, 1);

 	cout << m.Choose() << '\n';

	return 0;
}

