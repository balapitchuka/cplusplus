#include "Header.h"

#define MaxSz 100

class Users
{
public:
	User m_userList[MaxSz];

	Users();

	void AddRecord(int userid, const char *name, const char *type, const char *emailid, const char *mobileno);
	void EditRecord(int pos, const char *emailid, const char *mobileno);
	void DeleteRecord(int pos);
	int ReadRecords();
	int WriteRecords();
	int DisplayMainMenu();
	void ViewRecords();
	void InputRecords();
	void EditRecords();
	void DeleteRecords();
	int UserMain();
	int inputLogin();
	int checkLogin(const char *username,const char *password);
};

class Halls
{
public:
	Hall hallList[MaxSz];

	Halls();

	void AddRecord(int hallid, const char *name);
	int EditRecord(int pos, const char *name);
	void DeleteRecord(int pos);
	int ReadRecords();
	int WriteRecords();
	int DisplayMainMenu();
	void ViewRecords();
	void InputRecords();
	void EditRecords();
	void DeleteRecords();
	int HallMain();
};


class Movies
{
public:
	Movie movieList[MaxSz];

	Movies();

	void AddRecord(int movieid, const char *name);
	void EditRecord(int pos, const char *name);
	void DeleteRecord(int pos);
	int ReadRecords();
	int WriteRecords();
	int DisplayMainMenu();
	void ViewRecords();
	void InputRecords();
	void EditRecords();
	void DeleteRecords();
	int MovieMain();

};


class HallCapacities
{
public:
	HallCapacity hallCapacityList[MaxSz];
	Hall hallList[MaxSz];
	SeatType seatTypeList[MaxSz];

	HallCapacities();

	void AddRecord(int hallid, int seattypeid, int seatcount);
	void EditRecord(int pos, int seatcount);
	void DeleteRecord(int pos);
	int ReadRecords();
	int HallReadRecords();
	int SeatTypeReadRecords();
	int MovieReadRecords();
	int WriteRecords();
	int DisplayMainMenu();
	void ViewRecords();
	void InputRecords();
	void EditRecords();
	void DeleteRecords();
	int HallCapacityMain();

};


class Shows
{
public:
	Show showList[MaxSz];
	Hall hallList[MaxSz];
	SeatType seatTypeList[MaxSz];
	Movie movieList[MaxSz];

	Shows();

	void AddRecord(int showId, int hallId, int movieId, const char *date, int slot);
	void DeleteRecord(int pos);
	int ReadRecords();
	int HallReadRecords();
	int MovieReadRecords();
	int WriteRecords();
	int DisplayMainMenu();
	void ViewRecords();
	void InputRecords();
	void EditRecords();
	void DeleteRecords();
	int ShowMain();

};

class Bookings
{
public:
	Show showList[MaxSz];
	MovieBook bookingList[MaxSz];
	SeatType seatTypeList[MaxSz];
	HallCapacity hallCapacityList[MaxSz];
	User userList[MaxSz];
	Hall hallList[MaxSz];
	Movie movieList[MaxSz];

	Bookings();

	void AddRecord(int bookingid, int showId, int userId, const char *bookingDate, const char *showDate, int seattypeid, int noofseats);
	int DeleteRecord(int pos);
	bool extractBookingDate(const std::string& s, int& d, int& m, int& y);
	int ReadRecords();
	int ShowReadRecords();
	int UserReadRecords();
	int WriteRecords();
	int HallReadRecords();
	int MovieReadRecords();
	int SeatTypeReadRecords();
	int HallCapacityReadRecords();
	int DisplayMainMenu();
	void ViewRecords();
	void InputRecords();
	void EditRecords();
	void DeleteRecords();
	int BookingMain();

};

class SeatTypes
{
public:
	SeatType seatTypeList[MaxSz];

	SeatTypes();

	void AddRecord(int seatid, const char *name, int fare);
	void EditRecord(int pos, double fare);
	void DeleteRecord(int pos);
	int ReadRecords();
	int WriteRecords();
	int DisplayMainMenu();
	void ViewRecords();
	void InputRecords();
	void EditRecords();
	void DeleteRecords();
	int SeatTypeMain();

};


