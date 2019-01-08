
#include "binarytree.h"

int main(int argc, char *argv[])
{
	BinaryTree<int> tree;

	BTNode<int> *p0 = tree.insertRoot(0);

	BTNode<int> *p1 = tree.insertLeft(p0, 1);
	BTNode<int> *p2 = tree.insertRight(p0, 2);
	BTNode<int> *p3 = tree.insertLeft(p2, 3);
	BTNode<int> *p4 = tree.insertRight(p2, 4);
	BTNode<int> *p5 = tree.insertRight(p4, 5);

	tree.walkPreOrder();
	tree.walkInOrder();
	tree.walkPostOrder();

	std::cout << tree << std::endl;

	tree.removeRight(p2);

	std::cout << tree << std::endl;

	return 0;
}

