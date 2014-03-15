#include <iostream.h>
#include <string.h>

char* CopyOf (const char *str)
{
	char *copy = new char[strlen(str) + 1];

	strcpy(copy, str);
	return copy;
}

main ()
{
	char *copy;
	cout << (copy = CopyOf("HELLO")) << '\n';
	delete copy;

	return 0;
}