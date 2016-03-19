//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <vector>
# include <string>
# include "Allocator.hpp"

namespace s3d
{
	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	class Array : protected std::vector<Type, Allocator>
	{
	private:

		using base_type = std::vector<Type, Allocator>;

	public:

		using base_type::value_type;
		using base_type::pointer;
		using base_type::const_pointer;
		using base_type::reference;
		using base_type::const_reference;
		using base_type::iterator;
		using base_type::const_iterator;
		using base_type::reverse_iterator;
		using base_type::const_reverse_iterator;
		using base_type::size_type;
		using base_type::difference_type;
		using base_type::allocator_type;

		using base_type::vector;
		using base_type::operator=;
		using base_type::assign;
		using base_type::get_allocator;
		using base_type::at;
		using base_type::operator[];
		using base_type::front;
		using base_type::back;
		using base_type::data;
		using base_type::begin;
		using base_type::cbegin;
		using base_type::end;
		using base_type::cend;
		using base_type::rbegin;
		using base_type::crbegin;
		using base_type::rend;
		using base_type::empty;
		using base_type::size;
		using base_type::max_size;
		using base_type::reserve;
		using base_type::capacity;
		using base_type::shrink_to_fit;
		using base_type::clear;
		using base_type::insert;
		using base_type::emplace;
		using base_type::erase;
		using base_type::push_back;
		using base_type::emplace_back;
		using base_type::pop_back;
		using base_type::resize;
		using base_type::swap;
	};

	template <class Type, class Allocator>
	inline bool operator ==(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b)
	{
		return ((a.size() == b.size()) && std::equal(a.begin(), a.end(), b.begin()));
	}

	template <class Type, class Allocator>
	inline bool operator !=(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b)
	{
		return ((a.size() != b.size()) || !std::equal(a.begin(), a.end(), b.begin()));
	}

	template <class Type, class Allocator>
	inline bool operator <(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b)
	{
		return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	template <class Type, class Allocator>
	inline bool operator >(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b)
	{
		return b < a;
	}

	template <class Type, class Allocator>
	inline bool operator <=(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b)
	{
		return !(b < a);
	}

	template <class Type, class Allocator>
	inline bool operator >=(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b)
	{
		return !(a < b);
	}

	template <class Type, class Allocator>
	inline void swap(Array<Type, Allocator>& a, Array<Type, Allocator>& b)
	{
		a.swap(b);
	}

	template <>
	class Array<bool> : protected std::basic_string<bool>
	{
	private:

		using base_type = std::basic_string<bool>;

	public:

		using base_type::value_type;
		using base_type::pointer;
		using base_type::const_pointer;
		using base_type::reference;
		using base_type::const_reference;
		using base_type::iterator;
		using base_type::const_iterator;
		using base_type::reverse_iterator;
		using base_type::const_reverse_iterator;
		using base_type::size_type;
		using base_type::difference_type;
		using base_type::allocator_type;

		using base_type::operator=;
		using base_type::assign;
		using base_type::get_allocator;
		using base_type::at;
		using base_type::operator[];
		using base_type::front;
		using base_type::back;
		using base_type::data;
		using base_type::begin;
		using base_type::cbegin;
		using base_type::end;
		using base_type::cend;
		using base_type::rbegin;
		using base_type::crbegin;
		using base_type::rend;
		using base_type::empty;
		using base_type::size;
		using base_type::max_size;
		using base_type::reserve;
		using base_type::capacity;
		using base_type::shrink_to_fit;
		using base_type::clear;
		using base_type::insert;
		using base_type::erase;
		using base_type::push_back;
		using base_type::pop_back;
		using base_type::resize;
		using base_type::swap;

		Array() = default;

		Array(size_type count, const bool& value)
			: base_type(count, value) {}

		explicit Array(size_type count)
			: base_type(count, false) {}

		template <class InputIt>
		Array(InputIt first, InputIt last)
			: base_type(first, last) {}

		Array(const Array& other)
			: base_type(other) {}

		Array(Array&& other) noexcept
			: base_type(std::move(other)) {}

		Array(std::initializer_list<bool> init)
			: base_type(init.begin(), init.end()) {}

		template<class... Args>
		iterator emplace(const_iterator pos, Args&&... args)
		{
			bool tmp(std::forward<Args>(args)...);
			return (insert(pos, tmp));
		}

		template<class... Args>
		void emplace_back(Args&&... args)
		{
			bool tmp(std::forward<Args>(args)...);
			push_back(tmp);
		}
	};
}
