
#include "searchtree.h"

int main(int argc, char *argv[])
{
	SearchTree<int> st;
	STNode<int> *p = st.insert(3);
	st.insert(2);
	st.insert(4);
	st.insert(0);
	st.insert(1);
	st.insert(5);

	std::cout << st << std::endl;

	std::cout << st.min()->value << std::endl;
	std::cout << st.max()->value << std::endl;

	st.remove(p);

	std::cout << st << std::endl;

	return 0;
}

