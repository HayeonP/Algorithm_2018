#include "Station.h"

Station::Station(string _name, int _transfers[], vector<string> _prev, vector<string> _next) {
	name = _name;
	for (int i = 0; i < TRANSFER_NUM; i++) {
		transfers[i] = _transfers[i];
		prev.push_back(_prev[i]);
		next.push_back(_next[i]);
	}
}

void Station::printName() {
	cout << "�� �� : " << name<<endl;
}

void Station::printTransfers() {
	cout << "ȯ �� : ";
	for (int i = 0; i < TRANSFER_NUM; i++) {
		cout << transfers[i] << " ";
	}
	cout << endl;
}

void Station::printPrev() {
	cout << "������ : ";
	for (int i = 0; i < TRANSFER_NUM; i++) {
		cout << prev[i] << " ";
	}
	cout << endl;
}

void Station::printNext() {
	cout << "������ : ";
	for (int i = 0; i < TRANSFER_NUM; i++) {
		cout << next[i] << " ";
	}
	cout << endl;
}
