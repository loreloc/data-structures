
#include <string>

#include "hashtable.h"

template<>
class Hash<std::string>
{
public:
	size_t operator()(std::string k) const
	{
		size_t h = 0;

		for(size_t i = 0; i < k.size(); i++)
			h += k[i];

		return h;
	}
};

int main(int argc, char *argv[])
{
	HashTable<std::string, int> ht(5);

	ht.insert("a", 1);
	ht.insert("b", 2);
	ht.insert("c", 3);
	ht.insert("d", 4);
	ht.insert("e", 5);
	ht.insert("f", 6);
	ht.insert("g", 7);
	ht.insert("h", 8);
	ht.insert("i", 9);

	std::cout << ht << std::endl;

	ht.remove("b");

	std::cout << ht << std::endl;

	std::cout << ht.get("d") << std::endl;

	std::cout << ht.values() << std::endl;

	std::cout << ht.keys() << std::endl;

	ht.resize(8);

	std::cout << ht << std::endl;

	return 0;
}

