#include "cstring.h"

String::String (const char *str)
{
	len = strlen(str);
	chars = new char[len + 1];
	strcpy(chars, str);
}

String::String (const String &str)
{
	len = str.len;
	chars = new char[len + 1];
	strcpy(chars, str.chars);
}

String::String (const short size)
{
	len = size;
	chars = new char[len + 1];
	chars[0] = '\0';
}

String::~String (void)
{
	delete chars;
}

String& String::operator = (const char *str)
{
	short	strLen = strlen(str);
	if (len != strLen) {
		delete chars;
        len = strLen;
		chars = new char[strLen + 1];
	}
	strcpy(chars, str);
	return(*this);
}

String& String::operator = (const String &str)
{
	if (this != &str) {
		if (len != str.len) {
			delete chars;
            len = str.len;
			chars = new char[str.len + 1];
		}
		strcpy(chars, str.chars);
	}
    return(*this);	
}

char& String::operator [] (const short index)
{
	static char	dummy = '\0';
	return(index >= 0 && index < len ? chars[index] : dummy);
}

String operator + (const String &str1, const String &str2)
{
	String result(str1.len + str2.len);

	strcpy(result.chars, str1.chars);
	strcpy(result.chars + str1.len, str2.chars);
	return(result);
}

ostream& operator <<	(ostream &out, String &str)
{
	out << str.chars;
	return(out);
}

#ifndef _NOMAIN_

main ()
{
	String	str1("Hello");
	String	str2("Bye");

	cout << (str1 + str2) << "\n";
	cout << str1 << "\n";
	cout << str2 << "\n";
	cout << str1[4] << "\n";

	String	str3(5);
	str3[0] = 'M';	str3[1] = 'E';	str3[2] = '\0';
	cout << str3 << "\n";
	str3 = str1;
	cout << str3 << "\n";

}

#endif