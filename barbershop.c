#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

#define NUM_CHAIR 5

typedef enum{SLEEP, WORK, FREE} barber_st;
typedef enum{CHECK, WAIT, READY} customer_st;
typedef enum{ON, OFF} chair_st;
typedef enum{DEF, UNDEF} thread_st;

pthread_mutex_t wake_barber;
pthread_mutex_t mutex_cust;
pthread_cond_t condition; // I learned to use conditional variable.
pthread_barrier_t barrier_start;
pthread_barrier_t barrier_end;
pthread_t cust_thrs[10];


int chair_num = NUM_CHAIR;
int customer_ID[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
barber_st state_bar = FREE;

/* We don't need an additional variable for the barber chair. */
void check_barber()
{
	if(state_bar == SLEEP)
	{
		if(chair_num < 5)
		{
			pthread_cond_signal(&condition);
		}
	}
}

void cut()
{
	//int sleep_time = (rand() % 3) > 0 ? (rand() % 3) : (rand() % 3 + 3);
	sleep(3);
}

void get_cut()
{
	//int sleep_time = (rand() % 3) > 0 ? (rand() % 3) : (rand() % 3 + 3);
	sleep(3);
}

void* barber_action(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&wake_barber);
		
		while(chair_num == 5) // No one's waiting in the room
		{
			state_bar = SLEEP;
			printf("[Barber] Sleep \n\n");
			pthread_cond_wait(&condition, &wake_barber);
			printf("[Barber] Wake \n\n");
		}
		
		printf("[Barber] Bring in one customer \n\n");
		pthread_mutex_unlock(&mutex_cust);

		pthread_mutex_unlock(&wake_barber);
		
		state_bar = WORK;
		pthread_barrier_wait(&barrier_start);
		printf("[Barber] Start cutting \n\n");
		cut();
		printf("[Barber] Finish \n\n");
		pthread_barrier_wait(&barrier_end);

		state_bar = FREE;
	}
	
	return NULL;
}

void* custromer_action(void* id)
{
	int* ID = (int*)id;
	
	while(1)
	{
		int sleep_time = (rand() % 3) > 0 ? (rand() % 3) : (rand() % 3 + 3);
		sleep(sleep_time);
		
		if(chair_num != 0)
		{
			pthread_mutex_lock(&wake_barber);
			chair_num--; // Sit in the waiting room first

			printf("[Customer %d] Come in and sit. Num of seat %d \n\n", *ID, chair_num);
			check_barber();

			pthread_mutex_unlock(&wake_barber);
			
			pthread_mutex_lock(&mutex_cust);
			chair_num++;
			printf("[Customer %d] Get into barber chair \n\n", *ID);

			pthread_barrier_wait(&barrier_start);
			printf("[Customer %d] Get haircut \n\n", *ID);
			get_cut(); // Being cut.
			printf("[Customer %d] Finish \n\n", *ID);
			pthread_barrier_wait(&barrier_end);

			printf("[Customer %d] Go home. Num of seat %d \n\n", *ID, chair_num);
		}
		else
			printf("[Customer %d] The shop is full. I am leaving. \n\n", *ID);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	/* Threads definition */
	pthread_t barber;
	//pthread_t generator;
	
	/* Barrier initialiazation */
	pthread_barrier_init(&barrier_start, NULL, 2);
	pthread_barrier_init(&barrier_end, NULL, 2);
	
	/* Mutex initialization*/
	pthread_mutex_init(&wake_barber, NULL);
	pthread_mutex_init(&mutex_cust, NULL);
	pthread_mutex_lock(&mutex_cust);
	
	/* Condition Initialization */
	pthread_cond_init(&condition, NULL);
	
	/* threads activation */
	pthread_create(&barber, NULL, barber_action, NULL);
	//pthread(&generator, NULL, customer_generator, NULL);
	for(int i = 0; i < 10; i++)
	{
		pthread_create(&cust_thrs[i], NULL, custromer_action, (void*)&customer_ID[i]);
	}
	
	/* threads termination */
	pthread_join(barber, NULL);
	//pthread_join(generator, NULL);
	for(int k = 0; k < 10; k++)
	{
		pthread_join(cust_thrs[k], NULL);
	}
	
	/* mutex destruction */
	pthread_mutex_destroy(&wake_barber);
	pthread_mutex_destroy(&mutex_cust);
	
	/* condition destruction*/
    	pthread_cond_destroy(&condition);
    	
    	/* barrier destruction */
    	pthread_barrier_destroy(&barrier_start);
    	pthread_barrier_destroy(&barrier_end);
    	
    	
    	pthread_exit(NULL);
    	return 0;
}
