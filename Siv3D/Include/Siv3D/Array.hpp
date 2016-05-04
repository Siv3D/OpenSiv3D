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
# include <algorithm>
# include <functional>
# include "Fwd.hpp"
# include "Allocator.hpp"
# include "String.hpp"
# include "Functor.hpp"
# include "Format.hpp"
# include "Random.hpp"

namespace s3d
{
	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	class Array : protected std::vector<Type, Allocator>
	{
	private:

		using base_type = std::vector<Type, Allocator>;

	public:

		using typename base_type::value_type;
		using typename base_type::pointer;
		using typename base_type::const_pointer;
		using typename base_type::reference;
		using typename base_type::const_reference;
		using typename base_type::iterator;
		using typename base_type::const_iterator;
		using typename base_type::reverse_iterator;
		using typename base_type::const_reverse_iterator;
		using typename base_type::size_type;
		using typename base_type::difference_type;
		using typename base_type::allocator_type;

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

		size_t count() const noexcept
		{
			return size();
		}

		bool isEmpty() const noexcept
		{
			return empty();
		}

		void release()
		{
			clear();

			shrink_to_fit();
		}

		size_t size_bytes() const noexcept
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Array::size_bytes() Type must be trivially copyable.");

			return size() * sizeof(value_type);
		}

		Array& operator <<(const Type& value)
		{
			push_back(value);

			return *this;
		}

		Array& operator <<(Type&& value)
		{
			push_back(std::move(value));

			return *this;
		}

		bool all(std::function<bool(const Type&)> f = NotNot()) const
		{
			for (const auto& v : *this)
			{
				if (!f(v))
				{
					return false;
				}
			}

			return true;
		}

		bool any(std::function<bool(const Type&)> f = NotNot()) const
		{
			for (const auto& v : *this)
			{
				if (f(v))
				{
					return true;
				}
			}

			return false;
		}

		Array& append(const Array& other_array)
		{
			insert(end(), other_array.begin(), other_array.end());

			return *this;
		}

		const Type& choice() const
		{
			return choice(GetDefaultRNG());
		}

		template <class URNG, std::enable_if_t<!std::is_scalar<URNG>::value>* = nullptr>
		const Type& choice(URNG&& rng) const
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice() choice from empty Array");
			}

			const size_t index = std::uniform_int_distribution<size_t>(0, size() - 1)(rng);

			return operator[](index);
		}

		template <class Size_t, std::enable_if_t<std::is_scalar<Size_t>::value>* = nullptr>
		Array choice(Size_t n) const
		{
			return choice(n, GetDefaultRNG());
		}

		template <class URNG>
		Array choice(size_t n, URNG&& rng) const
		{
			return shuffled(rng).taken(n);
		}

		size_t count(const Type& value) const
		{
			size_t result = 0;

			for (const auto& v : *this)
			{
				if (v == value)
				{
					++result;
				}
			}

			return result;
		}

		size_t count_if(std::function<bool(const Type&)> f) const
		{
			size_t result = 0;

			for (const auto& v : *this)
			{
				if (f(v))
				{
					++result;
				}
			}

			return result;
		}

		Array& drop(size_t n)
		{
			if (n >= size())
			{
				clear();
			}
			else
			{
				erase(begin(), begin() + n);
			}

			return *this;
		}

		Array dropped(size_t n) const
		{
			if (n >= size())
			{
				return Array();
			}

			return Array(begin() + n, end());
		}

		Array& drop_while(std::function<bool(const Type&)> f)
		{
			erase(begin(), std::find_if_not(begin(), end(), f));

			return *this;
		}

		Array dropped_while(std::function<bool(const Type&)> f) const
		{
			return Array(std::find_if_not(begin(), end(), f), end());
		}

		Array& each(std::function<void(Type&)> f)
		{
			for (auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		const Array& each(std::function<void(const Type&)> f) const
		{
			for (const auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		Array& each_index(std::function<void(size_t, Type&)> f)
		{
			size_t i = 0;

			for (auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		const Array& each_index(std::function<void(size_t, const Type&)> f) const
		{
			size_t i = 0;

			for (const auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		const Type& fetch(size_t index, const Type& defaultValue) const
		{
			if (index >= size())
			{
				return defaultValue;
			}

			return operator[](index);
		}

		Array& fill(const Type& value)
		{
			std::fill(begin(), end(), value);

			return *this;
		}

		Array filter(std::function<bool(const Type&)> f) const
		{
			Array new_array;

			for (const auto& v : *this)
			{
				if (f(v))
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		bool include(const Type& value) const
		{
			for (const auto& v : *this)
			{
				if (v == value)
				{
					return true;
				}
			}

			return false;
		}

		bool include_if(std::function<bool(const Type&)> f) const
		{
			return any(f);
		}

		String join(const String& sep = L",", const String& begin = L"{", const String& end = L"}") const
		{
			String s;

			s.append(begin);

			bool isFirst = true;

			for (const auto& v : *this)
			{
				if (isFirst)
				{
					isFirst = false;
				}
				else
				{
					s.append(sep);
				}

				s.append(Format(v));
			}

			s.append(end);

			return s;
		}

		Array& keep_if(std::function<bool(const Type&)> f)
		{
			erase(std::remove_if(begin(), end(), std::not1(f)), end());

			return *this;
		}

		template <class Fty>
		auto map(Fty f) const
		{
			Array<decltype(std::declval<Fty>()(std::declval<Type>()))> new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		bool none(std::function<bool(const Type&)> f = NotNot()) const
		{
			for (const auto& v : *this)
			{
				if (f(v))
				{
					return false;
				}
			}

			return true;
		}

		template <class Fty>
		auto reduce(Fty f, decltype(std::declval<Fty>()(std::declval<Type>(), std::declval<Type>())) init) const
		{
			decltype(init) value = init;

			for (const auto& v : *this)
			{
				value = f(value, v);
			}

			return value;
		}

		template <class Fty>
		auto reduce1(Fty f) const
		{
			if (empty())
			{
				throw std::out_of_range("Array::reduce1() reduce from empty Array");
			}

			auto it = begin();
			const auto itEnd = end();

			decltype(std::declval<Fty>()(std::declval<Type>(), std::declval<Type>())) value = *it++;

			while (it != itEnd)
			{
				value = f(value, *it++);
			}

			return value;
		}

		Array& remove(const Type& value)
		{
			erase(std::remove(begin(), end(), value), end());

			return *this;
		}

		Array removed(const Type& value) const &
		{
			Array new_array;

			for (const auto& v : *this)
			{
				if (v != value)
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array removed(const Type& value) &&
		{
			erase(std::remove(begin(), end(), value), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array& remove_at(size_t index)
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::remove_at() index out of range");
			}

			erase(begin() + index);

			return *this;
		}

		Array removed_at(size_t index) const
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::removed_at() index out of range");
			}

			Array new_array;

			new_array.reserve(size() - 1);

			new_array.insert(new_array.end(), begin(), begin() + index);

			new_array.insert(new_array.end(), begin() + index + 1, end());

			return new_array;
		}

		Array& remove_if(std::function<bool(const Type&)> f)
		{
			erase(std::remove_if(begin(), end(), f), end());

			return *this;
		}

		Array removed_if(std::function<bool(const Type&)> f) const &
		{
			Array new_array;

			for (const auto& v : *this)
			{
				if (!f(v))
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array removed_if(std::function<bool(const Type&)> f) &&
		{
			erase(std::remove_if(begin(), end(), f), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array& replace(const Type& oldValue, const Type& newValue)
		{
			for (auto& v : *this)
			{
				if (v == oldValue)
				{
					v = newValue;
				}
			}

			return *this;
		}

		Array replaced(const Type& oldValue, const Type& newValue) const &
		{
			Array new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				if (v == oldValue)
				{
					new_array.push_back(newValue);
				}
				else
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array replaced(const Type& oldValue, const Type& newValue) &&
		{
			replace(oldValue, newValue);

			return std::move(*this);
		}

		Array& replace_if(std::function<bool(const Type&)> f, const Type& newValue)
		{
			for (auto& v : *this)
			{
				if (f(v))
				{
					v = newValue;
				}
			}

			return *this;
		}

		Array replaced_if(std::function<bool(const Type&)> f, const Type& newValue) const &
		{
			Array new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				if (f(v))
				{
					new_array.push_back(newValue);		
				}
				else
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array replaced_if(std::function<bool(const Type&)> f, const Type& newValue) &&
		{
			replace_if(f, newValue);

			return std::move(*this);
		}

		Array& reverse()
		{
			std::reverse(begin(), end());

			return *this;
		}

		Array reversed() const &
		{
			return Array(rbegin(), rend());
		}

		Array reversed() &&
		{
			reverse();

			return std::move(*this);
		}

		Array& reverse_each(std::function<void(Type&)> f)
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		const Array& reverse_each(std::function<void(const Type&)> f) const
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		Array& rotate(std::ptrdiff_t count = 1)
		{
			if (empty())
			{
				;
			}
			else if (count > 0) // rotation to the left
			{
				if (static_cast<size_t>(count) > size())
				{
					count %= size();
				}

				std::rotate(begin(), begin() + count, end());
			}
			else if (count < 0) // rotation to the right
			{
				count = -count;

				if (static_cast<size_t>(count) > size())
				{
					count %= size();
				}

				std::rotate(rbegin(), rbegin() + count, rend());
			}

			return *this;
		}

		Array rotated(std::ptrdiff_t count = 1) const &
		{
			return Array(*this).rotate(count);
		}

		Array rotated(std::ptrdiff_t count = 1) &&
		{
			rotate(count);

			return std::move(*this);
		}

		Array& shuffle()
		{
			return shuffle(GetDefaultRNG());
		}

		template <class URNG>
		Array& shuffle(URNG&& rng)
		{
			std::shuffle(begin(), end(), std::move(rng));

			return *this;
		}

		Array shuffled() const &
		{
			return shuffled(GetDefaultRNG());
		}

		Array shuffled() &&
		{
			return shuffled(GetDefaultRNG());
		}

		template <class URNG>
		Array shuffled(URNG&& rng) const &
		{
			return Array(*this).shuffle(std::move(rng));
		}

		template <class URNG>
		Array shuffled(URNG&& rng) &&
		{
			shuffle(std::move(rng));

			return std::move(*this);
		}

		Array slice(size_t index) const
		{
			if (index >= size())
			{
				return Array();
			}

			return Array(begin() + index, end());
		}

		Array slice(size_t index, size_t length) const
		{
			if (index >= size())
			{
				return Array();
			}

			return Array(begin() + index, begin() + std::min(index + length, size()));
		}

		Array& sort()
		{
			std::sort(begin(), end());

			return *this;
		}

		Array& sort_by(std::function<bool(const Type& a, const Type& b)> f)
		{
			std::sort(begin(), end(), f);

			return *this;
		}

		Array sorted() const &
		{
			return Array(*this).sort();
		}

		Array sorted() &&
		{
			sort();

			return std::move(*this);
		}

		Array sorted_by(std::function<bool(const Type& a, const Type& b)> f) const &
		{
			return Array(*this).sort_by(f);
		}

		Array sorted_by(std::function<bool(const Type& a, const Type& b)> f) &&
		{
			sort_by(f);

			return std::move(*this);
		}

		Array& take(size_t n)
		{
			erase(begin() + std::min(n, size()), end());

			return *this;
		}

		Array taken(size_t n) const
		{
			return Array(begin(), begin() + std::min(n, size()));
		}

		Array& take_while(std::function<bool(const Type&)> f)
		{
			erase(std::find_if_not(begin(), end(), f), end());

			return *this;
		}

		Array taken_while(std::function<bool(const Type&)> f) const
		{
			return Array(begin(), std::find_if_not(begin(), end(), f));
		}

		Array& unique()
		{
			sort();

			erase(std::unique(begin(), end()), end());

			return *this;
		}

		Array uniqued() const &
		{
			return Array(*this).unique();
		}

		Array uniqued() &&
		{
			sort();

			erase(std::unique(begin(), end()), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array values_at(std::initializer_list<size_t> indices) const
		{
			Array new_array;

			new_array.reserve(indices.size());

			for (auto index : indices)
			{
				if (index >= size())
				{
					throw std::out_of_range("Array::values_at() index out of range");
				}

				new_array.push_back(operator[](index));
			}

			return new_array;
		}
	};

	template <>
	class Array<bool> : protected std::basic_string<bool>
	{
	private:

		using base_type = std::basic_string<bool>;

	public:

		using typename base_type::value_type;
		using typename base_type::pointer;
		using typename base_type::const_pointer;
		using typename base_type::reference;
		using typename base_type::const_reference;
		using typename base_type::iterator;
		using typename base_type::const_iterator;
		using typename base_type::reverse_iterator;
		using typename base_type::const_reverse_iterator;
		using typename base_type::size_type;
		using typename base_type::difference_type;
		using typename base_type::allocator_type;

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

		Array& operator =(const Array& other) = default;

		Array& operator =(Array&& other) = default;

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

		size_t count() const noexcept
		{
			return size();
		}

		bool isEmpty() const noexcept
		{
			return empty();
		}

		void release()
		{
			clear();

			shrink_to_fit();
		}

		size_t size_bytes() const noexcept
		{
			return size() * sizeof(bool);
		}

		Array& operator <<(const bool& value)
		{
			push_back(value);

			return *this;
		}

		Array& operator <<(bool&& value)
		{
			push_back(std::move(value));

			return *this;
		}

		bool all(std::function<bool(const bool&)> f = NotNot()) const
		{
			for (const auto& v : *this)
			{
				if (!f(v))
				{
					return false;
				}
			}

			return true;
		}

		bool any(std::function<bool(const bool&)> f = NotNot()) const
		{
			for (const auto& v : *this)
			{
				if (f(v))
				{
					return true;
				}
			}

			return false;
		}

		Array& append(const Array& other_array)
		{
			insert(end(), other_array.begin(), other_array.end());

			return *this;
		}

		const bool& choice() const
		{
			return choice(GetDefaultRNG());
		}

		template <class URNG, std::enable_if_t<!std::is_scalar<URNG>::value>* = nullptr>
		const bool& choice(URNG&& rng) const
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice() choice from empty Array");
			}

			const size_t index = std::uniform_int_distribution<size_t>(0, size() - 1)(rng);

			return operator[](index);
		}

		template <class Size_t, std::enable_if_t<std::is_scalar<Size_t>::value>* = nullptr>
		Array choice(Size_t n) const
		{
			return choice(n, GetDefaultRNG());
		}

		template <class URNG>
		Array choice(size_t n, URNG&& rng) const
		{
			return shuffled(rng).taken(n);
		}

		size_t count(const bool& value) const
		{
			size_t result = 0;

			for (const auto& v : *this)
			{
				if (v == value)
				{
					++result;
				}
			}

			return result;
		}

		size_t count_if(std::function<bool(const bool&)> f) const
		{
			size_t result = 0;

			for (const auto& v : *this)
			{
				if (f(v))
				{
					++result;
				}
			}

			return result;
		}

		Array& drop(size_t n)
		{
			if (n >= size())
			{
				clear();
			}
			else
			{
				erase(begin(), begin() + n);
			}

			return *this;
		}

		Array dropped(size_t n) const
		{
			if (n >= size())
			{
				return Array();
			}

			return Array(begin() + n, end());
		}

		Array& drop_while(std::function<bool(const bool&)> f)
		{
			erase(begin(), std::find_if_not(begin(), end(), f));

			return *this;
		}

		Array dropped_while(std::function<bool(const bool&)> f) const
		{
			return Array(std::find_if_not(begin(), end(), f), end());
		}

		Array& each(std::function<void(bool&)> f)
		{
			for (auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		const Array& each(std::function<void(const bool&)> f) const
		{
			for (const auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		Array& each_index(std::function<void(size_t, bool&)> f)
		{
			size_t i = 0;

			for (auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		const Array& each_index(std::function<void(size_t, const bool&)> f) const
		{
			size_t i = 0;

			for (const auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		const bool& fetch(size_t index, const bool& defaultValue) const
		{
			if (index >= size())
			{
				return defaultValue;
			}

			return operator[](index);
		}

		Array& fill(const bool& value)
		{
			std::fill(begin(), end(), value);

			return *this;
		}

		Array filter(std::function<bool(const bool&)> f) const
		{
			Array new_array;

			for (const auto& v : *this)
			{
				if (f(v))
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		bool include(const bool& value) const
		{
			for (const auto& v : *this)
			{
				if (v == value)
				{
					return true;
				}
			}

			return false;
		}

		bool include_if(std::function<bool(const bool&)> f) const
		{
			return any(f);
		}

		String join(const String& sep = L",", const String& begin = L"{", const String& end = L"}") const
		{
			String s;

			s.append(begin);

			bool isFirst = true;

			for (const auto& v : *this)
			{
				if (isFirst)
				{
					isFirst = false;
				}
				else
				{
					s.append(sep);
				}

				s.append(ToString(v));
			}

			s.append(end);

			return s;
		}

		Array& keep_if(std::function<bool(const bool&)> f)
		{
			erase(std::remove_if(begin(), end(), std::not1(f)), end());

			return *this;
		}

		template <class Fty>
		auto map(Fty f) const
		{
			Array<decltype(std::declval<Fty>()(std::declval<bool>()))> new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		bool none(std::function<bool(const bool&)> f = NotNot()) const
		{
			for (const auto& v : *this)
			{
				if (f(v))
				{
					return false;
				}
			}

			return true;
		}

		template <class Fty>
		auto reduce(Fty f, decltype(std::declval<Fty>()(std::declval<bool>(), std::declval<bool>())) init) const
		{
			decltype(init) value = init;

			for (const auto& v : *this)
			{
				value = f(value, v);
			}

			return value;
		}

		template <class Fty>
		auto reduce1(Fty f) const
		{
			if (empty())
			{
				throw std::out_of_range("Array::reduce1() reduce from empty Array");
			}

			auto it = begin();
			const auto itEnd = end();

			decltype(std::declval<Fty>()(std::declval<bool>(), std::declval<bool>())) value = *it++;

			while (it != itEnd)
			{
				value = f(value, *it++);
			}

			return value;
		}

		Array& remove(const bool& value)
		{
			erase(std::remove(begin(), end(), value), end());

			return *this;
		}

		Array removed(const bool& value) const &
		{
			Array new_array;

			for (const auto& v : *this)
			{
				if (v != value)
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array removed(const bool& value) &&
		{
			erase(std::remove(begin(), end(), value), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array& remove_at(size_t index)
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::remove_at() index out of range");
			}

			erase(begin() + index);

			return *this;
		}

		Array removed_at(size_t index) const
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::removed_at() index out of range");
			}

			Array new_array;

			new_array.reserve(size() - 1);

			new_array.insert(new_array.end(), begin(), begin() + index);

			new_array.insert(new_array.end(), begin() + index + 1, end());

			return new_array;
		}

		Array& remove_if(std::function<bool(const bool&)> f)
		{
			erase(std::remove_if(begin(), end(), f), end());

			return *this;
		}

		Array removed_if(std::function<bool(const bool&)> f) const &
		{
			Array new_array;

			for (const auto& v : *this)
			{
				if (!f(v))
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array removed_if(std::function<bool(const bool&)> f) &&
		{
			erase(std::remove_if(begin(), end(), f), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array& replace(const bool& oldValue, const bool& newValue)
		{
			for (auto& v : *this)
			{
				if (v == oldValue)
				{
					v = newValue;
				}
			}

			return *this;
		}

		Array replaced(const bool& oldValue, const bool& newValue) const &
		{
			Array new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				if (v == oldValue)
				{
					new_array.push_back(newValue);
				}
				else
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array replaced(const bool& oldValue, const bool& newValue) &&
		{
			replace(oldValue, newValue);

			return std::move(*this);
		}

		Array& replace_if(std::function<bool(const bool&)> f, const bool& newValue)
		{
			for (auto& v : *this)
			{
				if (f(v))
				{
					v = newValue;
				}
			}

			return *this;
		}

		Array replaced_if(std::function<bool(const bool&)> f, const bool& newValue) const &
		{
			Array new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				if (f(v))
				{
					new_array.push_back(newValue);
				}
				else
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		Array replaced_if(std::function<bool(const bool&)> f, const bool& newValue) &&
		{
			replace_if(f, newValue);

			return std::move(*this);
		}

		Array& reverse()
		{
			std::reverse(begin(), end());

			return *this;
		}

		Array reversed() const &
		{
			return Array(rbegin(), rend());
		}

		Array reversed() &&
		{
			reverse();

			return std::move(*this);
		}

		Array& reverse_each(std::function<void(bool&)> f)
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		const Array& reverse_each(std::function<void(const bool&)> f) const
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		Array& rotate(std::ptrdiff_t count = 1)
		{
			if (empty())
			{
				;
			}
			else if (count > 0) // rotation to the left
			{
				if (static_cast<size_t>(count) > size())
				{
					count %= size();
				}

				std::rotate(begin(), begin() + count, end());
			}
			else if (count < 0) // rotation to the right
			{
				count = -count;

				if (static_cast<size_t>(count) > size())
				{
					count %= size();
				}

				std::rotate(rbegin(), rbegin() + count, rend());
			}

			return *this;
		}

		Array rotated(std::ptrdiff_t count = 1) const &
		{
			return Array(*this).rotate(count);
		}

		Array rotated(std::ptrdiff_t count = 1) &&
		{
			rotate(count);

			return std::move(*this);
		}

		Array& shuffle()
		{
			return shuffle(GetDefaultRNG());
		}

		template <class URNG>
		Array& shuffle(URNG&& rng)
		{
			std::shuffle(begin(), end(), std::move(rng));

			return *this;
		}

		Array shuffled() const &
		{
			return shuffled(GetDefaultRNG());
		}

		Array shuffled() &&
		{
			return shuffled(GetDefaultRNG());
		}

		template <class URNG>
		Array shuffled(URNG&& rng) const &
		{
			return Array(*this).shuffle(std::move(rng));
		}

		template <class URNG>
		Array shuffled(URNG&& rng) &&
		{
			shuffle(std::move(rng));

			return std::move(*this);
		}

		Array slice(size_t index) const
		{
			if (index >= size())
			{
				return Array();
			}

			return Array(begin() + index, end());
		}

		Array slice(size_t index, size_t length) const
		{
			if (index >= size())
			{
				return Array();
			}

			return Array(begin() + index, begin() + std::min(index + length, size()));
		}

		Array& sort()
		{
			std::sort(begin(), end());

			return *this;
		}

		Array& sort_by(std::function<bool(const bool& a, const bool& b)> f)
		{
			std::sort(begin(), end(), f);

			return *this;
		}

		Array sorted() const &
		{
			return Array(*this).sort();
		}

		Array sorted() &&
		{
			sort();

			return std::move(*this);
		}

		Array sorted_by(std::function<bool(const bool& a, const bool& b)> f) const &
		{
			return Array(*this).sort_by(f);
		}

		Array sorted_by(std::function<bool(const bool& a, const bool& b)> f) &&
		{
			sort_by(f);

			return std::move(*this);
		}

		Array& take(size_t n)
		{
			erase(begin() + std::min(n, size()), end());

			return *this;
		}

		Array taken(size_t n) const
		{
			return Array(begin(), begin() + std::min(n, size()));
		}

		Array& take_while(std::function<bool(const bool&)> f)
		{
			erase(std::find_if_not(begin(), end(), f), end());

			return *this;
		}

		Array taken_while(std::function<bool(const bool&)> f) const
		{
			return Array(begin(), std::find_if_not(begin(), end(), f));
		}

		Array& unique()
		{
			sort();

			erase(std::unique(begin(), end()), end());

			return *this;
		}

		Array uniqued() const &
		{
			return Array(*this).unique();
		}

		Array uniqued() &&
		{
			sort();

			erase(std::unique(begin(), end()), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array values_at(std::initializer_list<size_t> indices) const
		{
			Array new_array;

			new_array.reserve(indices.size());

			for (auto index : indices)
			{
				if (index >= size())
				{
					throw std::out_of_range("Array::values_at() index out of range");
				}

				new_array.push_back(operator[](index));
			}

			return new_array;
		}
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

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline std::ostream & operator << (std::ostream& os, const Array<Type, Allocator>& v)
	{
		return os << Format(v).narrow();
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline std::wostream & operator << (std::wostream& os, const Array<Type, Allocator>& v)
	{
		return os << Format(v);
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline void Formatter(FormatData& formatData, const Array<Type, Allocator>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}
}

namespace std
{
	template <class Type, class Allocator>
	inline void swap(s3d::Array<Type, Allocator>& a, s3d::Array<Type, Allocator>& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
}
