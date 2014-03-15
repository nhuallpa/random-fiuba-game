#ifndef _STRING_
#define _STRING_

#include <string.h>
#include <iostream.h>

class String {
public:
					String		(const char*);
					String		(const String&);
					String		(const short);
					~String		(void);
		String&		operator =	(const char*);
		String&		operator =	(const String&);
		char&		operator []	(const short);
		int			Length		(void)		{return(len);}
friend	String	 	operator +	(const String&, const String&);
friend	ostream& 	operator <<	(ostream&, String&);

protected:
	char		*chars;     // string characters
	short		len;		// length of chars
};

#endif