#include "Metro.h"

int main() {
	Metro metro;


	metro.DijkstraPath("����", "����", metro.getTime(10, 0));
	metro.BellmanPath("����", "����", metro.getTime(10,0));

	metro.DijkstraPath("����", "����", metro.getTime(10, 10));
	metro.BellmanPath("����", "����", metro.getTime(10, 10));

	return 0;
}
