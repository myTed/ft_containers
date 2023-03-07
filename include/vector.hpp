#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <memory>
#include <iterator>
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "vector_iterator.hpp"
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "iterator_traits.hpp"
#include "equal.hpp"

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
	void	allocateFromRef(allocator_type& alloc, size_type n, const vector& rV);
	void	allocateFromVal(allocator_type& alloc, size_type n, const value_type& val);
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
	size_type				size() const;
	size_type				max_size() const;
	void					resize(size_type n, value_type val = value_type());
	size_type				capacity() const;
	bool					empty() const;
	void					reserve(size_type n);
	
	/*element access*/
	reference				operator[] (size_type n);
	const_reference			operator[] (size_type n) const;
	reference				at (size_type n);
	const_reference			at (size_type n) const;
	reference				front();
	const_reference			front() const;
	reference				back();
	const_reference			back() const;
	
	/*Modifiers*/
	void					assign(size_type n, const value_type& val);
	template<typename InputIterator>
	typename ft::enable_if< ft::is_inputable_iterator<InputIterator>::value, void>::type
							assign(InputIterator first, InputIterator last);
	void					push_back(const value_type& val);
	void					pop_back();
	iterator				insert(iterator position, const value_type& val);
	void					insert(iterator position, size_type n, const value_type& val);
	template<typename InputIterator>
	typename ft::enable_if< ft::is_inputable_iterator<InputIterator>::value, void>::type
							insert(iterator position, InputIterator first, InputIterator last);
	iterator				erase(iterator position);
	iterator				erase(iterator first, iterator last);
	void					swap(vector& x);
	void					clear();
	
	/*Allocator*/
	allocator_type			get_allocator() const;
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
	allocator_type& alloc,
	size_type n, 
	const vector& rV
){
	_pElem = alloc.allocate(n);
	for (size_type idx = 0; idx < n; ++idx)
		alloc.construct(&(_pElem[idx]), rV[idx]);
	_elemCnt = n;
	_capacity = n;
}

template<typename T, typename Alloc>
void 
vector<T, Alloc>::allocateFromVal(
	allocator_type& alloc,
	size_type n, 
	const value_type& val
){
	_pElem = alloc.allocate(n);
	for (size_type idx = 0; idx < n; ++idx)
		alloc.construct(&(_pElem[idx]), val);
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
	return (iterator(_pElem + _elemCnt));
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
	T* tmp = _alloc.allocate(n);
	try {
		std::uninitialized_copy(begin(), end(), tmp);
	}
	catch(std::exception& e)
	{
		_alloc.deallocate(tmp, n);
		throw ;
	}
	//destroy	
	for (size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.destroy(&(_pElem[idx]));
	_alloc.deallocate(_pElem, _capacity);
	_pElem = tmp;
	_capacity = n;
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::resize(size_type n, value_type val)
{
	if (n < _elemCnt)
	{
		for(size_type idx = n; idx < _elemCnt; ++idx)
			_alloc.destory(&(_pElem[idx]));
		_elemCnt = n;
	}
	else if (n > _capacity)
	{
		reserve(n);
		for(size_type idx = _elemCnt; idx < n; ++idx)
			_alloc.construct(&(_pElem[idx]), val);
		_elemCnt = n;
	}
	else if (n > _elemCnt)
	{
		for(size_type idx = _elemCnt; idx < n; ++idx)
			_alloc.construct(&(_pElem[idx]), val);
		_elemCnt = n;
	}
	else
		return ;
	return ;
}

template<typename T, typename Alloc>
bool
vector<T, Alloc>::empty() const
{
	return (_elemCnt == 0);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::operator[] (size_type n)
{
	return (_pElem[n]);
}


template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference			
vector<T, Alloc>::operator[] (size_type n) const
{
	return (_pElem[n]);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference				
vector<T, Alloc>::at (size_type n)
{
	if (n >= _elemCnt)
		throw std::out_of_range("Invalid index");
	return (_pElem[n]);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference			
vector<T, Alloc>::at (size_type n) const
{
	if (n >= _elemCnt)
		throw std::out_of_range("Invalid index");
	return (_pElem[n]);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::front()
{
	return (_pElem[0]);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::front() const
{
	return (_pElem[0]);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::back()
{
	return (_pElem[_elemCnt - 1]);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::back() const
{
	return (_pElem[_elemCnt - 1]);
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::assign(size_type n, const value_type& val)
{
	for(size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.destroy(&_pElem[idx]);
	_elemCnt = 0;
	if ( n > _capacity)
	{
		T* tmp = _alloc.allocate(n);
		try
		{
			std::uninitialized_fill_n(tmp, n, val);
		}
		catch(std::exception& e)
		{
			_alloc.deallocate(tmp, n);
			throw ;
		}
		_pElem = tmp;
		_elemCnt = n;
		_capacity = n;
		return ;
	}
	std::uninitialized_fill_n(_pElem, n, val);
	_elemCnt = n;
}

template<typename T, typename Alloc>
template<typename InputIterator>
typename ft::enable_if< ft::is_inputable_iterator<InputIterator>::value, void>::type
vector<T, Alloc>::assign(InputIterator first, InputIterator last)
{

	size_type dist = std::distance(first, last);
	if (dist == 0)
		return ;
	if (_elemCnt == 0)
		return ;
	if (dist > _capacity)
	{
		T* tmp = _alloc.allocate(dist);
		try {
			std::uninitialized_copy(first, last, tmp);
		}
		catch(std::exception& e)
		{
			_alloc.deallocate(tmp, dist);
			throw ;
		}
		for(size_type idx = 0; idx < _elemCnt; ++idx)
			_alloc.destroy(&_pElem[idx]);
		_alloc.deallocate(_pElem, _capacity);
		_pElem = tmp;
		_elemCnt = dist;
		_capacity = dist;
		return ;
	}
	for (size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.destroy(&_pElem[idx]);
	_elemCnt = 0;
	std::uninitialized_copy(first, last, _pElem);
	_elemCnt = dist;
	_capacity = dist;
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::push_back(const value_type& val)
{
	if (_elemCnt >= _capacity)
	{
		size_type doubleCapacity = _capacity * 2;
		if (doubleCapacity == 0)
			doubleCapacity = 2;
		reserve(doubleCapacity);
	}
	_alloc.construct(&_pElem[_elemCnt], val);
	_elemCnt++;
}


template<typename T, typename Alloc>
void
vector<T, Alloc>::pop_back()
{
	_alloc.destroy(&_pElem[_elemCnt - 1]);
	--_elemCnt;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::insert(iterator position, const value_type& val)
{
	if (_elemCnt >= _capacity)
	{
		reserve(_elemCnt * 2);
		if (position == end())
			push_back(val);
		else
		{
			std::uninitialized_copy(position, end(), position + 1);
			_alloc.construct(&(_pElem[position]), val);
			_elemCnt++;
		}
		return (iterator(position));
	}
	if (position == end())
	{
		push_back(val);
		_elemCnt++;
		return (iterator(position));
	}
	try
	{
		std::uninitialized_copy(position, end(), position + 1);
	}
	catch(std::exception& e)
	{
		_elemCnt = std::distance(begin(), position);
		throw ;
	}
	_alloc.destroy(&_pElem[position]);
	_alloc.construct(&(_pElem[position]), val);
	_elemCnt++;
	return (iterator(position));
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
{
	size_type dist = std::distance(position, end());
	if (dist == 0)
		return ;
	if (_elemCnt + n > _capacity)
	{
		size_type _tmpCap = _capacity;
		size_type _target = _capacity + n;
		while (_tmpCap <= _target)
			_tmpCap <<= 1;
		reserve(_tmpCap);
		std::uninitialized_copy(position, position + dist, end() - dist);
		std::uninitialized_fill_n(position, n, val);
		return ;
	}
	std::uninitialized_copy(position, position + dist, end() - dist);
	std::uninitialized_fill_n(position, n, val);
	return ;
}

template<typename T, typename Alloc>
template<typename InputIterator>
typename ft::enable_if< ft::is_inputable_iterator<InputIterator>::value, void>::type
		vector<T,Alloc>::insert(iterator position, InputIterator first, InputIterator last)
{
	size_type dist = std::distance(first, last);
	if (dist == 0)
		return ;
	if (_elemCnt + dist > _capacity)
	{
		size_type	_tmpCap = _capacity;
		size_type	_target = _capacity + dist;
		while (_tmpCap <= _target)
			_tmpCap <<= 1;
		reserve(_tmpCap);
		std::uninitialized_copy(position, position + dist, end() - dist);
		std::uninitialized_copy(first, last, position);
		return ;
	}
	std::uninitialized_copy(position, position + dist, end() - dist);
	std::uninitialized_copy(first, last, position);
	return ;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator position)
{
	size_type dist = std::distance(position, end());
	if (dist == 1)
	{
		pop_back();
		return (iterator(end()));
	}
	_alloc.distroy(&(*position));
	std::uninitialized_copy(position + 1, end(), position);
	--_elemCnt;
	return (iterator(position));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator first, iterator last)
{
	size_type dist = std::distance(first, last);
	T* startAddr = &(*first);
	for(size_type idx = 0; idx < dist; ++idx, ++startAddr)
	{
		_alloc.distroy(startAddr);
		--_elemCnt;
	}
	std::uninitialized_copy(++last, end(), first);
	return (first);
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::swap(vector& x)
{
	std::swap(x._alloc, this->_alloc);
	std::swap(x._capacity, this->_capacity);
	std::swap(x._elemCnt, this->_elemCnt);
	std::swap(x._pElem, this->_pElem);
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::clear()
{
	for(size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.distroy(&(_pElem[idx]));
	_elemCnt = 0;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::allocator_type
vector<T, Alloc>::get_allocator() const
{
	return (_alloc);
}

/*Non-member function overloads*/
template <typename T, typename Alloc>
	bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T, typename Alloc>
	bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T, typename Alloc>
	bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T, typename Alloc>
	bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), bigger<T>()));
}

template <typename T, typename Alloc>
	bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), bigger<T>()));
}

template <typename T, typename Alloc>
	bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T, typename Alloc>
	void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
{
	x.swap(y);
}

}
#endif
