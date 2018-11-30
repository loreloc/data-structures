
#pragma once

#include <cstring>

#include "list.h"

#define VECTORLIST_INIT_SIZE 10

template<class T>
class VectorList : public List<T, int>
{
public:
	VectorList();
	VectorList(const VectorList &l);
	~VectorList();

	VectorList &operator=(const VectorList &l);

	T read(int p) const;
	void write(int p, T v);
	int next(int p) const;
	int prev(int p) const;
	void clear();
	bool empty() const;
	size_t size() const;
	int begin() const;
	bool end(int p) const;
	void insert(int p, T v);
	void pushBack(T v);
	void pushFront(T v);
	void popBack();
	void popFront();
	void remove(int p);
	int find(T v) const;

private:
	T *m_elements;
	int m_size;
	int m_capacity;

	void _changeSize(int s);
};

template<typename T>
VectorList<T>::VectorList()
{
	m_elements = new T[VECTORLIST_INIT_SIZE];
	m_capacity = VECTORLIST_INIT_SIZE;
	m_size = 0;
}

template<typename T>
VectorList<T>::VectorList(const VectorList<T> &l)
{
	m_elements = new T[l.m_capacity];
	m_capacity = l.m_capacity;
	m_size = l.m_size;

	memcpy(m_elements, l.m_elements, sizeof(T) * m_size);
}

template<typename T>
VectorList<T>::~VectorList()
{
	delete [] m_elements;
}

template<typename T>
VectorList<T> &VectorList<T>::operator=(const VectorList<T> &l)
{
	if(this == &l)
		return *this;

	clear();

	m_elements = new T[l.m_capacity];
	m_capacity = l.m_capacity;
	m_size = l.m_size;

	memcpy(m_elements, l.m_elements, sizeof(T) * m_size);
}

template<typename T>
T VectorList<T>::read(int p) const
{
	if(p < 0 || p >= m_size)
		throw "index out of bounds";

	return m_elements[p];
}

template<typename T>
void VectorList<T>::write(int p, T v)
{
	if(p < 0 || p >= m_size)
		throw "index out of bounds";

	m_elements[p] = v;
}

template<typename T>
int VectorList<T>::next(int p) const
{
	return p + 1;
}

template<typename T>
int VectorList<T>::prev(int p) const
{
	return p - 1;
}

template<typename T>
void VectorList<T>::clear()
{
	m_size = 0;
}

template<typename T>
bool VectorList<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
size_t VectorList<T>::size() const
{
	return m_size;
}

template<typename T>
int VectorList<T>::begin() const
{
	return 0;
}

template<typename T>
bool VectorList<T>::end(int p) const
{
	return p == m_size;
}

template<typename T>
void VectorList<T>::insert(int p, T v)
{
	if(p < 0 || p >= m_size)
		throw "index out of bounds";

	if(m_size >= m_capacity)
		_changeSize(2 * m_capacity);

	for(int i = m_size; i > p; i--)
		m_elements[i] = m_elements[i - 1];

	m_elements[p] = v;

	m_size++;
}

template<typename T>
void VectorList<T>::remove(int p)
{
	if(p < 0 || p >= m_size)
		throw "index out of bounds";

	for(int i = p; i < m_size - 1; i++)
		m_elements[i] = m_elements[i + 1];

	m_size--;
}

template<typename T>
int VectorList<T>::find(T v) const
{
	int p = begin();

	while(!end(p))
	{
		if(m_elements[p] == v)
			return p;

		p = next(p);
	}

	return -1;
}

template<typename T>
void VectorList<T>::pushBack(T v)
{
	if(m_size >= m_capacity)
		_changeSize(2 * m_capacity);

	m_elements[m_size] = v;

	m_size++;
}

template<typename T>
void VectorList<T>::pushFront(T v)
{
	if(m_size >= m_capacity)
		_changeSize(2 * m_capacity);

	for(int i = m_size; i > 0; i--)
		m_elements[i] = m_elements[i - 1];

	m_elements[0] = v;

	m_size++;
}

template<typename T>
void VectorList<T>::popBack()
{
	m_size--;
}

template<typename T>
void VectorList<T>::popFront()
{
	for(int i = 0; i < m_size - 1; i++)
		m_elements[i] = m_elements[i + 1];

	m_size--;
}

template<typename T>
void VectorList<T>::_changeSize(int s)
{
	T *elements = new T[s];

	memcpy(elements, m_elements, sizeof(T) * m_size);

	T *tmp = m_elements;
	m_elements = elements;
	delete [] tmp;

	m_capacity = s;
}


