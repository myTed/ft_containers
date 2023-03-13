#ifndef __STACK_HPP
#define __STACK_HPP

#include "../vector/vector.hpp"
namespace ft
{
/*
template<typename T, typename Container>
class stack;

template<typename T, typename Container>
bool			operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
*/
template <typename T, typename Container = ft::vector<T> >
class stack
{
public:
		typedef	T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;
protected:
		container_type c;
public:
		explicit			stack(const container_type& ctnr = container_type());
		bool				empty() const;
		size_type			size() const;
		value_type&			top();
		const value_type& 	top() const;
		void				push(const value_type& val);
		void				pop();
		/*
		friend bool			operator== <T, Container>(const stack<T, Container>& lhs, const stack<T, Container>& rhs);
		*/
		template <typename U, typename ContainerU>
		friend bool			operator==(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs);
		template <typename U, typename ContainerU>
		friend bool			operator!=(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs);
		template <typename U, typename ContainerU>
		friend bool			operator<(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs);
		template <typename U, typename ContainerU>
		friend bool			operator<=(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs);
		template <typename U, typename ContainerU>
		friend bool			operator>(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs);
		template <typename U, typename ContainerU>
		friend bool			operator>=(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs);
};

template<typename T, typename Container>
stack<T, Container>::stack(const container_type& ctnr)
 : c(ctnr)
{}
	
template<typename T, typename Container>	
bool
stack<T, Container>::empty() const
{
	return (c.empty());
}
		
template<typename T, typename Container>
typename stack<T, Container>::size_type
stack<T, Container>::size() const
{
	return (c.size());
}

template<typename T, typename Container>
typename stack<T, Container>::value_type&
stack<T, Container>::top()
{
	return (*(c.end() - 1));
}


template<typename T, typename Container>
const typename stack<T, Container>::value_type&
stack<T, Container>::top() const
{
	return (*(c.end() - 1));
}

template<typename T, typename Container>
void
stack<T, Container>::push(const value_type& val)
{
	return (c.push_back(val));
}

template<typename T, typename Container>		
void
stack<T, Container>::pop()
{
	return (c.pop_back());
}

/*Non Member Function overloads*/
/*
template <typename T, typename Container>
bool
operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
{
	return (operator==(lhs.c, rhs.c));
}
*/

template <typename U, typename ContainerU>
bool
operator==(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs)
{
	return (operator==(lhs.c, rhs.c));
}

template <typename U, typename ContainerU>
bool
operator!=(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs)
{
	return (operator!=(lhs.c, rhs.c));
}

template <typename U, typename ContainerU>
bool
operator<(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs)
{
	return (operator<(lhs.c, rhs.c));
}

template <typename U, typename ContainerU>
bool
operator<=(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs)
{
	return (operator<=(lhs.c, rhs.c));
}

template <typename U, typename ContainerU>
bool
operator>(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs)
{
	return (operator>(lhs.c, rhs.c));
}

template <typename U, typename ContainerU>
bool
operator>=(const stack<U, ContainerU>& lhs, const stack<U, ContainerU>& rhs)
{
	return (operator>=(lhs.c, rhs.c));
}

}

#endif

