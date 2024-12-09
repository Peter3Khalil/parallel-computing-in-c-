#include <iostream>
#include <pthread.h>
#include <cmath>
using namespace std;
double workedHours[5] = {160, 130, 120, 60, 168};
double hoursRate[5] = {50, 80, 45, 300, 50};
double netSalary[5];
double grossSalary = 0, tax = 0, insurance = 0;

pthread_mutex_t grossSalaryMutex, taxMutex, insuranceMutex, netSalaryMutex1, netSalaryMutex2;
int employeeIndex = 0;

bool isFinished()
{
	return employeeIndex >= 5;
}

void *calcGrossSalary(void *arg)
{
	while (!isFinished())
	{
		pthread_mutex_lock(&grossSalaryMutex);
		if (!isFinished())
		{
			grossSalary = workedHours[employeeIndex] * hoursRate[employeeIndex];
		}
		pthread_mutex_unlock(&taxMutex);
		pthread_mutex_unlock(&insuranceMutex);
	}
	pthread_exit(NULL);
	return NULL;
}

void *calcTax(void *arg)
{
	while (!isFinished())
	{
		pthread_mutex_lock(&taxMutex);
		if (!isFinished())
		{
			tax = grossSalary * 0.14;
		}
		pthread_mutex_unlock(&netSalaryMutex2);
	}
	pthread_exit(NULL);
	return NULL;
}

void *calcInsurance(void *arg)
{
	while (!isFinished())
	{
		pthread_mutex_lock(&insuranceMutex);
		if (!isFinished())
		{
			insurance = grossSalary * 0.1;
		}
		pthread_mutex_unlock(&netSalaryMutex1);
	}
	pthread_exit(NULL);
	return NULL;
}

void *calcNetSalary(void *arg)
{
	while (!isFinished())
	{
		pthread_mutex_lock(&netSalaryMutex1);
		pthread_mutex_lock(&netSalaryMutex2);
		if (!isFinished())
		{
			netSalary[employeeIndex] = grossSalary - (tax + insurance);
			++employeeIndex;
		}
		pthread_mutex_unlock(&grossSalaryMutex);
	}
	pthread_exit(NULL);
	return NULL;
}

void main()
{
	pthread_mutex_init(&grossSalaryMutex, NULL);
	pthread_mutex_init(&taxMutex, NULL);
	pthread_mutex_init(&insuranceMutex, NULL);
	pthread_mutex_init(&netSalaryMutex2, NULL);
	pthread_mutex_init(&netSalaryMutex1, NULL);

	pthread_mutex_lock(&taxMutex);
	pthread_mutex_lock(&insuranceMutex);
	pthread_mutex_lock(&netSalaryMutex2);
	pthread_mutex_lock(&netSalaryMutex1);

	pthread_t threadA, threadB, threadC, threadD;

	pthread_create(&threadA, NULL, calcGrossSalary, NULL);
	pthread_create(&threadB, NULL, calcTax, NULL);
	pthread_create(&threadC, NULL, calcInsurance, NULL);
	pthread_create(&threadD, NULL, calcNetSalary, NULL);

	pthread_join(threadA, NULL);
	pthread_join(threadB, NULL);
	pthread_join(threadC, NULL);
	pthread_join(threadD, NULL);
	for (int j = 0; j < 5; j++)
	{
		cout << netSalary[j] << " " << endl;
	}
	system("pause");
}
