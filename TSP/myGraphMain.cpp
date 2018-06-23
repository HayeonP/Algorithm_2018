#include "myGraph.h"

MyVertex<MyEdge> ����("����");
MyVertex<MyEdge> ��õ("��õ");
MyVertex<MyEdge> ����("����");
MyVertex<MyEdge> ����("����");
MyVertex<MyEdge> ����("����");
MyVertex<MyEdge> ����("����");
MyVertex<MyEdge> �뱸("�뱸");
MyVertex<MyEdge> ����("����");
MyVertex<MyEdge> �λ�("�λ�");

void makeGraph(MyGraph< MyVertex<MyEdge> >& graph);

int main() {
	MyGraph< MyVertex<MyEdge> > graph;
	
	makeGraph(graph);
	//graph.printGraph();

	cout << "[ Brute-Force ]" << endl;
	graph.bruteTSP("����");
	
	cout << "[ Dynamic Programig ] " << endl;
	graph.dpTSP3("����");
	return 0;
}

void makeGraph(MyGraph< MyVertex<MyEdge> >& graph){
	����.setIdx(_����);
	��õ.setIdx(_��õ);
	����.setIdx(_����);
	����.setIdx(_����);
	����.setIdx(_����);
	����.setIdx(_����);
	�뱸.setIdx(_�뱸);
	����.setIdx(_����);
	�λ�.setIdx(_�λ�);

	����.addEdge(MyEdge(35, &��õ));
	����.addEdge(MyEdge(126, &����));
	����.addEdge(MyEdge(233, &����));
	����.addEdge(MyEdge(150, &����));

	��õ.addEdge(MyEdge(35, &����));
	��õ.addEdge(MyEdge(247, &����));

	����.addEdge(MyEdge(126, &����));
	����.addEdge(MyEdge(162, &����));
	����.addEdge(MyEdge(220, &�뱸));
	����.addEdge(MyEdge(313, &�λ�));
	����.addEdge(MyEdge(117, &����));

	����.addEdge(MyEdge(117, &����));
	����.addEdge(MyEdge(255, &�뱸));
	����.addEdge(MyEdge(343, &�λ�));

	����.addEdge(MyEdge(247, &��õ));
	����.addEdge(MyEdge(233, &����));
	����.addEdge(MyEdge(82, &����));
	����.addEdge(MyEdge(98, &����));

	����.addEdge(MyEdge(150, &����));
	����.addEdge(MyEdge(162, &����));
	����.addEdge(MyEdge(154, &�뱸));
	����.addEdge(MyEdge(120, &����));
	����.addEdge(MyEdge(82, &����));

	�뱸.addEdge(MyEdge(220, &����));
	�뱸.addEdge(MyEdge(255, &����));
	�뱸.addEdge(MyEdge(106, &�λ�));
	�뱸.addEdge(MyEdge(206, &����));
	�뱸.addEdge(MyEdge(154, &����));

	����.addEdge(MyEdge(98, &����));
	����.addEdge(MyEdge(120, &����));
	����.addEdge(MyEdge(206, &�뱸));
	����.addEdge(MyEdge(242, &�λ�));

	�λ�.addEdge(MyEdge(343, &����));
	�λ�.addEdge(MyEdge(313, &����));
	�λ�.addEdge(MyEdge(106, &�뱸));
	�λ�.addEdge(MyEdge(242, &����));

	// �ε��� ������� ���� ��
	graph.addVertex(����);
	graph.addVertex(��õ);
	graph.addVertex(����);
	graph.addVertex(����);
	graph.addVertex(����);
	graph.addVertex(����);
	graph.addVertex(�뱸);
	graph.addVertex(����);
	graph.addVertex(�λ�);
	

	graph.createEdgeWeights();
}