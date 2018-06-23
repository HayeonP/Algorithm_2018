#include "myGraph.h"

MyVertex<MyEdge> 서울("서울");
MyVertex<MyEdge> 인천("인천");
MyVertex<MyEdge> 원주("원주");
MyVertex<MyEdge> 강릉("강릉");
MyVertex<MyEdge> 전주("전주");
MyVertex<MyEdge> 대전("대전");
MyVertex<MyEdge> 대구("대구");
MyVertex<MyEdge> 광주("광주");
MyVertex<MyEdge> 부산("부산");

void makeGraph(MyGraph< MyVertex<MyEdge> >& graph);

int main() {
	MyGraph< MyVertex<MyEdge> > graph;
	
	makeGraph(graph);
	//graph.printGraph();

	cout << "[ Brute-Force ]" << endl;
	graph.bruteTSP("서울");
	
	cout << "[ Dynamic Programig ] " << endl;
	graph.dpTSP3("서울");
	return 0;
}

void makeGraph(MyGraph< MyVertex<MyEdge> >& graph){
	서울.setIdx(_서울);
	인천.setIdx(_인천);
	원주.setIdx(_원주);
	강릉.setIdx(_강릉);
	전주.setIdx(_전주);
	대전.setIdx(_대전);
	대구.setIdx(_대구);
	광주.setIdx(_광주);
	부산.setIdx(_부산);

	서울.addEdge(MyEdge(35, &인천));
	서울.addEdge(MyEdge(126, &원주));
	서울.addEdge(MyEdge(233, &전주));
	서울.addEdge(MyEdge(150, &대전));

	인천.addEdge(MyEdge(35, &서울));
	인천.addEdge(MyEdge(247, &전주));

	원주.addEdge(MyEdge(126, &서울));
	원주.addEdge(MyEdge(162, &대전));
	원주.addEdge(MyEdge(220, &대구));
	원주.addEdge(MyEdge(313, &부산));
	원주.addEdge(MyEdge(117, &강릉));

	강릉.addEdge(MyEdge(117, &원주));
	강릉.addEdge(MyEdge(255, &대구));
	강릉.addEdge(MyEdge(343, &부산));

	전주.addEdge(MyEdge(247, &인천));
	전주.addEdge(MyEdge(233, &서울));
	전주.addEdge(MyEdge(82, &대전));
	전주.addEdge(MyEdge(98, &광주));

	대전.addEdge(MyEdge(150, &서울));
	대전.addEdge(MyEdge(162, &원주));
	대전.addEdge(MyEdge(154, &대구));
	대전.addEdge(MyEdge(120, &광주));
	대전.addEdge(MyEdge(82, &전주));

	대구.addEdge(MyEdge(220, &원주));
	대구.addEdge(MyEdge(255, &강릉));
	대구.addEdge(MyEdge(106, &부산));
	대구.addEdge(MyEdge(206, &광주));
	대구.addEdge(MyEdge(154, &대전));

	광주.addEdge(MyEdge(98, &전주));
	광주.addEdge(MyEdge(120, &대전));
	광주.addEdge(MyEdge(206, &대구));
	광주.addEdge(MyEdge(242, &부산));

	부산.addEdge(MyEdge(343, &강릉));
	부산.addEdge(MyEdge(313, &원주));
	부산.addEdge(MyEdge(106, &대구));
	부산.addEdge(MyEdge(242, &광주));

	// 인덱스 순서대로 넣을 것
	graph.addVertex(서울);
	graph.addVertex(인천);
	graph.addVertex(원주);
	graph.addVertex(강릉);
	graph.addVertex(전주);
	graph.addVertex(대전);
	graph.addVertex(대구);
	graph.addVertex(광주);
	graph.addVertex(부산);
	

	graph.createEdgeWeights();
}