/******************************************************************************
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  Author:Zheng Fasheng
 *
 *  Email:zheng_fasheng@outlook.com
 *
 *  Date:2016/9/4 20:55
 *
 *  Summary:Declares any class Derived from the boost library
 *  
 ******************************************************************************/
#pragma once
#include <exception>
#include <typeinfo>
#include <type_traits>
#include <typeindex>
namespace boost{
	template <bool B, class T = void>
	struct disable_if_c {
	typedef T type;
	};

	template <class T>
	struct disable_if_c<true, T> {};

	template <class Cond, class T = void>
	struct disable_if : public disable_if_c<Cond::value, T> {};

	namespace detail
	{
		template <class T> struct remove_bounds : public remove_extent<T> {};
		template <class T, bool Array, bool Function> struct decay_imp { typedef typename remove_cv<T>::type type; };
		template <class T> struct decay_imp<T, true, false> { typedef typename remove_bounds<T>::type* type; };
		template <class T> struct decay_imp<T, false, true> { typedef T* type; };

		//remove const
		//template <class T, bool isConst > struct remove_const { typedef typename T type; };
		//template <class T > struct remove_const<T , true > { typedef typename std::remove_const<T>::type type; };
		//template <class T > struct remove_const<T, false> { typedef typename T type; };
		//remove reference
		//template <class T, bool isReference > struct remove_reference { typedef typename T type; };
		//template <class T > struct remove_reference<T, true > { typedef typename std::remove_reference<T>::type type; };
		//template <class T > struct remove_reference<T, false> { typedef typename T type; };
	}

	template< class T >
	struct decay
	{
	private:
		typedef typename std::remove_reference<T>::type Ty;
	public:
		typedef typename boost::detail::decay_imp<Ty, std::is_array<Ty>::value, std::is_function<Ty>::value>::type type;
	};

	class any
	{

	public:

		any()
			: content(0)
		{
		}

		template<typename value_type>
		any(const value_type & value)
			: content(new holder<std::remove_cv<boost::decay<const value_type>::type>::type>(value))
		{
		}

		any(const any & other)
			: content(other.content ? other.content->clone() : 0)
		{
		}

		//c++11
		// Move constructor
		any(any&& other)
			: content(other.content)
		{
			other.content = 0;
		}

		// Perfect forwarding of ValueType
		template<typename value_type>
		any(value_type&& value
			, typename disable_if<std::is_same<any&, value_type> >::type* = 0 // disable if value has type `any&`
			, typename disable_if<std::is_const<value_type> >::type* = 0) // disable if value has type `const ValueType&&`
			: content(new holder< typename boost::decay<value_type>::type >(static_cast<value_type&&>(value)))
		{
		}

		~any()
		{
			if (content)
			{
				delete content;
			}
			content = nullptr;
		}

	public:

		any& swap(any& rhs)
		{
			std::swap(content, rhs.content);
			return *this;
		}

		any& operator=(const any& rhs)
		{
			any(rhs).swap(*this);
			return *this;
		}

		//c++11
		//move assignement
		any& operator=(any&& rhs)
		{
			rhs.swap(*this);
			any().swap(rhs);
			return *this;
		}

		//perfect forwarding of valueType
		template<class valueType>
		any& operator=(valueType&& rhs)
		{
			any(static_cast<valueType&&>(rhs)).swap(*this);
			return *this;
		}

	public: // queries

		bool empty()
		{
			return !content;
		}

		void clear()
		{
			any().swap(*this);
		}

		const std::type_info& type() const
		{
			return content ? content->type() : typeid(void);
		}

	private:

		class placeholder
		{
		public:
			virtual ~placeholder(){}
			virtual const std::type_info& type() const = 0;
			virtual placeholder* clone() const = 0;
		};

		template<typename value_type>
		class holder : public placeholder
		{
		public:
			typedef value_type value_type;
			holder(const value_type& value) :held(value){}
			holder(value_type&& value)
				:held(static_cast<value_type&&>(value))
			{
				
			}

			virtual const std::type_info& type() const
			{
				return typeid(value_type);
			}

			virtual placeholder* clone() const
			{
				return new holder(held);
			}

		public:
			value_type held;

		private:
			// intentionally left unimplemented
			holder& operator=(const holder &);
		};

	private: // representation

		template<typename value_type>
		friend value_type * any_cast(any *);

		template<typename value_type>
		friend value_type * unsafe_any_cast(any *);

	private:

		placeholder* content;
	};

	inline void swap(any & lhs, any & rhs)
	{
		lhs.swap(rhs);
	}

	template<typename value_type>
	value_type * any_cast(any * operand)
	{
		return operand && operand->type() == typeid(value_type)
		? &static_cast<any::holder<std::remove_cv<value_type>::type> *>(operand->content)->held
		: 0;
	}

	template<typename value_type>
	inline const value_type * any_cast(const any * operand)
	{
		return any_cast<value_type>(const_cast<any *>(operand));
	}

	template<typename value_type>
	value_type any_cast(any & operand)
	{
		typedef std::remove_reference<value_type>::type nonref;

		nonref * result = any_cast<nonref>(&operand);
		if (!result)
			throw std::bad_cast("boost::bad_any_cast: failed conversion using boost::any_cast");

		// Attempt to avoid construction of a temporary object in cases when 
		// `ValueType` is not a reference. Example:
		// `static_cast<std::string>(*result);` 
		// which is equal to `std::string(*result);`
		typedef typename std::_If<
			std::is_reference<value_type>::value,
			value_type,
			std::add_reference<value_type>::type
			>::type ref_type;

			return static_cast<ref_type>(*result);
	}

	template<typename value_type>
	inline value_type any_cast(const any & operand)
	{
		typedef typename std::remove_reference<value_type>::type nonref;
		return any_cast<const nonref &>(const_cast<any &>(operand));
	}

	template<typename value_type>
	inline value_type any_cast(any&& operand)
	{
		static_assert(
			std::is_rvalue_reference<value_type&&>::value /*true if ValueType is rvalue or just a value*/
			|| std::is_const< typename std::remove_reference<value_type>::type >::value,
			"boost::any_cast shall not be used for getting nonconst references to temporary objects"
			);
		return any_cast<value_type>(operand);
	}

	// Note: The "unsafe" versions of any_cast are not part of the
	// public interface and may be removed at any time. They are
	// required where we know what type is stored in the any and can't
	// use typeid() comparison, e.g., when our types may travel across
	// different shared libraries.
	template<typename value_type>
	inline value_type * unsafe_any_cast(any * operand)
	{
		return &static_cast<any::holder<value_type> *>(operand->content)->held;
	}

	template<typename value_type>
	inline const value_type * unsafe_any_cast(const any * operand)
	{
		return unsafe_any_cast<value_type>(const_cast<any *>(operand));
	}
}