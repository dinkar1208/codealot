//INCLUDES//
#include<iostream>
#include<cstring>
#include<ctime>
#include<cstdlib>

using namespace std;

//CONSTANTS//
#define NUM_KNIGHTS 12
#define loop for(int i=0; i<NUM_KNIGHTS; i++)

//ENUM DATA TYPES//
enum location {	TAVERN,
				TRAINING};

//STRUCTS//
typedef struct 
{
	location log[24]; //used like a stack
	int hours;
	int stam;
	int xp;
	int old_stam;
	int old_xp;
}Typedef_knight;

//CLASSES//
class knight
{
	Typedef_knight k[NUM_KNIGHTS];
	int knights_with_complete_day;
	void calc_end_of_day(int knight_id);		//called after every 24 hours to calculate result
	void calc_bonus(); 							//called after result for all knights is calculated
	
	public:
		knight()
		{
			knights_with_complete_day=0;
			loop
			{
				k[i].hours 	=0;
				k[i].stam	=0;
				k[i].xp		=0;
				k[i].old_xp	=0;
			}
		}
		//PLACEMENT FUNCTION//
		void fix_pos(int knight_id, location loc);	//fix position of a knight
		//PRINT FUNCTIONS//
		void print_result(int knight_id);			
		void print_result();
		//HELPER FUNCTION//
		void random_placement(int no_of_days);

};

void knight::fix_pos(int knight_id, location loc)
{
	k[knight_id].log[ (k[knight_id].hours) ] = loc;
	k[knight_id].hours ++;	
	if(k[knight_id].hours == 24) calc_end_of_day(knight_id);
}

void knight::calc_end_of_day(int knight_id)
{
	location loc;
	knights_with_complete_day++;
	cout<<knights_with_complete_day;
	for(int i=0; i<24; i++)
	{
		loc = k[knight_id].log[i];
		
		if(loc == TAVERN) k[knight_id].stam++;
		else if((loc == TRAINING)){
			k[knight_id].stam--;
			if((k[knight_id].stam >= 0))	k[knight_id].xp++;
		}
	}
	k[knight_id].hours = 0;
	if(knights_with_complete_day == NUM_KNIGHTS) calc_bonus();
}

void knight::calc_bonus()
{
	//		New bonus system definition
	//+Calculate the min and max XP earned by all the knights
	//+Find the median and reward all knights above median with +5XP
	//+Find the upper quartile and reward all knights above median with +10XP
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
	
	loop k[i].old_xp	= k[i].xp;
	knights_with_complete_day=0;
}

void knight::print_result(int knight_id)
{
	cout<<"\nKnight "<<knight_id<<endl;
	cout<<"Stamina : "<<k[knight_id].stam<<endl;
	cout<<"XP      : "<<k[knight_id].xp<<endl;
}

void knight::print_result()
{
	loop print_result(i);
}

//HELPER FUNCTIONS//
void knight::random_placement(int no_of_days)
{
	int hours = no_of_days * 24;
	srand(time(NULL));
	for(int j=0; j<hours; j++)
	{
		loop
		{
			if(rand()%2) 	fix_pos(i,TAVERN);
			else 			fix_pos(i,TRAINING);			
		}
	}
	
}

//DRIVER CODE//
int main(void)
{
	knight k;
	k.random_placement(1);
	k.print_result();
	return 0;
}
