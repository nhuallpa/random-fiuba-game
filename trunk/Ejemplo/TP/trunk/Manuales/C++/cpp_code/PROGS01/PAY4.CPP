#include <iostream.h>

int main (void)
{
	int		workDays = 5;
	float	workHours, payRate, weeklyPay;

	cout << "What are the work hours and the hourly pay rate? ";
	cin >> workHours >> payRate;

	weeklyPay = workDays * workHours * payRate;
	cout << "Weekly Pay = " << weeklyPay << '\n';
}