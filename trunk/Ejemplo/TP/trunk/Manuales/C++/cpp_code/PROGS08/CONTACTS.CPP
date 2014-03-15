#include <iostream.h>
#include <string.h>

class Contact {
public:
				Contact		(const char *name,
							 const char *address, const char *tel);
				~Contact	(void);
	const char	*Name		(void) const	{return name;}
	const char	*Address	(void) const	{return address;}
	const char	*Tel		(void) const	{return tel;}
friend ostream	&operator <<(ostream&, Contact&);

private:
	char		*name;
	char		*address;
	char		*tel;
};

Contact::Contact (const char *name, const char *address, const char *tel)
{
	Contact::name = new char[strlen(name) + 1];
	Contact::address = new char[strlen(address) + 1];
	Contact::tel = new char[strlen(tel) + 1];
	strcpy(Contact::name, name);
	strcpy(Contact::address, address);
	strcpy(Contact::tel, tel);
}

Contact::~Contact (void)
{
	delete name;
	delete address;
	delete tel;
}

ostream	&operator << (ostream &os, Contact &c)
{
	os << "(" << c.name << " , " << c.address << " , " << c.tel << ")";
    return os;
}

// --------------------------------------------------------------

class ContactDir {
public:
				ContactDir	(const int maxSize);
				~ContactDir	(void);
		void	Insert		(const Contact&);
		void	Delete		(const char *name);
		Contact	*Find		(const char *name);
friend	ostream	&operator <<(ostream&, ContactDir&);

protected:
virtual	int		Lookup		(const char *name);

	Contact		**contacts;	// list of contacts
	int			dirSize;	// current directory size
    int			maxSize;    // max directory size
};

ContactDir::ContactDir (const int max)
{
	typedef Contact *ContactPtr;
	dirSize = 0;
	maxSize = max;
	contacts = new ContactPtr[maxSize];
};

ContactDir::~ContactDir (void)
{
	for (register i = 0; i < dirSize; ++i)
		delete contacts[i];
	delete [] contacts;
}

void ContactDir::Insert (const Contact& c)
{
	if (dirSize < maxSize) {
		int idx = Lookup(c.Name());
		if (idx > 0 && strcmp(c.Name(), contacts[idx]->Name()) == 0) {
        	delete contacts[idx];
		} else {
			for (register i = dirSize; i > idx; --i)	// shift right
				contacts[i] = contacts[i-1];
			++dirSize;
		}
		contacts[idx] = new Contact(c.Name(), c.Address(), c.Tel());
	}
}

void ContactDir::Delete (const char *name)
{
	int idx = Lookup(name);
	if (idx < dirSize) {
		delete contacts[idx];
		--dirSize;
		for (register i = idx; i < dirSize; ++i)	// shift left
			contacts[i] = contacts[i+1];
	}
}

Contact *ContactDir::Find (const char *name)
{
	int idx = Lookup(name);
	return (idx < dirSize && strcmp(contacts[idx]->Name(), name) == 0)
			? contacts[idx]
			: 0;
}

int ContactDir::Lookup (const char *name)
{
	for (register i = 0; i < dirSize; ++i)
		if (strcmp(contacts[i]->Name(), name) == 0)
			return i;
	return dirSize;
}

ostream	&operator << (ostream &os, ContactDir &c)
{
	for (register i = 0; i < c.dirSize; ++i)
		os << *(c.contacts[i]) << '\n';
    return os;
}

// --------------------------------------------------------------

class SmartDir : public ContactDir {
public:
			SmartDir (const int max) : ContactDir(max) {recent = 0;}
	Contact	*Recent	 (void);
	Contact	*Find	 (const char *name);

protected:
	char	*recent;	// the most recently looked-up name
};

Contact *SmartDir::Recent (void)
{
	return recent == 0 ? 0 : ContactDir::Find(recent);
}

Contact *SmartDir::Find (const char *name)
{
	Contact *c = ContactDir::Find(name);
	if (c != 0)
		recent = (char*) c->Name();
    return c;
}

// --------------------------------------------------------------

class SortedDir : public ContactDir {
public:
				SortedDir	(const int max) : ContactDir(max) {}
protected:
virtual	int		Lookup		(const char *name);
};

int SortedDir::Lookup (const char *name)
{
	int bot = 0;
	int top = dirSize - 1;
	int pos = 0;
	int	mid, cmp;

	while (bot <= top) {
		mid = (bot + top) / 2;
		if ((cmp = strcmp(name, contacts[mid]->Name())) == 0)
			return mid;				// return item index
		else if (cmp < 0)
			pos = top = mid - 1;	// restrict search to lower half
		else
			pos = bot = mid + 1;	// restrict search to upper half
	}
	return pos < 0 ? 0 : pos;		// expected slot
}

int main (void)
{
	SortedDir	dir(10);
	dir.Insert(Contact("Mary", "11 South Rd", "282 1324"));
	dir.Insert(Contact("Peter", "9 Port Rd", "678 9862"));
	dir.Insert(Contact("Jane", "321 Yara Ln", "982 6252"));
	dir.Insert(Contact("Jack", "42 Wayne St", "663 2989"));
	dir.Insert(Contact("Fred", "2 High St", "458 2324"));

	cout << dir;
	return 0;
};