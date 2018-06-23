#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <time.h>

#define _서울 0
#define _인천 1
#define _원주 2
#define _강릉 3
#define _전주 4
#define _대전 5
#define _대구 6
#define _광주 7
#define _부산 8
#define INFINITE 999999

#define swap(a,b,temp) temp = a; a = b; b = temp;

clock_t before;
clock_t after;
clock_t result;

using namespace std;

template<typename T>
class MyVertex {
public:
	MyVertex(string n);
	MyVertex(string n, T e);
	void addEdge(T e);
	void setIdx(int i) { idx = i; };
	string getName() { return name; };
	int getIdx() { return idx; };
	void printVertex();
	
	deque<T> edges;
private:
	string name;
	int idx = -1;	
};

class MyEdge {
public:
	MyEdge();
	MyEdge(int c, MyVertex<MyEdge>* op);
	int cost;
	MyVertex<MyEdge>* opponent;
};

MyEdge::MyEdge() {
	cost = 0;
	opponent = NULL;
}

MyEdge::MyEdge(int c, MyVertex<MyEdge>* op) {
	cost = c;
	opponent = op;
}

template <typename T>
MyVertex<T>::MyVertex(string n) {
	name = n;
	edges.push_back(MyEdge());
}

template <typename T>
MyVertex<T>::MyVertex(string n, T e) {
	name = n;
	edges.push_back(e);
}


template <typename T>
void MyVertex<T>::addEdge(T e) {
	if (edges.front().cost == 0) edges.pop_front();
	edges.push_back(e);
}

template <typename T>
void MyVertex<T>::printVertex() {
	cout << "< " << name << " > (" << idx<<")"<<endl;	
	for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
		cout << (*iter).opponent->name<<"(" << (*iter).cost << ")\t";
	}
	cout << endl;
}