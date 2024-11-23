// Notes and test functions on threads 

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// need to compile with -pthread


/***************************How to create threads**********************************/
/*void *routine() {
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
}

int main(int ac, char **av) {
	
	// intialize a thread variable, 
	// where the pthread library API will save info about the thread
	pthread_t t1, t2; 

	// initialize thread with pthread_create
	// pthread_create takes 4 vaiables
	// 1/ pointer to the pthread_t variable
	// 2/ pointer to an attribute variable to customize the thread
	// 3/ pointer to the function that the thread will execute
	// 4/ args to be passed to the function 
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1; // error occured
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2; // error occured

	// Similar to wait function for processes but for threads
	// 1/ the pthread variable
	// 2/ pointer to get the result from the thread
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;

	return (0);
}*/


/*************************What are race conditions*********************************/

/*int mails = 0;
pthread_mutex_t mutex;

void *routine() {
	for (int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// three operations that happen when we are changing a value
		// read value
		// increment
		// write value
	}
	return 0;
}

int main(int ac, char **av) {
	
	pthread_t t1, t2; 
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL))
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL))
		return 2;
	if (pthread_join(t1, NULL))
		return 3;
	if (pthread_join(t2, NULL))
		return 4;
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return 0;
}*/

/**********************How to create threads in a loop*****************************/

int mails = 0;
pthread_mutex_t mutex;

void *routine() {
	for (int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		// three operations that happen when we are changing a value
		// read value
		// increment
		// write value
	}
	return 0;
}

int main(int ac, char **av) {
	
	pthread_t threads[4];
	pthread_mutex_init(&mutex, NULL);

	int i = 0;
	while (i < 4)
	{
		if (pthread_create(&(threads[i]), NULL, &routine, NULL))
			return 1;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(threads[i], NULL))
			return 2;
		i++;
	}

	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return 0;
}
