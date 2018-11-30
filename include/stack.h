
#pragma once

#include <iostream>

template<class T>
struct SNode
{
	T value;
	SNode<T> *next;
};

template<class T>
class Stack
{
public:
	Stack();
	Stack(const Stack &s);
	~Stack();

	Stack &operator=(const Stack &s);

	void clear();
	bool empty() const;
	size_t size() const;
	void push(T v);
	void pop();
	T top() const;

	template<class U>
	friend std::ostream &operator<<(std::ostream &os, const Stack<U> &s);

private:
	SNode<T> *m_top;
	size_t m_size;
};

template<typename T>
Stack<T>::Stack()
{
	m_top = nullptr;
	m_size = 0;
}

template<typename T>
Stack<T>::Stack(const Stack &s)
{
	m_top = nullptr;
	m_size = 0;

	if(s.empty())
		return;

	SNode<T> *tmp1 = s.m_top;

	m_top = new SNode<T>;
	m_top->value = tmp1->value;
	m_top->next = nullptr;

	tmp1 = tmp1->next;
	SNode<T> *tmp2 = m_top;

	while(tmp1 != nullptr)
	{
		SNode<T> *node = new SNode<T>;
		node->value = tmp1->value;
		node->next = nullptr;

		tmp2->next = node;

		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
}

template<typename T>
Stack<T>::~Stack()
{
	clear();
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &s)
{
	if(this == &s)
		return *this;

	if(!empty())
		clear();

	m_top = nullptr;
	m_size = 0;

	if(s.empty())
		return *this;

	SNode<T> *tmp1 = s.m_top;

	m_top = new SNode<T>;
	m_top->value = tmp1->value;
	m_top->next = nullptr;

	tmp1 = tmp1->next;
	SNode<T> *tmp2 = m_top;

	while(tmp1 != nullptr)
	{
		SNode<T> *node = new SNode<T>;
		node->value = tmp1->value;
		node->next = nullptr;

		tmp2->next = node;

		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}

	return *this;
}

template<typename T>
void Stack<T>::clear()
{
	while(!empty())
		pop();
}

template<typename T>
bool Stack<T>::empty() const
{
	return m_top == nullptr;
}

template<typename T>
size_t Stack<T>::size() const
{
	return m_size;
}

template<typename T>
void Stack<T>::push(T v)
{
	SNode<T> *node = new SNode<T>;
	node->value = v;
	node->next = m_top;
	m_top = node;

	m_size++;
}

template<typename T>
void Stack<T>::pop()
{
	if(empty())
		throw "stack is empty";

	SNode<T> *node = m_top;
	m_top = m_top->next;
	delete node;

	m_size--;
}

template<typename T>
T Stack<T>::top() const
{
	return m_top->value;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &s)
{
	SNode<T> *tmp = s.m_top;

	os << "[ ";

	while(tmp != nullptr)
	{
		std::cout << tmp->value << " ";

		tmp = tmp->next;
	}

	os << "]";

	return os;
}



