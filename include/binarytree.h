
#pragma once

#include <iostream>

template<class T>
class BTNode
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
	BinaryTree(const BinaryTree &bt);
	~BinaryTree();

	void clear();

	BinaryTree &operator=(const BinaryTree &bt);

private:
	BTNode<T> *m_root;
	size_t m_size;

	void _clear(BTNode<T> *n);
};

template<typename T>
BinaryTree<T>::BinaryTree()
{
	m_root = nullptr;
	m_size = 0;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	clear();
}

template<typename T>
void BinaryTree<T>::clear()
{
	_clear(m_root);
}

template<typename T>
void BinaryTree<T>::_clear(BTNode<T> *n)
{
	if(n != nullptr)
	{
		_clear(n->left);
		_clear(n->right);

		delete n;
	}
}

