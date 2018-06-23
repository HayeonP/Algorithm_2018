#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <algorithm>
#include <deque>

#define BUF_SIZE 16
#define TRAIN2 0
#define TRAIN3 1
#define TRAIN4 2
#define TRAIN7 3
#define TRAIN9 4
#define TRAIN_BUNDANG 5
#define TRANSFER_NUM 6
#define TRANSFER_TIME 5
#define MOVE_TIME 5
#define STOP_TIME 1
#define TIME_TABLE_NUM 144
#define INFINITE 9999
#define PREV 0
#define NEXT 1


using namespace std;

class Station {
public:
	Station() : name("0"), transfers(), prev(), next() {};
	Station(string _name, int _transfers[], vector<string> _prev, vector<string> _next);
	string getName() { return name; };
	void printName();
	void printTransfers();
	void printPrev();
	void printNext();

	int transfers[TRANSFER_NUM];
	vector<string> prev;
	vector<string> next;
	int toNextTable[TRANSFER_NUM][TIME_TABLE_NUM];
	int toPrevTable[TRANSFER_NUM][TIME_TABLE_NUM];
private:
	string name;
	
};
