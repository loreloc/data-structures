
#include "queue.h"

int main(int argc, char *argv[])
{
	Queue<int> queue;
	queue.push(0);
	queue.push(1);
	queue.push(2);
	queue.push(3);

	std::cout << queue << std::endl;

	std::cout << queue.front() << std::endl;

	queue.pop();

	std::cout << queue << std::endl;

	std::cout << queue.size() << std::endl;

	return 0;
}

