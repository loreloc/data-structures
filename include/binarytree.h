
#pragma once

#include <iostream>

template<class T>
struct BTNode
{
	T value;
	BTNode<T> *left;
	BTNode<T> *right;
	BTNode<T> *parent;
};

template<class T>
class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(const BinaryTree &t);
	~BinaryTree();

	BinaryTree &operator=(const BinaryTree &t);

	bool empty() const;
	size_t size() const;
	void clear();
	BTNode<T>* root() const;
	BTNode<T>* insertRoot(T v);
	BTNode<T>* insertLeft(BTNode<T> *n, T v);
	BTNode<T>* insertRight(BTNode<T> *n, T v);
	void removeLeft(BTNode<T> *n);
	void removeRight(BTNode<T> *n);

	void walkPreOrder() const;
	void walkInOrder() const;
	void walkPostOrder() const;

	static void print(std::ostream &os, BTNode<T> *n);

	template<class U>
	friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &t);

private:
	BTNode<T> *m_root;
	size_t m_size;

	BTNode<T> *_copy(BTNode<T> *n, BTNode<T> *p);
	void _remove(BTNode<T> *n);

	void _walkPreOrder(BTNode<T> *n) const;
	void _walkInOrder(BTNode<T> *n) const;
	void _walkPostOrder(BTNode<T> *n) const;

	static void _print(std::ostream &os, BTNode<T> *n);
};

template<typename T>
BinaryTree<T>::BinaryTree() :
	m_root(nullptr),
	m_size(0)
{

}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &t)
{
	m_size = 0;
	m_root = _copy(t.root(), nullptr);
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	_remove(m_root);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T> &t)
{
	if(this == &t)
		return *this;

	if(!empty())
		clear();

	m_root = _copy(t.root(), nullptr);

	return *this;
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
void BinaryTree<T>::clear()
{
	_remove(m_root);
	m_root = nullptr;
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
	m_root->parent = nullptr;

	return m_root;
}

template<typename T>
BTNode<T>* BinaryTree<T>::insertLeft(BTNode<T> *n, T v)
{
	if(n->left != nullptr)
		throw "node has already a left sub-tree";

	BTNode<T> *node = new BTNode<T>;
	node->value = v;
	node->left = nullptr;
	node->right = nullptr;
	node->parent = n;

	n->left = node;

	m_size++;

	return node;
}

template<typename T>
BTNode<T>* BinaryTree<T>::insertRight(BTNode<T> *n, T v)
{
	if(n->right != nullptr)
		throw "node has already a right sub-tree";

	BTNode<T> *node = new BTNode<T>;
	node->value = v;
	node->left = nullptr;
	node->right = nullptr;
	node->parent = n;

	n->right = node;

	m_size++;

	return node;
}

template<typename T>
void BinaryTree<T>::removeLeft(BTNode<T> *n)
{
	_remove(n->left);
	n->left = nullptr;
}

template<typename T>
void BinaryTree<T>::removeRight(BTNode<T> *n)
{
	_remove(n->right);
	n->right = nullptr;
}

template<typename T>
void BinaryTree<T>::walkPreOrder() const
{
	_walkPreOrder(root());
}

template<typename T>
void BinaryTree<T>::walkInOrder() const
{
	_walkInOrder(root());
}

template<typename T>
void BinaryTree<T>::walkPostOrder() const
{
	_walkPostOrder(root());
}

template<typename T>
void BinaryTree<T>::print(std::ostream &os, BTNode<T> *n)
{
	if(n == nullptr)
		os << "[ ]";
	else
		_print(os, n);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &t)
{
	BinaryTree<T>::print(os, t.root());
	return os;
}

template<typename T>
BTNode<T> *BinaryTree<T>::_copy(BTNode<T> *n, BTNode<T> *p)
{
	if(n == nullptr)
		return nullptr;

	BTNode<T> *node = new BTNode<T>;
	node->value = n->value;
	node->parent = p;
	node->left = _copy(n->left, node);
	node->right = _copy(n->right, node);
	m_size++;

	return node;
}

template<typename T>
void BinaryTree<T>::_remove(BTNode<T> *n)
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
void BinaryTree<T>::_walkPreOrder(BTNode<T> *n) const
{
	if(n != nullptr)
	{
		// do something with n

		_walkPreOrder(n->left);
		_walkPreOrder(n->right);
	}
}

template<typename T>
void BinaryTree<T>::_walkInOrder(BTNode<T> *n) const
{
	if(n != nullptr)
	{
		_walkInOrder(n->left);

		// do something with n

		_walkInOrder(n->right);
	}
}

template<typename T>
void BinaryTree<T>::_walkPostOrder(BTNode<T> *n) const
{
	if(n != nullptr)
	{
		_walkPostOrder(n->left);
		_walkPostOrder(n->right);

		// do something with n
	}
}

template<typename T>
void BinaryTree<T>::_print(std::ostream &os, BTNode<T> *n)
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

