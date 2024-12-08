#include <iostream>
#include <math.h>
using namespace std;
#include <omp.h>

void main()
{
    const int N = 5;
    int arr[N];
    for (int i = 0; i < N; i++)
        arr[i] = i + 1;
    int k = N;
    for (int j = 0; j < ceil(log2(N)); j++)
    {
        int numOfProcessors = ceil(k / 2.0);
#pragma omp parallel num_threads(numOfProcessors)
        {
            int id = omp_get_thread_num();
            int last = k - 1 - id;
            if (id != last)
            {
                arr[id] = arr[id] + arr[last];
            }
            else
            {
                arr[id - 1] += arr[id];
            }
        }
        k = ceil(k / 2);
    }

    cout << "Sum = " << arr[0] << endl;

    system("pause");
}