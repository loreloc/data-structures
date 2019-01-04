
#pragma once

#include <iostream>
#include <cstring>

#include "queue.h"
#include "linkedlist.h"
#include "searchtree.h"

template<class T, class W>
class Graph;

template<class T, class W>
class GEdge;

template<class T, class W>
class GNode
{
	friend class Graph<T, W>;

	GNode() : valid(false) { }

private:
	bool valid;
	T value;
	size_t id;
	GEdge<T, W> *edges;
	
};

template<class T, class W>
class GEdge
{
	friend class Graph<T, W>;

	GEdge() : valid(false) { }

private:
	bool valid;
	GNode<T, W> *first;
	GNode<T, W> *second;
	W weight;
};

template<class T, class W>
class Graph
{
public:
	Graph(size_t s);
	Graph(const Graph &g);
	~Graph();

	Graph &operator=(const Graph &g);
	GNode<T, W>* getFirst(GEdge<T, W> *e) const;
	GNode<T, W>* getSecond(GEdge<T, W> *e) const;
	W getWeight(GEdge<T, W> *e) const;
	T getValue(GNode<T, W> *n) const;
	void setWeight(GEdge<T, W> *e, W w);
	void setValue(GNode<T, W> *n, T v);

	size_t size() const;
	size_t nodes() const;
	size_t edges() const;

	bool empty() const;
	GNode<T, W>* insertNode(T v);
	GEdge<T, W>* insertEdge(GNode<T, W> *a, GNode<T, W> *b, W w);
	void removeNode(GNode<T, W> *n);
	void removeEdge(GNode<T, W> *a, GNode<T, W> *b);

	GEdge<T, W>* edgeBetween(GNode<T, W> *a, GNode<T, W> *b) const;
	LinkedList<GNode<T, W> *> getAdjacents(GNode<T, W> *n) const;

	LinkedList<GNode<T, W> *> getNodes() const;
	LinkedList<GEdge<T, W> *> getEdges() const;

	size_t inDegree(GNode<T, W> *n) const;
	size_t outDegree(GNode<T, W> *n) const;
	double meanOutDegree() const;
	bool existsPath(GNode<T, W> *a, GNode<T, W> *b) const;

private:
	size_t m_size;
	size_t m_nodes;
	size_t m_edges;
	GNode<T, W> *m_matrix;
};

template<typename T, typename W>
Graph<T, W>::Graph(size_t s)
{
	m_size = s;
	m_nodes = 0;
	m_edges = 0;
	m_matrix = new GNode<T, W>[m_size];

	for(size_t i = 0; i < m_size; i++)
		m_matrix[i].edges = new GEdge<T, W>[m_size];
}

template<typename T, typename W>
Graph<T, W>::Graph(const Graph &g)
{
	m_size = g.m_size;
	m_nodes = g.m_nodes;
	m_edges = g.m_edges;
	m_matrix = new GNode<T, W>[m_size];

	for(size_t i = 0; i < m_size; i++)
	{
		m_matrix[i].value = g.m_matrix[i].value;
		m_matrix[i].edges = new GEdge<T, W>[m_size];
		
		for(size_t j = 0; j < m_size; j++)
			m_matrix[i].edges[j] = g.m_matrix[i].edges[j];
	}
}

template<typename T, typename W>
Graph<T, W>::~Graph()
{
	for(size_t i = 0; i < m_size; i++)
		delete [] m_matrix[i].edges;

	delete [] m_matrix;
}

template<typename T, typename W>
Graph<T, W> &Graph<T, W>::operator=(const Graph &g)
{
	if(this == &g)
		return *this;

	this->~Graph();

	m_size = g.m_size;
	m_nodes = g.m_nodes;
	m_edges = g.m_edges;
	m_matrix = new GNode<T, W>[m_size];

	for(size_t i = 0; i < m_size; i++)
	{
		m_matrix[i].value = g.m_matrix[i].value;
		m_matrix[i].edges = new GEdge<T, W>[m_size];
		
		for(size_t j = 0; j < m_size; j++)
			m_matrix[i].edges[j] = g.m_matrix[i].edges[j];
	}

	return *this;
}

template<typename T, typename W>
GNode<T, W>* Graph<T, W>::getFirst(GEdge<T, W> *e) const
{
	return e->first;
}

template<typename T, typename W>
GNode<T, W>* Graph<T, W>::getSecond(GEdge<T, W> *e) const
{
	return e->second;
}

template<typename T, typename W>
W Graph<T, W>::getWeight(GEdge<T, W> *e) const
{
	return e->weight;
}

template<typename T, typename W>
T Graph<T, W>::getValue(GNode<T, W> *n) const
{
	return n->value;
}

template<typename T, typename W>
void Graph<T, W>::setWeight(GEdge<T, W> *e, W w)
{
	e->weight = w;
}

template<typename T, typename W>
void Graph<T, W>::setValue(GNode<T, W> *n, T v)
{
	n->value = v;
}

template<typename T, typename W>
size_t Graph<T, W>::size() const
{
	return m_size;
}

template<typename T, typename W>
size_t Graph<T, W>::nodes() const
{
	return m_nodes;
}

template<typename T, typename W>
size_t Graph<T, W>::edges() const
{
	return m_edges;
}

template<typename T, typename W>
bool Graph<T, W>::empty() const
{
	return m_nodes == 0;
}

template<typename T, typename W>
GNode<T, W>* Graph<T, W>::insertNode(T v)
{
	if(m_nodes == m_size)
		throw "graph is full";

	size_t i = 0;
	while(m_matrix[i].valid)
		i++;

	m_matrix[i].valid = true;
	m_matrix[i].value = v;
	m_matrix[i].id = i;

	for(size_t j = 0; j < m_size; j++)
		m_matrix[i].edges[j].valid = false;

	m_nodes++;

	return &m_matrix[i];
}

template<typename T, typename W>
GEdge<T, W>* Graph<T, W>::insertEdge(GNode<T, W> *a, GNode<T, W> *b, W w)
{
	if(edgeBetween(a, b) != nullptr)
		throw "the edge already exists";

	a->edges[b->id].valid = true;
	a->edges[b->id].first = a;
	a->edges[b->id].second = b;
	a->edges[b->id].weight = w;

	m_edges++;

	return &a->edges[b->id];
} 

template<typename T, typename W>
void Graph<T, W>::removeNode(GNode<T, W> *n)
{
	if(!m_matrix[n->id].valid)
		throw "the node doesn't exist";

	for(size_t i = 0; i < m_size; i++)
	{
		if(n->edges[i].valid)
		{
			n->edges[i].valid = false;
			m_edges--;
		}

		if(m_matrix[i].edges[n->id].valid)
		{
			m_matrix[i].edges[n->id].valid = false;
			m_edges--;
		}
	}

	m_matrix[n->id].valid = false;

	m_nodes--;
}

template<typename T, typename W>
void Graph<T, W>::removeEdge(GNode<T, W> *a, GNode<T, W> *b)
{
	if(edgeBetween(a, b) == nullptr)
		throw "the edge doesn't exist";

	a->edges[b->id].valid = false;

	m_edges--;
}

template<typename T, typename W>
GEdge<T, W>* Graph<T, W>::edgeBetween(GNode<T, W> *a, GNode<T, W> *b) const
{
	if(a->edges[b->id].valid)
		return &a->edges[b->id];

	return nullptr;
}

template<typename T, typename W>
LinkedList<GNode<T, W> *> Graph<T, W>::getAdjacents(GNode<T, W> *n) const
{
	LinkedList<GNode<T, W> *> adj;

	for(size_t i = 0; i < m_size; i++)
		if(n->edges[i].valid)
			adj.pushBack(&m_matrix[i]);

	return adj;
}

template<typename T, typename W>
LinkedList<GNode<T, W> *> Graph<T, W>::getNodes() const
{
	LinkedList<GNode<T, W> *> l;

	for(size_t i = 0; i < m_size; i++)
		if(m_matrix[i].valid)
			l.pushBack(&m_matrix[i]);

	return l;
}

template<typename T, typename W>
LinkedList<GEdge<T, W> *> Graph<T, W>::getEdges() const
{
	LinkedList<GEdge<T, W> *> l;

	for(size_t i = 0; i < m_size; i++)
		if(m_matrix[i].valid)
			for(size_t j = 0; j < m_size; j++)
				if(m_matrix[i].edges[j].valid)
					l.pushBack(&m_matrix[i].edges[j]);

	return l;
}

template<typename T, typename W>
size_t Graph<T, W>::inDegree(GNode<T, W> *n) const
{
	size_t count = 0;

	for(size_t i = 0; i < m_size; i++)
		if(m_matrix[i].edges[n->id].valid)
			count++;

	return count;
}

template<typename T, typename W>
size_t Graph<T, W>::outDegree(GNode<T, W> *n) const
{
	size_t count = 0;

	for(size_t i = 0; i < m_size; i++)
		if(m_matrix[n->id].edge[i].valid)
			count++;

	return count;
}

template<typename T, typename W>
double Graph<T, W>::meanOutDegree() const
{
	size_t sum_out_degree = 0;
	size_t nodes_cnt = nodes();

	for(size_t i = 0; i < m_size; i++)
		if(m_matrix[i].valid)
			for(size_t j = 0; j < m_size; j++)
				if(m_matrix[i].edges[j].valid)
					sum_out_degree++;

	return static_cast<double>(sum_out_degree) / nodes_cnt;
}

template<typename T, typename W>
bool Graph<T, W>::existsPath(GNode<T, W> *a, GNode<T, W> *b) const
{
	if(a == b)
		return true;

	Queue<GNode<T, W> *> queue;
	SearchTree<GNode<T, W> *> visited;

	visited.insert(a);
	queue.push(a);

	while(!queue.empty())
	{
		GNode<T, W> *s = queue.front();
		queue.pop();

		LinkedList<GNode<T, W> *> adj = getAdjacents(s);

		LNode<GNode<T, W> *> *tmp = adj.begin();

		while(!adj.end(tmp))
		{
			GNode<T, W> *n = adj.read(tmp);

			if(b == n)
				return true;

			if(!visited.contains(n))
			{
				visited.insert(n);
				queue.push(n);
			}

			tmp = adj.next(tmp);
		}
	}

	return false;
}

