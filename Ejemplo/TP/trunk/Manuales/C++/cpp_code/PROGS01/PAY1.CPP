#include <iostream.h>

int main (void)
{
	int		workDays;
	float	workHours, payRate, weeklyPay;

    workDays = 5;
	workHours = 7.5;
	payRate = 38.55;
	weeklyPay = workDays * workHours * payRate;
	cout << "Weekly Pay = ";
	cout << weeklyPay;
	cout << '\n';
}