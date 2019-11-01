#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include "ClassDeclaration.h"
#include <time.h>
#include <ctime>
#include <sstream>

using namespace std;

int m_nMaxMovies;

Movies::Movies()
{

}

void Movies::AddRecord(int movieid, const char *name)
{
	int pos = m_nMaxMovies;
	movieList[pos].movieId = movieid;
	strcpy(movieList[pos].name, name);
	m_nMaxMovies++;
	WriteRecords();
}

void Movies::EditRecord(int pos, const char *name)
{
	strcpy(movieList[pos].name, name);
	WriteRecords();
}

void Movies::DeleteRecord(int pos)
{
	m_nMaxMovies--;
	for (int i = pos; i < m_nMaxMovies; i++)
	{
		movieList[i] = movieList[i + 1];
	}

	WriteRecords();
}



int Movies::ReadRecords()
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

	m_nMaxMovies = nTotalRecordsRead;

	return nTotalRecordsRead;
}


int Movies::WriteRecords()
{
	FILE *ostream = fopen("movies.bin", "wb");

	if (ostream == 0)
		return 0;

	int nTotalRecordsWritten = 0;
	char buf[4096];

	for (int i = 0; i < m_nMaxMovies; i++)
	{
		fwrite((char*)&movieList[i], 1, sizeof(Movie), ostream);
		nTotalRecordsWritten++;
	}

	fclose(ostream);

    return nTotalRecordsWritten;
}

Movies movies;

int Movies::DisplayMainMenu()
{
	//::system("cls");
	cout << "Movie Menu" << endl;
	cout << "________________________________________________" << endl;

	cout << "1.  Add new movie data" << endl;
	cout << "2.  Search and modify the movie data" << endl;
	cout << "3.  Delete movie data" << endl;
	cout << "4.  List all movies" << endl;
	cout << "5.  Back" << endl;
	cout << "___________________________________________" << endl;

	cout << "Enter your Selection: " << endl;
	int m = -1;
	cin >> m;

	return m;
}

void Movies::ViewRecords()
{
    
    movies.ReadRecords();
	cout << "List all Movies" << endl;
	cout << "___________________________________________" << endl;
	cout << "Id\t" << "Name\t\t\t" << endl;
	cout << "___________________________________________" << endl;

  	for (int i = 0; i < m_nMaxMovies; i++)
	{
		cout << movies.movieList[i].movieId << "\t" << movies.movieList[i].name << endl;

		cout << "___________________________________________" << endl;

	}

}

void Movies::InputRecords()
{
	while (1)
	{
		cout << "Add Movies" << endl;
		cout << "___________________________________________" << endl;
		int movieid,found =0;
		char name[64];

		cout << "Movie ID: " << endl;
		cin >> movieid;
		cout << "Name: " << endl;
		cin >> name;

		movies.ReadRecords();
		for (int i = 0; i < m_nMaxMovies; i++)
		{
			if (movies.movieList[i].movieId == movieid)
			{
				found = 1;
				break;
			}
			else if (strcmp(name, movies.movieList[i].name) == 0)
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
			cout << "Movie already exists" << endl;
		}
		else
		{
			found = 0;
			movies.AddRecord(movieid, name);
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


void Movies::EditRecords()
{
	movies.ViewRecords();
	cout << "Enter the row id you want to edit: ";
	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxMovies)
	{
		cout << "Edit Seat Type Details";
		cout << "___________________________________________"<<endl;
		char name[64];

		cout << "Name: ";
		cin >> name;

		movies.EditRecord(m - 1, name);

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

void Movies::DeleteRecords()
{

	movies.ViewRecords();
	cout << "Enter the row id you want to delete: ";

	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxMovies)
	{

		movies.DeleteRecord(m - 1);
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

int Movies::MovieMain()
{
    movies.AddRecord(21,"AirLift");
    movies.AddRecord(22,"Titanic");

	movies.ReadRecords();
	while (1)
	{
		int selection = movies.DisplayMainMenu();
		switch (selection)
		{
		case 1:
			movies.InputRecords();
			break;
		case 2:
			movies.EditRecords();
			break;
		case 4:
		
			movies.ViewRecords();
			cout << "Press any key to return to Main Menu: ";
			getchar();
			getchar();
		
		break;
		case 3:
			movies.DeleteRecords();
			break;
		case 5:
			return 5;
		default:
			return 0;

		}
	}
}

