#ifndef MAIN_HPP
#define MAIN_HPP

//****INCLUDES****//
#include<iostream>
#include<cstring>
#include<ctime>
#include<cstdlib>

//****CONSTANTS****//
#define NUM_KNIGHTS 12
#define loop for(int i=0; i<=NUM_KNIGHTS; i++)

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

//****CLASSES****//
class knight
{
	Typedef_knight k[NUM_KNIGHTS+1];			//the +1 denotes the King Arthur 
	int knights_with_complete_day;
	void initializeKnight(Typedef_knight *k);	//initialization function for a knight
	void calc_end_of_day(int knight_id);		//called after every 24 hours to calculate result
	void calc_bonus(); 							//called after result for all knights is calculated
	
	public:
		knight();
		void fix_pos(int knight_id, location loc);	//fix position of a knight
		void print_result(int knight_id);			
		void print_result();
		void random_placement(int no_of_days);

};

#endif
