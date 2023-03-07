#ifndef __IS_ITERATOR_HPP
#define __IS_ITERATOR_HPP
#include "enable_if.hpp"
#include <iterator>
#include "iterator_traits.hpp"

namespace ft
{
    template<typename T>
    struct is_input_iterator
    {
        static const bool value = false;
    };

    template<>
    struct is_input_iterator<std::input_iterator_tag>
    {
        static const bool value = true;
    };

    template<typename T>
    struct is_output_iterator
    {
        static const bool value = false;
    };

    template<>
    struct is_output_iterator<std::output_iterator_tag>
    {
        static const bool value = true;
    };

    template<typename T>
    struct is_forward_iterator
    {
        static const bool value = false;
    };

    template<>
    struct is_forward_iterator<std::forward_iterator_tag>
    {
        static const bool value = true;
    };

    template<typename T>
    struct is_bidirectional_iterator
    {
        static const bool value = false;
    };

    template<>
    struct is_bidirectional_iterator<std::bidirectional_iterator_tag>
    {
        static const bool value = true;
    };
	
    template<typename T>
    struct is_random_access_iterator
    {
        static const bool value = false;
    };
	
    template<>
    struct is_random_access_iterator<std::random_access_iterator_tag>
    {
        static const bool value = true;
    };


	template<typename iterator>
	struct is_inputable_iterator
	{
		static const bool value = ((!is_output_iterator<typename ft::iterator_traits<iterator>::iterator_category>::value) &&
			( is_input_iterator<typename ft::iterator_traits<iterator>::iterator_category>::value ||
			  is_forward_iterator<typename ft::iterator_traits<iterator>::iterator_category>::value ||
			  is_bidirectional_iterator<typename ft::iterator_traits<iterator>::iterator_category>::value ||
			  is_random_access_iterator<typename ft::iterator_traits<iterator>::iterator_category>::value));
	};
	
	template<>
	struct is_inputable_iterator<bool>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<signed char>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<short int>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<int>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<long int>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<long long int>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<unsigned char>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<unsigned short int>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<unsigned int>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<unsigned long int>
	{
		static const bool value = false;
	};

	template<>
	struct is_inputable_iterator<unsigned long long int>
	{
		static const bool value = false;
	};
}

#endif
