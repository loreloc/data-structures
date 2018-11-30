
#include "linkedlist.h"
#include "vectorlist.h"

int main(int argc, char *argv[])
{
	std::cout << "linked list test" << std::endl;

	LinkedList<int> ll;
	ll.pushBack(1);
	ll.pushBack(2);
	ll.pushBack(3);
	ll.pushFront(0);

	std::cout << ll << std::endl;

	ll.insert(ll.find(2), 4);

	std::cout << ll << std::endl;

	ll.remove(ll.find(2));

	std::cout << ll << std::endl;

	ll.invert();

	std::cout << ll << std::endl;

	std::cout << ll.size() << std::endl << std::endl;

	/* --------------------------------------------------------- */

	std::cout << "vector list test" << std::endl;

	VectorList<int> vl;
	vl.pushBack(1);
	vl.pushBack(2);
	vl.pushBack(3);
	vl.pushBack(4);
	vl.pushFront(0);

	std::cout << vl << std::endl;

	vl.insert(vl.find(2), 5);

	std::cout << vl << std::endl;

	vl.remove(vl.find(2));

	std::cout << vl << std::endl;

	vl.invert();

	std::cout << vl << std::endl;

	std::cout << vl.size() << std::endl << std::endl;

	return 0;
}

