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

#include <iostream.h>
#include <stdlib.h>  		// needed for atoi() below

int const cacheSize = 10;

class RawBook {
public:
			RawBook		 (char *str)	{ data = str; }
	Book	*operator -> (void);
	Book	&operator *  (void);
	Book	*operator &  (void);
private:
	Book	*RawToBook (void);

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

Book *RawBook::operator -> (void)	{return RawToBook(); }
Book &RawBook::operator *  (void)	{return *RawToBook();}
Book *RawBook::operator &  (void)	{return RawToBook(); }

main ()
{
	RawBook r1("%AA. Peters\0%TBlue Earth\0%PPhedra\0%CSydney\0%Y1981\0\n");
	RawBook r2("%TPregnancy\0%AF. Jackson\0%Y1987\0%PMiles\0\n");
	cout << r1->author    << ", " << r1->title     << ", "
	     << r1->publisher << ", " << r1->city      << ", "
		 << (*r1).vol     << ", " << (*r1).year    << '\n';

	Book* bp = &r2;		  // note use of &
	cout << bp->author    << ", " << bp->title     << ", "
	     << bp->publisher << ", " << bp->city      << ", "
		 << bp->vol       << ", " << bp->year      << '\n';
}
