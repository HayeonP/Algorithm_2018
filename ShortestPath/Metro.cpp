#include "Metro.h"

Metro::Metro() {
	vector<string> stationName;
	int num;

	ifstream data("data.txt");
	if (data.is_open()) {
		data >> num;
	}
	else {
		cout << " NO FILE!" << endl;
	}

	string s;
	string name;
	string transferFlag = "(";
	int transferAry[TRANSFER_NUM];


	// 이름, 환승정보, 이전역, 다음역 초기화
	for (int i = 0; i < num + TRANSFER_NUM; i++) {
		data >> s; // 역명
		if (s.find(transferFlag) != string::npos) continue;/*{
			cout << s << endl;
		}*/
		else {

			// 역명, 환승정보 추가
			name = s;
			for (int j = 0; j < TRANSFER_NUM; j++) {
				data >> s;
				transferAry[j] = stoi(s);
			}

			// 이전역
			vector<string> tempPrev;
			for (int j = 0; j < TRANSFER_NUM; j++) {
				data >> s;
				tempPrev.push_back(s);
			}

			// 다음역
			vector<string> tempNext;
			for (int j = 0; j < TRANSFER_NUM; j++) {
				data >> s;
				tempNext.push_back(s);
			}

			metroMap.emplace_back(name, transferAry, tempPrev, tempNext);

			// 중복되는 역 삭제
			vector<Station>::iterator itr = metroMap.begin();
			for (; itr != metroMap.end() - 1; ++itr) {
				if ((*itr).getName() == name) {
					metroMap.pop_back();
					break;
				}
			}
		}
	}
	data.close();

	stationNum = metroMap.size();

	first.push_back(findStation("사당"));
	first.push_back(findStation("충무로"));
	first.push_back(findStation("서울역"));
	first.push_back(findStation("이수"));
	first.push_back(findStation("동작"));
	first.push_back(findStation("왕십리"));

	last.push_back(findStation("건대입구"));
	last.push_back(findStation("도곡"));
	last.push_back(findStation("사당"));
	last.push_back(findStation("건대입구"));
	last.push_back(findStation("종합운동장"));
	last.push_back(findStation("도곡"));

	initTrainVec();
	initTimeTable();
}

void Metro::initTrainVec() {
	sIter temp;
	string lastName;
	
	temp = getFirst("2호선");
	lastName = last[TRAIN2]->getName();
	while (1) {
		train2.push_back(temp);
		if (temp->getName() == lastName) break;
		temp = findStation(temp->next[TRAIN2]);		
	}

	temp = getFirst("3호선");
	lastName = last[TRAIN3]->getName();
	while (1) {
		train3.push_back(temp);
		if (temp->getName() == lastName) break;
		temp = findStation(temp->next[TRAIN3]);
	}

	temp = getFirst("4호선");
	lastName = last[TRAIN4]->getName();
	while (1) {
		train4.push_back(temp);
		if (temp->getName() == lastName) break;
		temp = findStation(temp->next[TRAIN4]);
	}
	
	temp = getFirst("7호선");
	lastName = last[TRAIN7]->getName();
	while (1) {
		train7.push_back(temp);
		if (temp->getName() == lastName) break;
		temp = findStation(temp->next[TRAIN7]);
	}
	
	temp = getFirst("9호선");
	lastName = last[TRAIN9]->getName();
	while (1) {
		train9.push_back(temp);
		if (temp->getName() == lastName) break;
		temp = findStation(temp->next[TRAIN9]);
	}
	
	temp = getFirst("분당선");
	lastName = last[TRAIN_BUNDANG]->getName();
	while (1) {
		trainB.push_back(temp);
		if (temp->getName() == lastName) break;
		temp = findStation(temp->next[TRAIN_BUNDANG]);
	}
}

void Metro::initTimeTable() {
	int startTable[TIME_TABLE_NUM];
	sIter temp;
	sIter before;
	startTable[0] = 0;
	
	// Timetable 시작값 세팅
	for (int i = 1; i < TIME_TABLE_NUM; i++) {
		startTable[i] = startTable[i - 1] + 10;
	}

	setTime(startTable, TRAIN2);
	setTime(startTable, TRAIN3);
	setTime(startTable, TRAIN4);
	setTime(startTable, TRAIN7);
	setTime(startTable, TRAIN9);
	setTime(startTable, TRAIN_BUNDANG);
}

void Metro::setTime(int startTable[], int transferIndex) {
	sIter temp;
	sIter before;

	// next 방향
	temp = first[transferIndex];
	for (int i = 0; i < TIME_TABLE_NUM; i++) {
		temp->toNextTable[transferIndex][i] = startTable[i];
	}

	while (temp != last[transferIndex]) {
		before = temp;
		temp = findStation(temp->next[transferIndex]);
		for (int i = 0; i < TIME_TABLE_NUM; i++) {
			if (before->toNextTable[transferIndex][i] == INFINITE) {
				temp->toNextTable[transferIndex][i] = INFINITE;
				continue;
			}
			int time = before->toNextTable[transferIndex][i] + 6;
			if (time > 1440) temp->toNextTable[transferIndex][i] = INFINITE;
			else temp->toNextTable[transferIndex][i] = time;
		}
	}

	// prev 방향
	temp = last[transferIndex];
	for (int i = 0; i < TIME_TABLE_NUM; i++) {
		temp->toPrevTable[transferIndex][i] = startTable[i];
	}

	while (temp != first[transferIndex]) {
		before = temp;
		temp = findStation(temp->prev[transferIndex]);
		for (int i = 0; i < TIME_TABLE_NUM; i++) {
			if (before->toPrevTable[transferIndex][i] == INFINITE) {
				temp->toPrevTable[transferIndex][i] = INFINITE;
				continue;
			}
			int time = before->toPrevTable[transferIndex][i] + 6;
			if (time > 1440) temp->toPrevTable[transferIndex][i] = INFINITE;
			else temp->toPrevTable[transferIndex][i] = time;
		}
	}
}

void Metro::printMetro() {
	
	for (int i = 0; i < TRANSFER_NUM; i++) {
		cout << "[ " << getTransferName(i) << " ]" << endl;
		vector<Station>::iterator itr = metroMap.begin();
		for (; itr != metroMap.end(); ++itr) {
			if ((*itr).transfers[i] == 1) {
				cout << "역 명 : " << (*itr).getName() << " / ";
				for (int j = 0; j < TRANSFER_NUM; j++) {
					if ((*itr).transfers[j] == 1) {
						cout << getTransferName(j) << " ";
					}
				}
				cout << endl;
			}
		}
	}
}

string Metro::getTransferName(int num) {
	string transferName;
	switch (num) {
	case 0:
		transferName = "2호선";
		break;
	case 1:
		transferName = "3호선";
		break;
	case 2:
		transferName = "4호선";
		break;
	case 3:
		transferName = "7호선";
		break;
	case 4:
		transferName = "9호선";
		break;
	case 5:
		transferName = "분당선";
		break;
	}
	return transferName;
}

int Metro::getTransferNum(string _name) {
	if (_name == "2호선") return TRAIN2;
	else if (_name == "3호선") return TRAIN3;
	else if (_name == "4호선") return TRAIN4;
	else if (_name == "7호선") return TRAIN7;
	else if (_name == "9호선") return TRAIN9;
	else if (_name == "3호선") return TRAIN3;
	else return TRAIN_BUNDANG;
}

sIter Metro::findStation(string _name) {
	vector<Station>::iterator itr = metroMap.begin();
	for (; itr != metroMap.end(); ++itr) {
		if ((*itr).getName() == _name) {
			return itr;
		}
	}
	return metroMap.end();
}

sIter Metro::getFirst(string _name) {
	return first[getTransferNum(_name)];
}

sIter Metro::getLast(string _name) {
	return last[getTransferNum(_name)];
}

void Metro::printTime(int time) {
	if (time == INFINITE) {
		cout << "운행불가" << endl;
		return;
	}
	int hour = time / 60;
	int minute = time - 60 * hour;
	cout << hour << "시 " << minute << "분" << endl;
}

int Metro::getTime(int hour, int minute) {
	return hour * 60 + minute;
}

int Metro::findIdx(string data) {
	int idx = 0;

	for (sIter iter = metroMap.begin(); iter != metroMap.end(); ++iter) {
		if ((*iter).getName() == data) return idx;
		else idx++;
	}
	return -1;
}

void Metro::DijkstraPath(string start, string goal, int startTime) {

	vector< vector<string> > stationList;
	vector< vector<string> > visited; // 방문한 노드
	vector< vector<int> > distance; // 출발점부터 각 노드 까지의 거리합
	vector< vector<string> > prevPath; // 이전역

	sIter startStation = findStation(start);
	int startDirectionNum = 0;
	vector<string> secondStation;

	// path 출발 방향 및 두번째 정거장 찾기
	for (strIter iter = startStation->prev.begin(); iter != startStation->prev.end(); ++iter) {
		if ((*iter) != "0") {
			startDirectionNum++;
			secondStation.push_back((*iter));
		}
	}
	for (strIter iter = startStation->next.begin(); iter != startStation->next.end(); ++iter) {
		if ((*iter) != "0") {
			startDirectionNum++;
			secondStation.push_back((*iter));
		}
	}

	// stationList, distance, prevPath 초기화
	for (int i = 0; i < startDirectionNum; i++) {
		vector<string> tempStationList;
		vector<int> tempDistance;
		vector<string> tempPrevPath;

		for (sIter iter = metroMap.begin(); iter != metroMap.end(); ++iter) {
			tempStationList.push_back((*iter).getName());
			tempDistance.push_back(INFINITE);
			tempPrevPath.push_back("0");
		}
		stationList.push_back(tempStationList);
		distance.push_back(tempDistance);
		prevPath.push_back(tempPrevPath);
	}

	// 시작점 cost 세팅, 두번째역 방문
	for (int i = 0; i < startDirectionNum; i++) {
		sIter tempStation = findStation(start);
		string tempSecondStationName = secondStation[i];
		int boardingTime = INFINITE;

		for (int j = 0; j < TRANSFER_NUM; j++) { // j = 다음역의 호선
			sIter tempSecondStation;

			if ((tempStation->prev[j]) == tempSecondStationName) {
				for (int k = 0; k < TIME_TABLE_NUM; k++) {
					if (tempStation->toPrevTable[j][k] > startTime) {
						boardingTime = tempStation->toPrevTable[j][k];
						break;
					}
				}
				if (boardingTime != INFINITE) break;
			}
			else if ((tempStation->next[j]) == tempSecondStationName) {
				for (int k = 0; k < TIME_TABLE_NUM; k++) {
					if (tempStation->toNextTable[j][k] > startTime) {
						boardingTime = tempStation->toNextTable[j][k];
						break;
					}
				}
				if (boardingTime != INFINITE) break;
			}
		}
		distance[i][findIdx(start)] = boardingTime - startTime;
		distance[i][findIdx(secondStation[i])] = distance[i][findIdx(start)] + MOVE_TIME + STOP_TIME;
		stationList[i][findIdx(start)] = "0";

		vector<string> tempVisit;
		tempVisit.push_back(start);
		visited.push_back(tempVisit);

		prevPath[i][findIdx(secondStation[i])] = start;
	}

	for (int i = 0; i < startDirectionNum; i++) {
		string u;
		while (visited[i].size() != stationNum) {
			u = extractMin(stationList[i], distance[i]);
			if (u == "ERROR") {
				break;
			}
			stationList[i][findIdx(u)] = "0";
			visited[i].push_back(u);

			sIter currentStation = findStation(u);
			vector<string> adjacentStation;

			// 인접 역 리스트 생성
			for (auto iter = currentStation->prev.begin(); iter != currentStation->prev.end(); ++iter) {
				if ((*iter) != "0") {
					adjacentStation.push_back((*iter));
				}
			}
			for (auto iter = currentStation->next.begin(); iter != currentStation->next.end(); ++iter) {
				if ((*iter) != "0") {
					adjacentStation.push_back((*iter));
				}
			}
			
			// 값 갱신
			for (auto iter = adjacentStation.begin(); iter != adjacentStation.end(); ++iter) {				
				if (stationList[i][findIdx(*iter)] == "0") continue;

				int distU = distance[i][findIdx(u)];
				int distAdj = distance[i][findIdx(*iter)];
				int cost = 0;
				int weight;

				int prevTransferNum;
				int currentTransferNum;
				sIter stationU = findStation(u);
				sIter stationPrev = findStation(prevPath[i][findIdx(u)]);
				int direction = -1;

				// 이전, 현재 호선 획득
				for (int j = 0; j < TRANSFER_NUM; j++) {
					if (stationPrev->prev[j] == u) {
						prevTransferNum = j;
					}
					else if (stationPrev->next[j] == u) {
						prevTransferNum = j;
					}

					if (stationU->prev[j] == (*iter)) {
						currentTransferNum = j;
						direction = PREV;
					}
					else if (stationU->next[j] == (*iter)) {
						currentTransferNum = j;
						direction = NEXT;
					}
				}


				// weight 구하기				
				if (prevTransferNum == currentTransferNum) {
					weight = MOVE_TIME + STOP_TIME;
				}
				else {
					int boardingTime = INFINITE;

					cost = distU + MOVE_TIME + TRANSFER_TIME;
					if (direction == PREV) {
						for (int j = 0; j < TIME_TABLE_NUM; j++) {
							if (stationU->toPrevTable[currentTransferNum][j] >= cost) {
								boardingTime = stationU->toPrevTable[currentTransferNum][j];
								break;
							}
						}
					}
					else if (direction == NEXT) {
						for (int j = 0; j < TIME_TABLE_NUM; j++) {
							if (stationU->toNextTable[currentTransferNum][j] >= cost) {
								boardingTime = stationU->toNextTable[currentTransferNum][j];
								break;
							}
						}
					}

					if (boardingTime == INFINITE) {
						cout << " boardint TIme Error ! ";
						exit(1);
					}

					int waitTime = boardingTime - cost;
					//weight = waitTime + MOVE_TIME + TRANSFER_TIME + STOP_TIME;
					weight = 11;
				}

				if ((distU + weight < distAdj)) {
					distAdj = distU + weight;
					distance[i][findIdx(*iter)] = distAdj;
					prevPath[i][findIdx(*iter)] = u;
				}
			}
		}
	}

	int minIdx = INFINITE;
	int minCost = INFINITE;
	for (int i = 0; i < startDirectionNum; i++) {
		int cost = distance[i][findIdx(goal)];
		if (minCost > cost) {
			minCost = cost;
			minIdx = i;
		}
	}

	string pathStr = goal;
	deque<string> path;
	while (pathStr != start) {
		path.push_front(pathStr);
		pathStr = prevPath[minIdx][findIdx(pathStr)];
	}
	path.push_front(start);

	cout << "< Dijkstra Path >" << endl;
	for (auto iter = path.begin(); iter != path.end(); ++iter) {
		cout << "- " << (*iter) << endl;
	}
	cout << "Number of node : " << path.size()<<endl;
}

string Metro::extractMin(vector<string> stationList, vector<int> distance) {
	int min = INFINITE;
	int idx = 0;
	string u = "ERROR";

	for (strIter iter = stationList.begin(); iter != stationList.end(); ++iter) {
		if ((*iter) == "0") continue;
		idx = findIdx(*iter);
		if (distance[idx] < min) {
			min = distance[idx];
			u = stationList[idx];
		}
	}

	return u;
}

void Metro::BellmanPath(string start, string goal, int startTime) {
	vector<string> stationList;
	vector<int> distance; // 출발점부터 각 노드 까지의 거리합
	vector<string> prevPath; // 이전역
	int** edgeList;
	int beforeTime = 0;
	int currentTime;

	for (int i = 0; i < stationNum; i++) {
		stationList.push_back(metroMap[i].getName());
		distance.push_back(INFINITE);
		prevPath.push_back("0");
	}
	distance[findIdx(start)] = 0;

	edgeList = new int*[stationNum];
	for (int i = 0; i < stationNum; i++) {
		edgeList[i] = new int[stationNum];
	}

	
	for (int i = 0; i < stationNum - 1; i++) {
		// EDGE 생성
		int beforeTransferNum;
		for (int j = 0; j < stationNum; j++) {
			for (int k = 0; k < stationNum; k++) {
				int afterTransferNum = INFINITE;
				sIter startStation = findStation(metroMap[j].getName());
				sIter arriveStation = findStation(metroMap[k].getName());
				sIter prevStation;
				int tempEdge = INFINITE;

				if (i == 0 ) {
					for (int l = 0; l < TRANSFER_NUM; l++) {
						// PREV방향
						if ((startStation->prev[l]) == (arriveStation->getName())) {
							tempEdge = 6;
						}
						// NEXT 방향
						else if ((startStation->next[l]) == (arriveStation->getName())) {
							tempEdge = 6;
						}
					}
				}
				else {
					for (int l = 0; l < TRANSFER_NUM; l++) {
						// PREV방향
						if ((startStation->prev[l]) == (arriveStation->getName())) {
							afterTransferNum = l;
							if (afterTransferNum == beforeTransferNum)
								tempEdge = 6;
							else tempEdge = 11;
						}
						// NEXT 방향
						else if ((startStation->next[l]) == (arriveStation->getName())) {
							afterTransferNum = l;
							if (afterTransferNum == beforeTransferNum)
								tempEdge = 6;
							else tempEdge = 11;
						}
					}
				}
				beforeTransferNum = afterTransferNum;
				edgeList[j][k] = tempEdge;
				/*if (tempEdge != INFINITE) cout << edgeList[j][k] << " ";
				else cout << -1 << " ";*/
			}
			//cout << endl;
		}
		
		for (int j = 0; j < stationNum; j++) {
			for (int k = 0; k < stationNum; k++) {
				if (edgeList[j][k] == INFINITE) continue;
				if (distance[j] + edgeList[j][k] < distance[k]) {
					distance[k] = distance[j] + edgeList[j][k];
					string prevStationName = metroMap[j].getName();
					string nextStationName = metroMap[k].getName();
					prevPath[findIdx(nextStationName)] = prevStationName;
				}
			}
		}
	}


	string pathStr = goal;
	deque<string> path;
	while (pathStr != start) {
		path.push_front(pathStr);
		pathStr = prevPath[findIdx(pathStr)];
	}
	path.push_front(start);

	cout << "< Bellamn Path >" << endl;
	for (auto iter = path.begin(); iter != path.end(); ++iter) {
		cout << "- " << (*iter) << endl;
	}
	cout << "Number of node : " << path.size() << endl;

	for (int i = 0; i < stationNum; i++) {
		delete[] edgeList[i];
	}
	delete[] edgeList;
}

	

