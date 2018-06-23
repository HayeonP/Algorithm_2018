#include "Metro.h"

int main() {
	Metro metro;


	metro.DijkstraPath("³»¹æ", "¼±¸ª", metro.getTime(10, 0));
	metro.BellmanPath("³»¹æ", "¼±¸ª", metro.getTime(10,0));

	metro.DijkstraPath("³»¹æ", "µµ°î", metro.getTime(10, 10));
	metro.BellmanPath("³»¹æ", "µµ°î", metro.getTime(10, 10));

	return 0;
}
