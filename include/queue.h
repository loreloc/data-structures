
#pragma once

#include <iostream>

template<class T>
struct QNode
{
	T value;
	QNode<T> *next;
};

template<class T>
class Queue
{
public:
	Queue();
	Queue(const Queue &q);
	~Queue();

	Queue &operator=(const Queue &q);

	void clear();
	bool empty() const;
	size_t size() const;
	void push(T v);
	T front() const;
	void pop();

	template<class U>
	friend std::ostream &operator<<(std::ostream &os, const Queue<U> &q);

private:
	QNode<T> *m_head;
	QNode<T> *m_tail;
	size_t m_size;
};

template<typename T>
Queue<T>::Queue()
{
	m_head = m_tail = nullptr;
	m_size = 0;
}

template<typename T>
Queue<T>::Queue(const Queue &q)
{
	m_head = m_tail = nullptr;
	m_size = 0;

	QNode<T> *tmp = q.m_head;

	while(tmp != nullptr)
	{
		push(tmp->value);
		tmp = tmp->next;
	}
}

template<typename T>
Queue<T>::~Queue()
{
	clear();
}

template<typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &q)
{
	if(this == &q)
		return *this;

	if(!empty())
		clear();

	m_head = m_tail = nullptr;
	m_size = 0;

	QNode<T> *tmp = q.m_head;

	while(tmp != nullptr)
	{
		push(tmp->value);
		tmp = tmp->next;
	}

	return this;
}

template<typename T>
void Queue<T>::clear()
{
	while(!empty())
		pop();
}

template<typename T>
bool Queue<T>::empty() const
{
	return m_head == nullptr;
}

template<typename T>
size_t Queue<T>::size() const
{
	return m_size;
}

template<typename T>
void Queue<T>::push(T v)
{
	QNode<T> *node = new QNode<T>;
	node->value = v;
	node->next = nullptr;

	if(empty())
	{
		m_head = m_tail = node;
	}
	else
	{
		m_tail->next = node;
		m_tail = node;
	}

	m_size++;
}

template<typename T>
T Queue<T>::front() const
{
	if(empty())
		throw "queue is empty";

	return m_head->value;
}

template<typename T>
void Queue<T>::pop()
{
	if(empty())
		throw "queue is empty";

	QNode<T> *node = m_head;

	m_head = m_head->next;
	delete node;

	m_size--;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &q)
{
	QNode<T> *tmp = q.m_head;

	os << "[ ";

	while(tmp != nullptr)
	{
		std::cout << tmp->value << " ";

		tmp = tmp->next;
	}

	os << "]";

	return os;
}



