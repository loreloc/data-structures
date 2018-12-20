
#include "searchtree.h"

int main(int argc, char *argv[])
{
	SearchTree<int> st;
	st.insert(3);
	st.insert(2);
	st.insert(4);
	st.insert(0);
	st.insert(1);

	std::cout << st << std::endl;

	return 0;
}

