#pragma once
#include "MyVertex.h"

typedef deque< MyVertex<MyEdge> >::iterator itVtx;

void Permutation(deque<int> a, const int k, const int m, deque< deque<int> >& path);
void createSubset(deque<int> data, deque<int> flag, int initDepth, int depth, deque< deque<int> >& subsetList);

template<typename T>
class MyGraph {
public:
	MyGraph();
	void addVertex(MyVertex<MyEdge> v);
	void deleteVertex(MyVertex<MyEdge> v);
	bool isEmpty();
	int getNum() { return num; };
	itVtx getItByName(string name);
	itVtx getItByIdx(int _idx);
	void printGraph();
	void bruteTSP(string start);
	void dpTSP3(string start);
	int calCost(deque<int> path, deque<int> adj, int startIdx);
	int calCostDp(deque<int> path, int startIdx, int endIdx);
	void createEdgeWeights();
	int getSubsetIdx(deque<int> subset, deque< deque<int> > list);
private:
	deque<T> nodes;
	deque<string> nodeNames;
	deque< deque<int> > edgeWeights;
	int num;
};

template <typename T>
MyGraph<T>::MyGraph() {
	num = 0;
}

template <typename T>
void MyGraph<T>::addVertex(MyVertex<MyEdge> v) {
	itVtx iter = getItByName(v.getName());
	if (iter == nodes.end()) {
		nodes.push_back(v);
		nodeNames.push_back(v.getName());
		num++;
	}
	else
		cout << v.getName() << " is already exist." << endl;
}

template <typename T>
void MyGraph<T>::deleteVertex(MyVertex<MyEdge> v) {
	itVtx iter = getIt(v.getName());
	if (iter == nodes.end())
		cout << v.getName() << " is not exist." << endl;
	else {
		nodes.erase(iter);
		num--;
	}
}

template <typename T>
bool MyGraph<T>::isEmpty() {
	return nodes.empty();
}

template <typename T>
itVtx MyGraph<T>::getItByIdx(int _idx) {
	for (auto iter = nodes.begin(); iter != nodes.end(); ++iter) {
		if ((*iter).getIdx() == _idx) return iter;
	}
	return nodes.end();
}

template <typename T>
itVtx MyGraph<T>::getItByName(string name) {
	for (auto iter = nodes.begin(); iter != nodes.end(); ++iter) {
		if ((*iter).getName() == name) return iter;
	}
	return nodes.end();
}

template <typename T>
void MyGraph<T>::printGraph() {
	cout << "Number of nodes : " << num << endl << endl;

	for (auto iter = nodes.begin(); iter != nodes.end(); ++iter) {
		(*iter).printVertex();
		cout << endl;
	}
}

template <typename T>
void MyGraph<T>::bruteTSP(string start) {

	before = clock();
	itVtx startIt = getItByName(start);
	if (startIt == nodes.end()) {
		cout << "Start node name is wrong!" << endl;
		return;
	}

	int startIdx = (*startIt).getIdx();

	deque<int> adjacent; // start노드와의 인접 노드
	for (auto iter = (*startIt).edges.begin(); iter != (*startIt).edges.end(); ++iter){
		adjacent.push_back((*iter).opponent->getIdx());
	}

	deque<int> pathData;
	for (int i = 0; i < num; i++)
		pathData.push_back(i);

	deque< deque <int> > path;
	Permutation(pathData, 0, pathData.size() - 1, path);

	deque<int> cost;
	deque<int> minPath;

	int min = INFINITE;
	for (auto iter = path.begin(); iter != path.end(); ++iter) {
		cost.push_back(calCost((*iter), adjacent, startIdx));
		int temp = cost.back();

		if ( (temp != -1) && (min > temp) ) {
			minPath = (*iter);
			min = temp;
		}
	}
	after = clock();
	result = after - before;

	cout << "Cost : " << min << endl;
	cout << "Path : ";
	for (auto iter = minPath.begin(); iter != minPath.end(); iter++) {
		cout << nodeNames[*iter] << " ";
	}
	cout << endl;
	cout << "Time : " << (double)result / CLOCKS_PER_SEC << endl;
}

template <typename T>
void MyGraph<T>::dpTSP3(string start) {
	before = clock();
	itVtx startIt = getItByName(start);
	if (startIt == nodes.end()) {
		cout << "Start node name is wrong!" << endl;
		return;
	}
	int startIdx = (*startIt).getIdx();
	deque<int> Vset;
	for (int i = 0; i < num; i++)
		Vset.push_back(1);

	deque<int> data;
	deque<int> flag;
	for (int i = 0; i < num; i++) {
		if (i == startIdx) continue;
		data.push_back(i);
		flag.push_back(1);
	}

	// Subset 생성 ( D의 행 생성 )
	deque< deque<int> > subsetList;
	deque<int> emptySubset;
	emptySubset.push_back(-1);
	subsetList.push_back(emptySubset);

	createSubset(data, flag, 0, data.size() - 1, subsetList);
	while (1) {
		if (data.size() == 1) break;
		data.pop_front();
		flag.pop_front();
		for (unsigned int j = 0; j < data.size(); j++)
			flag[j] = 1;

		createSubset(data, flag, 0, data.size() - 1, subsetList);
	}

	// D 동적할당
	int** D = new int*[num];
	int** P = new int*[num];
	for (int i = 0; i < num; i++) {
		D[i] = new int[subsetList.size() + 1];
		P[i] = new int[subsetList.size() + 1];
	}

	// D 초기화
	for (int i = 0; i < num; i++) {
		for (int j = 0; j <= subsetList.size(); j++) {
			D[i][j] = INFINITE;
		}
	}
	for(int i = 0; i < num; i++){
		D[i][0] = edgeWeights[i][0];
	}

	// P 초기화
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < subsetList.size(); j++)
			P[i][j] = -1;
	}

	deque<int> A_start;
	for (int i = 0; i < num; i++)
		if (i != startIdx) A_start.push_back(i);

	for (int k = 0; k < num - 2; k++) {
		deque< deque<int> > kSubset;
		for (auto iter = subsetList.begin() + 1; iter != subsetList.end(); ++iter) {
			if ((*iter).size() == k + 1)
				kSubset.push_back((*iter));
		}

		// A : 원소가 K개인 벡터
		for (auto A = kSubset.begin(); A != kSubset.end(); ++A) {
			
			deque<int> notInA;
			for (int i = 0; i < num; i++) {
				if (i == startIdx) continue;
				bool flag = true;
				for (auto iter = (*A).begin(); iter != (*A).end(); ++iter)
					if (i == (*iter)) flag = false;
				if (flag == true) notInA.push_back(i);
			}

			int Aidx = getSubsetIdx(*A, subsetList);

			for (auto I = notInA.begin(); I != notInA.end(); ++I) {

				int min = INFINITE;
				int jMin;

				for (auto J = (*A).begin(); J != (*A).end(); ++J) {
					deque<int> A_J;
					for (auto iter = (*A).begin(); iter != (*A).end(); ++iter) {
						if ((*iter) == startIdx || (*iter) == *J) continue;
						A_J.push_back(*iter);
					}

					int temp;
					if (A_J.empty()) {
						temp = edgeWeights[*I][*J] + D[*J][0];
					}
					else {
						temp = edgeWeights[*I][*J] + D[*J][getSubsetIdx(A_J, subsetList)];
						
					}

					if (temp < min && temp > 0) {
						min = temp;
						
						jMin = *J;
					}
				}
				D[*I][Aidx] = min;
				P[*I][Aidx] = jMin;

			}
		}
	}

	deque<int>  A_1;
	int min = INFINITE;
	int jMin = -1;

	for (int i = 0; i < num; i++) {
		if (i == startIdx) continue;
		A_1.push_back(i);
	}

	

	for (int j = 0; j < num; j++) {
		if (j == startIdx) continue;

		deque<int> A_1_J;
		for (int i = 0; i < num; i++) {
			if (i == startIdx || i == j) continue;
			A_1_J.push_back(i);
		}
	
		int temp;
		temp = edgeWeights[startIdx][j] + D[j][getSubsetIdx(A_1_J, subsetList)];

		if (temp < min) {
			min = temp;
			jMin = j;
		}
	}

	D[startIdx][getSubsetIdx(A_1,subsetList)] = min;

	P[startIdx][getSubsetIdx(A_1, subsetList)] = jMin;
	after = clock();

	result = after - before;

	cout << "Cost : " << D[startIdx][getSubsetIdx(A_1, subsetList)] << endl;


	int checkPoint = startIdx;

	cout << "Path : ";
	cout << (*getItByIdx(checkPoint)).getName() << " ";

	deque<int> tempList;
	for (int i = 0; i < num; i++) {
		if (i != startIdx)
			tempList.push_back(i);
	}

	for (auto iter = tempList.begin(); iter != tempList.end(); ++iter){
		checkPoint = P[checkPoint][getSubsetIdx(tempList, subsetList)];
		if (checkPoint < 0 || checkPoint >= num) 
			break;
		tempList.erase(std::find(tempList.begin(), tempList.end(), checkPoint));

		cout << (*getItByIdx(checkPoint)).getName() << " ";
	}
	cout << endl;
	cout << "Time : " << (double)result / CLOCKS_PER_SEC<<endl;


	for (int i = 0; i < num; i++) {
		delete[] D[i];
		delete[] P[i];
	}

	delete[] D;
	delete[] P;

	return;
}

template <typename T>
int MyGraph<T>::calCost(deque<int> path, deque<int> adj, int startIdx) {
	int cost = 0;
	
	if (path[0] != startIdx) return -1;

	bool loopCheck = false;
	for (auto iter = adj.begin(); iter != adj.end(); ++iter) {
		if (path[num - 1] == (*iter)) loopCheck = true;
	}

	if (loopCheck == false) 
		return -1;
	
	itVtx temp;
	for (int i = 0; i < path.size() - 1; i++) {
		temp = getItByIdx(path[i]);

		bool enable = false;
		for (auto iter = (*temp).edges.begin(); iter != (*temp).edges.end(); ++iter) {
			if ((*iter).opponent->getIdx() == path[i + 1]) {
				cost += (*iter).cost;
				enable = true;
				break;
			}
		}
		if (enable == false) return -1;
	}

	temp = getItByIdx(path.back());

	for (auto iter = (*temp).edges.begin(); iter != (*temp).edges.end(); ++iter) {
		if ((*iter).opponent->getIdx() == startIdx) {
			cost += (*iter).cost;
			break;
		}
		else {
			cout << "Path Error" << endl;
			exit(1);
		}
	}
	
	return cost;
}

template <typename T>
int MyGraph<T>::calCostDp(deque<int> path, int startIdx, int endIdx) {
	int cost = 0;

	//if (path[0] != startIdx) return -1;
	
	itVtx temp;
	for (int i = 0; i < path.size() - 1; i++) {
		temp = getItByIdx(path[i]);

		bool enable = false;
		for (auto iter = (*temp).edges.begin(); iter != (*temp).edges.end(); ++iter) {
			if ((*iter).opponent->getIdx() == path[i + 1]) {
				cost += (*iter).cost;
				enable = true;
				break;
			}
		}
		//if (enable == false) return -1;
		if (enable == false) return INFINITE;
	}

	temp = getItByIdx(path.back());

	bool pathFlag = false;
	for (auto iter = (*temp).edges.begin(); iter != (*temp).edges.end(); ++iter) {
		if ((*iter).opponent->getIdx() == endIdx) {
			cost += (*iter).cost;
			pathFlag = true;
			break;
		}
		else {
			//return -1;
			return INFINITE;
		}
	}
	//if (pathFlag == false) return -1;
	if (pathFlag == false) return INFINITE;

	/*cout << "Path : ";
	for (auto iter = path.begin(); iter != path.end(); ++iter)
		cout << (*getItByIdx((*iter))).getName() << " ";
	cout << endl;
	cout << "cost : " << cost<<endl<<endl;*/
	return cost;
}

template <typename T>
void MyGraph<T>::createEdgeWeights() {

	deque<int> tempEdgeWeights;
	for (int i = 0; i < num; i++) {
		tempEdgeWeights.push_back(INFINITE);
	}

	for (int i = 0; i < num; i++) {
		edgeWeights.push_back(tempEdgeWeights);
	}

	for (int i = 0; i < num; i++) {
		itVtx tempVtx = getItByIdx(i);
		for (auto iter = (*tempVtx).edges.begin(); iter != (*tempVtx).edges.end(); ++iter) {
			edgeWeights[i][(*iter).opponent->getIdx()] = (*iter).cost;			
		}
		edgeWeights[i][i] = 0;
	}

	// Edge 출력
	/*for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			cout << edgeWeights[i][j] << "\t";
		}
		cout << endl;
	}*/
}

template <typename T>
int MyGraph<T>::getSubsetIdx(deque<int> subset, deque< deque<int> > list) {

	int idx = -1;
	for (auto iter = list.begin(); iter != list.end(); ++iter) {
		idx++;
		if ((*iter).size() != subset.size()) continue;
		
		bool flag = true;
		
		for (unsigned int i = 0; i < subset.size(); i++) 
			if (subset[i] != (*iter)[i]) flag = false;

		if (flag == true) return idx;
	}

	return -1;
}

void Permutation(deque<int> a, const int k, const int m, deque< deque<int> >& path)
{
	int i;
	int temp;

	if (k == m) //순열을 출력
	{
		deque<int> tempPath;
		for (i = 0; i <= m; i++)
		{
			tempPath.push_back(a[i]);
		}
		path.push_back(tempPath);
	}

	else // a[k] a[m]에 있는 여러 순열을 순환적으로 생성
	{
		for (i = k; i <= m; i++)
		{
			swap(a[k], a[i], temp); // a[k]와 a[i]를 교환
			Permutation(a, k + 1, m, path); // a[k+1],...a[m]에 대한 모든 순열
									   // 원래 상태로 되돌리기 위해 a[k]와 a[i]를 다시 교환
			swap(a[k], a[i], temp);
		}

	}

}

void createSubset(deque<int> data, deque<int> flag, int initDepth, int depth, deque< deque<int> >& subsetList){
	if (initDepth == depth) {
		deque<int> tempSubset;
		for (int i = 0; i <= depth; i++) {
			if(flag[depth - i] == 1)
				tempSubset.push_back(data[i]);
		}
		subsetList.push_back(tempSubset);
		
		
		return;
	}

	flag[initDepth] = 0;
	createSubset(data, flag, initDepth + 1, depth, subsetList);
	flag[initDepth] = 1;
	createSubset(data, flag, initDepth + 1, depth, subsetList);
}

