#include <pthread.h>
#include <iostream>

using namespace std;
/*
deadlock by not allowing philosophers to release a fork before picking up
the other one. Philosophers can pick up a fork but must wait until they have both forks to eat.
This can lead to a situation where all philosophers have one fork, and they are all waiting for
the second one, causing a deadlock.
*/
pthread_mutex_t *mutex;
int number_of_philosophers;

void *philosopher(void *arg)
{
	int index = (int)arg;

	cout << "Thread " << index << " is Thinking...\n";
	// right fork
	pthread_mutex_lock(&mutex[index]);
	cout << "Thread " << index << " Holds " << "fork " << index << endl;
	// left fork
	pthread_mutex_lock(&mutex[(index + 1) % number_of_philosophers]);
	cout << "Thread " << index << " Holds " << "fork " << index + 1 << endl;

	cout << "Thread " << index << " is Eating...\n\n";
	// put down forks
	pthread_mutex_unlock(&mutex[index]);
	pthread_mutex_unlock(&mutex[(index + 1) % number_of_philosophers]);

	return NULL;
}

void main()
{
	pthread_t *thread;

	cout << "Enter The Number Of Philosophers: ";
	cin >> number_of_philosophers;

	thread = new pthread_t[number_of_philosophers];
	mutex = new pthread_mutex_t[number_of_philosophers];

	for (int i = 0; i < number_of_philosophers; i++)
		pthread_mutex_init(&mutex[i], NULL);
	for (int i = 0; i < number_of_philosophers; i++)
		pthread_create(&thread[i], NULL, philosopher, (void *)i);
	for (int i = 0; i < number_of_philosophers; i++)
		pthread_join(thread[i], NULL);
	for (int i = 0; i < number_of_philosophers; i++)
		pthread_mutex_destroy(&mutex[i]);

	system("pause");
}