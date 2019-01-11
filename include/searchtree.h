
#pragma once

#include <iostream>

template<class T>
struct STNode
{
	T value;
	STNode<T> *left;
	STNode<T> *right;
	STNode<T> *parent;
};

template<class T>
class SearchTree
{
public:
	SearchTree();
	SearchTree(const SearchTree &t);
	~SearchTree();

	SearchTree &operator=(const SearchTree &t);

	bool empty() const;
	size_t size() const;
	void clear();
	STNode<T>* root() const;
	STNode<T>* search(T v) const;
	STNode<T>* min() const;
	STNode<T>* max() const;
	STNode<T>* next(STNode<T> *n) const;
	STNode<T>* prev(STNode<T> *n) const;
	STNode<T>* insert(T v);
	void remove(STNode<T> *n);
	bool contains(T v) const;

	static void print(std::ostream &os, STNode<T> *n);

	template<class U>
	friend std::ostream &operator<<(std::ostream &os, const SearchTree<T> &t);

private:
	STNode<T> *m_root;
	size_t m_size;

	STNode<T>* _min(STNode<T> *n) const;
	STNode<T>* _max(STNode<T> *n) const;
	void _transplant(STNode<T> *u, STNode<T> *v);
	STNode<T> *_copy(STNode<T> *n, STNode<T> *p);
	void _remove(STNode<T> *n);

	static void _print(std::ostream &os, STNode<T> *n);
};

template<typename T>
SearchTree<T>::SearchTree() :
	m_root(nullptr),
	m_size(0)
{

}

template<typename T>
SearchTree<T>::SearchTree(const SearchTree<T> &t)
{
	m_size = 0;
	m_root = _copy(t.root(), nullptr);
}

template<typename T>
SearchTree<T>::~SearchTree()
{
	_remove(m_root);
}

template<typename T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree<T> &t)
{
	if(this == &t)
		return *this;

	if(!empty())
		clear();

	m_root = _copy(t.root(), nullptr);

	return *this;
}

template<typename T>
bool SearchTree<T>::empty() const
{
	return m_root == nullptr;
}

template<typename T>
size_t SearchTree<T>::size() const
{
	return m_size;
}

template<typename T>
void SearchTree<T>::clear()
{
	_remove(m_root);
	m_root = nullptr;
}

template<typename T>
STNode<T>* SearchTree<T>::root() const
{
	return m_root;
}

template<typename T>
STNode<T>* SearchTree<T>::search(T v) const
{
	STNode<T>* tmp = root();

	while(tmp != nullptr && tmp->value != v)
	{
		if(v < tmp->value)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	return tmp;
}

template<typename T>
STNode<T>* SearchTree<T>::min() const
{
	if(empty())
		return nullptr;

	return _min(root());
}

template<typename T>
STNode<T>* SearchTree<T>::max() const
{
	if(empty())
		return nullptr;

	return _max(root());
}

template<typename T>
STNode<T>* SearchTree<T>::next(STNode<T> *n) const
{
	if(n->right != nullptr)
		return _min(n->right);

	STNode<T> *m = n->parent;

	while(m != nullptr && n == m->right)
	{
		n = m;
		m = m->parent;
	}

	return m;
}

template<typename T>
STNode<T>* SearchTree<T>::prev(STNode<T> *n) const
{
	if(n->left != nullptr)
		return _max(n->left);

	STNode<T> *m = n->parent;

	while(m != nullptr && n == m->left)
	{
		n = m;
		m = m->parent;
	}

	return m;
}

template<typename T>
STNode<T>* SearchTree<T>::insert(T v)
{
	STNode<T> *n = new STNode<T>;
	n->value = v;
	n->left = nullptr;
	n->right = nullptr;

	STNode<T> *tmp = root();
	STNode<T> *p = nullptr;

	while(tmp != nullptr)
	{
		p = tmp;

		if(n->value < tmp->value)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	n->parent = p;

	if(p == nullptr)
		m_root = n;
	else if(n->value < p->value)
		p->left = n;
	else
		p->right = n;

	m_size++;

	return n;
}

template<typename T>
void SearchTree<T>::remove(STNode<T> *n)
{
	if(n->left == nullptr)
		_transplant(n, n->right);
	else if(n->right == nullptr)
		_transplant(n, n->left);
	else
	{
		STNode<T> *m = _min(n->right);

		if(m->parent != n)
		{
			_transplant(m, m->right);
			m->right = n->right;
			m->right->parent = m;
		}

		_transplant(n, m);
		m->left = n->left;
		m->left->parent = m;
	}

	delete n;
}

template<typename T>
bool SearchTree<T>::contains(T v) const
{
	return search(v) != nullptr;
}

template<typename T>
void SearchTree<T>::print(std::ostream &os, STNode<T> *n)
{
	if(n == nullptr)
		os << "[ ]";
	else
		_print(os, n);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const SearchTree<T> &t)
{
	SearchTree<T>::print(os, t.root());
	return os;
}

template<typename T>
STNode<T>* SearchTree<T>::_min(STNode<T> *n) const
{
	while(n->left != nullptr)
		n = n->left;

	return n;
}

template<typename T>
STNode<T>* SearchTree<T>::_max(STNode<T> *n) const
{
	while(n->right != nullptr)
		n = n->right;

	return n;
}

template<typename T>
void SearchTree<T>::_transplant(STNode<T> *u, STNode<T> *v)
{
	if(u->parent == nullptr)
		m_root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if(v != nullptr)
		v->parent = u->parent;
}

template<typename T>
STNode<T>* SearchTree<T>::_copy(STNode<T> *n, STNode<T> *p)
{
	if(n == nullptr)
		return nullptr;

	STNode<T> *node = new STNode<T>;
	node->value = n->value;
	node->parent = p;
	node->left = _copy(n->left, node);
	node->right = _copy(n->right, node);
	m_size++;

	return node;
}

template<typename T>
void SearchTree<T>::_remove(STNode<T> *n)
{
	if(n != nullptr)
	{
		_remove(n->left);
		_remove(n->right);

		delete n;

		m_size--;
	}
}

template<typename T>
void SearchTree<T>::_print(std::ostream &os, STNode<T> *n)
{
	std::cout << "[ " << n->value << " ";

	if(n->left)
		_print(os, n->left);
	else
		os << "NULL ";

	if(n->right)
		_print(os, n->right);
	else
		os << "NULL ";

	std::cout << "] ";
}

