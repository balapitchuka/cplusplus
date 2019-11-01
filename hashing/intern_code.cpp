#include<iostream>
using namespace std;

int main()
{
	string s;
	cin>>s;
	int n=s.length();
	int x=n-1,val;
	cin>>val;
	for(int i=0;i<n;i++)
    {
    	if((x-i)%val==0)
    	{
    		cout<<s[i]<<" ";
		}
		else
		{
			cout<<s[i];
		}
	}
}
