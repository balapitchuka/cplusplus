#include<iostream>
using namespace std;



void swap(char *x,char *y )
{
	char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void backtrack(string s,int start,int n )
{
	if(start==n)
	{
		cout<<s<<"   ";
	}
	for(int i=start;i<=n;i++)
	{
		swap(s[start],s[i]);
		backtrack(s,start+1,n);
		swap(s[start],s[i]);
		
		
		
	}
}





int main()
{
	string s;
	cin>>s;
	backtrack(s,0,s.length()-1);
	return 0;
}





