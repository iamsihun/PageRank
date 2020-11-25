#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <typeinfo>


using namespace std;

 int main() {

      //////// WHY DOES THIS ONE SAY 'NO MATCHING FUNCTION FOR CALL TO 'strtok'"////////
    ///////////////////////////////////////////////////////////////////////////////////
/*
ifstream file("data/small_data.tsv");       //load data into 'file'
const char s[2] = "\t";                     //string stream for 'tab'
string line;                                //holds each data entry
char* token;                                //holds individual element of a data entry i.e. 'SOURCE_SUBREDDIT' or 'TARGET_SUBREDDIT'
while (getline(file, line)) {               //extract data entry into 'line'
     // Split line into tab-separated parts
    vector<string> parts;
    token = strtok(&line, s);
    
   
    
  }
return 0; 
*/

        ////// ONLINE EXAMPLE CODE WHERE 'strtok' IS DEFINED AND WORKS /////
        //////////////////////////////////////////////////////////////
   char str[80] = "This is - www.tutorialspoint.com - website";
   const char s[2] = "-"; 
   char *token;
   
   token = strtok(str, s);
   
  
   while( token != NULL ) {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
   }
   
   return(0); 

}