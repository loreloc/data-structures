
#pragma once

#include <iostream>

template<class T>
struct BTNode
{
	T value;
	BTNode<T> *left;
	BTNode<T> *right;
};

template<class T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	bool empty() const;
	size_t size() const;
	BTNode<T>* root() const;
	BTNode<T>* insertRoot(T v);
	BTNode<T>* insertLeft(BTNode<T> *p, T v);
	BTNode<T>* insertRight(BTNode<T> *p, T v);
	void removeLeft(BTNode<T> *p);
	void removeRight(BTNode<T> *p);

	static void print(std::ostream &os, BTNode<T> *p);

	template<class U>
	friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &t);

private:
	BTNode<T> *m_root;
	size_t m_size;

	static void _remove(BTNode<T> *p, BinaryTree<T> &t);
	static void _print(std::ostream &os, BTNode<T> *p);
};

template<typename T>
BinaryTree<T>::BinaryTree() :
	m_root(nullptr),
	m_size(0)
{

}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	_remove(m_root, *this);
}

template<typename T>
bool BinaryTree<T>::empty() const
{
	return m_root == nullptr;
}

template<typename T>
size_t BinaryTree<T>::size() const
{
	return m_size;
}

template<typename T>
BTNode<T>* BinaryTree<T>::root() const
{
	return m_root;
}

template<typename T>
BTNode<T>* BinaryTree<T>::insertRoot(T v)
{
	if(!empty())
		throw "binary tree has already a root";

	m_root = new BTNode<T>;
	m_root->value = v;
	m_root->left = nullptr;
	m_root->right = nullptr;

	return m_root;
}

template<typename T>
BTNode<T>* BinaryTree<T>::insertLeft(BTNode<T> *p, T v)
{
	if(p->left != nullptr)
		throw "node has already a left sub-tree";

	BTNode<T> *node = new BTNode<T>;
	node->value = v;
	node->left = nullptr;
	node->right = nullptr;

	p->left = node;

	m_size++;

	return node;
}

template<typename T>
BTNode<T>* BinaryTree<T>::insertRight(BTNode<T> *p, T v)
{
	if(p->right != nullptr)
		throw "node has already a right sub-tree";

	BTNode<T> *node = new BTNode<T>;
	node->value = v;
	node->left = nullptr;
	node->right = nullptr;

	p->right = node;

	m_size++;

	return node;
}

template<typename T>
void BinaryTree<T>::removeLeft(BTNode<T> *p)
{
	_remove(p->left, *this);
}

template<typename T>
void BinaryTree<T>::removeRight(BTNode<T> *p)
{
	_remove(p->right, *this);
}

template<typename T>
void BinaryTree<T>::print(std::ostream &os, BTNode<T> *p)
{
	if(p == nullptr)
		os << "[ ]";
	else
		_print(os, p);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &t)
{
	BinaryTree<T>::print(os, t.root());
	return os;
}

template<typename T>
void BinaryTree<T>::_remove(BTNode<T> *p, BinaryTree<T> &t)
{
	if(p != nullptr)
	{
		_remove(p->left, t);
		_remove(p->right, t);

		delete p;

		t.m_size--;
	}
}

template<typename T>
void BinaryTree<T>::_print(std::ostream &os, BTNode<T> *p)
{
	std::cout << "[ " << p->value << " - ";

	if(p->left)
		_print(os, p->left);
	else
		os << "NULL ";

	if(p->right)
		_print(os, p->right);
	else
		os << "NULL ";

	std::cout << "] ";
}

