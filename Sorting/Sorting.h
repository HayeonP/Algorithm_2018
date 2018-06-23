#pragma once
#pragma once

#include <iostream>
#include <iterator>
#include <time.h>
#include <chrono>

#define _25 0
#define _50 1
#define _75 2
#define RANDOM 3

using namespace std;

class Sorting {
public:
	Sorting(int psize);
	~Sorting();
	void run();
	void createData(int num);
	void insertionSort(int data[], int num);
	void mergeSort(int data[], int p, int r);
	void merge(int data[], int p, int q, int r);
	void quickSort(int data[], int p, int r);
	int partition(int data[], int p, int r);
	void printAry(int ary[], int num);
	int select(int data[], int p, int r, int i);
	float percent(int data[], int p, int r, int pivot);
private:
	clock_t sTime;
	clock_t fTime;
	clock_t p_sTime;
	clock_t p_fTime;
	clock_t p_time;
	double time;	
	int size;
	int *data;
	int *insertData;
	int *mergeData;
	int *quickDataRandom;
	int *quickData25;
	int *quickData50;
	int *quickData75;
	int pvType;
	bool randomDebug= false;
};



