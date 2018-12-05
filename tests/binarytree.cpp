
#include "binarytree.h"

int main(int argc, char *argv[])
{
	BinaryTree<int> tree;
	BTNode<int> *p;

	p = tree.insertRoot(0);
	tree.insertLeft(p, 1);
	p = tree.insertRight(p, 2);
	tree.insertLeft(p, 3);
	p = tree.insertRight(p, 4);
	tree.insertRight(p, 5);

	std::cout << tree << std::endl;

	return 0;
}

