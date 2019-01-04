
#include "linkedlist.h"
#include "vectorlist.h"

int main(int argc, char *argv[])
{
	std::cout << "linked list test" << std::endl;

	LinkedList<int> ll;
	ll.pushBack(2);
	ll.pushBack(3);
	ll.pushBack(0);
	ll.pushFront(1);

	std::cout << ll << std::endl;

	ll.insert(ll.find(2), 6);

	std::cout << ll << std::endl;

	ll.remove(ll.find(2));

	std::cout << ll << std::endl;

	ll.invert();

	std::cout << ll << std::endl;

	std::cout << ll.size() << std::endl << std::endl;

	ll.sort();

	std::cout << ll << std::endl;

	/* --------------------------------------------------------- */

	std::cout << "vector list test" << std::endl;

	VectorList<int> vl;
	vl.pushBack(2);
	vl.pushBack(4);
	vl.pushBack(3);
	vl.pushBack(0);
	vl.pushFront(1);

	std::cout << vl << std::endl;

	vl.insert(vl.find(2), 1);

	std::cout << vl << std::endl;

	vl.remove(vl.find(2));

	std::cout << vl << std::endl;

	vl.invert();

	std::cout << vl << std::endl;

	std::cout << vl.size() << std::endl << std::endl;

	vl.sort();

	std::cout << vl << std::endl;

	return 0;
}

