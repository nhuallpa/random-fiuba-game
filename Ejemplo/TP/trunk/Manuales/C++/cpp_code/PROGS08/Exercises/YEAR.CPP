#define _NOMAIN_

#include "..\..\progs07\exers\bitvec.cpp"

enum Month {
	Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

inline Bool LeapYear(const short year)	{return year%4 == 0;}

class Year : public BitVec {
public:
			Year	(const short year);
	void	WorkDay	(const short day);	// set day as work day
	void	OffDay	(const short day);	// set day as off day
	Bool	Working	(const short day);	// true if a work day
	short	Day		(const short day,	// convert date to day
					 const Month month, const short year);   
protected:
	short	year;	// calendar year
};

Year::Year (const short year) : BitVec(366)
{
	Year::year = year;
}

void Year::WorkDay (const short day)
{
	Set(day);
}

void Year::OffDay (const short day)
{
	Reset(day);
}

Bool Year::Working (const short day)
{
	return (*this)[day] == 1 ? true : false;
}

short Year::Day (const short day, const Month month, const short year)
{
	static short days[12] = {
		31, 28, 31, 30, 31, 30, 31, 31, 20, 31, 30, 31
	};
    days[Feb] = LeapYear(year) ? 29 : 28;

	int res = day;
	for (register i = Jan; i < month; ++i)
		res += days[i];
	return res;
}

int main (void)
{
	Year y(1994);

    y.WorkDay(12);
    y.WorkDay(78);
    cout << y.Working(70) << ' ' << y.Working(78) << '\n';
    cout << y << '\n';
}