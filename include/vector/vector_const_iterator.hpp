#ifndef __CONST_VECTOR_ITERATOR_HPP
#define __CONST_VECTOR_ITERATOR_HPP


#include <iterator>
#include "vector_iterator.hpp"

namespace ft
{
	template <typename T>
	struct remove_const
	{
		typedef T type;
	};

	template <typename T>
	struct remove_const<const T>
	{
		typedef T type;
	};
}


template <typename T>
class Vector_const_iterator : public std::iterator<std::random_access_iterator_tag,
	T, std::ptrdiff_t, const T*, const T&>
{
private:
	T* _p;
public:
	typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
	typedef	Vector_const_iterator<T>		iterator_type;
	Vector_const_iterator();
	Vector_const_iterator(T* p);
	Vector_const_iterator(Vector_iterator<T> rV);
	Vector_const_iterator(const Vector_const_iterator& rV);
	Vector_const_iterator(const int* p);
	Vector_const_iterator&	operator=(const Vector_const_iterator& rV);
	Vector_const_iterator&	operator++();
	Vector_const_iterator	operator++(int);
	Vector_const_iterator&	operator--();
	Vector_const_iterator	operator--(int);
	bool					operator==(const Vector_const_iterator& rV) const;
	bool					operator!=(const Vector_const_iterator& rv) const;
	const T&				operator*() const; 
	Vector_const_iterator&	operator+=(difference_type n);
	Vector_const_iterator	operator+(difference_type n) const;
	Vector_const_iterator&	operator-=(difference_type n);
	Vector_const_iterator	operator-(difference_type n) const;
	difference_type			operator-(const Vector_const_iterator& rV) const;
	const T&				operator[](difference_type n) const;
	bool					operator<(const Vector_const_iterator& rV) const;
	bool					operator>(const Vector_const_iterator& rV) const;
	bool					operator>=(const Vector_const_iterator& rV) const;
	bool					operator<=(const Vector_const_iterator& rV) const;
	const T*				operator->() const;
};

template <typename T>
Vector_const_iterator<T>::Vector_const_iterator() : _p(0)
{}

template <typename T>
Vector_const_iterator<T>::Vector_const_iterator(T* p) : _p(p)
{}

template <typename T>
Vector_const_iterator<T>::Vector_const_iterator(const Vector_const_iterator& rV) : _p(rV._p) {}


template <typename T>
Vector_const_iterator<T>::Vector_const_iterator(Vector_iterator<T> rV)
	: _p(&(*rV))
{}

template <typename T>
Vector_const_iterator<T>& Vector_const_iterator<T>::operator=(const Vector_const_iterator& rV)
{
	if (this == &rV)
		return (*this);
	_p = rV._p;
	return (*this);
}

template <typename T>
Vector_const_iterator<T>& Vector_const_iterator<T>::operator++()
{
	_p++;
	return (*this);
}

template <typename T>
Vector_const_iterator<T> Vector_const_iterator<T>::operator++(int)
{
	Vector_const_iterator tmp(*this);
	_p++;
	return (tmp);
}

template <typename T>
Vector_const_iterator<T>& Vector_const_iterator<T>::operator--()
{
	_p--;
	return (*this);
}

template <typename T>
Vector_const_iterator<T> Vector_const_iterator<T>::operator--(int)
{
	Vector_const_iterator tmp(*this);
	_p--;
	return (tmp);
}

template <typename T>
bool	Vector_const_iterator<T>::operator==(const Vector_const_iterator& rV) const
{
	return (rV._p == _p);
}

template <typename T>
bool	Vector_const_iterator<T>::operator!=(const Vector_const_iterator& rV) const
{
	return (!operator==(rV));
}

template <typename T>
const T& Vector_const_iterator<T>::operator*() const { return (*_p); }


template <typename T>	
typename Vector_const_iterator<T>::difference_type
Vector_const_iterator<T>::operator-(const Vector_const_iterator& rV) const
{
	return (this->_p - rV._p);
}

template <typename T>
Vector_const_iterator<T>& 
Vector_const_iterator<T>::operator+=(difference_type n)
{
	_p += n;
	return (*this);
}
	
template <typename T>
Vector_const_iterator<T> 
Vector_const_iterator<T>::operator+(difference_type n) const
{
	return (Vector_const_iterator(_p + n));
}
	

template <typename T>
Vector_const_iterator<T>& 
Vector_const_iterator<T>::operator-=(difference_type n)
{
	_p -= n;
	return (*this);
}

template <typename T>
Vector_const_iterator<T> 
Vector_const_iterator<T>::operator-(difference_type n) const
{
	return (Vector_const_iterator(_p - n));
}

template <typename T>
const T&
Vector_const_iterator<T>::operator[](difference_type n) const
{
	return (_p[n]);
}

template <typename T>
bool
Vector_const_iterator<T>::operator<(const Vector_const_iterator& rV) const
{
	return (_p < rV._p);
}
	

template <typename T>
bool
Vector_const_iterator<T>::operator>(const Vector_const_iterator& rV) const
{
	return (_p > rV._p);
}
	
template <typename T>
bool
Vector_const_iterator<T>::operator>=(const Vector_const_iterator& rV) const
{
	return (_p >= rV._p);
}
	
template <typename T>
bool
Vector_const_iterator<T>::operator<=(const Vector_const_iterator& rV) const
{
	return (_p <= rV._p);
}

template <typename T>
const T*
Vector_const_iterator<T>::operator->() const
{
	return (_p);
}

/*non member function*/
template <typename T>
Vector_const_iterator<T>
operator+(typename Vector_const_iterator<T>::difference_type n, Vector_const_iterator<T> it)
{
	return (it + n);
}

template <typename T>
bool
operator<(const Vector_iterator<T>& rV, const Vector_const_iterator<T>& rcV) 
{
	return (rV.operator->() < rcV.operator->());
}

template <typename T>
bool
operator>(const Vector_iterator<T>& rV, const Vector_const_iterator<T>& rcV)
{
	return (rV.operator->() > rcV.operator->());	
}

template <typename T>
bool
operator<=(const Vector_iterator<T>& rV, const Vector_const_iterator<T>& rcV)
{
	return (!operator>(rV, rcV));
}

template <typename T>
bool
operator>=(const Vector_iterator<T>& rV, const Vector_const_iterator<T>& rcV)
{
	return (!operator<(rV, rcV));	
}

template <typename T>
bool
operator==(const Vector_iterator<T>& rV, const Vector_const_iterator<T>& rcV)
{
	return (rV.operator->() == rcV.operator->());	
}

template <typename T>
bool
operator!=(const Vector_iterator<T>& rV, const Vector_const_iterator<T>& rcV)
{
	return (rV.operator->() != rcV.operator->());	
}

template <typename T>
typename Vector_const_iterator<T>::difference_type
operator-(const Vector_iterator<T>& rV, const Vector_const_iterator<T>& rcV)
{
	return (rV.operator->() - rcV.operator->());
}

#endif

