
#include "deque.h"

int main(int argc, char *argv[])
{
	Deque<int> deque;
	deque.pushBack(0);
	deque.pushFront(1);
	deque.pushBack(2);
	deque.pushFront(3);

	std::cout << deque << std::endl;

	std::cout << deque.popBack() << std::endl;
	std::cout << deque.popFront() << std::endl;

	std::cout << deque << std::endl;

	std::cout << deque.size() << std::endl;

	return 0;
}

