// ChengLiProject.cpp : Defines the entry point for the console application.

#include "stdafx.h"

//Created by Cheng Li
//Plantform: x86 from Visual Studio

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <queue>
#define limit 8
using namespace std;

typedef struct {
	int left;
	int right;
} PARTITION_STRUCT;

void insertionSort(vector<int> &A, int &count);
void Merger(vector<int> &A, int low, int mid, int hig, int &count);
void MergeSortHelper(vector<int> &A, int low, int hig, int &count);
void MergeSort(vector<int> &A, int A_size, int &count);
void InsertionSort(vector<int> &A, int start, int end, int &count);
void Merge(vector<int> &A, int start, int mid, int end, int &count);
void split(vector<int> &A, int start, int end, int &count);
void mergeSort(vector<int> &A, int end, int &count);
void swap(vector<int> &A, int i, int j);
void SortNextPartition(vector<int> &A, queue<PARTITION_STRUCT> &partition_queue, int left, int right, int &count);
void QuickSort(vector<int> &A, int left, int right, int &count);
int Partition(vector<int> &A, int left, int right, int &count);
void populateVector(vector<int> &A, double m);

int main()
{

	// Initialize the vector used by populateVector
	// Set the parameters n and m
	int n = 10000;
	double m = 100;
	int N = 50;
	int j = 0;

	clock_t start1, finish1, start2, finish2, start3, finish3, start4, finish4;
	vector<int> A(n);
	vector<int> E(N);
	vector<int> F(N);
	vector<int> G(N);
	vector<int> H(N);
	vector<double> I(N);
	vector<double> J(N);
	vector<double> K(N);
	vector<double> L(N);
	ofstream file("C:\\Ademaro\\temp.txt");

	for(int i=0; i<N; i++){
	populateVector(A, m);   // Populate the vector
	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
	std::vector<int> B = std::vector<int>(A);
	std::vector<int> C = std::vector<int>(A);
	std::vector<int> D = std::vector<int>(A);

	// Implementing insertionSort
	
	start1 = clock();
	insertionSort(A, count1);
	finish1 = clock();

	start2 = clock();
	MergeSort(B, n, count2);
	finish2 = clock();

	start3 = clock();
	mergeSort(C, n, count3);
	finish3 = clock();

	start4 = clock();
	QuickSort(D, 0, n - 1, count4);
	finish4 = clock();

	E[j] = count1;
	F[j] = count2;
	G[j] = count3;
	H[j] = count4;
	I[j] = (double)(finish1 - start1) / CLOCKS_PER_SEC;
	J[j] = (double)(finish2 - start2) / CLOCKS_PER_SEC;
	K[j] = (double)(finish3 - start3) / CLOCKS_PER_SEC;
	L[j] = (double)(finish4 - start4) / CLOCKS_PER_SEC;
	j++;
	}

	for (vector<int>::iterator i = E.begin(); i != E.end(); i++)
		file << *i << " ";
	file << endl;
	
	for (vector<int>::iterator i = F.begin(); i != F.end(); i++)
		file << *i << " ";
	file << endl;

	for (vector<int>::iterator i = G.begin(); i != G.end(); i++)
		file << *i << " ";
	file << endl;

	for (vector<int>::iterator i = H.begin(); i != H.end(); i++)
		file << *i << " ";
	file << endl;

	for (vector<double>::iterator i = I.begin(); i != I.end(); i++)
		file << *i << " ";
	file << endl;

	for (vector<double>::iterator i = J.begin(); i != J.end(); i++)
		file << *i << " ";
	file << endl;

	for (vector<double>::iterator i = K.begin(); i != K.end(); i++)
		file << *i << " ";
	file << endl;

	for (vector<double>::iterator i = L.begin(); i != L.end(); i++)
		file << *i << " ";
	file << endl;

	return 0;
}

// Implementation of Insertion Sort
void insertionSort(vector<int> &A, int &count)
{
	int i;
	int j;
	int key;
	
	for (i = 1; i < A.size(); i++) {
		key = A[i];
		j = i - 1;

		while (j >= 0 && A[j] > key)
		{
			count++;
			A[j + 1] = A[j];
			j -= 1;
		}
		count++;
		A[j + 1] = key;
	}
}

// Implementation of Merge Sort
void Merger(vector<int> &A, int low, int mid, int hig, int &count)
{
	int *temp = new int[hig - low + 1];
	int i = low;
	int j = mid + 1;
	int k = 0;

	while (i <= mid&&j <= hig)
	{
		if (A[i] <= A[j])
			temp[k++] = A[i++];
		else
			temp[k++] = A[j++];
		count++;
	}

	while (i <= mid)
		temp[k++] = A[i++];

	while (j <= hig)
		temp[k++] = A[j++];

	for (k = 0, i = low; i <= hig; ++i, ++k)
		A[i] = temp[k];

	delete[]temp;
}

void MergeSortHelper(vector<int> &A, int low, int hig, int &count)
{
	int mid;
	if (low < hig)
	{
		mid = (low + hig) >> 1;
		MergeSortHelper(A, low, mid, count);
		MergeSortHelper(A, mid + 1, hig, count);
		Merger(A, low, mid, hig, count);
	}
}

void MergeSort(vector<int> &A, int A_size, int &count)
{
	MergeSortHelper(A, 0, A_size - 1, count);
}

// Implementation of MergeInsertion Sort
void InsertionSort(vector<int> &A, int start, int end, int &count)
{
	int key, k;
	for (int i = start + 1; i <= end; i++)
	{
		key = A[i];
		k = i - 1;
		while (k > start - 1 && A[k] > key)
		{
			count++;
			A[k + 1] = A[k];
			k--;
		}
		count++;
		A[k + 1] = key;
	}
}


void Merge(vector<int> &A, int start, int mid, int end, int &count)
{
	int *temp = new int[end - start + 1];
	int index = 0;
	int	p1 = start;
	int p2 = mid + 1;
	while (p1 <= mid&&p2 <= end) {
		if (A[p1]>A[p2]) {
			temp[index] = A[p2];
			index++; p2++;
		}
		else {
			temp[index] = A[p1];
			index++; p1++;
		}
		count++;
	}

	if (p1 <= mid) {
		for (; p1 <= mid; p1++, index++)
		temp[index] = A[p1];
	}
	else {
		for (; p2 <= end; p2++, index++)
		temp[index] = A[p2];
	}
	

	//copy back to the array
	for (index = 0, p1 = start; p1 <= end; ++p1, ++index)
		A[p1] = temp[index];

		delete[]temp;
}

void split(vector<int> &A, int start, int end, int &count)
{
	if (end - start < limit)//if the array is small then use insertion sort
	{
		InsertionSort(A, start, end, count);
	}
	else if (start < end) {
		int mid = (start + end) / 2;
		split(A, start, mid, count);
		split(A, mid + 1, end, count);
		Merge(A, start, mid, end, count);
	}
}

void mergeSort(vector<int> &A, int end, int &count)
{
	split(A, 0, end - 1, count);
}

// Implementation of Quick Sort
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void QuickSort(vector<int> &A, int left, int right, int &count)
{
	PARTITION_STRUCT new_partition = { left, right };
	queue<PARTITION_STRUCT> partition_queue = queue<PARTITION_STRUCT>();
	partition_queue.push(new_partition);

	PARTITION_STRUCT next_partition;
	while (!partition_queue.empty())
	{
		next_partition = partition_queue.front();
		partition_queue.pop();
		SortNextPartition(A, partition_queue, next_partition.left, next_partition.right, count);
	}
}


void SortNextPartition(vector<int> &A, queue<PARTITION_STRUCT> &partition_queue, int left, int right, int &count)
{
	if (left < right)
	{
		int mid = Partition(A, left, right, count);
		PARTITION_STRUCT new_partition1 = { left, mid - 1 };
		PARTITION_STRUCT new_partition2 = { mid + 1, right };
		partition_queue.push(new_partition1);
		partition_queue.push(new_partition2);
	}
}

int Partition(vector<int> &A, int left, int right, int &count)
{
	int key = A[left];
	int i = left, j = left + 1;
	while (j <= right && i<right)
	{
		if (A[j] < key)
		{
			count++;
			swap(A[j], A[++i]);
		}
		j++;
		count++;
	}
	swap(A[left], A[i]);
	return i;
}


// Implementation of populateVector to select integer numbers from [-m,m] Randomly and uniformly
void populateVector(vector<int> &A, double m)
{
	vector<int>::size_type size_vec = A.size();
	std::random_device rdev{};
	std::mt19937 gen(rdev());
	std::uniform_int_distribution<long long> dist(-1 * m, m);

	for (vector<int>::iterator i = A.begin(); i != A.end(); i++)
		*i = dist(gen);
}