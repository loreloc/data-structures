
#include "graph.h"

int main(int argc, char *argv[])
{
	Graph<char, int> graph(4);

	GNode<char, int> *n1 = graph.insertNode('a');
	GNode<char, int> *n2 = graph.insertNode('b');
	GNode<char, int> *n3 = graph.insertNode('c');
	GNode<char, int> *n4 = graph.insertNode('d');

	GEdge<char, int> *e1 = graph.insertEdge(n1, n2, 1);
	GEdge<char, int> *e2 = graph.insertEdge(n1, n3, 2);
	GEdge<char, int> *e3 = graph.insertEdge(n1, n4, 3);
	GEdge<char, int> *e4 = graph.insertEdge(n2, n4, 4);
	GEdge<char, int> *e5 = graph.insertEdge(n3, n2, 5);

	std::cout << graph.nodes() << " " << graph.edges() << std::endl;

	graph.removeEdge(n1, n2);

	std::cout << graph.nodes() << " " << graph.edges() << std::endl;

	graph.removeNode(n1);

	std::cout << graph.nodes() << " " << graph.edges() << std::endl;

	return 0;
}

