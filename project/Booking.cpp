#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include "ClassDeclaration.h"
#include <time.h>
#include <ctime>
#include <sstream>
#include<stdio.h>

using namespace std;

int m_nMaxBookCapacity, m_MaxBookShow, m_MaxBookUser, m_MaxBookHall, m_MaxBookMovie, m_nMaxBookSeatTypes, m_nMaxBookHallCapacity;

Bookings::Bookings()
{
}

void Bookings::AddRecord(int bookingid, int showId, int userId, const char *bookingDate, const char *showDate, int seattypeid, int noofseats)
{
	int pos = m_nMaxBookCapacity;
	bookingList[pos].bookingId = bookingid;
	bookingList[pos].showId = showId;
	strcpy(bookingList[pos].bookingDate, bookingDate);
	strcpy(bookingList[pos].showDate, showDate);
	bookingList[pos].userId = userId;
	bookingList[pos].seattypeid = seattypeid;
	bookingList[pos].noofseats = noofseats;

	m_nMaxBookCapacity++;
	WriteRecords();
}

int Bookings::DeleteRecord(int pos)
{
    
    int max = m_nMaxBookCapacity;
   
    //Students code
    for (int i = pos; i < m_nMaxBookCapacity; i++)
	{
		hallCapacityList[i] = hallCapacityList[i + 1];
	}
	m_nMaxBookCapacity--;
    

    if(max == m_nMaxBookCapacity)
       return 0;
    else
       return 1;
}

int Bookings::HallReadRecords()
{
	FILE *istream = fopen("Halls.bin", "rb");
	if (istream == 0)
		return 0;

	char buf[4096];
	int nTotalRecordsRead = 0;

	for (int i = 0; i < MaxSz; i++)
	{
		if (feof(istream))
			break;
		int nBytesRead = fread(buf, 1, sizeof(Hall), istream);

		if (nBytesRead < sizeof(Hall))
			break;

		char *p = (char*)(&hallList[i]);
		memcpy(p, buf, sizeof(Hall));
		nTotalRecordsRead++;
	}
	fclose(istream);

	m_MaxBookHall = nTotalRecordsRead;

	return nTotalRecordsRead;
}


int Bookings::MovieReadRecords()
{
	FILE *istream = fopen("movies.bin", "rb");
	if (istream == 0)
		return 0;

	char buf[4096];
	int nTotalRecordsRead = 0;

	for (int i = 0; i < MaxSz; i++)
	{
		if (feof(istream))
			break;
		int nBytesRead = fread(buf, 1, sizeof(Movie), istream);

		if (nBytesRead < sizeof(Movie))
			break;

		char *p = (char*)(&movieList[i]);
		memcpy(p, buf, sizeof(Movie));
		nTotalRecordsRead++;
	}
	fclose(istream);

	m_MaxBookMovie = nTotalRecordsRead;

	return nTotalRecordsRead;
}



int Bookings::ShowReadRecords()
{
	FILE *istream = fopen("Shows.bin", "rb");
	if (istream == 0)
		return 0;

	char buf[4096];
	int nTotalRecordsRead = 0;

	for (int i = 0; i < MaxSz; i++)
	{
		if (feof(istream))
			break;
		int nBytesRead = fread(buf, 1, sizeof(Show), istream);

		if (nBytesRead < sizeof(Show))
			break;

		char *p = (char*)(&showList[i]);
		memcpy(p, buf, sizeof(Show));
		nTotalRecordsRead++;
	}
	fclose(istream);

	m_MaxBookShow = nTotalRecordsRead;

	return nTotalRecordsRead;
}

int Bookings::HallCapacityReadRecords()
{
	FILE *istream = fopen("hallcapacity.bin", "rb");
	if (istream == 0)
		return 0;

	char buf[4096];
	int nTotalRecordsRead = 0;

	for (int i = 0; i < MaxSz; i++)
	{
		if (feof(istream))
			break;
		int nBytesRead = fread(buf, 1, sizeof(HallCapacity), istream);

		if (nBytesRead < sizeof(HallCapacity))
			break;

		char *p = (char*)(&hallCapacityList[i]);
		memcpy(p, buf, sizeof(HallCapacity));
		nTotalRecordsRead++;
	}
	fclose(istream);

	m_nMaxBookHallCapacity = nTotalRecordsRead;

	return nTotalRecordsRead;

}

int Bookings::SeatTypeReadRecords()
{
	FILE *istream = fopen("SeatTypes.bin", "rb");
	if (istream == 0)
		return 0;

	char buf[4096];
	int nTotalRecordsRead = 0;

	for (int i = 0; i < MaxSz; i++)
	{
		if (feof(istream))
			break;
		int nBytesRead = fread(buf, 1, sizeof(SeatType), istream);

		if (nBytesRead < sizeof(SeatType))
			break;

		char *p = (char*)(&seatTypeList[i]);
		memcpy(p, buf, sizeof(SeatType));
		nTotalRecordsRead++;
	}
	fclose(istream);

	m_nMaxBookSeatTypes = nTotalRecordsRead;

	return nTotalRecordsRead;

}



int Bookings::UserReadRecords()
{
	FILE *istream = fopen("users.bin", "rb");
	if (istream == 0)
		return 0;

	char buf[4096];
	int nTotalRecordsRead = 0;

	for (int i = 0; i < MaxSz; i++)
	{
		if (feof(istream))
			break;
		int nBytesRead = fread(buf, 1, sizeof(User), istream);

		if (nBytesRead < sizeof(User))
			break;

		char *p = (char*)(&userList[i]);
		memcpy(p, buf, sizeof(User));
		nTotalRecordsRead++;
	}
	fclose(istream);

	m_MaxBookUser = nTotalRecordsRead;

	return nTotalRecordsRead;
}


int Bookings::WriteRecords()
{
	FILE *ostream = fopen("Books.bin", "wb");

	if (ostream == 0)
		return 0;

	int nTotalRecordsWritten = 0;
	char buf[4096];

	for (int i = 0; i < m_nMaxBookCapacity; i++)
	{
		fwrite((char*)&bookingList[i], 1, sizeof(MovieBook), ostream);
		nTotalRecordsWritten++;
	}

	fclose(ostream);

	return nTotalRecordsWritten;
}

Bookings booking;

int Bookings::DisplayMainMenu()
{
	//::system("cls");
	cout << "Bookings Menu" << endl;
	cout << "________________________________________________" << endl;

	cout << "1. Book a show" << endl;
	cout << "2. Delete booking" << endl;
	cout << "3. List all bookings" << endl;
	cout << "4.  Back" << endl;
	cout << "___________________________________________" << endl;

	cout << "Enter your Selection: " << endl;
	int m = -1;
	cin >> m;

	return m;
}

void Bookings::ViewRecords()
{
	booking.ReadRecords();

    cout << "List all Booking Details" << endl;
	cout << "___________________________________________" << endl;
	cout << "Booking Id " << "Show ID " << "Booking Date " << "Book Show Dt  " << "User ID\t" << endl;
	cout << "___________________________________________" << endl;

    //Students code
    for (int i = 0; i < m_nMaxBookCapacity; i++)
	{
		cout << booking.bookingList[i].bookingId <<"\t" << booking.bookingList[i].showId << "\t" <<
			booking.bookingList[i].bookingDate << "\t" << booking.bookingList[i].showDate << "\t" <<
			booking.bookingList[i].userId << endl;

		cout << "___________________________________________" << endl;

	}

}


bool Bookings::extractBookingDate(const std::string& s, int& d, int& m, int& y)
{
	std::istringstream is(s);
	char delimiter;
	if (is >> d >> delimiter >> m >> delimiter >> y) {
		struct tm t = { 0 };
		t.tm_mday = d;
		t.tm_mon = m - 1;
		t.tm_year = y - 1900;
		t.tm_isdst = -1;

		// normalize:
		time_t when = mktime(&t);
		const struct tm *norm = localtime(&when);

		// validate (is the normalized date still the same?):
		return (norm->tm_mday == d    &&
			norm->tm_mon == m - 1 &&
			norm->tm_year == y - 1900);
	}
	return false;
}


void Bookings::InputRecords()
{
	int bookingid = 0, showid = 0, hallid = 0, seatid = 0, noofseats = 0, userid = 0, showfound = 0, userfound = 0, found = 0, seattypefound = 0;
	char bookingdt[80], showdt[80];
	while (1)
	{

		booking.ShowReadRecords();

		time_t rawtime;
		struct tm * timeinfo;
		

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(bookingdt, 80, "%d-%m-%Y", timeinfo);

		cout << "Add Booking" << endl;
		cout << "___________________________________________" << endl;

		cout << "Booking ID: " << endl;
		cin >> bookingid;

		cout << "Show ID: " << endl;
		cin >> showid;

		for (int i = 0; i < m_MaxBookShow; i++)
		{
			int sid = booking.showList[i].showId;
			if (showid == sid)
			{
				showfound = 1;
				userfound = 0;

				booking.HallReadRecords();
				for (int j = 0; j < m_MaxBookHall; j++)
				{
					hallid = booking.hallList[j].hallId;
					if (hallid == booking.showList[i].hallId)
					{
						cout << "Hall " << booking.hallList[j].name << endl;
						break;
					}
				}

				booking.MovieReadRecords();
				for (int j = 0; j < m_MaxBookMovie; j++)
				{
					if (booking.movieList[j].movieId == booking.showList[i].movieId)
					{
						cout << "Movie " << booking.movieList[j].name << endl;
						break;
					}
				}
				if (booking.showList[i].slot == 1)
					cout << "Slot: 10:30 AM" << endl;
				else if (booking.showList[i].slot == 2)
					cout << "Slot: 02:30 PM" << endl;
				else if (booking.showList[i].slot == 3)
					cout << "Slot: 05:30 PM" << endl;
				else if (booking.showList[i].slot == 4)
					cout << "Slot: 08:30 PM" << endl;

				strcpy(showdt,booking.showList[i].showdate);

				cout << "Show Date: " << showdt << endl;
				break;
			}
		}

		if (showfound == 0)
		{
			cout << "Invalid Show ID" << endl;
			userfound = 0;
		}
		else
		{
			booking.UserReadRecords();

			cout << "User ID: " << endl;
			cin >> userid;

			for (int i = 0; i < m_MaxBookUser; i++)
			{
				int uid = booking.userList[i].userId;
				if (uid == userid)
				{
					userfound = 1;
					showfound = 0;
					cout << "User Name " << booking.userList[i].userName << endl;
					cout << "Email ID " << booking.userList[i].emailId << endl;
					cout << "Mobile Number " << booking.userList[i].mobileNumber << endl;
					break;
				}
			}



			if (userfound == 0)
			{
				showfound = 0;
				cout << "Invalid User ID" << endl;
			}
			else
			{
				booking.ReadRecords();
				for (int i = 0; i < m_nMaxBookCapacity; i++)
				{
					if (booking.bookingList[i].bookingId == bookingid)
					{
						found = 1;
						break;
					}
					else
						found = 0;
				}

				if (found == 1)
				{
					found = 0;
					cout << "Booking ID already exists" << endl;
				}
				else
				{
					found = 0;

					char showdate[30];

					cout << "Enter Show Date [ DD/MM/YYYY]" << endl;
					cin >> showdate;

					std::string s(showdate);
					int d, m, y;

					if (extractBookingDate(s, d, m, y))
					{
						if (strcmp(showdate, showdt) == 0)
						{
							cout << "Seat type ids available" << endl;

							booking.HallCapacityReadRecords();

							for (int i = 0; i < m_nMaxBookHallCapacity; i++)
							{
								if (booking.hallCapacityList[i].hId = hallid)
								{
									cout << booking.hallCapacityList[i].sId << " ";
								}
							}

							cout << endl;

							cout << "Seat Type ID: " << endl;
							cin >> seatid;

							booking.SeatTypeReadRecords();

							for (int i = 0; i < m_nMaxBookHallCapacity; i++)
							{
								if (booking.hallCapacityList[i].hId = hallid && booking.hallCapacityList[i].sId == seatid)
								{
									seattypefound = 1;
									break;
								}
								else
									seattypefound = 0;
							}

							if (seattypefound == 0)
							{
								seattypefound = 0;
								cout << "Seat Type ID doesn't exists" << endl;
							}
							else
							{
								seattypefound = 0;

								cout << "No of Seats: " << endl;
								cin >> noofseats;

								booking.AddRecord(bookingid, showid, userid, bookingdt, showdate, seatid, noofseats);
							}
						}
						else
						{
							cout << "Show not available on the booking date" << endl;
						}
					}
					else
						cout << "Date is Invalid" << endl;

				}
			}
		}
		
		cout << "Do you want to add another record (Y/N)? " << endl;
		getchar();
		char ch = getchar();
		if (ch == 'Y' || ch == 'y')
			continue;
		else
			break;

	}

}

void Bookings::DeleteRecords()
{
	booking.ViewRecords();
	cout << "Enter the row id you want to delete: ";

	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxBookCapacity)
	{

		booking.DeleteRecord(m - 1);
		cout << "Record deleted. Press any key to return to Main Menu";
		getchar();
		getchar();
	}
	else
	{
		cout << "Invalid Entry. Press any key to return to Main Menu";

		getchar();
		getchar();
	}
}

int Bookings::ReadRecords()
{
	FILE *istream = fopen("Books.bin", "rb");
	if (istream == 0)
		return 0;

     char buf[4096];
     int nTotalRecordsRead = 0;

    for (int i = 0; i < m_nMaxBookCapacity; i++)
     {
        if (feof(istream))
            break;

        //Students code
        int nBytesRead = fread(buf, 1, sizeof(MovieBook), istream);

		if (nBytesRead < sizeof(MovieBook))
			break;

		char *p = (char*)(&bookingList[i]);
		memcpy(p, buf, sizeof(User));
		nTotalRecordsRead++;
        
  
     }
    fclose(istream);

    m_nMaxBookCapacity = nTotalRecordsRead;

    return nTotalRecordsRead;
}


int Bookings::BookingMain()
{
	booking.ReadRecords();
	while (1)
	{
		int selection = booking.DisplayMainMenu();

		switch (selection)
		{
		case 1:
			booking.InputRecords();
			break;
		case 3:
		{
			booking.ViewRecords();
			cout << "Press any key to return to Main Menu: ";
			getchar();
			getchar();
		}
		break;
		case 2:
			booking.DeleteRecords();
			break;
		case 4:
			return 4;
		default:
			return 0;

		};
	}
}

