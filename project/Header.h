using namespace std;

struct Hall
{
public:
	int hallId;
	char name[200];
};

struct User
{
public:
	int userId;
	char userName[64];
	char userType[64];
	char mobileNumber[10];
	char emailId[64];
};

struct MovieBook
{
	int bookingId;
	int showId;
	int userId;
	char bookingDate[80];
	char showDate[80];
	int seattypeid;
	int noofseats;
};

struct Show
{
public:
	int showId;
	int hallId;
	int movieId;
	int slot;
	char showdate[80];
};

struct SeatType
{
public:
	int seatId;
	char name[200];
	int fare;
};

struct HallCapacity
{	
public:
	int hId;
	int sId;
	int seatCount;
};

struct Movie
{
public:
	int movieId;
	char name[200];
};



