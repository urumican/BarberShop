#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

#define NUM_CHAIR 5

typedef enum{SLEEP, WORK, FREE} state_barber;
typedef enmu{WAIT, CUT} state_customer;

pthreat_mutex_t wake_barber;
pthreat_mutex_t customer_wait;

int chair_num = NUM_CHAIR;

/* We don't need an additional variable for the barber chair. */

void* barber()

void* custromer()
{
	if()
}

int main(int argc, char *argv[])
{

}
