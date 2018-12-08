
#include <iostream>

#include "linkedlist.h"

template<class T>
class Tree;

template<class T>
class TNode
{
	friend class Tree<T>;

private:
	T value;
	TNode<T> *parent;
	LinkedList<TNode<T> *> childs;
};

template<class T>
class Tree
{
public:
	Tree();
	Tree(const Tree &t);
	~Tree();

	Tree &operator=(const Tree &t);

	T& value(TNode<T> *n);
	T value(TNode<T> *n) const;
	TNode<T>* parent(TNode<T> *n) const;
	const LinkedList<TNode<T> *>& childs(TNode<T> *n) const;
	TNode<T>* addChild(TNode<T> *n, T v);

	bool empty() const;
	size_t size() const;
	TNode<T>* root() const;
	void clear();
	TNode<T>* insertRoot(T v);

	static void print(std::ostream &os, TNode<T> *n);

	template<class U>
	friend std::ostream &operator<<(std::ostream &os, const Tree<T> &t);

private:
	TNode<T> *m_root;
	size_t m_size;

	TNode<T> *_copy(TNode<T> *n, TNode<T> *p);
	void _remove(TNode<T> *n);

	static void _print(std::ostream &os, TNode<T> *n);
};

template<typename T>
Tree<T>::Tree() :
	m_root(nullptr),
	m_size(0)
{

}

template<typename T>
Tree<T>::Tree(const Tree &t)
{
	m_size = 0;
	m_root = _copy(t.root(), nullptr);
}

template<typename T>
Tree<T>::~Tree()
{
	clear();
}

template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T> &t)
{
	if(this == &t)
		return *this;

	if(!empty())
		clear();

	m_root = _copy(t.root(), nullptr);

	return *this;
}

template<typename T>
T Tree<T>::value(TNode<T> *n) const
{
	return n->value;
}

template<typename T>
T& Tree<T>::value(TNode<T> *n)
{
	return n->value;
}

template<typename T>
TNode<T>* Tree<T>::parent(TNode<T> *n) const
{
	return n->parent;
}

template<typename T>
const LinkedList<TNode<T> *>& Tree<T>::childs(TNode<T> *n) const
{
	return n->childs;
}

template<typename T>
TNode<T>* Tree<T>::addChild(TNode<T> *n, T v)
{
	TNode<T> *tmp = new TNode<T>;
	tmp->value = v;
	tmp->parent = n;

	n->childs.pushBack(tmp);

	m_size++;

	return tmp;
}

template<typename T>
bool Tree<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
size_t Tree<T>::size() const
{
	return m_size;
}

template<typename T>
TNode<T>* Tree<T>::root() const
{
	return m_root;
}

template<typename T>
void Tree<T>::clear()
{
	_remove(m_root);
	m_root = nullptr;
}

template<typename T>
TNode<T>* Tree<T>::insertRoot(T v)
{
	if(m_root != nullptr)
		throw "tree has already a root";

	m_root = new TNode<T>;
	m_root->value = v;
	m_root->parent = nullptr;

	return m_root;
}

template<typename T>
void Tree<T>::print(std::ostream &os, TNode<T> *n)
{
	if(n == nullptr)
		os << "[ ]";
	else
		_print(os, n);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Tree<T> &t)
{
	Tree<T>::print(os, t.root());
	return os;
}

template<typename T>
TNode<T>* Tree<T>::_copy(TNode<T> *n, TNode<T> *p)
{
	if(n == nullptr)
		return nullptr;

	TNode<T> *node = new TNode<T>;
	node->value = n->value;
	node->parent = p;

	const LinkedList<TNode<T> *> &ch = childs(n);

	LNode<TNode<T> *> *tmp = ch.begin();
	while(!ch.end(tmp))
	{
		TNode<T> *k = _copy(ch.read(tmp), node);
		node->childs.pushBack(k);
		tmp = ch.next(tmp);
	}

	m_size++;

	return node;
}

template<typename T>
void Tree<T>::_remove(TNode<T> *n)
{
	if(n != nullptr)
	{
		const LinkedList<TNode<T> *> &ch = childs(n);

		LNode<TNode<T> *> *tmp = ch.begin();
		while(!ch.end(tmp))
		{
			_remove(ch.read(tmp));
			tmp = ch.next(tmp);
		}

		delete n;

		m_size--;
	}
}

template<typename T>
void Tree<T>::_print(std::ostream &os, TNode<T> *n)
{
	std::cout << "[ " << n->value << " ";

	const LinkedList<TNode<T> *> &ch = n->childs;

	LNode<TNode<T> *> *tmp = ch.begin();
	while(!ch.end(tmp))
	{
		_print(os, ch.read(tmp));
		tmp = ch.next(tmp);
	}

	std::cout << "] ";
}

