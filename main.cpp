//****Includes****//
#include "main.hpp"

using namespace std;

//****Functions Definitions****//

/**
	Default constructor for class knight to initialize variables to 0
	@param None
	@return None
*/
knight::knight()
{
		knights_with_complete_day=0;
		loop
		{
				initializeKnight(&k[i]);
		}
}

/**
	Initializing the knight parameters to zero
	@param Pointer to Typedef_knight data
	@return None
*/
void knight::initializeKnight(Typedef_knight *k) 
{
	k->hours 	=0;
	k->stam		=0;
	k->xp		=0;
	k->old_xp	=0;
	k->old_stam=0;
}

/**
	Alots the knight i with definied location for the hour
	@Note Called by the random_placement function or explicitly
	@param id number od the knight
	@param location of placement for the particular knight
	@return None
	@Example
		knight::fix_pos(1, ROUND_TABLE) fixes the location of knight 1
*/
void knight::fix_pos(int knight_id, location loc)
{
	k[knight_id].log[ (k[knight_id].hours) ] = loc;
	k[knight_id].hours ++;	
	if(k[knight_id].hours == 24) calc_end_of_day(knight_id);
}

/**
	Called internally to calculate XP and STAMINA for a knight
	@param id number of the knight
	@return None
*/
void knight::calc_end_of_day(int knight_id)
{
	location loc;
	int round_table_counter;					//counter for round table visits
	round_table_counter = 0;
	knights_with_complete_day++;
	//cout<<knights_with_complete_day;			//for debugging
	
	bool no_xp_day;								//no stamina training detector
	no_xp_day = false;
	
	for(int i=0; i<24; i++)
	{
		loc = k[knight_id].log[i];
		if(loc == ROUND_TABLE) round_table_counter++;
		if(loc == TAVERN) k[knight_id].stam++;
		else if((loc == TRAINING)){
			k[knight_id].stam--;
			if(k[knight_id].stam < 0)  			// strict check to make +XP=0 incase stamina falls below 0
			{									// which triggers when stam = 0 and stam-- makes it < 0
				no_xp_day = true;
			}
			if((k[knight_id].stam >= 0))	k[knight_id].xp++;
		}
	}
	if(round_table_counter < 3) no_xp_day = true;			//check for round table visits
		
	if(no_xp_day) k[knight_id].xp = k[knight_id].old_xp;	//stamina keeps draining but +XP=0 in the end
	k[knight_id].hours = 0;
	if(knights_with_complete_day == NUM_KNIGHTS) calc_bonus();
}

/**
	Calculates bonus for all the knights combined at the end of the day
	@param None
	@return None
*/
void knight::calc_bonus()
{
	//		New bonus system definition
	//+Calculate the min and max XP earned by all the knights
	//+Find the median and reward all knights above median with +5XP
	//+Find the upper quartile and reward all knights above median with +10XP
	//
	int min=INT_MAX, max=INT_MIN;
	loop
	{
		if((k[i].xp - k[i].old_xp) > max) max = (k[i].xp - k[i].old_xp);
		if((k[i].xp - k[i].old_xp) < min) min = (k[i].xp - k[i].old_xp);
	}
	int median 	= (int)(max-min)/2    + min;
	int quar	= (int)(max-median)/2 + median;
	loop
	{
		if((k[i].xp - k[i].old_xp) > median)
		{
			if((k[i].xp - k[i].old_xp) > quar)
			{
				k[i].xp+=5;
			}
			k[i].xp+=5;
		}	
	}	
	
	/*				ORIGINAL BONUS SYSTEM
	int knights_with_greater_than_three_xp = 0;
	loop if((k[i].xp - k[i].old_xp) >=3) knights_with_greater_than_three_xp ++;
	switch(knights_with_greater_than_three_xp)
	{
		case 3:
			loop if((k[i].xp - k[i].old_xp) >=3) k[i].xp+=5;
			break;
		case 5:
			loop if((k[i].xp - k[i].old_xp) >=3) k[i].xp+=10;
			break;
		case 6:
			loop if((k[i].xp - k[i].old_xp) >=3) k[i].xp+=20;
			break;			
	}
	*/
	loop k[i].old_stam	= k[i].stam;
	loop k[i].old_xp	= k[i].xp;
	knights_with_complete_day=0;
}

/**
	Print result for a particular knight
	@param id number of the knight
	@return None
	Example:
		print_result(2) will print XP and Stamina for knight 2
*/
void knight::print_result(int knight_id)
{
	if(knight_id < NUM_KNIGHTS) 
	{
		cout<<"\nKnight "<<knight_id<<endl;
		cout<<"Stamina : "<<k[knight_id].stam<<endl;
		cout<<"XP      : "<<k[knight_id].xp<<endl;
	}
	else
	{
		cout<<"\nKing Arthur "<<endl;
		cout<<"Stamina : "<<k[knight_id].stam<<endl;
		cout<<"XP      : "<<k[knight_id].xp<<endl;
	}
}

/**
	Print combined result for all the knights
	@param None
	@return None
*/
void knight::print_result()
{
	loop print_result(i);
	
	int sum=0;
	for(int i=0; i<NUM_KNIGHTS; i++) sum+= k[i].xp;				//total of all knights excluding Arthur
	cout << "\nTotal XP:" << sum;
}

/**
	Randomly sets the location of the knights 
	@param number of days to simulate
	@return None
*/
void knight::random_placement(int no_of_days)
{
	int hours = no_of_days * 24;
	srand(time(NULL));
	for(int j=0; j<hours; j++)
	{
		loop
		{
			switch(rand()%3)
			{
				case 0:
					fix_pos(i,TAVERN);
					break;
				case 1:
					fix_pos(i,TRAINING);
					break;
				case 2:
					fix_pos(i,ROUND_TABLE);
					break;
			}			
		}
	}	
}

//****DRIVER CODE****//
int main(void)
{
	knight k;
	k.random_placement(100); //<<-- update number of days here 
	k.print_result();
	return 0;
}
