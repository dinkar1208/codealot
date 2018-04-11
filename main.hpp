#ifndef MAIN_HPP
#define MAIN_HPP

//****INCLUDES****//
#include<iostream>
#include<cstring>
#include<ctime>
#include<cstdlib>

//****CONSTANTS****//
#define NUM_KNIGHTS 12
#define loop for(int i=0; i<NUM_KNIGHTS; i++)

//****ENUMERATED DATA TYPES****//
enum location {	TAVERN,
				TRAINING,
				ROUND_TABLE};

//****TYPEDEFS****//
typedef struct 
{
	location log[24]; //used like a stack
	int hours;
	int stam;
	int xp;
	int old_stam;
	int old_xp;
}Typedef_knight;

#endif
