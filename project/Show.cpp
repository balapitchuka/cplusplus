
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include "ClassDeclaration.h"
#include <time.h>
#include <ctime>
#include <sstream>

using namespace std;

int m_nMaxShowCapacity, m_MaxHall, m_MaxMovie;

Shows::Shows()
{
}

void Shows::AddRecord(int showId, int hallId, int movieId, const char *date, int slot)
{
	int pos = m_nMaxShowCapacity;
	showList[pos].showId = showId;
	showList[pos].hallId = hallId;
	showList[pos].movieId = movieId;
	strcpy(showList[pos].showdate, date);
	showList[pos].slot = slot;

	m_nMaxShowCapacity++;
	WriteRecords();
}

void Shows::DeleteRecord(int pos)
{
	m_nMaxShowCapacity--;
	for (int i = pos; i < m_nMaxShowCapacity; i++)
	{
		showList[i] = showList[i + 1];
	}

	WriteRecords();
}

int Shows::HallReadRecords()
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

	m_MaxHall = nTotalRecordsRead;

	return nTotalRecordsRead;
}


int Shows::MovieReadRecords()
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

	m_MaxMovie = nTotalRecordsRead;

	return nTotalRecordsRead;
}

int Shows::ReadRecords()
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

	m_nMaxShowCapacity = nTotalRecordsRead;

	return nTotalRecordsRead;
}

int Shows::WriteRecords()
{
	FILE *ostream = fopen("Shows.bin", "wb");

	if (ostream == 0)
		return 0;

	int nTotalRecordsWritten = 0;
	char buf[4096];

	for (int i = 0; i < m_nMaxShowCapacity; i++)
	{
		fwrite((char*)&showList[i], 1, sizeof(Show), ostream);
		nTotalRecordsWritten++;
	}

	fclose(ostream);

	return nTotalRecordsWritten;
}

Shows show;

int Shows::DisplayMainMenu()
{
	//::system("cls");
	cout << "Show Menu" << endl;
	cout << "________________________________________________" << endl;

	cout << "5.  Add a show" << endl;
	cout << "6.  Delete a show" << endl;
	cout << "7.  List all shows" << endl;
	cout << "8.  Back" << endl;
	cout << "___________________________________________" << endl;

	cout << "Enter your Selection: " << endl;
	int m = -1;
	cin >> m;

	return m;
}

void Shows::ViewRecords()
{
	show.ReadRecords();
	//::system("cls");
	cout << "List all Show Details" << endl;
	cout << "_______________________________________________________________________________" << endl;
	cout << "Show Id " << "Movie Name " << "Hall Name  " << "Show Date\t" << "\tSlot" << endl;
	cout << "_______________________________________________________________________________" << endl;

	for (int i = 0; i < m_nMaxShowCapacity; i++)
	{
		cout << endl;
		cout << show.showList[i].showId;
		
		show.MovieReadRecords();
		for (int j = 0; j < m_MaxMovie; j++)
		{
			if (show.movieList[j].movieId == show.showList[i].movieId)
			{
				cout << "\t" << show.movieList[j].name;
				break;
			}
		}
		
		show.HallReadRecords();
		for (int j = 0; j < m_MaxHall; j++)
		{
			if (show.hallList[j].hallId == show.showList[i].hallId)
			{
				cout << "\t\t" << show.hallList[j].name;
				break;
			}
		}
		cout << "\t" << show.showList[i].showdate << "\t";
		
		if (show.showList[i].slot == 1)
			cout << "10:30 AM" << endl;
		else if (show.showList[i].slot == 2)
			cout << "02:30 PM" << endl;
		else if (show.showList[i].slot == 3)
			cout << "05:30 PM" << endl;
		else if (show.showList[i].slot == 4)
			cout << "08:30 PM" << endl;

	}
	cout << "______________________________________________________________________________" << endl;

}


bool extractDate(const std::string& s, int& d, int& m, int& y){
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
		// the actual date would be:
		// m = norm->tm_mon + 1;
		// d = norm->tm_mday;
		// y = norm->tm_year;
		// e.g. 29/02/2013 would become 01/03/2013

		// validate (is the normalized date still the same?):
		return (norm->tm_mday == d    &&
			norm->tm_mon == m - 1 &&
			norm->tm_year == y - 1900);
	}
	return false;
}


void Shows::InputRecords()
{
	int movieid = 0, hallid = 0, showid = 0, slot = 0, hallfound = 0, moviefound = 0, found = 0;

	while (1)
	{
		show.HallReadRecords();

		

		cout << "Add Show" << endl;
		cout << "___________________________________________" << endl;

		cout << "Show ID: " << endl;
		cin >> showid;

		cout << "Hall ID: " << endl;
		cin >> hallid;

		for (int i = 0; i < m_MaxHall; i++)
		{
			int hid = show.hallList[i].hallId;
			if (hid == hallid)
			{
				hallfound = 1;
				moviefound = 0;
				cout << "Hall Name " << "\t" << show.hallList[i].name << endl;
				break;
			}
		}

		if (hallfound == 0)
		{
			cout << "Invalid Hall ID" << endl;
			moviefound = 0;
		}
		else
		{
			show.MovieReadRecords();

			cout << "Movie ID: " << endl;
			cin >> movieid;

			for (int i = 0; i < m_MaxMovie; i++)
			{
				int mid = show.movieList[i].movieId;
				if (mid == movieid)
				{
					moviefound = 1;
					hallfound = 0;
					cout << "Movie Name " << "\t" << show.movieList[i].name << endl;
					break;
				}
			}

			if (moviefound == 0)
			{
				hallfound = 0;
				cout << "Invalid Movie ID" << endl;
			}
			else
			{

				cout << "Available slots for the show are: " << endl;
				cout << "1. 10:30 AM" << endl;
				cout << "2.  2:30 PM" << endl;
				cout << "3.  5:30 PM" << endl;
				cout << "4.  8:30 PM" << endl;
				
				cout << "Slot No: " << endl;
				cin >> slot;

				if (slot <= 0 || slot >= 5)
					cout << "Invalid Slot" << endl;
				else
				{

					show.ReadRecords();
					for (int i = 0; i < m_nMaxShowCapacity; i++)
					{
						if (show.showList[i].showId == showid)
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
						cout << "Show Already exists" << endl;
					}
					else
					{
						found = 0;

						char showdate[30];

						cout << "Enter Show Date [ DD/MM/YYYY]" << endl;
						cin >> showdate;

						std::string s(showdate);
						int d, m, y;

						if (extractDate(s, d, m, y))
							show.AddRecord(showid, hallid, movieid, showdate, slot);
						else
							cout << "Date is Invalid" << endl;
					}
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

void Shows::DeleteRecords()
{

	show.ViewRecords();
	cout << "Enter the row id you want to delete: ";

	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxShowCapacity)
	{

		show.DeleteRecord(m - 1);
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

int Shows::ShowMain()
{

	show.ReadRecords();
	while (1)
	{
		int selection = show.DisplayMainMenu();
		switch (selection)
		{
		case 5:
			show.InputRecords();
			break;
		case 7:
		{
			show.ViewRecords();
			cout << "Press any key to return to Main Menu: ";
			getchar();
			getchar();
		}
		break;
		case 6:
			DeleteRecords();
			break;
		case 8:
			return 8;
		default:
			return 0;
		
	}
}
}

