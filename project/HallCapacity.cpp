#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include "ClassDeclaration.h"
#include <time.h>
#include <ctime>
#include <sstream>

using namespace std;

int m_nMaxHallCapacity, m_nMaxHallSeatTypes, m_MaxHallMovie, m_MaxHall_Hall;

HallCapacities::HallCapacities()
{
}

void HallCapacities::AddRecord(int hallid, int seattypeid, int seatcount)
{
	int pos = m_nMaxHallCapacity;
	hallCapacityList[pos].hId = hallid;
	hallCapacityList[pos].sId = seattypeid;
	hallCapacityList[pos].seatCount = seatcount;
	
	m_nMaxHallCapacity++;
	WriteRecords();
}

void HallCapacities::EditRecord(int pos, int seatcount)
{
	hallCapacityList[pos].seatCount = seatcount;

	WriteRecords();
}

void HallCapacities::DeleteRecord(int pos)
{
	m_nMaxHallCapacity--;
	for (int i = pos; i < m_nMaxHallCapacity; i++)
	{
		hallCapacityList[i] = hallCapacityList[i + 1];
	}

	WriteRecords();
}

int HallCapacities::HallReadRecords()
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

	m_MaxHall_Hall = nTotalRecordsRead;

	return nTotalRecordsRead;
}

int HallCapacities::SeatTypeReadRecords()
{
	FILE *istream = fopen("SeatTypes.bin", "rb");
	if (istream == 0)
		return 0;

    //students code
    
      char buf[4096];
	int nTotalRecordsRead = 0;

	for (int i = 0; i <m_nMaxHallSeatTypes ; i++)
	{
		if (feof(istream))
			break;
		int nBytesRead = fread(buf, 1, sizeof(SeatType), istream);

		if (nBytesRead < sizeof(SeatType))
			break;

		char *p = (char*)(&seatTypeList[i]);
		memcpy(p, buf, sizeof(seatType));
		nTotalRecordsRead++;
	}
	fclose(istream);

	m_MaxHall_Hall = nTotalRecordsRead;

	return nTotalRecordsRead;
	

}

int HallCapacities::ReadRecords()
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

	m_nMaxHallCapacity = nTotalRecordsRead;

	return nTotalRecordsRead;
}



int HallCapacities::WriteRecords()
{
	FILE *ostream = fopen("hallcapacity.bin", "wb");

	if (ostream == 0)
		return 0;

	int nTotalRecordsWritten = 0;
	char buf[4096];

	for (int i = 0; i < m_nMaxHallCapacity; i++)
	{
		fwrite((char*)&hallCapacityList[i], 1, sizeof(HallCapacity), ostream);
		nTotalRecordsWritten++;
	}

	fclose(ostream);

	return nTotalRecordsWritten;
}

HallCapacities hallcapacity;

int HallCapacities::DisplayMainMenu()
{
	//::system("cls");
	cout << "Movie Menu" << endl;
	cout << "________________________________________________" << endl;
	
	cout << "9.   Add new hall capacity" << endl;
	cout << "10.  Search and modify hall capacity" << endl;
	cout << "11.  Delete a hall capacity data" << endl;
	cout << "12.  List all hall capacity data" << endl;
	cout << "13.  Back" << endl;
	cout << "___________________________________________" << endl;

	cout << "Enter your Selection: " << endl;
	int m = -1;
	cin >> m;

	return m;
}

void HallCapacities::ViewRecords()
{
	hallcapacity.ReadRecords();
	//::system("cls");
	cout << "List all Hall Capcity Details" << endl;
	cout << "___________________________________________" << endl;
	cout << "Hall Id\t" << "Seat Type ID: \t\t" << "Seat Capacity "<< endl;
	cout << "___________________________________________" << endl;

			for (int i = 0; i < m_nMaxHallCapacity; i++)
			{
				hallcapacity.HallReadRecords();
				for (int j = 0; j < m_MaxHall_Hall; j++)
				{
					if (hallcapacity.hallList[j].hallId == hallcapacity.hallCapacityList[i].hId)
					{
						cout << hallcapacity.hallList[j].name << "\t";
						break;
					}
				}

				hallcapacity.SeatTypeReadRecords();
				for (int k = 0; k < m_nMaxHallSeatTypes; k++)
				{
					if (hallcapacity.seatTypeList[k].seatId == hallcapacity.hallCapacityList[i].sId)
					{
						cout << hallcapacity.seatTypeList[k].name << "\t\t";
						break;
					}
				}

				cout << hallcapacity.hallCapacityList[i].seatCount << endl;
		
				cout << "___________________________________________" << endl;
		
			}
		
}

void HallCapacities::InputRecords()
{
	int seattypeid, hallid, seatcount, hallfound = 0, seattypefound = 0, found = 0;

	while (1)
	{

		hallcapacity.HallReadRecords();

		cout << "Add Hall Capacity" << endl;
		cout << "___________________________________________" << endl;

		cout << "Hall ID: " << endl;
		cin >> hallid;

		for (int i = 0; i < m_MaxHall_Hall; i++)
		{
			int hid = hallcapacity.hallList[i].hallId;
			if (hid == hallid)
			{
				hallfound = 1;
				seattypefound = 0;
				cout << "Hall Name " << "\t" << hallcapacity.hallList[i].name << endl;
				break;
			}
		}

		if (hallfound == 0)
		{
			cout << "Invalid Hall ID" << endl;
			seattypefound = 0;
		}
		else
		{
			hallcapacity.SeatTypeReadRecords();

			cout << "Seat Type ID: " << endl;
			cin >> seattypeid;

			for (int i = 0; i < m_nMaxHallSeatTypes; i++)
			{
				int sid = hallcapacity.seatTypeList[i].seatId;
				if (sid == seattypeid)
				{
					seattypefound = 1;
					hallfound = 0;
					cout << "Seat Type Name " << "\t" << hallcapacity.seatTypeList[i].name << ", Fare " << hallcapacity.seatTypeList[i].fare << endl;
					break;
				}
			}

			if (seattypefound == 0)
			{
				hallfound = 0;
				cout << "Invalid Seat ID" << endl;
			}
			else
			{

				cout << "Seat Capacity: " << endl;
				cin >> seatcount;

				hallcapacity.ReadRecords();
				for (int i = 0; i < m_MaxHall_Hall; i++)
				{
					if (hallcapacity.hallCapacityList[i].hId == hallid && hallcapacity.hallCapacityList[i].sId == seattypeid)
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
					cout << "Hall Capacity Details already exists" << endl;
				}
				else
				{
					found = 0;
					hallcapacity.AddRecord(hallid, seattypeid, seatcount);
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


void HallCapacities::EditRecords()
{
	hallcapacity.ViewRecords();
	cout << "Enter the row id you want to edit: ";
	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxHallCapacity)
	{
		cout << "Edit Hall Cacpcity Details";
		cout << "___________________________________________"<<endl;
		
		int seatcount;

		cout << "Seat Capacity: " << endl;
		cin >> seatcount;

		hallcapacity.EditRecord(m - 1, seatcount);

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

void HallCapacities::DeleteRecords()
{

	hallcapacity.ViewRecords();
	cout << "Enter the row id you want to delete: ";

	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxHallCapacity)
	{

		hallcapacity.DeleteRecord(m - 1);
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

int HallCapacities::HallCapacityMain()
{
    
    hallcapacity.AddRecord(21,22,100);

	hallcapacity.ReadRecords();
	while (1)
	{
		int selection = hallcapacity.DisplayMainMenu();
		switch (selection)
		{
		case 9:
			hallcapacity.InputRecords();
			break;
		case 10:
			hallcapacity.EditRecords();
			break;
		case 12:
		{
			hallcapacity.ViewRecords();
			cout << "Press any key to return to Main Menu: ";
			getchar();
			getchar();
		}
		break;
		case 11:
			hallcapacity.DeleteRecords();
			break;
		case 13:
			return 13;
		default:
			return 0;

		};
	}
}

