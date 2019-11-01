#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<deque>
using namespace std;

int main()
{
	int a[]={6,33,-2,78,333,1};
	cout<<sizeof(a)<<endl;
	int n=sizeof(a)/sizeof(a[0]);
	sort(a,a+n);
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<endl;
	}
	vector<int> v;
	v.push_back(5);
	for(int i=0;i<v.size();i++)
	{
		cout<<v[i];
	}
	
	
	
}
