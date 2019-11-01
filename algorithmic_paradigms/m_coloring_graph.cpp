#include<iostream>
using namespace std;

#define n 4

void printsolution(int color[n])
{
    printf("Solution Exists:"
            " Following are the assigned colors \n");
    for (int i = 0; i < n; i++)
    {
    	cout<<color[i]<<" ";
	 } 
}

int issafe(int a[n][n],int color[n],int v,int c)
{
	for(int i=0;i<n;i++)
	{
		if(a[v][i] && c==color[i])
		{
			return 0;
		}
	}
	return 1;
}

int issolvable(int a[n][n],int m,int color[n],int v)
{
	if(v==n)
	{
		return 1;
    }
    for(int i=1;i<=m;i++)
    {
    	if(issafe(a,color,v,i))
    	{
    		color[v]=i;
    		if(issolvable(a,m,color,v+1))
    		{
    			return 1;
			}
			color[v]=0;
		}
	}
}

void graph_colour(int a[n][n],int m)
{
	int *color=new int[n];
	for(int i=0;i<n;i++)
	{
		color[i]=0;
	}
	if(issolvable(a,m,color,0))
	{
		printsolution(color);
	}
	else
	{
		cout<<"no solution\n";
	}
	
}


int main()
{
	int m;
	cin>>m;
	int a[n][n]={{0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0},
    };
    graph_colour(a,m);
}
