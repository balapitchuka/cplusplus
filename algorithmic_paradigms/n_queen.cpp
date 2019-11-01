#include<iostream>
using namespace std;
#define n 5


void printsolution(int a[n][n])
{
	cout<<"Solution is:\n\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
         {
                 cout<<a[i][j]<<" "; 	
		}   
		cout<<"\n";
    
    }
}
 

int issafe(int a[n][n],int row,int col)
{
	for(int i=0;i<col;i++)
	{
		if(a[row][i])
		{
			return 0;
		}
	}
	for(int i=row ,j=col;i>=0 && j>=0;i--,j--)
	{
		if(a[i][j])
		{
			return 0;
		}
	}
	for(int i=row,j=col;i<n && j>=0;i++,j--)
	{
		if(a[i][j])
		{
			return 0;
		}
	}
	return 1;
	
}

int issolvable(int a[n][n],int col)
{
	if(col==n)
	{
		printsolution(a);
		return 1;
	}
	for(int i=0;i<n;i++)
	{
		if(issafe(a,i,col)==1)
		{
			a[i][col]=1;
			issolvable(a,col+1);
			a[i][col]=0;
		}
		
	}
	return false;
}

void solve()
{
	int a[n][n]={0};
	issolvable(a,0);	
}

int main()
{
	solve();
	return 0;
	
}
