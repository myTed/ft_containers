#ifndef __EQUAL_HPP
#define __EQUAL_HPP
#include "enable_if.hpp"
#include "is_iterator.hpp"

namespace ft
{
	template <typename InputIterator1, typename InputIterator2>
	typename ft::enable_if< ft::is_inputable_iterator<InputIterator1>::value
					&& ft::is_inputable_iterator<InputIterator2>::value , bool>::type
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	typename ft::enable_if< ft::is_inputable_iterator<InputIterator1>::value
					&& ft::is_inputable_iterator<InputIterator2>::value , bool>::type
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
				BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}


	template<typename InputIterator1, typename InputIterator2>
	typename ft::enable_if< ft::is_inputable_iterator<InputIterator1>::value
					&& ft::is_inputable_iterator<InputIterator2>::value , bool>::type
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
			++first1;
			++first2;
		}
		return ((first1 == last1) && (first2 != last2));
	}

	template<typename InputIterator1, typename InputIterator2, typename Compare>
	typename ft::enable_if< ft::is_inputable_iterator<InputIterator1>::value
					&& ft::is_inputable_iterator<InputIterator2>::value , bool>::type
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2,
							Compare comp)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
			++first1;
			++first2;
		}
		return ((first1 == last1) && (first2 != last2));
	}

}

#endif

