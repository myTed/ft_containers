#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <memory>
#include <iterator>
#include <string>
#include <iostream>
#include <limits>
#include <exception>
#include <cstring>
#include "vector_iterator.hpp"
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "iterator_traits.hpp"
#include "equal.hpp"
#include "reverse_iterator.hpp"
#include "vector_const_iterator.hpp"

namespace ft {
template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
	typedef		T																value_type;
	typedef		Alloc															allocator_type;
	typedef		typename	allocator_type::reference							reference;
	typedef		typename	allocator_type::const_reference 					const_reference;
	typedef		typename	allocator_type::pointer								pointer;
	typedef		typename	allocator_type::const_pointer 						const_pointer;
	typedef		Vector_iterator<T>												iterator;
	typedef		Vector_const_iterator<T>										const_iterator;
	typedef		ft::reverse_iterator<iterator>									reverse_iterator;
	typedef		ft::reverse_iterator<const_iterator>							const_reverse_iterator;
	typedef		typename	ft::iterator_traits<iterator>::difference_type		difference_type;
	typedef		size_t															size_type;
private:
	allocator_type																_alloc;
	T*																			_pElem;
	size_type																	_elemCnt;
	size_type																	_capacity;
private:
	void	allocateFromRef(size_type n, const vector& rV);
	void	allocateFromVal(size_type n, const value_type& val);
	void	reserve_copy(iterator position, size_type newCapacity,  size_type n, const value_type& val);
	template<typename InputIterator>
	typename ft::enable_if< ft::is_inputable_iterator<InputIterator>::value, void>::type
	reserve_copy_iter(iterator position, size_type newCapacity, InputIterator first, InputIterator last);
public:
	/*constructor*/
	explicit	vector(const allocator_type& alloc = allocator_type());
	explicit	vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type());

	template<typename InputIterator>
				vector(InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type(),
						typename ft::enable_if< ft::is_inputable_iterator<InputIterator>::value, void*>::type last_tmp = 0);

	vector(const vector& rV);

	vector& operator=(const vector& rV);
	/*destructor*/
	~vector();

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
	allocateFromVal(n, val);
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(
	const vector& rV)
	: _alloc(rV._alloc), _pElem(0), _elemCnt(0), _capacity(0)
{
	allocateFromRef(rV.size(), rV);
}

template<typename T, typename Alloc>
template<typename InputIterator>
vector<T, Alloc>::vector(InputIterator first, InputIterator last,
						const allocator_type& alloc,
						typename ft::enable_if< ft::is_inputable_iterator<InputIterator>::value, void*>::type tmp)
	: _alloc(alloc)
{
	static_cast<void>(tmp);
	difference_type dist = std::distance(first, last);
	_pElem = _alloc.allocate(dist);
	std::uninitialized_copy(first, last, _pElem);
	_elemCnt = dist;
	_capacity = dist;
}

template<typename T, typename Alloc>
vector<T, Alloc>::~vector()
{
	for(size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.destroy(&_pElem[idx]);
	_alloc.deallocate(_pElem, _capacity);
}

template<typename T, typename Alloc>
void 
vector<T, Alloc>::allocateFromRef(
	size_type n, 
	const vector& rV
){
	if (n == 0)
		return ;
	_pElem = _alloc.allocate(n);
	for (size_type idx = 0; idx < n; ++idx)
		_alloc.construct(&(_pElem[idx]), rV[idx]);
	_elemCnt = n;
	_capacity = n;
}

template<typename T, typename Alloc>
void 
vector<T, Alloc>::allocateFromVal(
	size_type n, 
	const value_type& val
){
	if (n == 0)
		return ;
	_pElem = _alloc.allocate(n);
	for (size_type idx = 0; idx < n; ++idx)
		_alloc.construct(&(_pElem[idx]), val);
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
		allocateFromRef(rV.size(), rV);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() <<std::endl;
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
	return (std::numeric_limits<size_type>::max()/ sizeof(value_type));
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
	return (const_iterator(_pElem));
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
		return (const_iterator(_pElem));
	return (const_iterator(_pElem + _elemCnt));
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
	catch(...)
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
			_alloc.destroy(&(_pElem[idx]));
		_elemCnt = n;
	}
	else if (n > _capacity)
	{
		reserve(_capacity * 2);
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
		catch(...)
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
	if (dist > _capacity)
	{
		T* tmp = _alloc.allocate(dist);
		try {
			std::uninitialized_copy(first, last, tmp);
		}
		catch(...)
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
	if (_elemCnt == 0)
		return ;
	for (size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.destroy(&_pElem[idx]);
	_elemCnt = 0;
	std::uninitialized_copy(first, last, _pElem);
	_elemCnt = dist;
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
void
vector<T, Alloc>::reserve_copy(iterator position, size_type newCapacity,  size_type n, const value_type& val)
{
	//strong gurantee
	if (newCapacity > max_size())
		throw std::length_error("overed length alloc");
	T* tmp = _alloc.allocate(newCapacity);
	try {
		difference_type dist = std::distance(begin(), position);
		std::uninitialized_fill_n(tmp + dist, n, val);
		std::uninitialized_copy(begin(), position, tmp);
		std::uninitialized_copy(position, end(), tmp + dist + n);
	}
	catch(...)
	{
		_alloc.deallocate(tmp, newCapacity);
		throw ;
	}
	for(size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.destroy(&_pElem[idx]);
	_alloc.deallocate(_pElem, _capacity);
	_pElem = tmp;
	_elemCnt += n;
	_capacity = newCapacity;
}

template<typename T, typename Alloc>
template<typename InputIterator>
typename ft::enable_if< ft::is_inputable_iterator<InputIterator>::value, void>::type
vector<T, Alloc>::reserve_copy_iter(iterator position, size_type newCapacity, InputIterator first, InputIterator last)
{
	//strong gurantee
	if (newCapacity > max_size())
		throw std::length_error("overed length alloc");
	T* tmp = _alloc.allocate(newCapacity);
	difference_type dist = std::distance(begin(), position);
	try{
		std::uninitialized_copy(first, last, tmp + dist);
		std::uninitialized_copy(begin(), position, tmp);
		std::uninitialized_copy(position, end(), tmp + dist + std::distance(first, last));
	}
	catch(...)
	{
		_alloc.deallocate(tmp, newCapacity);
		throw ;
	}
	for (size_type idx = 0; idx < _elemCnt; ++idx)
		_alloc.destroy(&_pElem[idx]);
	_alloc.deallocate(_pElem, _capacity);
	_pElem = tmp;
	_elemCnt += std::distance(first, last);
	_capacity = newCapacity;
}


template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::insert(iterator position, const value_type& val)
{
	if (_elemCnt >= _capacity)
	{
		difference_type dist = std::distance(begin(), position);
		if (position == end())
		{
			reserve(_elemCnt * 2);
			push_back(val);
		}
		else
		{
			reserve_copy(position, 2 * _elemCnt, 1, val);
		}
		return (iterator(_pElem + dist));
	}
	if (position == end())
	{
		push_back(val);
		return (iterator(position));
	}
	iterator lastElemPosition(end() - 1);
	for (; lastElemPosition != position; --lastElemPosition)
		*(lastElemPosition + 1) = *lastElemPosition;
	*(lastElemPosition + 1) = *lastElemPosition;
	_alloc.construct(&_pElem[std::distance(begin(), position)], val);
	++_elemCnt;
	return (iterator(position));
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
{
	if (n == 0)
		return ;
	if (_elemCnt + n >= _capacity)
	{
		size_type _tmpCap = _elemCnt + n;
		reserve_copy(position, _tmpCap, n, val);
		return ;
	}
	if (position == end())
	{
		std::uninitialized_fill_n(end(), n, val);
		_elemCnt += n;
		return ;
	}
	iterator lastElemPosition(end() - 1);
	for (; lastElemPosition != position; --lastElemPosition)
		*(lastElemPosition + n) = *lastElemPosition;
	*(lastElemPosition + n) = *lastElemPosition;
	std::uninitialized_fill_n(position, n, val);
	_elemCnt += n;
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
	if (_elemCnt + dist >= _capacity)
	{
		size_type	_tmpCap = _capacity;
		size_type	_target = _capacity + dist;
		if (_tmpCap == 0)
			_tmpCap = _target;
		else
		{
			while (_tmpCap <= _target)
				_tmpCap <<= 1;
		}
		reserve_copy_iter(position, _tmpCap, first, last);
		return ;
	}
	if (position == end())
	{
		std::uninitialized_copy(first, last, end());
		_elemCnt += dist;
		return ;
	}
	iterator lastElemPosition(end() - 1);
	for (; lastElemPosition != position; --lastElemPosition)
		*(lastElemPosition + dist) = *lastElemPosition;
	*(lastElemPosition + dist) = *lastElemPosition;
	std::uninitialized_copy(first, last, position);
	_elemCnt += dist;
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
	_alloc.destroy(&(*position));
	std::memmove(&(*position), (&(*position) + 1), dist * sizeof(value_type));
	--_elemCnt;
	return (iterator(position));
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator first, iterator last)
{
	size_type dist = std::distance(first, last);
	size_type move_cnt = std::distance(last, end());
	T* startAddr = &(*first);
	for(size_type idx = 0; idx < dist; ++idx, ++startAddr)
		_alloc.destroy(startAddr);
	std::memmove(&(*first), &(*last), move_cnt * sizeof(value_type));
	_elemCnt -= dist;
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
		_alloc.destroy(&(_pElem[idx]));
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
	typename ft::vector<T, Alloc>::size_type	lhs_size = lhs.size();
	typename ft::vector<T, Alloc>::size_type	rhs_size = rhs.size();

	if (lhs_size != rhs_size)
		return (false);
	if ((lhs_size == 0) && (rhs_size == 0))
		return (true);
	if (lhs_size > rhs_size)
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	return (ft::equal(rhs.begin(), rhs.end(), lhs.begin()));
}

template <typename T, typename Alloc>
	bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!operator==(lhs, rhs));
}

template <typename T, typename Alloc>
	bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T, typename Alloc>
	bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!operator<=(lhs, rhs));
}

template <typename T, typename Alloc>
	bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (operator<(lhs, rhs) || operator==(lhs, rhs));
}

template <typename T, typename Alloc>
	bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!operator<(lhs, rhs));
}

} //namespace_for_ft

namespace std
{
	template <typename T, typename Alloc>
		void	swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y)
	{
		x.swap(y);
	}
}
#endif
