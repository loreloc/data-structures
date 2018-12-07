
#pragma once

#include <cstddef>
#include <cstring>

template<class T>
class Heap
{
public:
	Heap();
	Heap(const Heap &h);
	~Heap();

	Heap &operator=(const Heap &h);

	bool empty() const;
	size_t size() const;
	void clear();
	void insert(T v);
	void pop();
	T min() const;
	T& min();

private:
	size_t m_size;
	size_t m_capacity;
	T *m_data;

	void _changeSize(size_t s);
	void _fixUp();
	void _fixDown();
};

template<typename T>
Heap<T>::Heap() :
	m_size(0),
	m_capacity(10)
{
	m_data = new T[m_capacity];
}

template<typename T>
Heap<T>::Heap(const Heap<T> &h)
{
	m_size = h.m_size;
	m_capacity = h.m_capacity;
	m_data = new T[m_capacity]; 
}

template<typename T>
Heap<T>::~Heap()
{
	delete [] m_data;
}

template<typename T>
bool Heap<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
size_t Heap<T>::size() const
{
	return m_size;
}

template<typename T>
void Heap<T>::clear()
{
	m_size = 0;
}

template<typename T>
void Heap<T>::insert(T v)
{
	if(m_size == m_capacity)
		_changeSize(m_capacity * 2);

	m_data[m_size++] = v;

	_fixUp();
}

template<typename T>
void Heap<T>::pop()
{
	if(empty())
		throw "heap is empty";

	m_data[0] = m_data[--m_size];

	_fixDown();
}

template<typename T>
T Heap<T>::min() const
{
	if(empty())
		throw "heap is empty";

	return m_data[0];
}

template<typename T>
T& Heap<T>::min()
{
	if(empty())
		throw "heap is empty";

	return m_data[0];
}

template<typename T>
void Heap<T>::_changeSize(size_t s)
{
	T *data = new T[s];

	memcpy(data, m_data, sizeof(T) * m_size);

	T *tmp = m_data;
	m_data = data;
	delete [] tmp;

	m_capacity = s;
}

template<typename T>
void Heap<T>::_fixUp()
{
	size_t i = m_size - 1;

	while(i != 0 && m_data[i] < m_data[i / 2])
	{
		T tmp = m_data[i];
		m_data[i] = m_data[i / 2];
		m_data[i / 2] = tmp;
		i /= 2;
	}
}

template<typename T>
void Heap<T>::_fixDown()
{
	size_t i = 0;

	while(i < m_size / 2)
	{
		size_t j = 2 * i;

		if(j < m_size && m_data[j] > m_data[j + 1])
			j++;

		if(m_data[j] < m_data[i])
		{
			T tmp = m_data[i];
			m_data[i] = m_data[j];
			m_data[j] = tmp;
			i = j;
		}
		else
		{
			break;
		}
	}
}

