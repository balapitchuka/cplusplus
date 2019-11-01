#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <string>
#include "ClassDeclaration.h"
#include <time.h>
#include <ctime>
#include <sstream>

using namespace std;

int m_nMaxUsers;

Users::Users()
{

}

void Users::AddRecord(int userid, const char *name, const char *type, const char *emailid, const char *mobileno)
{
	int pos = m_nMaxUsers;
	m_userList[pos].userId = userid;
	strcpy(m_userList[pos].userName, name);
	strcpy(m_userList[pos].userType, type);
	strcpy(m_userList[pos].emailId, emailid);
	strcpy(m_userList[pos].mobileNumber, mobileno);
	m_nMaxUsers++;
	WriteRecords();
}

void Users::EditRecord(int pos,const char *emailid, const char *mobileno)
{
	strcpy(m_userList[pos].emailId, emailid);
	strcpy(m_userList[pos].mobileNumber, mobileno);
	WriteRecords();
}

void Users::DeleteRecord(int pos)
{
	m_nMaxUsers--;
	for (int i = pos; i < m_nMaxUsers; i++)
	{
		m_userList[i] = m_userList[i + 1];
	}

	WriteRecords();
}

int Users::ReadRecords()
{
	FILE *istream = fopen("users.bin", "rb+");
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

		char *p = (char*)(&m_userList[i]);
		memcpy(p, buf, sizeof(User));
		nTotalRecordsRead++;
	}
	fclose(istream);

	m_nMaxUsers = nTotalRecordsRead;

	return nTotalRecordsRead;
}

int Users::WriteRecords()
{
	FILE *ostream = fopen("users.bin", "w+");

	if (ostream == 0)
		return 0;

	int nTotalRecordsWritten = 0;
	

	for (int i = 0; i < m_nMaxUsers; i++)
	{
		fwrite((char*)&m_userList[i], 1, sizeof(User), ostream);
		nTotalRecordsWritten++;
	}

	fclose(ostream);

	return nTotalRecordsWritten;
}

Users users;

int Users::DisplayMainMenu()
{
	cout << "Users Menu" << endl;
	cout << "________________________________________________" << endl;
	cout << "1.  Add new user data" << endl;
	cout << "2.  Search and modify the user data" << endl;
	cout << "3.  Delete user data" << endl;
	cout << "4.  List all users" << endl;
	cout << "5.  Back" << endl;
    cout << "___________________________________________" << endl;

	cout << "Enter your Selection: " << endl;
	int m = -1;
	cin >> m;

	return m;
}

void Users::ViewRecords()
{
	users.ReadRecords();
	//::system("cls");
	cout << "List all Users" << endl;
	cout << "___________________________________________" << endl;
	cout << "Id\t"<< "Name\t"<<"Type\t"<<"Email Id\t"<<"Mobile No\t" << endl;
	cout << "___________________________________________" << endl;

	for (int i = 0; i < m_nMaxUsers; i++)
	{
		cout << users.m_userList[i].userId <<"\t" << users.m_userList[i].userName << "\t" <<
			users.m_userList[i].userType << "\t" << users.m_userList[i].emailId << "\t" <<
				users.m_userList[i].mobileNumber << endl;

		cout << "___________________________________________" << endl;

	}

}

void Users::InputRecords()
{
	while (1)
	{
		cout << "Add Users" << endl;
		cout << "___________________________________________" << endl;
		int userid,found = 0;
		char name[64], type[64], emailid[64],mobileno[64];

		cout << "User ID: " << endl;
		cin >> userid;
		cout << "User Name: " << endl;
		cin >> name;
		cout << "User Type: [Hint: Admin/User]" << endl;
		cin >> type;
		cout << "Email ID: " << endl;
		cin >> emailid;
		cout << "Mobile Number: " << endl;
		cin >> mobileno;

		users.ReadRecords();
		for (int i = 0; i < m_nMaxUsers; i++)
		{
			if (userid == users.m_userList[i].userId)
			{
				found = 1;
				break;
			}
			else if (strcmp(name, users.m_userList[i].userName) == 0)
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
			cout << "User already exists" << endl;
		}
		else
		{
			found = 0;
			users.AddRecord(userid, name, type, emailid, mobileno);
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


void Users::EditRecords()
{
	users.ViewRecords();
	cout << "Enter the row id you want to edit: ";
	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxUsers)
	{
		cout << "Edit User Details";
		cout << "___________________________________________"<<endl;
		char emailid[64],mobileno[64];

		cout << "Email ID: ";
		cin >> emailid;
		cout << "Mobile Number: ";
		cin >> mobileno;

		users.EditRecord(m - 1, emailid, mobileno);

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

void Users::DeleteRecords()
{

	users.ViewRecords();
	cout << "Enter the row id you want to delete: ";

	int m;
	cin >> m;

	if (m >= 1 && m <= m_nMaxUsers)
	{

		users.DeleteRecord(m - 1);
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

int Users::UserMain()
{
	users.ReadRecords();
	while (1)
	{
		int selection = users.DisplayMainMenu();
		switch (selection)
		{
		case 1:
			users.InputRecords();
			break;
		case 2:
			users.EditRecords();
			break;
		case 4:
		{
			users.ViewRecords();
			cout << "Press any key to return to Main Menu: ";
			getchar();
			getchar();
		}
		break;
		case 3:
			users.DeleteRecords();
			break;
		case 5:
			return 5;
		default:
			return 0;
		};
	}

}

int Users::inputLogin()
{
    users.AddRecord(21, "suresh","admin","suresh", "9886244711");
    users.AddRecord(22, "janakiram", "admin", "janakiram", "123456789");

    cout << "Login" << endl;
	cout << "________________________________________________" << endl;

	int found = 0;
	char username[50], password[50];

	cout << "User Name: " << endl;
	cin >> username;

	cout << "Password: " << endl;
	cin >> password;

    return checkLogin(username,password);
}


int Users::checkLogin(const char *username,const char *password)
{
    int found = 0;
	//::system("cls");
	
	users.ReadRecords();
	//::system("cls");

	if (strcmp(username, "manipal") == 0 && strcmp(password, "manipal") == 0)
	{
		found = 1;
	}
	else
	{

        //Students code
        FILE *istream = fopen("users.bin", "rb+");
        
        
        
	}

	if (found == 1)
	{
		found = 0;
		cout << "Login Sucuessfull" << endl;
		getchar();
		getchar();
		return 1;
	}
	else
	{
		found = 0;
		cout << "Login Information Invalid" << endl;
		getchar();
		getchar();
		return 0;
	}
}


