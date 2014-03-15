#include <iostream.h>

int main (void)
{
	int		workDays = 5;
	float	workHours = 7.5;
	float	payRate, weeklyPay;

	cout << "What is the hourly pay rate? ";
	cin >> payRate;

	weeklyPay = workDays * workHours * payRate;
	cout << "Weekly Pay = ";
	cout << weeklyPay;
	cout << '\n';
}