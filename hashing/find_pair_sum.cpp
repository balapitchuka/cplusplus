#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int n,a[n],x;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	cin>>x;
	sort(a,a+n);
	int i=0,j=n-1;
	while(i<j)
	{
		if(a[i]+a[j]==x)
		{
			cout<<a[i];
			cout<<" ";
			cout<<a[j]<<"\n";
			
		}
		else if(a[i]+a[j]<x)
		{
			i++;
		}
		else
		{
			j--;
		}
	}
}
