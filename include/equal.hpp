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
		while (first1 != last1)
		{
			if ((first2 == last2) || (*first1 > *first2))
				return (false);
			if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<typename InputIterator1, typename InputIterator2, typename Compare>
	typename ft::enable_if< ft::is_inputable_iterator<InputIterator1>::value
					&& ft::is_inputable_iterator<InputIterator2>::value , bool>::type
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2,
							Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2)
				return (false);
			if (comp(*first1, *first2))
				return (true);
			else
				return (false);
			++first1;
			++first2;
		}
		return (first2 != last2);
	}


	template<typename T>
	class bigger
	{
	public:
		bool operator()(const T& first, const T& last) {
			if (first > last)
				return (true);
			return (false);
		}
	};
}

#endif

