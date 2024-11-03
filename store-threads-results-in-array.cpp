#include<iostream>
#include<pthread.h>
#include<cmath>

using namespace std;
const int arraySize = 10;
const int numThreads = 4;
int array[arraySize];
int results[numThreads];

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
   results[i] = partialSum;
   return NULL; 
}
void main(){
     // Initialize the array with some values (1 to arraySize)
    for (int i = 0; i < arraySize; ++i) {
        array[i] = i + 1;
    }

	pthread_t threads[numThreads];

	for(int i=0;i<numThreads;i++){
	   pthread_create(&threads[i], NULL , sum , (void*)i);
	}

	for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

	int totalSum = 0;
	for(int i =0;i<numThreads;i++){
		totalSum+=results[i];
	}
	cout<<"Total Sum = "<<totalSum<<endl;
    system("pause");
}
