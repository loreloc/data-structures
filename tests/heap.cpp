
#include <iostream>

#include "heap.h"

int main(int argc, char *argv[])
{
	Heap<int> heap;
	heap.insert(2);
	heap.insert(5);
	heap.insert(3);
	heap.insert(0);
	heap.insert(4);
	heap.insert(1);
	heap.insert(6);

	while(!heap.empty())
	{
		std::cout << heap.min() << std::endl;
		heap.pop();
	}

	return 0;
}

