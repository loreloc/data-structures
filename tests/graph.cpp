
#include "graph.h"

int main(int argc, char *argv[])
{
	Graph<char, unsigned> graph(4);

	GNode<char, unsigned> *n1 = graph.insertNode('a');
	GNode<char, unsigned> *n2 = graph.insertNode('b');
	GNode<char, unsigned> *n3 = graph.insertNode('c');
	GNode<char, unsigned> *n4 = graph.insertNode('d');

	GEdge<char, unsigned> *e1 = graph.insertEdge(n1, n2, 8);
	GEdge<char, unsigned> *e2 = graph.insertEdge(n1, n3, 2);
	GEdge<char, unsigned> *e3 = graph.insertEdge(n1, n4, 3);
	GEdge<char, unsigned> *e4 = graph.insertEdge(n2, n4, 4);
	GEdge<char, unsigned> *e5 = graph.insertEdge(n3, n2, 5);
	GEdge<char, unsigned> *e6 = graph.insertEdge(n4, n3, 1);

	graph.BST(n1);
	graph.DST(n1);

	std::cout << graph.existsPath(n3, n4) << std::endl << std::endl;

	HashTable<GNode<char, unsigned> *, unsigned> dist = Dijkstra(graph, n1);

	LinkedList<GNode<char, unsigned> *> keys = dist.keys();
	LNode<GNode<char, unsigned> *> *tmp = keys.begin();

	while(!keys.end(tmp))
	{
		GNode<char, unsigned> *k = keys.read(tmp);

		std::cout << graph.getValue(k) << " - " << dist.get(k) << std::endl;

		tmp = keys.next(tmp);
	}

	std::cout << std::endl;

	LinkedList<GNode<char, unsigned> *> path = FindPath(graph, n1, n2);
	tmp = path.begin();

	while(!path.end(tmp))
	{
		std::cout << graph.getValue(path.read(tmp)) << " ";

		tmp = path.next(tmp);
	}

	std::cout << std::endl << std::endl;

	HashTable<GNode<char, unsigned> *, GNode<char, unsigned> *> tree = Prim(graph);

	keys = tree.keys();
	tmp = keys.begin();

	while(!keys.end(tmp))
	{
		GNode<char, unsigned> *k = keys.read(tmp);
		GNode<char, unsigned> *v = tree.get(k);

		std::cout << graph.getValue(k) << " - ";

		if(v == nullptr)
			std::cout << "NULL" << std::endl;
		else
			std::cout << graph.getValue(v) << std::endl;

		tmp = keys.next(tmp);
	}

	std::cout << std::endl << std::endl;

	std::cout << graph.nodes() << " " << graph.edges() << std::endl;

	graph.removeEdge(n1, n2);

	std::cout << graph.nodes() << " " << graph.edges() << std::endl;

	graph.removeNode(n1);

	std::cout << graph.nodes() << " " << graph.edges() << std::endl;

	return 0;
}

