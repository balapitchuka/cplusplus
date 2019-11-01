#include<stdio.h>
#include<iostream>
using namespace std;

int main () {
   FILE *fp;
   char str[]= "This is tutorialspoint.com";
   char *s=str;
   cout<<sizeof(str);
   

   fp = fopen( "file.txt" , "w" );
   for(int i=0;i<4;i++)
   {
   
      fwrite(str , 1 , sizeof(str) , fp );
  }
   fclose(fp);
  
   return(0);
}
