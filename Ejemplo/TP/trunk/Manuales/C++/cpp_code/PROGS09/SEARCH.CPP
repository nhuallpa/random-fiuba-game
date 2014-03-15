#include <iostream.h>
#include <string.h>

template <class Type>
int BinSearch (Type &item, Type *table, int n)
{
	int bot = 0;
	int top = n - 1;
	int mid, cmp;

	while (bot <= top) {
		mid = (bot + top) / 2;
		if (item == table[mid])
			return mid;				// return item index
		else if (item < table[mid])
			top = mid - 1;			// restrict search to lower half
		else
			bot = mid + 1;			// restrict search to upper half
	}
	return -1;						// not found
}


struct Book {
	char	*raw;		// raw format (kept for reference)
	char	*author;
	char	*title;
	char	*publisher;
	char	*city;
	short	vol;
	short	year;
};

Book defBook = {
	"raw", "Author?", "Title?", "Publisher?", "City?", 0, 0
};

#include <stdlib.h>

int const cacheSize = 10;

class RawBook {
public:
			RawBook		 (char *str)	{ data = str; }
	Book	*operator -> (void);
	Book	&operator *  (void);
	Book	*operator &  (void);
    int		operator <	(RawBook &b)	{return Compare(b) < 0;}
	int		operator >	(RawBook &b)	{return Compare(b) > 0;}
	int		operator ==	(RawBook &b)	{return Compare(b) == 0;}
private:
	Book	*RawToBook	(void);
    int		Compare		(RawBook&);

	char	*data;
	static	Book  *cache;		// cache memory
	static	short curr;			// current record in cache
	static	short used;			// number of used cache records
};

Book	*RawBook::cache = new Book[cacheSize];
short	RawBook::curr = 0;
short	RawBook::used = 0;

Book *RawBook::RawToBook (void)
{
	char *str = data;
	for (register i = 0; i < used; ++i)		// search cache
		if (data == cache[i].raw)
			return cache + i;
	curr = used < cacheSize ? used++		// update curr and used
			         		: (curr < 9 ? ++curr : 0);
	Book *bk = cache + curr;				// the book
	*bk = defBook;							// set default values
	bk->raw = data;
	for (;;) {
		while (*str++ != '%')				// skip to next specifier
			;
		switch (*str++) {					// get a field
			case 'A': bk->author = str;     break;
			case 'T': bk->title  = str;     break;
			case 'P': bk->publisher = str;  break;
			case 'C': bk->city = str;       break;
			case 'V': bk->vol = atoi(str);  break;
			case 'Y': bk->year = atoi(str); break;
		}
		while (*str++ != '\0')              // skip till end of field
			;
		if (*str == '\n') break;            // end of record
	}
	return bk;
}

int RawBook::Compare (RawBook &b)
{
	int	cmp;
	Book *b1 = RawToBook();
    Book *b2 = b.RawToBook();
	if ((cmp = strcmp(b1->title, b2->title)) == 0)
		if ((cmp = strcmp(b1->author, b2->author)) == 0)
			return strcmp(b1->publisher, b2->publisher);
    return cmp;
}

Book *RawBook::operator -> (void)	{return RawToBook(); }
Book &RawBook::operator *  (void)	{return *RawToBook();}
Book *RawBook::operator &  (void)	{return RawToBook(); }

main ()
{
	RawBook books[] = {
		RawBook("%APeters\0%TBlue Earth\0%PPhedra\0%CSydney\0%Y1981\0\n"),
		RawBook("%TPregnancy\0%AJackson\0%Y1987\0%PMiles\0\n"),
        RawBook("%TZoro\0%ASmiths\0%Y1988\0%PMiles\0\n")
	};
	cout << BinSearch(RawBook("%TPregnancy\0%AJackson\0%PMiles\0\n"), books, 3) << '\n';
}

/*
int nums[] = {10,12,30,38,52,100};

main (void)
{
	int k = 52;
	cout << BinSearch(k,nums,6) << '\n';
}
*/

/*
char *cities[] = {"Boston", "London", "Sydney", "Tokyo"};

main ()
{
	cout << BinSearch("Sydney", cities, 4, strcmp) << '\n';
}
*/