#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <memory>
#include <iterator>
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "vector_iterator.hpp"

namespace ft {
template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
	typedef		T																value_type;
	typedef		std::allocator<value_type>										allocator_type;
	typedef		typename	allocator_type::reference							reference;
	typedef		typename	allocator_type::const_reference 					const_reference;
	typedef		typename	allocator_type::pointer								pointer;
	typedef		typename	allocator_type::const_pointer 						const_pointer;
	typedef		Vector_iterator<T>												iterator;
	typedef		const Vector_iterator<T>										const_iterator;
	typedef		std::reverse_iterator<iterator>									reverse_iterator;
	typedef		std::reverse_iterator<const_iterator>							const_reverse_iterator;
	typedef		typename	std::iterator_traits<iterator>::difference_type		difference_type;
	typedef		size_t															size_type;
private:
	allocator_type																_alloc;
	T*																			_pElem;
	size_type																	_elemCnt;
	size_type																	_capacity;
private:
	void	allocateFromRef(const allocator_type& alloc, int n, const vector& rV);
	void	allocateFromVal(const allocator_type& alloc, int n, const value_type& val);
public:
	/*constructor*/
	explicit	vector(const allocator_type& alloc = allocator_type());
	explicit	vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type());
	vector(const vector& rV);
	/*copy operator*/
	vector& operator=(const vector& rV);
	/*destructor*/
	//~vector();

	/*iterators*/
	iterator 				begin();
	const_iterator			begin() const;
	iterator				end();
	const_iterator 			end() const;
	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;

	/*Capacity*/
	size_type size() const;
	size_type max_size() const;
	size_type capacity() const;
	void	reserve(size_type n);

	/*Modifiers*/
	void	push_back(const value_type& val);
};

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const allocator_type& alloc)
: _alloc(alloc), _pElem(0), _elemCnt(0), _capacity(0)
{
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(
	size_type n,
	const value_type& val,
	const allocator_type& alloc)
: _alloc(alloc), _pElem(0), _elemCnt(0), _capacity(0)
{
	try
	{
		allocateFromVal(_alloc, n, val);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		throw ;
	}
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(
	const vector& rV)
	: _alloc(rV._alloc), _pElem(0), _elemCnt(0), _capacity(0)
{
	try
	{
		allocateFromRef(_alloc, rV.size(), rV);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		throw ;
	}
}

template<typename T, typename Alloc>
void 
vector<T, Alloc>::allocateFromRef(
	const allocator_type& alloc,
	int n, 
	const vector& rV
){
	_pElem = alloc.allocate(n);
	for (size_type idx = 0; idx < n; ++idx)
		alloc.construct(&(_pElem[idx], rV[idx]));
	_elemCnt = n;
	_capacity = n;
}

template<typename T, typename Alloc>
void 
vector<T, Alloc>::allocateFromVal(
	const allocator_type& alloc,
	int n, 
	const value_type& val
){
	_pElem = alloc.allocate(n);
	for (size_type idx = 0; idx < n; ++idx)
		alloc.construct(&(_pElem[idx], val));
	_elemCnt = n;
	_capacity = n;
}

template<typename T, typename Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(
	const vector& rV)
{
	if (this == &rV)
		return (*this);
	for(size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.destroy(&(_pElem[idx]));
	_alloc.deallocate(_pElem, _elemCnt);
	
	try
	{
		allocatedFromRef(rV.size(), rV);
	}
	catch(std::exception& e)
	{
		throw ;
	}
	return (*this);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
{
	return (_capacity);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
{
	return (std::numeric_limits<vector<T, Alloc>::size_type>::max() / sizeof(value_type));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T,Alloc>::size() const
{
	return (_elemCnt);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::begin()
{
	return (iterator(_pElem));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::begin() const
{
	return (iterator(_pElem));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::end()
{
	if (_elemCnt == 0)
		return (iterator(_pElem));
	return (iterator(_pElem + sizeof(value_type)));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::end() const
{
	if (_elemCnt == 0)
		return (iterator(_pElem));
	return (iterator(_pElem + sizeof(value_type)));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rbegin()
{
	return (reverse_iterator(end()));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rbegin() const
{
	return (const_reverse_iterator(end()));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rend()
{
	return (reverse_iterator(begin()));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rend() const
{
	return (const_reverse_iterator(begin()));
}


template<typename T, typename Alloc>
void
vector<T, Alloc>::reserve(size_type n)
{
	if (n <= _capacity)
		return ;
	if (n > max_size())
		throw std::length_error("overed length alloc call!");
	if (_elemCnt * 2 > max_size())
		throw std::length_error("can't alloc huge memory");
	
}


}
#endif
