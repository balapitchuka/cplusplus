#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<deque>
using namespace std;

int main()
{

    vector<int> v;
	v.push_back(5);
	v.push_back(30);
	v.push_back(90);
	v.push_back(-2);
	for(int i=0;i<v.size();i++)
	{
		cout<<v[i]<<endl;
	}
	cout<<"----------------"<<endl;
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();i++)
	{
		cout<<v[i]<<endl;
	}
	
	
	
}
