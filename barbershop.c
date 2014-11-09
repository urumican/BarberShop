#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

#define NUM_CHAIR 5

typedef enum{SLEEP, WORK, FREE} barber_st;
typedef enmu{WAIT, CUT} customer_st;

pthreat_mutex_t wake_barber;
pthreat_mutex_t customer_wait;
pthreat_cond_t condition; // I learned to use conditional variable.

int chair_num = NUM_CHAIR;
barber_st state_bar = FREE;


/* We don't need an additional variable for the barber chair. */

void check_barber(int ID)
{
	if(state_bar == FREE)
	{
		pthreat_mutex_unlock(customer_wait);
		printf("[Customer %d] Get barber serving.\n\n", ID);
	}
	else if(state_bar == WORK)
	{
		chair_num--;
		printf("[Custermer %d] Start wating.\n\n", ID);
	}
	else if(state_bar == SLEEP)
	{
		pthreat_cond_signal(condition);
		printf("[Custermer %d] Wake up the sleeping barber.\n\n", ID);
	}
}

void cut_hair(int ID)

void get_haircut()

void* barber()

void* custromer(void* id)
{
	int* ID = (int*)id;
	
	if(chair_num != 0)
	{
		check_barber();
		
	}
	else
		print("[Customer %d] The shop is full. I am leaving.", *ID);
}

int main(int argc, char *argv[])
{

}
