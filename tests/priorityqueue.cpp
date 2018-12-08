
#include <iostream>

#include "priorityqueue.h"

int main(int argc, char *argv[])
{
	PriorityQueue<int> queue;
	queue.push(2);
	queue.push(5);
	queue.push(3);
	queue.push(0);
	queue.push(4);
	queue.push(1);
	queue.push(6);

	while(!queue.empty())
	{
		std::cout << queue.min() << std::endl;
		queue.pop();
	}

	return 0;
}

