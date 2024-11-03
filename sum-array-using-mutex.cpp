#include<iostream>
#include<pthread.h>
#include<cmath>

using namespace std;
const int arraySize = 80;
const int numThreads = 6;
int array[arraySize];
int totalSum = 0;
pthread_mutex_t sumMutex;

void* sum (void* arg)
{
   int i = (int)arg;
   int chunk = ceil((double)arraySize/numThreads);
   int start = i*chunk;
   int end = min(arraySize,start+chunk);
   cout<<"Thread = " << i <<", start = "<<start<<", end = "<<end<<endl;
   int partialSum = 0;
   for (int j = start; j < end; ++j) {
        partialSum += array[j];
    }
    pthread_mutex_lock(&sumMutex);
    totalSum += partialSum;
    pthread_mutex_unlock(&sumMutex);
   return NULL; 
}
void main(){
     // Initialize the array with some values (1 to arraySize)
    for (int i = 0; i < arraySize; ++i) {
        array[i] = i + 1;
    }
	pthread_mutex_init(&sumMutex, NULL);

	pthread_t threads[numThreads];

	for(int i=0;i<numThreads;i++){
	   pthread_create(&threads[i], NULL , sum , (void*)i);
	}

	for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

	// Destroy the mutex
    pthread_mutex_destroy(&sumMutex);

    // Display the total sum
    cout << "Total Sum: " << totalSum << endl;
    system("pause");
}
