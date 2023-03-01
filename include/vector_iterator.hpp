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
	Vector_iterator();
	Vector_iterator(T* p);
	Vector_iterator(const Vector_iterator& rV);
	Vector_iterator& operator=(const Vector_iterator& rV);
	Vector_iterator& operator++();
	Vector_iterator operator++(int);
	Vector_iterator& operator--();
	Vector_iterator operator--(int);
	bool	operator==(const Vector_iterator& rV) const;
	bool	operator!=(const Vector_iterator& rv) const;
	T& operator*();
	const T& operator*() const; 
	T* operator->();
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
	return (rV.p == _p);
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
T* Vector_iterator<T>::operator->() { return (_p); };
#endif
