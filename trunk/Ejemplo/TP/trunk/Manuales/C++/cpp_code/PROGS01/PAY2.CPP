#include <iostream.h>

int main (void)
{
	int		workDays = 5;
	float	workHours = 7.5;
	float	payRate = 38.55;
	float	weeklyPay = workDays * workHours * payRate;

	cout << "Weekly Pay = ";
	cout << weeklyPay;
	cout << '\n';
}