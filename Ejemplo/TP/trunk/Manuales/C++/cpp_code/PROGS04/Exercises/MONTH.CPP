#include <iostream.h>

enum Month {
	Jan, Feb, Mar, Apr, May, Jun,
	Jul, Aug, Sep, Oct, Nov, Dec
};

char* MonthStr (Month month)
{
	switch (month) {
		case Jan:	return "January";
		case Feb:	return "february";
		case Mar:	return "March";
		case Apr:	return "April";
		case May:	return "May";
		case Jun:	return "June";
		case Jul:	return "July";
		case Aug:	return "August";
		case Sep:	return "September";
		case Oct:	return "October";
		case Nov:	return "November";
		case Dec:	return "December";
		default:	return "";
	}

}

int main (void)
{
	cout << MonthStr(Aug) << '\n';
	return 0;
}