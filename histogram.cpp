#include <iostream>
#include <ctime>
#include <omp.h>
using namespace std;

void main()
{
    const int rows = 100, cols = 10;
    int grayscale[rows][cols];
    int histogram[256] = {0};

    // Intialize Matrix
#pragma omp parallel for num_threads(100)
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grayscale[i][j] = rand() % 256;

    clock_t time1 = clock();

#pragma omp parallel num_threads(100)
    {
        int partialHistogram[256] = {0};
#pragma omp for
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                partialHistogram[grayscale[i][j]]++;

#pragma omp critical
        for (int i = 0; i < 256; i++)
        {
            histogram[i] += partialHistogram[i];
        }
    }

    clock_t time2 = clock();
    cout << (double)(time2 - time1) / CLOCKS_PER_SEC << endl;

    system("pause");
}