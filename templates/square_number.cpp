#include<iostream>
using namespace std;

template <typename t>

t square(t x)
{
	return x*x;
}

int main()
{
	cout<<square<int>(5)<<" ";
	cout<<square<double>(20.34);
}
