class Table;
typedef int (Table::*Compare)(const char*, const char*);

class Table {
public:
			Table	(const int slots);
			~Table	(void);
	int		Search	(char *item, Compare comp);

	int		CaseSesitiveComp (const char*, const char*);
	int		NormalizedComp	 (const char*, const char*);
	int		FastComp		 (const char*, const char*);
private:
	int		slots;
	char	**entries;
	//...
};

Table::Table (const int slots)
{
	//...
}

Table::~Table (void)
{
	//...
}

int Table::Search (char *item, Compare comp)
{
	int bot = 0;
	int top = slots - 1;
	int mid, cmp;

	while (bot <= top) {
		mid = (bot + top) / 2;
		if ((cmp = (this->*comp)(item, entries[mid])) == 0)
			return mid;				// return item index
		else if (cmp < 0)
			top = mid - 1;			// restrict search to lower half
		else
			bot = mid + 1;			// restrict search to upper half
	}
	return -1;						// not found
}

int	Table::FastComp (const char*, const char*)
{
	int	Table::*n = &Table::slots;
	int m = this->*n;
}

int main (void)
{
	Table	tab(10);

	tab.Search("me", Table::FastComp);

	return 0;
}