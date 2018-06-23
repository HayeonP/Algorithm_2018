#include "Sorting.h"

Sorting::Sorting(int psize) {
	size = psize;
	pvType = RANDOM;

	data = new int[size];
	insertData = new int[size];
	mergeData = new int[size];
	quickDataRandom = new int[size];
	quickData25 = new int[size];
	quickData50 = new int[size];
	quickData75 = new int[size];

	createData(size);

	copy(data, data + size, stdext::checked_array_iterator<int *>(insertData, size));
	copy(data, data + size, stdext::checked_array_iterator<int *>(mergeData, size));
	copy(data, data + size, stdext::checked_array_iterator<int *>(quickDataRandom, size));
	copy(data, data + size, stdext::checked_array_iterator<int *>(quickData25, size));
	copy(data, data + size, stdext::checked_array_iterator<int *>(quickData50, size));
	copy(data, data + size, stdext::checked_array_iterator<int *>(quickData75, size));

}

Sorting::~Sorting() {
	delete[] insertData;
	delete[] mergeData;
	delete[] quickData25;
	delete[] quickData50;
	delete[] quickData75;
	delete[] quickDataRandom;
}

void Sorting::run() {
	cout << "[ n = " << size << " ]" << endl;

	sTime = clock();
	insertionSort(insertData, size);
	fTime = clock();
	time = (float)((fTime - sTime) / CLOCKS_PER_SEC);
	cout << "Insertion sorting time : " << time<< " seconds" << endl;


	sTime = clock();
	mergeSort(mergeData, 0, size - 1);
	fTime = clock();
	time = (float)((fTime - sTime) / CLOCKS_PER_SEC);
	cout << endl << "Merge sorting time : " << time << " seconds" << endl;

	pvType = _25;
	p_time = 0;
	sTime = clock();
	quickSort(quickData25, 0, size - 1);
	fTime = clock();
	time = (float)((fTime - sTime-p_time) / CLOCKS_PER_SEC);
	cout << endl <<"Quick sorting 25% time : " << time << " seconds" << endl;

	pvType = _50;
	p_time = 0;
	sTime = clock();
	quickSort(quickData50, 0, size - 1);
	fTime = clock();
	time = (float)((fTime - sTime-p_time) / CLOCKS_PER_SEC);
	cout << endl <<"Quick sorting 50% time : " << time << " seconds" << endl;

	pvType = _75;
	p_time = 0;
	sTime = clock();
	quickSort(quickData75, 0, size - 1);
	fTime = clock(); 
	time = (float)((fTime - sTime - p_time) / CLOCKS_PER_SEC);
	cout << endl <<"Quick sorting 75% time : " << time << " seconds" << endl;

	if(randomDebug) cout << "[ random % : ";
	pvType = RANDOM;
	p_time = 0;
	sTime = clock();
	quickSort(quickDataRandom, 0, size - 1);
	fTime = clock();
	time = (float)((fTime - sTime - p_time) / CLOCKS_PER_SEC);
	cout << endl<<"Quick sorting RANDOM time : " << time << " seconds" << endl;
	if (randomDebug) cout << "]" << endl;

	cout << "-------------------------------------------------------------------------------------------" << endl;

}

void Sorting::createData(int num) {
	fill_n(data, num, 0);
	for (int i = 1; i <= num; i++) {
		int index = rand() % num;
		while (1) {
			if (data[index] == 0) {
				data[index] = i;
				break;
			}
			else {
				if (index >= num) { index = 0; }
				else { index++; }
			}
		}
	}
}

void Sorting::insertionSort(int data[], int num) {
	int temp;

	for (int i = 1; i < num; i++) {
		temp = data[i];
		int j = i - 1;
		while ((j >= 0) && (temp<data[j])) {
			data[j + 1] = data[j];
			j--;
		}
		if (temp > data[j]) data[j + 1] = temp;
	}
}

void Sorting::mergeSort(int data[], int p, int r) {
	int q;
	if (p < r) {
		q = (p + r) / 2;
		mergeSort(data, p, q);
		mergeSort(data, q + 1, r);
		merge(data, p, q, r);
	}
}

void Sorting::merge(int data[], int p, int q, int r) {
	int i = p;
	int j = q + 1;
	int t = 0;
	int* tempAry = new int[r - p + 1];
	while (i <= q && j <= r) {
		if (data[i] > data[j]) {
			tempAry[t++] = data[j++];
		}
		else {
			tempAry[t++] = data[i++];
		}
	}
	while (i <= q) {
		tempAry[t++] = data[i++];
	}
	while (j <= r) {
		tempAry[t++] = data[j++];
	}
	for (t = 0; t < r - p + 1; t++) {
		data[p + t] = tempAry[t];
	}


	return;
}

void Sorting::quickSort(int data[], int p, int r) {
	int q;
	if (p < r) {

		p_sTime = clock();

		int pivot, pvIndex;
		float pvRatio;
		int i = p - 1;
		int temp;

		switch (pvType) {
		case 0:
			pvRatio = 0.25;
			break;
		case 1:
			pvRatio = 0.5;
			break;
		case 2:
			pvRatio = 0.75;
			break;
		default:
			pvRatio = -1;
			break;
		}

		if (pvRatio != -1) {
			int selectPar = (int)((r - p + 1)*pvRatio);
			if (selectPar < 1) selectPar = 1;
			pvIndex = select(data, p, r, selectPar);
		}
		else {
			pvIndex = r;
			if (randomDebug) percent(data, p, r, data[r]);
		}
		p_fTime = clock();
		p_time += p_fTime - p_sTime;

		pivot = data[pvIndex];

		for (int j = p; j <= r; j++) {
			if (data[j] <= pivot) {
				if (j == pvIndex) continue;
				i++;

				if (i != j) {
					temp = data[i];
					data[i] = data[j];
					data[j] = temp;
				}

				if (data[j] == pivot) {
					pvIndex = j;
				}
			}
		}

		temp = data[i + 1];
		data[i + 1] = data[pvIndex];
		data[pvIndex] = temp;

		q = i + 1;


		quickSort(data, p, q - 1);
		quickSort(data, q + 1, r);
	}
}

int Sorting::partition(int data[], int p, int r) {
	int pivot, pvIndex;
	float pvRatio;
	int i = p - 1;
	int temp;

	switch (pvType) {
	case 0:
		pvRatio = 0.25;
		break;
	case 1:
		pvRatio = 0.5;
		break;
	case 2:
		pvRatio = 0.75;
		break;
	default:
		pvRatio = -1;
		break;
	}

	if (pvRatio != -1) {		
		int selectPar = (int)((r - p + 1)*pvRatio);
		if (selectPar < 1) selectPar = 1;
		pvIndex = select(data, p, r, selectPar);
	}
	else {
		pvIndex = r;
		if (randomDebug) percent(data, p, r, data[r]);
	}

	pivot = data[pvIndex];

	for (int j = p; j <= r; j++) {
		if (data[j] <= pivot) {
			if (j == pvIndex) continue;
			i++;

			if (i != j) {
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}

			if (data[j] == pivot) {
				pvIndex = j;
			}
		}
	}

	temp = data[i + 1];
	data[i + 1] = data[pvIndex];
	data[pvIndex] = temp;

	return i + 1;
}

void Sorting::printAry(int ary[], int num) {
	cout << "{";
	for (int i = 0; i < num; i++) {
		cout << " " << ary[i];
		if (i != num - 1) {
			cout << ",";
		}
	}
	cout << " }" << endl;
}

int Sorting::select(int data[], int p, int r, int i) {	
	int *tempAry = new int[r - p + 1];
	int pvIndex = -1;

	for (int j = 0; j < r - p + 1; j++) {
		tempAry[j] = data[p + j];
	}

	mergeSort(tempAry, 0, r - p);

	for (int j = 0; j < r - p + 1; j++) {
		if (tempAry[i - 1] == data[p+j]) {
			pvIndex = p + j;
			break;
		}
	}
	return pvIndex;
}

float Sorting::percent(int data[], int p, int r, int pivot) {
	int *tempAry = new int[r - p + 1];
	int dsize = r- p + 1;
	float percent = -1;

	for (int j = 0; j < r - p + 1; j++) {
		tempAry[j] = data[p + j];
	}

	mergeSort(tempAry, 0, r - p);

	for (int j = 0; j < dsize; j++) {
		if (tempAry[j] == pivot) {
			percent = (float)(j + 1) / dsize * 100.0;
			break;
		}
	}
	cout << percent << " %, " << endl;
	return percent;
}