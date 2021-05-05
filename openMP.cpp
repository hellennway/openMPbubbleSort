#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;

// Function for formatted data output
void PrintData(double* pData, int Size) {
	for (int i = 0; i < Size; i++)
		printf("%7.4f ", pData[i]);
	printf("\n");
}

void DummyDataInitialization(double*& pData, int& Size) {
	for (int i = 0; i < Size; i++)
		pData[i] = Size - i;
}

void RandomDataInitialization(double*& pData, int& Size) {
	srand((unsigned)time(0));
	for (int i = 0; i < Size; i++)
		pData[i] = rand() / double(1000);
}

// Function for allocating the memory and setting the initial values
void ProcessInitialization(double*& pData, int& Size) {
	do {
		printf("Enter the size of array: ");
		scanf_s("%d", &Size);
		if (Size <= 0)
			printf("Size should be greater than zero\n");
	} while (Size <= 0);
	printf("\nChosen objects size = %d\n", Size);
	pData = new double[Size];
	DummyDataInitialization(pData, Size);
	//RandomDataInitialization(pData, Size);
}
// Function for computational process termination
void ProcessTermination(double* pData) {
	delete[]pData;
}
// Function for bubble sort algorithm using openMP
void openMPsort(double* pData, int Size) {
	for (int i = 0; i < Size-1; i++)
	{
		int first = i % 2; // 0 if i is 0, 2, 4, ...
		                   // 1 if i is 1, 3, 5, ...
#pragma omp parallel for default(none),shared(pData,first,Size)
		for (int j = first; j < Size - 1; j += 1)
		{
			if (pData[j] > pData[j + 1])
			{
				std::swap(pData[j], pData[j + 1]);
			}
		}
	}
}

int main(int argc, char* argv[]) {
	double* pData = 0;
	int Size = 0;;
	double duration = 0.0;

	printf("OpenMP Bubble sort program\n");
	// Process initialization
	ProcessInitialization(pData, Size);
	//printf("Unsorted array\n");
	//PrintData(pData, Size);
	// bubble sort
	auto start = omp_get_wtime();
	openMPsort(pData, Size);
	//OddEvenSort(pData, Size);
	auto finish = omp_get_wtime();
	//printf("Sorted array\n");
	//PrintData(pData, Size);
	duration = finish - start;
	printf("Time of execution: %f\n", duration);
	// Process termination
	ProcessTermination(pData);
	return 0;
}
