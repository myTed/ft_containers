#ifndef __ENABLE_IF_HPP
#define __ENABLE_IF_HPP


namespace ft
{
	template<bool B, typename T = void>
	struct enable_if 
	{};

	template<typename T>
	struct enable_if<true, T>
	{ 
		typedef T type;
	};

	template<typename T, T v>
	struct integral_constant
	{
		static const T value = v;
		operator T() {return v;}
	};

	template<typename T>
	struct is_integral 
	: public integral_constant<bool, false>
	{};

	template<>
	struct is_integral<bool>
	 : public integral_constant<bool, true>
	{};
	
#ifndef LINUX
	/*
	template<>
	struct is_integral<char16_t>
	 : public integral_constant<bool, true>
	{};
	*/
#endif

	template<>
	struct is_integral<wchar_t>
	 : public integral_constant<bool, true>
	{};

	template<>
	struct is_integral<char>
	 : public integral_constant<bool, true>
	{};
	
	template<>
	struct is_integral<signed char>
	 : public integral_constant<bool, true>
	{};

	template<>
	struct is_integral<short int>
	 : public integral_constant<bool, true>
	{};

	template<>
	struct is_integral<int>
	 : public integral_constant<bool, true>
	{};

	template<>
	struct is_integral<long int>
	 : public integral_constant<bool, true>
	{};

	template<>
	struct is_integral<long long int>
	 : public integral_constant<bool, true>
	{};

	template<>
	struct is_integral<unsigned char>
	 : public integral_constant<bool, true>
	{};
	/*
	template<>
	struct is_integral<unsigned short int>
	 : public integral_constant<bool, true>
	{};
	*/
	template<>
	struct is_integral<unsigned int>
	 : public integral_constant<bool, true>
	{};

	template<>
	struct is_integral<unsigned long int>
	 : public integral_constant<bool, true>
	{};

	template<>
	struct is_integral<unsigned long long int>
	 : public integral_constant<bool, true>
	{};
}


#endif
