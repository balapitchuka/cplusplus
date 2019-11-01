#include<iostream>
using namespace std;


class animal
{
	public:
	    animal()
	   {
	   	  cout<<"constructor in animal class\n";
	   }
};


class dog : public animal
{
	public:
		 dog()
		{
			cout<<"constructor in dog class\n";
		}
};


int main()
{
	dog d;
}
