
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include "ClassDeclaration.h"
#include <time.h>
#include <ctime>
#include <sstream>

using namespace std;

int m_nMaxSeatTypes;

SeatTypes::SeatTypes()
{

}

void SeatTypes::AddRecord(int seatid, const char *name,int fare)
{
	int pos = m_nMaxSeatTypes;
    seatTypeList[pos].seatId=seatid;
    seatTypeList[pos].fare=fare;
    strcpy(seatTypeList[pos].name,name);
    //Student Code
    

	m_nMaxSeatTypes++;
	WriteRecords();
}

void SeatTypes::EditRecord(int pos, double fare)

{
	seatTypeList[pos].fare = fare;
	WriteRecords();
}

void SeatTypes::DeleteRecord(int pos)
{
	m_nMaxSeatTypes--;
	for (int i = pos; i < m_nMaxSeatTypes; i++)
	{
		seatTypeList[i] = seatTypeList[i + 1];
	}

	WriteRecords();
}



int SeatTypes::ReadRecords()
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

	m_nMaxSeatTypes = nTotalRecordsRead;

	return nTotalRecordsRead;
}



int SeatTypes::WriteRecords()
{
	FILE *ostream = fopen("SeatTypes.bin", "wb");

	if (ostream == 0)
		return 0;

    //Student Code
    int nTotalRecordsWritten = 0;
	

	for (int i = 0; i < m_nMaxSeatTypes; i++)
	{
		fwrite((char*)&seatTypeList[i], 1, sizeof(SeatType), ostream);
		nTotalRecordsWritten++;
	}

	fclose(ostream);

	return nTotalRecordsWritten;
    

    
}

SeatTypes seatTypes;

int SeatTypes::DisplayMainMenu()
{
	//::system("cls");
	cout << "Seat Types Menu" << endl;
	cout << "________________________________________________" << endl;

	cout << "6.   Add new seat type" << endl;
	cout << "7.   Search and modify seat type" << endl;
	cout << "8.   Delete a seat type" << endl;
	cout << "9.   List all seat types" << endl;
	cout << "10.  Back" << endl;
	cout << "___________________________________________" << endl;

	cout << "Enter your Selection: " << endl;
	int m = -1;
	cin >> m;

	return m;
}

void SeatTypes::ViewRecords()
{
	seatTypes.ReadRecords();
	//::system("cls");
	cout << "List all Seat Types" << endl;
	cout << "___________________________________________" << endl;
	cout << "Id\t" << "Name\t\t\t" << "Fare\t" << endl;
	cout << "___________________________________________" << endl;

	
	for (int i = 0; i < m_nMaxSeatTypes; i++)
	{
		cout << endl;
		cout << seatTypes.seatTypeList[i].seatId << "\t" << seatTypes.seatTypeList[i].name << "\t\t" << seatTypes.seatTypeList[i].fare << endl;

		cout << "___________________________________________" << endl;

	}

	
}

void SeatTypes::InputRecords()
{
	while (1)
	{

 		cout << "Add Seat Type" << endl;
		cout << "___________________________________________" << endl;
		int seatid,found =0,fare;
		char name[64];
		
		cout << "Seat Type ID: " << endl;
		cin >> seatid;
		cout << "Name: " << endl;
		cin >> name;
		cout << "Fare: " << endl;
		cin >> fare;

		seatTypes.ReadRecords();
		for (int i = 0; i < m_nMaxSeatTypes; i++)
		{
			if (seatTypes.seatTypeList[i].seatId == seatid)
			{
				found = 1;
				break;
			}
			else if (strcmp(name, seatTypes.seatTypeList[i].name) == 0)
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
			cout << "Seat Tpye already exists" << endl;
		}
		else
		{
			found = 0;
			seatTypes.AddRecord(seatid, name, fare);
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


void SeatTypes::EditRecords()
{
	seatTypes.ViewRecords();
	cout << "Enter the row id you want to edit: ";
	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxSeatTypes)
	{
		cout << "Edit Seat Type Details";
		cout << "___________________________________________"<<endl;
		double fare;

		cout << "Seat Fare: ";
		cin >> fare;

		seatTypes.EditRecord(m - 1, fare);

		cout << "Record updated" << endl;
		cout << "Press any key to return to Main Menu" << endl;
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

void SeatTypes::DeleteRecords()
{

	seatTypes.ViewRecords();
	cout << "Enter the row id you want to delete: ";

	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxSeatTypes)
	{

		seatTypes.DeleteRecord(m - 1);
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

int SeatTypes::SeatTypeMain()
{
    seatTypes.AddRecord(21,"First",500);
    seatTypes.AddRecord(22,"Executive",800);

	seatTypes.ReadRecords();
	while (1)
	{
		int selection = seatTypes.DisplayMainMenu();
		switch (selection)
		{
		case 6:
			seatTypes.InputRecords();
			break;
		case 7:
			seatTypes.EditRecords();
			break;
		case 9:
		{
			seatTypes.ViewRecords();
			cout << "Press any key to return to Main Menu: ";
			getchar();
			getchar();
		}
		break;
		case 8:
			seatTypes.DeleteRecords();
			break;
		case 10:
			return 10;
		default:
			return 0;

		};
	}
}

