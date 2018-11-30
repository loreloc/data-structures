
#pragma once

#include <iostream>
#include <cstring>

#include "linkedlist.h"

template<class K, class T>
class HTNode
{
public:
	K key;
	T value;
	HTNode<K, T> *next;
	HTNode<K, T> *prev;
};

template<class K>
class Hash
{
public:
	size_t operator()(K k) const;
};

template<class K, class T>
class HashTable
{
public:
	HashTable(size_t d);
	HashTable(const HashTable &ht);
	~HashTable();

	HashTable &operator=(const HashTable &ht);

	T& operator[](K k);
	T operator[](K k) const;

	size_t size() const;
	size_t divisor() const;

	bool empty() const;
	void clear();
	T get(K k) const;
	void insert(K k, T v);
	void remove(K k);
	void resize(size_t d);

	LinkedList<T> values() const;
	LinkedList<K> keys() const;

	template<class U, class V>
	friend std::ostream &operator<<(std::ostream &os, const HashTable<U, V> &ht);

private:
	HTNode<K, T> **m_table;
	Hash<K> m_hash;
	size_t m_size;
	size_t m_divisor;

	HTNode<K, T> *_search(K k, size_t h) const;
};

template<typename K, typename T>
HashTable<K, T>::HashTable(size_t d)
{
	if(d == 0)
		d = 1;

	m_divisor = d;
	m_size = 0;

	m_table = new HTNode<K, T> *[m_divisor];
	
	for(size_t i = 0; i < m_divisor; i++)
		m_table[i] = nullptr;
}

template<typename K, typename T>
HashTable<K, T>::HashTable(const HashTable<K, T> &ht)
{
	m_divisor = ht.m_divisor;
	m_size = 0;

	m_table = new HTNode<K, T>*[m_divisor];

	for(size_t i = 0; i < ht.m_divisor; i++)
	{
		HTNode<K, T> *tmp = ht.m_table[i];

		while(tmp != nullptr)
		{
			insert(tmp->key, tmp->value);

			tmp = tmp->next;
		}
	}
}

template<typename K, typename T>
HashTable<K, T>::~HashTable()
{
	clear();
	delete [] m_table;
}

template<typename K, typename T>
HashTable<K, T> &HashTable<K, T>::operator=(const HashTable<K, T> &ht)
{
	if(this == &ht)
		return *this;

	if(!empty())
	{
		clear();
		delete [] m_table;
	}

	m_divisor = ht.m_divisor;

	m_table = new HTNode<K, T>*[m_divisor];

	for(size_t i = 0; i < ht.m_divisor; i++)
	{
		HTNode<K, T> *tmp = ht.m_table[i];

		while(tmp != nullptr)
		{
			insert(tmp->key, tmp->value);

			tmp = tmp->next;
		}
	}

	return *this;
}

template<typename K, typename T>
T& HashTable<K, T>::operator[](K k)
{
	size_t h = m_hash(k) % m_divisor;

	HTNode<K, T> *e = _search(k, h);

	if(e == nullptr)
		throw "element not found";

	return e->value;
}

template<typename K, typename T>
T HashTable<K, T>::operator[](K k) const
{
	return get(k);
}

template<typename K, typename T>
size_t HashTable<K, T>::size() const
{
	return m_size;
}

template<typename K, typename T>
size_t HashTable<K, T>::divisor() const
{
	return m_divisor;
}

template<typename K, typename T>
bool HashTable<K, T>::empty() const
{
	return m_size == 0;
}

template<typename K, typename T>
void HashTable<K, T>::clear()
{
	for(size_t i = 0; i < m_divisor; i++)
	{
		HTNode<K, T> *tmp = m_table[i];

		while(tmp != nullptr)
		{
			HTNode<K, T> *node = tmp;
			tmp = tmp->next;
			delete node;
		}
	}

	m_size = 0;
}

template<typename K, typename T>
T HashTable<K, T>::get(K k) const
{
	size_t h = m_hash(k) % m_divisor;

	HTNode<K, T> *e = _search(k, h);

	if(e == nullptr)
		throw "element not found";

	return e->value;
}

template<typename K, typename T>
void HashTable<K, T>::insert(K k, T v)
{
	size_t h = m_hash(k) % m_divisor;

	HTNode<K, T> *e = _search(k, h);

	if(e == nullptr)
	{
		HTNode<K, T> *node = new HTNode<K, T>;
		node->key = k;
		node->value = v;
		node->next = m_table[h];
		node->prev = nullptr;

		if(m_table[h] != nullptr)
			m_table[h]->prev = node;

		m_table[h] = node;

		m_size++;
	}
	else
	{
		e->value = v;
	}
}

template<typename K, typename T>
void HashTable<K, T>::remove(K k)
{
	size_t h = m_hash(k) % m_divisor;

	HTNode<K, T> *e = _search(k, h);

	if(e == nullptr)
		throw "element not found";

	if(e->prev != nullptr)
		e->prev->next = e->next;
	else
		m_table[h] = e->next;

	if(e->next != nullptr)
		e->next->prev = e->prev;

	delete e;

	m_size--;
}

template<typename K, typename T>
void HashTable<K, T>::resize(size_t d)
{
	HashTable<K, T> other(d);

	for(size_t i = 0; i < m_divisor; i++)
	{
		HTNode<K, T> *tmp = m_table[i];

		while(tmp != nullptr)
		{
			other.insert(tmp->key, tmp->value);

			tmp = tmp->next;
		}
	}

	clear();
	delete [] m_table;

	*this = other;
}

template<typename K, typename T>
LinkedList<T> HashTable<K, T>::values() const
{
	LinkedList<T> values;

	for(size_t i = 0; i < m_divisor; i++)
	{
		HTNode<K, T> *tmp = m_table[i];

		while(tmp != nullptr)
		{
			values.pushBack(tmp->value);

			tmp = tmp->next;
		}
	}

	return values;
}

template<typename K, typename T>
LinkedList<K> HashTable<K, T>::keys() const
{
	LinkedList<K> keys;

	for(size_t i = 0; i < m_divisor; i++)
	{
		HTNode<K, T> *tmp = m_table[i];

		while(tmp != nullptr)
		{
			keys.pushBack(tmp->key);

			tmp = tmp->next;
		}
	}

	return keys;
}

template<typename K, typename T>
HTNode<K, T> *HashTable<K, T>::_search(K k, size_t h) const
{
	HTNode<K, T> *tmp = m_table[h];

	while(tmp != nullptr)
	{
		if(tmp->key == k)
			return tmp;

		tmp = tmp->next;
	}

	return nullptr;
}

template<class K, class T>
std::ostream &operator<<(std::ostream &os, const HashTable<K, T> &ht)
{
	for(size_t i = 0; i < ht.divisor(); i++)
	{
		os << i << ") [ ";

		HTNode<K, T> *tmp = ht.m_table[i];

		while(tmp != nullptr)
		{
			os << tmp->value << " ";

			tmp = tmp->next;
		}

		os << "]" << std::endl;
	}

	return os;
}

