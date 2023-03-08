#ifndef __REVESRE_ITERATOR_HPP
#define __REVESRE_ITERATOR_HPP

#include <iterator>
#include "iterator_traits.hpp"

namespace ft
{
template<typename Iterator>
class reverse_iterator :
	public std::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
					typename ft::iterator_traits<Iterator>::value_type,
					typename ft::iterator_traits<Iterator>::difference_type,
					typename ft::iterator_traits<Iterator>::pointer,
					typename ft::iterator_traits<Iterator>::reference>
{
public:
	typedef	Iterator													iterator_type;
	typedef	typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef	typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef	typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef	typename ft::iterator_traits<Iterator>::reference			reference;
private:
	Iterator	_base;
public:
	/*construct*/
	reverse_iterator();
	explicit reverse_iterator(Iterator it);
	template <typename Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it);
	
	iterator_type		base() const;
	reference			operator*() const;
	reverse_iterator	operator+(difference_type n) const;
	reverse_iterator&	operator++();
	reverse_iterator	operator++(int);
	reverse_iterator&	operator+=(difference_type n);
	reverse_iterator	operator-(difference_type n) const;
	reverse_iterator&	operator--();
	reverse_iterator	operator--(int);
	reverse_iterator&	operator-=(difference_type n);
	pointer				operator->() const;
	reference			operator[](difference_type n) const;
};

template<typename Iterator>
reverse_iterator<Iterator>::reverse_iterator()
 : _base()
{}

template<typename Iterator>
reverse_iterator<Iterator>::reverse_iterator(Iterator it)
 : _base(it)
{}

template<typename Iterator>
template<typename Iter>
reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<Iter>& rev_it)
: _base(rev_it._base)
{}

template<typename Iterator>
typename reverse_iterator<Iterator>::iterator_type
reverse_iterator<Iterator>::base() const
{
	return (Iterator(_base));
}

template<typename Iterator>
typename reverse_iterator<Iterator>::reference
reverse_iterator<Iterator>::operator*() const
{
	return (*(_base - 1));
}
	
template<typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator+(difference_type n) const
{
	return (reverse_iterator(_base - n));
}
	
template<typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator++()
{
	--_base;
	return (*this);
}
	
template<typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator++(int)
{
	reverse_iterator tmp(_base);
	--_base;
	return (tmp);
}
	
template<typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator+=(difference_type n)
{
	_base -= n;
	return (*this);
}
	
template<typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator-(difference_type n) const
{
	return (reverse_iterator(_base + n));
}
	
template<typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator--()
{
	++_base;
	return (*this);
}

	
template<typename Iterator>
reverse_iterator<Iterator>
reverse_iterator<Iterator>::operator--(int)
{
	reverse_iterator tmp(_base);
	++_base;
	return (tmp);
}
	
template<typename Iterator>
reverse_iterator<Iterator>&
reverse_iterator<Iterator>::operator-=(difference_type n)
{
	_base+=n;
	return (*this);
}
	
template<typename Iterator>
typename reverse_iterator<Iterator>::pointer
reverse_iterator<Iterator>::operator->() const
{
	return (&(*_base));
}
	
template<typename Iterator>
typename reverse_iterator<Iterator>::reference
reverse_iterator<Iterator>::operator[](difference_type n) const
{
	return (*(_base - n - 1));
}

/*non-member funcion overloads*/
template<typename Iterator>
bool
operator==(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() == rhs.base());
}

template<typename Iterator>
bool
operator!=(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() != rhs.base());
}

template<typename Iterator>
bool
operator<(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() < rhs.base());
}

template<typename Iterator>
bool
operator<=(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template<typename Iterator>
bool
operator>(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() > rhs.base());
}

template<typename Iterator>
bool
operator>=(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template<typename Iterator>
reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
{
	return (rev_it + n);
}

template<typename Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
{
	return (rhs.base() - lhs.base());
}

}

#endif

