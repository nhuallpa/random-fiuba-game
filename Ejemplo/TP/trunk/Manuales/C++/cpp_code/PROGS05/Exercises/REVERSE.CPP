#include <iostream.h>
#include <string.h>

char* ReverseString (char *str)
{
	int len = strlen(str);
	char *result = new char[len + 1];
	char *res = result + len;

    *res-- = '\0';
	while (*str)
		*res-- = *str++;
	return result;
}


int main (void)
{
	char *str = "Hello";

	cout << ReverseString(str) << '\n';

    return 0;
}