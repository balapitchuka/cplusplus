#include<iostream>
#include<map>
#include<string>
using namespace std;


int main()
{
	map<string,int> m ;
	map<string,int>::iterator it;
	cout<<"Size is : " <<m.size()<<endl;
	cout<<"Capacity is : "<<m.max_size()<<endl;
	m.insert(pair <string,int> ("Hello",23));
	for(it=m.begin();it!=m.end();it++)
    {
        cout<<it->first<<"  "<<it->second<<endl;	
	}	
	cout<<"Size is : " <<m.size()<<endl;
	m.insert(pair<string,int> ("World",12));
	m.insert(pair<string,int> ("Rediconolny",90));
	m.insert(pair<string,int> ("Bluecross",67));m.insert(pair<string,int> ("Chaining",390));
	cout<<"Capacity is : "<<m.size()<<endl;
	for(it=m.begin();it!=m.end();it++)
    {
        cout<<it->first<<"  "<<it->second<<endl;	
	}
	bool val=m.empty();	
	cout<<val<<endl;
	it=m.find("Bluecross");
	if(it!=m.end())
	{
	
	    cout<<it->first<<"  "<<it->second<<endl;
   }
   map<string,int> l(m.begin(),m.end());
   m.clear();
   cout<<"Size is : " <<m.size()<<endl;
   for(it=l.begin();it!=l.end();it++)
    {
        cout<<it->first<<"  "<<it->second<<endl;	
	}	
   	l.insert(pair<string,int> ("World",12));
   	cout<<"Size is : " <<l.size()<<endl;
   	l.insert(pair<string,int> ("World",56));
   	cout<<"Size is : " <<l.size()<<endl;
   	for(it=l.begin();it!=l.end();it++)
    {
        cout<<it->first<<"  "<<it->second<<endl;	
	}	
}
