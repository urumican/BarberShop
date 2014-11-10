#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

#define NUM_CHAIR 5

typedef enum{SLEEP, WORK, FREE} barber_st;
typedef enum{CHECK, WAIT, READY} customer_st;
typedef enum{ON, OFF} chair_st;

pthreat_mutex_t wake_barber;
pthreat_mutex_t mutex_cust;
pthreat_cond_t condition; // I learned to use conditional variable.
pthreat_barrier_t barrier_start;
pthreat_barrier_t barrier_end;

int chair_num = NUM_CHAIR;
barber_st state_bar = FREE;
//customer_st state_cust;
//chair_st state_ch[NUM_CHAIR];


/* We don't need an additional variable for the barber chair. */

void check_barber()
{
	/*
	if(state_bar == FREE)
	{
		pthreat_mutex_unlock(mutex_cust);
		printf("[Customer %d] Get barber serving.\n\n", ID);
	}
	else if(state_bar == WORK)
	{
		//chair_num--;
		printf("[Custermer %d] Start wating.\n\n", ID);
	}
	*/
	if(state_bar == SLEEP)
	{
		/*
		pthread_mutex_lock(&wake_barber);
		chair_num--; // Sit in the waiting room first
		*/
		/* Then try to wake barker*/
		if(chair < 5)
		{
			pthread_cond_signal(&condition);
		}
	//	pthread_mutex_unlock(&wake_barber);
		pthread_mutex_unlock(&mutex_cust);
		printf("[Custermer %d] Wake up the sleeping barber.\n\n", ID);
	}
}

void check_cust()
{
	
}

void* customer_generator()

void cut(int ID)

void get_cut()

void* barber_action()
{
	while(1)
	{
		pthread_mutex_lock(&wake_barber);
		if(chair_nu < 5) // It mean there is someone still waiting.
		{ 
			pthread_unlock_unlock(&mutex_cust);
		}
		while(chair_num == 5) // No one's waiting in the room
		{
			state_bar = SLEEP;
			pthread_cond_wait(&condition, &wake_barber);
		}
		chair_num++;
		pthread_mutex_unlock(&wake_barber);
		
		state_bar = WORK;
		pthreat_barrier_wait(&barrier_start);
		cut();
		pthreat_barrier_wiat(barrier_end);
		
		state_bar = FREE;
		//pthread_unlock_unlock(&mutex_cust);
		
	}
}

void* custromer_action(void* id)
{
	int* ID = (int*)id;
	
	if(chair_num != 0)
	{
		pthread_mutex_lock(&wake_barber);
		chair_num--; // Sit in the waiting room first
		check_barber();
		pthread_mutex_unlock(&wake_barber);
		
		pthread_mutex_lock(&mutex_cust);
		
		pthreat_barrier_wait(&barrier_start);
		get_cut(); // Being cut.
		pthreat_barrier_wiat(barrier_end);
	}
	else
		printf("[Customer %d] The shop is full. I am leaving.", *ID);
}

int main(int argc, char *argv[])
{
	/* Threads definition */
	pthread_t barber;
	pthread_t generator;
	
	/* Barrier initialiazation */
	pthread_barrier_init(&barrier_start, NULL, 2);
	pthread_barrier_init(&barrier_end, NULL, 2);
	
	/* Mutex initialization*/
	pthread_mutex_init(&wake_barber, NULL);
	pthread_mutex_init(&mutex_cust, NULL);
	
	/* Condition Initialization */
	pthread_cond_init(&condition, NULL);
	
	/* threads activation */
	pthread(&barber, NULL, barber_action, NULL);
	pthread(&generator, NULL, customer_generator, NULL);
	
	/* threads termination */
	pthread_join(barber, NULL);
	pthread_join(generator, NULL);
	
	/* mutex destruction */
	pthread_mutex_destroy(&wake_barber);
	pthread_mutex_destroy(&mutex_cust);
	
	/* condition destruction*/
    	pthread_cond_destroy(&condition);
    	
    	/* barrier destruction */
    	pthread_cond_destroy(&barrier_start);
    	pthread_cond_destroy(&barrier_end);
    	
    	
    	pthread_exit(NULL);
    	return 0;
}
