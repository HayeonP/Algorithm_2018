#pragma once
#include "Station.h"

typedef vector<Station>::iterator sIter;
typedef vector<int>::iterator intIter;
typedef vector<string>::iterator strIter;


class Metro {
	
public:
	friend Station;
	Metro();
	void initTrainVec();
	void initTimeTable();
	void setTime(int startTable[], int transferIndex);
	void printMetro();
	void setStationNum(int num) { stationNum = num; };
	string getTransferName(int num);
	int getTransferNum(string _name);
	sIter findStation(string _name);
	sIter getFirst(string _name);
	sIter getLast(string _name);
	void printTime(int time);
	int getTime(int hour, int minute);
	int findIdx(string data);

	void DijkstraPath(string start, string goal, int startTime); // 다익스트라로 최소 경로 찾기
	string extractMin(vector<string> stationList, vector<int> distance);
	void BellmanPath(string start, string goal, int startTime);

	vector<Station> metroMap;
	int stationNum;
	vector<sIter> first;
	vector<sIter> last;
	vector<sIter> train2;
	vector<sIter> train3;
	vector<sIter> train4;
	vector<sIter> train7;
	vector<sIter> train9;
	vector<sIter> trainB;
};