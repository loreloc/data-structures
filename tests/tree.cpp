
#include <iostream>

#include "tree.h"

int main(int argc, char *argv[])
{
	Tree<int> tree;
	TNode<int> *p;

	p = tree.insertRoot(1);
	tree.addChild(p, 2);
	tree.addChild(p, 4);
	p = tree.addChild(p, 8);
	tree.addChild(p, 3);
	tree.addChild(p, 6);
	p = tree.addChild(p, 9);
	p = tree.addChild(p, 8);
	p = tree.addChild(p, 7);
	tree.addChild(p, 6);
	tree.addChild(p, 1);
	tree.addChild(p, 2);
	tree.addChild(p, 3);

	std::cout << tree << std::endl;

	std::cout << tree.depth() << std::endl;

	std::cout << tree.width() << std::endl;

	tree.remove(p);

	std::cout << tree << std::endl;

	return 0;
}

