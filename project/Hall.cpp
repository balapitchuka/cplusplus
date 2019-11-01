#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include "ClassDeclaration.h"
#include <time.h>
#include <ctime>
#include <sstream>

using namespace std;

int m_nMaxHalls;

Halls::Halls()
{

}

void Halls::AddRecord(int hallid, const char *name)
{
	int pos = m_nMaxHalls;
	hallList[pos].hallId = hallid;
	strcpy(hallList[pos].name, name);
	m_nMaxHalls++;
	WriteRecords();
}

int Halls::EditRecord(int pos, const char *name)
{
	//Students code
	strcpy(hallList[pos].name,name);
	
	if(strlen(hallList[pos].name) > 0)
	    return 1;
	else 
	    return 0;
	
	WriteRecords();
}

void Halls::DeleteRecord(int pos)
{
	m_nMaxHalls--;
	for (int i = pos; i < m_nMaxHalls; i++)
	{
		hallList[i] = hallList[i + 1];
	}

	WriteRecords();
}

int Halls::ReadRecords()
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

	m_nMaxHalls = nTotalRecordsRead;

	return nTotalRecordsRead;
}



int Halls::WriteRecords()
{
	FILE *ostream = fopen("Halls.bin", "wb");

	if (ostream == 0)
		return 0;

	int nTotalRecordsWritten = 0;
	char buf[4096];

	for (int i = 0; i < m_nMaxHalls; i++)
	{
		fwrite((char*)&hallList[i], 1, sizeof(Hall), ostream);
		nTotalRecordsWritten++;
	}

	fclose(ostream);

	return nTotalRecordsWritten;
}

Halls halls;

int Halls::DisplayMainMenu()
{
	//::system("cls");
	cout << "Halls Menu" << endl;
	cout << "________________________________________________" << endl;

	cout << "1.  Add new hall data" << endl;
	cout << "2.  Search and modify the hall data" << endl;
	cout << "3.  Delete hall data" << endl;
	cout << "4.  List all halls" << endl;
	cout << "5.  Back" << endl;
	cout << "___________________________________________" << endl;

	cout << "Enter your Selection: " << endl;
	int m = -1;
	cin >> m;

	return m;
}

void Halls::ViewRecords()
{
	halls.ReadRecords();
	//::system("cls");
	cout << "List all Halls" << endl;
	cout << "___________________________________________" << endl;
	cout << "Id\t" << "Name\t\t\t" << endl;
	cout << "___________________________________________" << endl;

	for (int i = 0; i < m_nMaxHalls; i++)
	{
		cout << halls.hallList[i].hallId << "\t" << halls.hallList[i].name << "\t" << endl;

		cout << "___________________________________________" << endl;
	}
}

void Halls::InputRecords()
{
	while (1)
	{
		cout << "Add Halls" << endl;
		cout << "___________________________________________" << endl;
		int hallid, found = 0;
		char name[64];

		cout << "Hall ID: " << endl;
		cin >> hallid;
		cout << "Hall Name: " << endl;
		cin >> name;

		halls.ReadRecords();
		for (int i = 0; i < m_nMaxHalls; i++)
		{
			if (halls.hallList[i].hallId == hallid)
			{
				found = 1;
				break;
			}
			else if (strcmp(name, halls.hallList[i].name) == 0)
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
			cout << "Hall already exists" << endl;
		}
		else
		{
			found = 0;
			halls.AddRecord(hallid, name);
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


void Halls::EditRecords()
{
	halls.ViewRecords();
	cout << "Enter the row id you want to edit: ";
	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxHalls)
	{
		cout << "Edit Hall Details";
		cout << "___________________________________________"<<endl;
		char name[64];

		cout << "Hall Name: ";
		cin >> name;

		halls.EditRecord(m - 1, name);

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

void Halls::DeleteRecords()
{

	halls.ViewRecords();
	cout << "Enter the row id you want to delete: ";

	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxHalls)
	{

		halls.DeleteRecord(m - 1);
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

int Halls::HallMain()
{
    halls.AddRecord(21,"Gopalan");
    halls.AddRecord(22,"Inox");
    
	halls.ReadRecords();
	while (1)
	{
		int selection = halls.DisplayMainMenu();
		switch (selection)
		{
		case 1:
			halls.InputRecords();
			break;
		case 2:
			halls.EditRecords();
			break;
		case 4:
		{
			halls.ViewRecords();
			cout << "Press any key to return to Main Menu: ";
			getchar();
			getchar();
		}
		break;
		case 3:
			halls.DeleteRecords();
			break;
		case 5:
			return 5;
		default:
			return 0;

		};
	}
}

