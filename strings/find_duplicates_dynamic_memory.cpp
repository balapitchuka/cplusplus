#include<iostream>
#include<stdlib.h>
using namespace std;
#define len 256

int main()
{
	string s;
	getline(cin,s);
	int n=s.size();
	if(n==1)
	{
		cout<<"no duplicates\n";
		
	}
	else if(n>1)
	{
		int *temp=(int *)malloc(sizeof(int)*len);
		for(int i=0;i<len;i++)
		{
			temp[i]=0;
		}
		for(int i=0;i<n;i++)
		{
			temp[s[i]]++;
		
			
		}
		for(int i=0;i<len;i++)
		{
			if(temp[i]>1)
			{
				int x=i;
				
				cout<<(char)x<<" ";
			}
		}
		free(temp);
		
	}
	else
	{
		cout<<"empty string\n";
	}
	
}
