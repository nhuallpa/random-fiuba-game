#include <iostream.h>
#include <stdarg.h>

int Menu (char *option1 ...)
{
	va_list args;				// argument list
	char*   option = option1;
	int     count = 0, choice = 0;
	
	va_start(args, option1);	// initialize args

	do {
		cout << ++count << ". " << option << '\n';
	} while ((option = va_arg(args, char*)) != 0);

	va_end(args);				// clean up args
	cout << "option? ";
	cin >> choice;
	return (choice > 0 && choice <= count) ? choice : 0;
}

int main (void)
{
	int n = Menu(
		"Open file",
		"Close file",
		"Revert to saved file",
		"Delete file",
		"Quit application",
		0);
	cout << "Option " << n << " selected.\n";
	return 0;
}
