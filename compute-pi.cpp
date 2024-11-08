#include <iostream>
#include <pthread.h>
#include <cmath>
using namespace std;
#define NUMBER_OF_THREADS 12
#define N 1201245
const int INTERVAL_PER_THREAD = ceil((double)N / NUMBER_OF_THREADS);
const double STEP = 1.0 / N;
pthread_mutex_t mutex;
double pi = 0;

void *compute_pi(void *arg)
{
	int i = (int)arg;
	double sum = 0;
	int start = i * INTERVAL_PER_THREAD;
	int end = min((double)(start + INTERVAL_PER_THREAD), (double)N);
	for (int j = start; j < end; j++)
	{
		double x = j * STEP;
		sum += 4 / (1.0 + pow(x, 2));
	}
	pthread_mutex_lock(&mutex);
	pi += sum;
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	return NULL;
}

void main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_t threads[NUMBER_OF_THREADS];
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_create(&threads[i], NULL, compute_pi, (void *)i);

	for (int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], NULL);

	cout << "PI = " << pi * STEP << endl;
	pthread_mutex_destroy(&mutex);
	system("pause");
}
