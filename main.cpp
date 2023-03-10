#include "vector_iterator.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>
#include "is_iterator.hpp"
#include "reverse_iterator.hpp"

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


	//myvector.erase(myvector.begin() + 5);

	ft::vector<int> sv00(10);
	ft::vector<int> a;
	ft::vector<int> b;

	//std::vector<int>::iterator it = sv00.begin();

	//std::cout << ft::is_random_access_iterator<decltype(sv00.begin())::iterator_category>::value << std::endl;
	//v5.assign(5, 1);
	//ft::vector<int>::iterator it2 = sv00.begin();
	//ft::vector<int>::iterator it3 = sv00.end();
	//a.assign(it2, it3);
		
	a.assign(6, 1);

	for(ft::vector<int>::iterator it = a.begin();  it != a.end(); ++it)
		std::cout << *it << std::endl;
	
	ft::vector<int> kk;
	kk.push_back(1);
	kk.push_back(2);
	kk.push_back(3);
	kk.push_back(4);
	//kk.push_back(5);
	for(ft::vector<int>::iterator it = kk.begin();  it != kk.end(); ++it)
		std::cout << *it << std::endl;
	
	a.assign(kk.begin(), kk.end());
	
	for(ft::vector<int>::iterator it = a.begin();  it != a.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	a.insert(a.end(), 10);
	a.insert(a.begin() + 2, 4, 20);
	for(ft::vector<int>::iterator it = a.begin();  it != a.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	a.insert(a.end(), kk.begin(), kk.end());
	for(ft::vector<int>::iterator it = a.begin();  it != a.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	a.erase(a.begin() + 1, a.begin() + 4);
for(ft::vector<int>::iterator it = a.begin();  it != a.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;


	//a.assign(kk.begin(), kk.end());

	ft::vector<int> tmp(a.begin(), a.end());

	int	arr[] = {5,4,3,2,1};

	ft::vector<int> tmp2(arr, arr + sizeof(arr) / sizeof(arr[0]));
for(ft::vector<int>::iterator it = tmp2.begin();  it != tmp2.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

 
   ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  ft::reverse_iterator<ft::vector<int>::iterator> from;
  ft::reverse_iterator<ft::vector<int>::iterator> until;
  from = myvector.rbegin();
  until = myvector.rend();

  std::cout << "myvector has " << (until-from) << " elements.\n";
	
  ft::vector<int>::iterator it = tmp.begin();
  ft::vector<int>::iterator it2 = tmp.begin();

  if (it == it2)
	  std::cout << "true" << std::endl;
  else
	  std::cout << "false" << std::endl;


  it = 4 + it;
 // ft::vector<const int> cv;

 // cv.push_back(1);
	//int	bb[] = {1,2,3,4,5};

	//a.assign(bb, bb + 2);
	return (0);

}
