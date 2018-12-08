
#pragma once

#include <cstddef>
#include <cstring>

template<class T>
class PriorityQueue
{
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue &h);
	~PriorityQueue();

	PriorityQueue &operator=(const PriorityQueue &h);

	bool empty() const;
	size_t size() const;
	void clear();
	void push(T v);
	void pop();
	T min() const;
	T& min();

private:
	size_t m_size;
	size_t m_capacity;
	T *m_heap;

	void _changeSize(size_t s);
	void _fixUp();
	void _fixDown();
};

template<typename T>
PriorityQueue<T>::PriorityQueue() :
	m_size(0),
	m_capacity(10)
{
	m_heap = new T[m_capacity];
}

template<typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T> &h)
{
	m_size = h.m_size;
	m_capacity = h.m_capacity;
	m_heap = new T[m_capacity]; 
}

template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
	delete [] m_heap;
}

template<typename T>
bool PriorityQueue<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
size_t PriorityQueue<T>::size() const
{
	return m_size;
}

template<typename T>
void PriorityQueue<T>::clear()
{
	m_size = 0;
}

template<typename T>
void PriorityQueue<T>::push(T v)
{
	if(m_size == m_capacity)
		_changeSize(m_capacity * 2);

	m_heap[m_size++] = v;

	_fixUp();
}

template<typename T>
void PriorityQueue<T>::pop()
{
	if(empty())
		throw "heap is empty";

	m_heap[0] = m_heap[--m_size];

	_fixDown();
}

template<typename T>
T PriorityQueue<T>::min() const
{
	if(empty())
		throw "heap is empty";

	return m_heap[0];
}

template<typename T>
T& PriorityQueue<T>::min()
{
	if(empty())
		throw "heap is empty";

	return m_heap[0];
}

template<typename T>
void PriorityQueue<T>::_changeSize(size_t s)
{
	T *data = new T[s];

	memcpy(data, m_heap, sizeof(T) * m_size);

	T *tmp = m_heap;
	m_heap = data;
	delete [] tmp;

	m_capacity = s;
}

template<typename T>
void PriorityQueue<T>::_fixUp()
{
	size_t i = m_size - 1;

	while(i != 0 && m_heap[i] < m_heap[i / 2])
	{
		T tmp = m_heap[i];
		m_heap[i] = m_heap[i / 2];
		m_heap[i / 2] = tmp;
		i /= 2;
	}
}

template<typename T>
void PriorityQueue<T>::_fixDown()
{
	size_t i = 0;

	while(i < m_size / 2)
	{
		size_t j = 2 * i;

		if(j < m_size && m_heap[j] > m_heap[j + 1])
			j++;

		if(m_heap[j] < m_heap[i])
		{
			T tmp = m_heap[i];
			m_heap[i] = m_heap[j];
			m_heap[j] = tmp;
			i = j;
		}
		else
		{
			break;
		}
	}
}

