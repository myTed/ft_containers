#include <iostream>
#include <vector>


int	main()
{

	std::vector<int> v;

	for (int i = 0; i <=10; ++i)
		v.push_back(i);

	v.erase(v.begin() + 5);

	return (0);
}
