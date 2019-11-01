#include <iostream>
#include <fstream>
#include <cstdio>

#include "ClassDeclaration.h"

void UserMain();
void HallMain();
void MovieMain();
void SeatTypeMain();
void HallCapacityMain();
void ShowMain();
void BookingMain();
int DisplayMultiplexMain();
int LoginMain();

using namespace std;

#ifndef __CXX_TEST_MAIN__

int main()
{
	int status = LoginMain();
	if (status == 1)
	{
		while (1)
		{
			int selection = DisplayMultiplexMain();
			switch (selection)
			{
			case 1:
				UserMain();
				break;
			case 2:
				HallMain();
				break;
			case 3:
				MovieMain();
				break;
			case 4:
				SeatTypeMain();
				break;
			case 5:
				HallCapacityMain();
				break;
			case 6:
				ShowMain();
				break;
			case 7:
				BookingMain();
				break;
			default:
				cout << "Thank you for Multiplex Application" << endl;
				getchar();
				getchar();
				return 0;
			};
		}
	}

}

int DisplayMultiplexMain()
{
	cout << "Multiplex Booking System" << endl;
	cout << "________________________________________________" << endl;

	cout << "1.  Users" << endl;
	cout << "2.  Halls" << endl;
	cout << "3.  Movies" << endl;
	cout << "4.  Seat Types" << endl;
	cout << "5.  Halls Capacity" << endl;
	cout << "6.  Shows" << endl;
	cout << "7.  Booking" << endl;
	cout << "8.  Exit" << endl;
	cout << "___________________________________________" << endl;

	cout << "Enter your Selection: " << endl;
	int m = -1;
	cin >> m;

	return m;
}

int LoginMain()
{
	Users u;
	return u.inputLogin();
}

void UserMain()
{
	Users u;
	u.UserMain();
}

void HallMain()
{
	Halls h;
	h.HallMain();
}

void MovieMain()
{
	Movies m;
	m.MovieMain();
}

void SeatTypeMain()
{
	SeatTypes st;
	st.SeatTypeMain();
}

void HallCapacityMain()
{
	HallCapacities hc;
	hc.HallCapacityMain();
}

void ShowMain()
{
	Shows s;
	s.ShowMain();
}

void BookingMain()
{
	Bookings b;
	b.BookingMain();
}


#endif
