#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int coinchange(int a[],int n,int m)
{
	int dp[m+1];
	memset(dp,0,sizeof(dp));
	dp[0]=1;
	
	for(int i=0;i<n;i++)
	{
		for(int j=a[i];j<=m;j++)
		{
			
			
			  dp[j]+=dp[j-a[i]];
		    
	   }
	}
	return dp[m];
}


int main()
{
	//Coin change problem
	int a[]={2, 5, 3, 6};
	int n=sizeof(a)/sizeof(a[0]);
	cout<<"Df";
	cout<<coinchange(a,n,10);
}
