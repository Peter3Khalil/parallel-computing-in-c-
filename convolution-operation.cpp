#include <iostream>
#include <omp.h>
#include <ctime>
#include <vector>
#define NUM_OF_THREADS 10
using namespace std;

void main()
{
    const int input_rows = 500, input_cols = 100, kernal_rows = 3, kernal_cols = 3;
    int input[input_rows][input_cols];
    int kernal[kernal_rows][kernal_cols] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}};

    for (int i = 0; i < input_rows; i++)
        for (int j = 0; j < input_cols; j++)
            input[i][j] = rand() % 5;

    const int output_rows = input_rows - kernal_rows + 1, out_cols = input_cols - kernal_cols + 1;
    int output[output_rows][out_cols] = {0};

    clock_t start = clock();
    for (int i = 0; i < output_rows; i++)
    {
        for (int j = 0; j < out_cols; j++)
        {
            int sum = 0;
            for (int r = 0; r < kernal_rows; r++)
                for (int c = 0; c < kernal_cols; c++)
                    sum += kernal[r][c] * input[i + r][j + c];

            output[i][j] = sum;
        }
    }
    clock_t end = clock();
    double seq_time = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time of seq = " << seq_time << " s" << endl;

    clock_t start2 = clock();
#pragma omp parallel num_threads(NUM_OF_THREADS)
    {
#pragma omp for
        for (int i = 0; i < output_rows; i++)
        {
            for (int j = 0; j < out_cols; j++)
            {
                int sum = 0;
                for (int r = 0; r < kernal_rows; r++)
                    for (int c = 0; c < kernal_cols; c++)
                        sum += kernal[r][c] * input[i + r][j + c];

                output[i][j] = sum;
            }
        }
    }
    clock_t end2 = clock();
    double parallel_time = double(end2 - start2) / CLOCKS_PER_SEC;
    double speedup = seq_time / parallel_time;
    double efficiency = speedup / NUM_OF_THREADS;
    double cost = NUM_OF_THREADS * parallel_time;
    cout << "Time of parallel = " << parallel_time << " s" << endl;
    cout << "Speedup = " << speedup << endl;
    cout << "Efficiency = " << efficiency << endl;
    cout << "Cost = " << cost << endl;

    /*for (int i = 0; i < output_rows; i++)
    {
        for (int j = 0; j < out_cols; j++)
        {
            cout << output[i][j] << " ";
        }
        cout << endl;
    }*/

    system("pause");
}