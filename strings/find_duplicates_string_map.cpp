//How to Find Duplicate Characters on String using map

#include<iostream>
#include<map>
using namespace std;

int main()
{
	
	string s;
	cin>>s;
	int n=s.size();
	map<char,int> a;
	for(int i=0;i<n;i++)
    {
    	if(a.find(s[i])!=a.end())
    	{
    		a[s[i]]++;
    		
		}
		else
		{
			a.insert(make_pair(s[i],1));
		}
	}
	map<char,int> :: iterator itr;
	for(itr=a.begin();itr!=a.end();itr++)
	{
		if(itr->second>1)
		{
			cout<<itr->first<<" ";
		}
	}
	
}
