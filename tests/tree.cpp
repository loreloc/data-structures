
#include <iostream>

#include "tree.h"

int main(int argc, char *argv[])
{
	Tree<int> tree;
	TNode<int> *p1, *p2;

	p1 = tree.insertRoot(1);
	tree.addChild(p1, 2);
	p2 = tree.addChild(p1, 4);
	tree.addChild(p2, 3);
	tree.addChild(p2, 5);
	tree.addChild(p2, 7);
	p1 = tree.addChild(p1, 8);
	tree.addChild(p1, 3);
	tree.addChild(p1, 6);
	p1 = tree.addChild(p1, 9);
	p1 = tree.addChild(p1, 8);
	p1 = tree.addChild(p1, 7);
	tree.addChild(p1, 6);
	tree.addChild(p1, 1);
	tree.addChild(p1, 2);
	tree.addChild(p1, 3);

	std::cout << tree << std::endl;

	std::cout << tree.depth() << std::endl;

	std::cout << tree.width() << std::endl;

	tree.remove(p1);

	std::cout << tree << std::endl;

	return 0;
}

