#include<iostream>                      //  DEPTH FIRST TRAVERSAL OF A undirected graph
using namespace std;



void DFS(int i,int n,int **arr,int visited[])
{
	int j;
	
	cout<<i<<" ";
	
	visited[i]=1;
	for(j=0;j<n;j++)
	{
		if(!visited[j] && arr[i][j]==1)
		{
			DFS(j,n,arr,visited);
		}
	}
}

int main()
{
	int i,j,n,m;
	cin>>n;
	int **arr=new int*[n];
	for(i=0;i<n;i++)
	{
		arr[i]=new int[n];
	}
	 
	
	 for(i=0;i<n;i++)
	 {
	 	for(j=0;j<n;j++)
	 	{
	 		cin>>arr[i][j];
	 		
		 }
	 }
	 
	 int *visited=new int[n];
	 for( i=0;i<n;i++)
    {
    	visited[i]=0;
	}
	 DFS(0,n,arr,visited);
	 return 0;
}
