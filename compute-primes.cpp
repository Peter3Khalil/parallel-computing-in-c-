#include <iostream>
#include <pthread.h>
#include <cmath>
using namespace std;
#define NUMBER_OF_THREADS 10
#define x 80
pthread_mutex_t mutex;
const int chunk_per_thread = ceil((double)x / NUMBER_OF_THREADS); // ceil is used to avoid floating numbers that can lead bugs
int primesCount = 0;

bool isPrime(int n)
{
    if (n < 2)
        return false;

    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}
int countPrimesInRange(int start, int end)
{
    int c = 0;
    for (int i = start; i < end; i++)
        if (isPrime(i))
            c++;
    return c;
}

void *threadCompute(void *arg)
{
    int thread_index = (int)arg;
    int start = thread_index * chunk_per_thread;
    int end = min(start + chunk_per_thread, x); // min is used to avoid out of range
    int local_count = countPrimesInRange(start, end);
    pthread_mutex_lock(&mutex);
    primesCount += local_count;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
    return NULL;
}

void main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t *threads = new pthread_t[NUMBER_OF_THREADS];
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_create(&threads[i], NULL, threadCompute, (void *)i);

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_join(threads[i], NULL);

    cout << "Number of primes = " << primesCount << endl;
    pthread_mutex_destroy(&mutex);
    system("pause");
}