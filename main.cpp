#include "vector_iterator.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>


int	main(void)
{
	int	num[] = {10, 20, 30, 40, 50};
	Vector_iterator<int> iter(num);

	for(size_t idx = 0; idx < (sizeof(num) / sizeof(num[0])); idx++, ++iter)
		std::cout << *iter << std::endl;

	ft::vector<int>::iterator iter2;

	ft::vector<int> v2(3);
	
	iter2 = v2.begin();
	
	for(int idx = 0; idx < 3; ++idx, ++iter2)
	{
		*iter2 = idx + 10;
	}

	ft::vector<int>::iterator iter3 = v2.begin();
	for(int idx = 0; idx < 3; ++idx, ++iter3)
		std::cout << *iter3 << std::endl;

	ft::vector<int> v3(5);
	ft::vector<int>::iterator iter4(v3.begin());
	*iter4 = 100;
	std::cout << "v3 : " << v3.size() << std::endl;
	std::cout << "v3 : " << *v3.begin() << std::endl;
	std::cout << "v3 : " << *v3.end() << std::endl;

	const ft::vector<int> v4(5);

	//std::cout << *v4.begin() << std::endl;
	std::vector<int> sv1(1);
	std::cout << v3.max_size() << std::endl;
	
	//std::cout << ft::vector<int>(1).max_size() << std::endl;
	ft::vector<int> v5;

	ft::vector<int>::reverse_iterator rpos1(v5.begin());
	ft::vector<int>::reverse_iterator rpos2(v5.end());


	return (0);

}
