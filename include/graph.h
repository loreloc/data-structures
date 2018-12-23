
#pragma once

#include <iostream>
#include <cstring>

#include "linkedlist.h"

template<class T, class W>
class Graph;

template<class T, class W>
class GEdge
{
	friend class Graph<T, W>;

	GEdge() : valid(false) { }

private:
	bool valid;
	W weight;
};

template<class T, class W>
class GNode
{
	friend class Graph<T, W>;

	GNode() : valid(false) { }

private:
	bool valid;
	T value;
	GEdge<T, W> *edges;
	size_t id;
};

template<class T, class W>
class Graph
{
public:
	Graph(size_t s);
	Graph(const Graph &g);
	~Graph();

	Graph &operator=(const Graph &g);

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

	GEdge<T, W>* edgeBetween(GNode<T, W> *a, GNode<T, W> *b);

	LinkedList<GNode<T, W> *> getNodes() const;
	LinkedList<GEdge<T, W> *> getEdges() const;

	size_t inDegree(GNode<T, W> *n) const;
	size_t outDegree(GNode<T, W> *n) const;
	double meanOutDegree() const;

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

	m_matrix[a->id].edges[b->id].valid = true;
	m_matrix[a->id].edges[b->id].weight = w;

	m_edges++;

	return &m_matrix[a->id].edges[b->id];
} 

template<typename T, typename W>
void Graph<T, W>::removeNode(GNode<T, W> *n)
{
	for(size_t i = 0; i < m_size; i++)
	{
		if(m_matrix[n->id].edges[i].valid)
		{
			m_matrix[n->id].edges[i].valid = false;
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

	m_matrix[a->id].edges[b->id].valid = false;

	m_edges--;
}

template<typename T, typename W>
GEdge<T, W>* Graph<T, W>::edgeBetween(GNode<T, W> *a, GNode<T, W> *b)
{
	if(m_matrix[a->id].edges[b->id].valid)
		return &m_matrix[a->id].edges[b->id];

	return nullptr;
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

