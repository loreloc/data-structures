
#include "stack.h"

int main(int argc, char *argv[])
{
	Stack<int> stack;
	stack.push(0);
	stack.push(1);
	stack.push(2);
	stack.push(3);

	std::cout << stack << std::endl;

	stack.pop();

	std::cout << stack << std::endl;

	std::cout << stack.top() << std::endl;

	std::cout << stack.size() << std::endl;

	return 0;
}

