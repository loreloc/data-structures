
#pragma once

#include <iostream>

template<class T, class P>
class List
{
public:
	virtual T read(P p) const = 0;
	virtual void write(P p, T v) = 0;
	virtual P next(P p) const = 0;
	virtual P prev(P p) const = 0;
	virtual void clear() = 0;
	virtual bool empty() const = 0;
	virtual P begin() const = 0;
	virtual bool end(P p) const = 0;
	virtual void insert(P p, T v) = 0;
	virtual void remove(P p) = 0;
	virtual P find(T v) const = 0;
	virtual void pushBack(T v) = 0;
	virtual void pushFront(T v) = 0;
	virtual void popBack() = 0;
	virtual void popFront() = 0;

	virtual size_t size() const;
	virtual void invert();
};

template<class T, class P>
std::ostream &operator<<(std::ostream &os, const List<T, P> &l)
{
	P p = l.begin();

	os << "[ ";

	while(!l.end(p))
	{
		os << l.read(p) << " ";

		p = l.next(p);
	}

	os << "]";

	return os;
}

template<class T, class P>
size_t List<T, P>::size() const
{
	size_t size = 0;

	P p = begin();

	while(!end(p))
	{
		p = next(p);
		size++;
	}

	return size;
}

template<class T, class P>
void List<T, P>::invert()
{
	if(empty())
		return;

	T tmp;

	P p1 = begin();
	P p2 = begin();

	while(!end(next(p2)))
		p2 = next(p2);

	while(p1 != p2 && prev(p1) != p2)
	{
		tmp = read(p1);
		write(p1, read(p2));
		write(p2, tmp);

		p1 = next(p1);
		p2 = prev(p2);
	}
}

