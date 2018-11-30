
#pragma once

#include "list.h"

template<class T>
class LinkedList;

template<class T>
class LNode
{
	friend class LinkedList<T>;

private:
	T value;
	LNode<T> *next;
	LNode<T> *prev;
};

template<class T>
class LinkedList : public List<T, LNode<T> *>
{
public:
	LinkedList();
	LinkedList(const LinkedList &l);
	~LinkedList();

	LinkedList &operator=(const LinkedList &l);

	T read(LNode<T> *p) const;
	void write(LNode<T> *p, T v);
	LNode<T> *next(LNode<T> *p) const;
	LNode<T> *prev(LNode<T> *p) const;
	void create();
	void clear();
	bool empty() const;
	size_t size() const;
	LNode<T> *begin() const;
	bool end(LNode<T> *p) const;
	void insert(LNode<T> *p, T v);
	void remove(LNode<T> *p);
	LNode<T> *find(T v) const;
	void pushBack(T v);
	void pushFront(T v);
	void popBack();
	void popFront();

private:
	LNode<T> *m_head;
	LNode<T> *m_tail;
	size_t m_size;
};


template<typename T>
LinkedList<T>::LinkedList()
{
	create();
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &l)
{
	create();

	LNode<T> *tmp = l.begin();

	while(!l.end(tmp))
	{
		pushBack(tmp->value);
		tmp = tmp->next;
	}
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &l)
{
	if(this == &l)
		return *this;

	if(!empty())
	{
		clear();
		create();
	}

	LNode<T> *tmp = l.begin();

	while(!l.end(tmp))
	{
		pushBack(tmp->value);
		tmp = tmp->next;
	}

	return *this;
}

template<typename T>
T LinkedList<T>::read(LNode<T> *p) const
{
	return p->value;
}

template<typename T>
void LinkedList<T>::write(LNode<T> *p, T v)
{
	p->value = v;
}

template<typename T>
LNode<T> *LinkedList<T>::next(LNode<T> *p) const
{
	return p->next;
}

template<typename T>
LNode<T> *LinkedList<T>::prev(LNode<T> *p) const
{
	return p->prev;
}

template<typename T>
void LinkedList<T>::create()
{
	m_head = m_tail = nullptr;
}

template<typename T>
void LinkedList<T>::clear()
{
	LNode<T> *tmp;

	while(m_head != nullptr)
	{
		tmp = m_head;
		m_head = m_head->next;
		delete tmp;
	}
}

template<typename T>
bool LinkedList<T>::empty() const
{
	return m_head == nullptr;
}

template<typename T>
size_t LinkedList<T>::size() const
{
	return m_size;
}

template<typename T>
LNode<T> *LinkedList<T>::begin() const
{
	return m_head;
}

template<typename T>
bool LinkedList<T>::end(LNode<T> *p) const
{
	return p == nullptr;
}

template<typename T>
void LinkedList<T>::insert(LNode<T> *p, T v)
{
	LNode<T> *node = new LNode<T>;
	node->value = v;
	node->next = p->next;
	node->prev = p;

	if(p->next == nullptr)
		m_tail = node;
	else
		p->next->prev = node;

	p->next = node;

	m_size++;
}

template<typename T>
void LinkedList<T>::remove(LNode<T> *p)
{
	LNode<T> *tmp = p;

	if(p->prev == nullptr)
		m_head = p->next;
	else
		p->prev->next = p->next;

	if(p->next == nullptr)
		m_tail = p->prev;		
	else
		p->next->prev = p->prev;

	delete tmp;

	m_size--;
}

template<typename T>
LNode<T> *LinkedList<T>::find(T v) const
{
	LNode<T> *tmp = begin();

	while(!end(tmp))
	{
		if(tmp->value == v)
			return tmp;

		tmp = tmp->next;
	}

	return nullptr;
}

template<typename T>
void LinkedList<T>::pushBack(T v)
{
	LNode<T> *node = new LNode<T>;
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
void LinkedList<T>::pushFront(T v)
{
	LNode<T> *node = new LNode<T>;
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
void LinkedList<T>::popBack()
{
	if(empty())
		throw "list is empty";

	if(m_head == m_tail)
	{
		delete m_head;
		m_head = nullptr;
	}
	else
	{
		LNode<T> *tmp = m_tail;
		m_tail->prev->next = nullptr;
		m_tail = m_tail->prev;
		delete tmp;
	}

	m_size--;
}

template<typename T>
void LinkedList<T>::popFront()
{
	if(empty())
		throw "list is empty";

	LNode<T> *tmp = m_head;
	m_head = m_head->next;
	delete tmp;

	m_size--;
}



