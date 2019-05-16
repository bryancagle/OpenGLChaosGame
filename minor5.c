/**************************
Bryan Cagle
CSCE 3600 - Section 002
03-07-2016

The purpose of this program is to use mutex
locks to synchronize threads to give an output
in the correct order.

Modified from the original minor5.c
**************************/

#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define SIZE 50

char sentence[2000];
int  ind = 0;
pthread_mutex_t lock;

char convertUppercase(char lower)
{
	//Converts lowercase un uppercase
	if ((lower > 96) && (lower < 123))
	{
		return (lower - 32);
	}
	else
	{
		return lower;
	}
}

void printChar()
{
	//prints the converted sentence
	printf("The new sentence is [%d]: \t%c\n", ind, sentence[ind]);
	ind++;
}

void *convertMessage(void *ptr)
{
	// Function that each threads initiates its execution
	char aux;

	pthread_mutex_lock(&lock); //locking mutex so specific thread will finish

	if (ind % 2)
	{
		sentence[ind] = convertUppercase(sentence[ind]);
	}
			
	printChar();

	pthread_mutex_unlock(&lock); //unlocking the mutex

	return 0;
}

int main()
{
	int i;
	char buffer[SIZE];
	char *p;
	pthread_t ts[SIZE]; // define up to 50 threads

	printf("Please enter a phrase (less than 50 characters): ");

	if (fgets(buffer, sizeof(buffer), stdin) != NULL)
	{
		if ((p = strchr(buffer, '\n')) != NULL)
		{
			*p = '\0';
		}
	}

	strcpy(sentence, buffer); // copy string to char array
	
	printf("The original sentence is: \t %s\n", sentence);

	// create one thread for each character on the input word
	for(i = 0; i < strlen(buffer) + 1; ++i)
	{

		pthread_create(&ts[i], NULL, convertMessage, NULL);

	}
		
	// we wait until all threads finish execution
	for(i = 0; i < strlen(buffer); i++)
	{
		pthread_join(ts[i], NULL);
	}

	printf("\n");

	pthread_mutex_destroy(&lock); //destroying mutex lock

	return 0;
}
