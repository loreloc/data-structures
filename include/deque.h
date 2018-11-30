
#pragma once

#include <iostream>

template<class T>
struct DNode
{
	T value;
	DNode<T> *next;
	DNode<T> *prev;
};

template<class T>
class Deque
{
public:
	Deque();
	Deque(const Deque &d);
	~Deque();

	Deque &operator=(const Deque &d);

	void clear();
	bool empty() const;
	size_t size() const;
	void pushBack(T v);
	void pushFront(T v);
	T popBack();
	T popFront();

	template<class U>
	friend std::ostream &operator<<(std::ostream &os, const Deque<U> &q);

private:
	DNode<T> *m_head;
	DNode<T> *m_tail;
	size_t m_size;
};

template<typename T>
Deque<T>::Deque()
{
	m_head = m_tail = nullptr;
	m_size = 0;
}

template<typename T>
Deque<T>::Deque(const Deque &d)
{
	m_head = m_tail = nullptr;
	m_size = 0;

	DNode<T> *tmp = d.m_head;

	while(tmp != nullptr)
	{
		pushBack(tmp->value);
		tmp = tmp->next;
	}
}

template<typename T>
Deque<T>::~Deque()
{
	clear();
}

template<typename T>
Deque<T> &Deque<T>::operator=(const Deque<T> &d)
{
	if(this == &d)
		return *this;

	if(!empty())
		clear();

	m_head = m_tail = nullptr;
	m_size = 0;

	DNode<T> *tmp = d.m_head;

	while(tmp != nullptr)
	{
		push(tmp->value);
		tmp = tmp->next;
	}

	return this;
}

template<typename T>
void Deque<T>::clear()
{
	while(!empty())
		popFront();
}

template<typename T>
bool Deque<T>::empty() const
{
	return m_head == nullptr;
}

template<typename T>
size_t Deque<T>::size() const
{
	return m_size;
}

template<typename T>
void Deque<T>::pushBack(T v)
{
	DNode<T> *node = new DNode<T>;
	node->value = v;
	node->next = nullptr;

	if(empty())
	{
		m_head = node;
		node->prev = nullptr;
	}
	else
	{
		m_tail->next = node;
		node->prev = m_tail;
	}

	m_tail = node;

	m_size++;
}

template<typename T>
void Deque<T>::pushFront(T v)
{
	DNode<T> *node = new DNode<T>;
	node->value = v;
	node->prev = nullptr;

	if(empty())
	{
		m_tail = node;
		node->next = nullptr;
	}
	else
	{
		m_head->prev = node;
		node->next = m_head;
	}

	m_head = node;

	m_size++;
}

template<typename T>
T Deque<T>::popBack()
{
	if(empty())
		throw "deque is empty";

	T value;

	if(m_head == m_tail)
	{
		value = m_head->value;

		delete m_head;
		m_head = nullptr;
	}
	else
	{
		value = m_tail->value;

		DNode<T> *tmp = m_tail;
		m_tail->prev->next = nullptr;
		m_tail = m_tail->prev;
		delete tmp;
	}

	m_size--;

	return value;
}

template<typename T>
T Deque<T>::popFront()
{
	if(empty())
		throw "deque is empty";

	T value = m_head->value;

	DNode<T> *tmp = m_head;
	m_head = m_head->next;
	delete tmp;

	m_size--;

	return value;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Deque<T> &d)
{
	DNode<T> *tmp = d.m_head;

	os << "[ ";

	while(tmp != nullptr)
	{
		std::cout << tmp->value << " ";

		tmp = tmp->next;
	}

	os << "]";

	return os;
}



