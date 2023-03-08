#ifndef __VECTOR_ITERATOR_HPP
#define __VECTOR_ITERATOR_HPP

#include <iterator>

template <typename T>
class Vector_iterator : public std::iterator<std::random_access_iterator_tag,
	T>
{
private:
	T* _p;
public:
	typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
	Vector_iterator();
	Vector_iterator(T* p);
	Vector_iterator(const Vector_iterator& rV);
	Vector_iterator&	operator=(const Vector_iterator& rV);
	Vector_iterator&	operator++();
	Vector_iterator		operator++(int);
	Vector_iterator&	operator--();
	Vector_iterator		operator--(int);
	bool				operator==(const Vector_iterator& rV) const;
	bool				operator!=(const Vector_iterator& rv) const;
	T&					operator*();
	const T&			operator*() const; 
	Vector_iterator&	operator+=(difference_type n);
	Vector_iterator		operator+(difference_type n) const;
	Vector_iterator&	operator-=(difference_type n);
	Vector_iterator		operator-(difference_type n) const;
	difference_type		operator-(const Vector_iterator& rV) const;
	T&					operator[](difference_type n);
	const T&			operator[](difference_type n) const;
	bool				operator<(const Vector_iterator& rV);
	bool				operator>(const Vector_iterator& rV);
	bool				operator>=(const Vector_iterator& rV);
	bool				operator<=(const Vector_iterator& rV);
};

template <typename T>
Vector_iterator<T>::Vector_iterator() : _p(0)
{};

template <typename T>
Vector_iterator<T>::Vector_iterator(T* p) : _p(p)
{};

template <typename T>
Vector_iterator<T>::Vector_iterator(const Vector_iterator& rV) : _p(rV._p) {};


template <typename T>
Vector_iterator<T>& Vector_iterator<T>::operator=(const Vector_iterator& rV)
{
	if (this == &rV)
		return (*this);
	_p = rV._p;
	return (*this);
}


	template <typename T>
Vector_iterator<T>& Vector_iterator<T>::operator++()
{
	_p++;
	return (*this);
}

template <typename T>
Vector_iterator<T> Vector_iterator<T>::operator++(int)
{
	Vector_iterator tmp(*this);
	_p++;
	return (tmp);
}

template <typename T>
Vector_iterator<T>& Vector_iterator<T>::operator--()
{
	_p--;
	return (*this);
}

template <typename T>
Vector_iterator<T> Vector_iterator<T>::operator--(int)
{
	Vector_iterator tmp(*this);
	_p--;
	return (tmp);
}

template <typename T>
bool	Vector_iterator<T>::operator==(const Vector_iterator& rV) const
{
	return (rV._p == _p);
}

template <typename T>
bool	Vector_iterator<T>::operator!=(const Vector_iterator& rV) const
{
	return (!operator==(rV));
}

template <typename T>
T& Vector_iterator<T>::operator*() { return (*_p); }

template <typename T>
const T& Vector_iterator<T>::operator*() const { return (*_p); }


template <typename T>	
typename Vector_iterator<T>::difference_type
Vector_iterator<T>::operator-(const Vector_iterator& rV) const
{
	return (this->_p - rV._p);
}

template <typename T>
Vector_iterator<T>& 
Vector_iterator<T>::operator+=(difference_type n)
{
	_p += n;
	return (*this);
}
	
template <typename T>
Vector_iterator<T> 
Vector_iterator<T>::operator+(difference_type n) const
{
	return (Vector_iterator(_p + n));
}
	

template <typename T>
Vector_iterator<T>& 
Vector_iterator<T>::operator-=(difference_type n)
{
	_p -= n;
	return (*this);
}

template <typename T>
Vector_iterator<T> 
Vector_iterator<T>::operator-(difference_type n) const
{
	return (Vector_iterator(_p - n));
}

template <typename T>
T&
Vector_iterator<T>::operator[](difference_type n)
{
	return (_p[n]);
}

template <typename T>
const T&
Vector_iterator<T>::operator[](difference_type n) const
{
	return (_p[n]);
}

template <typename T>
bool
Vector_iterator<T>::operator<(const Vector_iterator& rV)
{
	return (_p < rV._p);
}
	

template <typename T>
bool
Vector_iterator<T>::operator>(const Vector_iterator& rV)
{
	return (_p > rV._p);
}
	
template <typename T>
bool
Vector_iterator<T>::operator>=(const Vector_iterator& rV)
{
	return (_p >= rV._p);
}
	
template <typename T>
bool
Vector_iterator<T>::operator<=(const Vector_iterator& rV)
{
	return (_p <= rV._p);
}
#endif
