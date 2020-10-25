﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "../KahanSummation.hpp"

namespace s3d
{
	template <class Type, class Allocator>
	template <class ArrayIsh, std::enable_if_t<Meta::HasAsArray<ArrayIsh>::value>*>
	inline Array<Type, Allocator>::Array(ArrayIsh&& a)
	{
		*this = std::forward<ArrayIsh>(a).asArray();
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Array<Type, Allocator>::Array(const size_type size, Arg::generator_<Fty> generator)
		: Array(Generate<Fty>(size, *generator)) {}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>*>
	inline Array<Type, Allocator>::Array(const size_type size, Arg::indexedGenerator_<Fty> indexedGenerator)
		: Array(IndexedGenerate<Fty>(size, *indexedGenerator)) {}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::swap(Array& other) noexcept
	{
		base_type::swap(other);
	}

	template <class Type, class Allocator>
	inline bool Array<Type, Allocator>::isEmpty() const noexcept
	{
		return base_type::empty();
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>::operator bool() const noexcept
	{
		return (not base_type::empty());
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::release()
	{
		clear();

		shrink_to_fit();
	}

	template <class Type, class Allocator>
	inline size_t Array<Type, Allocator>::size_bytes() const noexcept
	{
		static_assert(std::is_trivially_copyable_v<value_type>, "Array::size_bytes(): value_type must be trivially copyable.");

		return size() * sizeof(value_type);
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::push_front(const value_type& value)
	{
		insert(begin(), value);
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::push_front(value_type&& value)
	{
		insert(begin(), std::move(value));
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::pop_front()
	{
		erase(begin());
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::pop_front_N(const size_t n)
	{
		erase(begin(), begin() + Min(n, size()));
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::pop_back_N(const size_t n)
	{
		erase(end() - Min(n, size()), end());
	}

	template <class Type, class Allocator>
	inline const typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::operator[](const size_t index) const&
	{
		return base_type::operator[](index);
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::operator[](const size_t index) &
	{
		return base_type::operator[](index);
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type Array<Type, Allocator>::operator[](const size_t index) &&
	{
		return std::move(base_type::operator[](index));
	}

	template <class Type, class Allocator>
	inline const typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::at(const size_t index) const&
	{
		return base_type::at(index);
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::at(const size_t index) &
	{
		return base_type::at(index);
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type Array<Type, Allocator>::at(const size_t index) &&
	{
		return std::move(base_type::at(index));
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::operator <<(const value_type& value)
	{
		push_back(value);

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::operator <<(value_type&& value)
	{
		push_back(std::forward<value_type>(value));

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline bool Array<Type, Allocator>::all(Fty f) const
	{
		return std::all_of(begin(), end(), f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline bool Array<Type, Allocator>::any(Fty f) const
	{
		return std::any_of(begin(), end(), f);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::append(const Array& other_array)
	{
		insert(end(), other_array.begin(), other_array.end());

		return *this;
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::choice()
	{
		return choice(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	inline const typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::choice() const
	{
		return choice(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::choice(URBG&& rbg)
	{
		if (empty())
		{
			throw std::out_of_range("Array::choice(): Array is empty");
		}

		const size_t index = UniformIntDistribution<size_t>(0, size() - 1)(rbg);

		return operator[](index);
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline const typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::choice(URBG&& rbg) const
	{
		if (empty())
		{
			throw std::out_of_range("Array::choice(): Array is empty");
		}

		const size_t index = UniformIntDistribution<size_t>(0, size() - 1)(rbg);

		return operator[](index);
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_INTEGRAL_
	inline Array<Type, Allocator> Array<Type, Allocator>::choice(const Int n) const
	{
		return choice(n, GetDefaultRNG());
	}

	template <class Type, class Allocator>
# if __cpp_lib_concepts
	template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>*,
		std::enable_if_t<std::is_invocable_v<URBG&>&& std::is_unsigned_v<std::invoke_result_t<URBG&>>>*>
# endif
	inline Array<Type, Allocator> Array<Type, Allocator>::choice(const Size_t n, URBG&& rbg) const
	{
		Array result;

		result.reserve(Min(n, size()));

		std::sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));

		return result;
	}

	template <class Type, class Allocator>
	inline Array<Array<typename Array<Type, Allocator>::value_type>> Array<Type, Allocator>::chunk(size_t n) const
	{
		Array<Array<value_type>> result;

		if (n == 0)
		{
			return result;
		}

		for (size_t i = 0; i < (size() + n - 1) / n; ++i)
		{
			result.push_back(slice(i * n, n));
		}

		return result;
	}

	template <class Type, class Allocator>
	inline size_t Array<Type, Allocator>::count(const value_type& value) const
	{
		return std::count(begin(), end(), value);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline size_t Array<Type, Allocator>::count_if(Fty f) const
	{
		return std::count_if(begin(), end(), f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::each(Fty f)
	{
		for (auto& v : *this)
		{
			f(v);
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline const Array<Type, Allocator>& Array<Type, Allocator>::each(Fty f) const
	{
		for (const auto& v : *this)
		{
			f(v);
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, Type&>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::each_index(Fty f)
	{
		size_t i = 0;

		for (auto& v : *this)
		{
			f(i++, v);
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, Type>>*>
	inline const Array<Type, Allocator>& Array<Type, Allocator>::each_index(Fty f) const
	{
		size_t i = 0;

		for (const auto& v : *this)
		{
			f(i++, v);
		}

		return *this;
	}

	template <class Type, class Allocator>
	inline const typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::fetch(const size_t index, const value_type& defaultValue) const
	{
		if (index >= size())
		{
			return defaultValue;
		}

		return operator[](index);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::fill(const value_type& value)
	{
		std::fill(begin(), end(), value);

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::filter(Fty f) const
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

	template <class Type, class Allocator>
	inline Array<Array<typename Array<Type, Allocator>::value_type>> Array<Type, Allocator>::in_groups(size_t group) const
	{
		Array<Array<value_type>> result;

		if (group == 0)
		{
			return result;
		}

		const size_t div = size() / group;
		const size_t mod = size() % group;
		size_t index = 0;

		for (size_t i = 0; i < group; ++i)
		{
			const size_t length = div + (mod > 0 && mod > i);

			result.push_back(slice(index, length));

			index += length;
		}

		return result;
	}

	template <class Type, class Allocator>
	inline bool Array<Type, Allocator>::includes(const value_type& value) const
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

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline bool Array<Type, Allocator>::includes_if(Fty f) const
	{
		return any(f);
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline bool Array<Type, Allocator>::isSorted() const
	{
		return std::is_sorted(begin(), end());
	}

	template <class Type, class Allocator>
	inline String Array<Type, Allocator>::join(const StringView sep, const StringView begin, const StringView end) const
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

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline auto Array<Type, Allocator>::map(Fty f) const
	{
		Array<std::decay_t<std::invoke_result_t<Fty, Type>>> new_array;

		new_array.reserve(size());

		for (const auto& v : *this)
		{
			new_array.push_back(f(v));
		}

		return new_array;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline bool Array<Type, Allocator>::none(Fty f) const
	{
		return std::none_of(begin(), end(), f);
	}

	template <class Type, class Allocator>
	template <class Fty, class R>
	inline auto Array<Type, Allocator>::reduce(Fty f, R init) const
	{
		auto value = init;

		for (const auto& v : *this)
		{
			value = f(value, v);
		}

		return value;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type, Type>>*>
	inline auto Array<Type, Allocator>::reduce1(Fty f) const
	{
		if (empty())
		{
			throw std::out_of_range("Array::reduce1(): Array is empty");
		}

		auto it = begin();
		const auto itEnd = end();

		std::invoke_result_t<Fty, value_type, value_type> value = *it++;

		while (it != itEnd)
		{
			value = f(value, *it++);
		}

		return value;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::remove(const value_type& value)
	{
		erase(std::remove(begin(), end(), value), end());

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::removed(const value_type& value) const&
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

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::removed(const value_type& value)&&
	{
		erase(std::remove(begin(), end(), value), end());

		shrink_to_fit();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::remove_at(const size_t index)
	{
		if (index >= size())
		{
			throw std::out_of_range("Array::remove_at(): index out of range");
		}

		erase(begin() + index);

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::removed_at(const size_t index) const
	{
		if (index >= size())
		{
			throw std::out_of_range("Array::removed_at(): index out of range");
		}

		Array new_array;

		new_array.reserve(size() - 1);

		new_array.insert(new_array.end(), begin(), begin() + index);

		new_array.insert(new_array.end(), begin() + index + 1, end());

		return new_array;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::remove_if(Fty f)
	{
		erase(std::remove_if(begin(), end(), f), end());

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::removed_if(Fty f) const&
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

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::removed_if(Fty f)&&
	{
		erase(std::remove_if(begin(), end(), f), end());

		shrink_to_fit();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::replace(const value_type& oldValue, const value_type& newValue)
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

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::replaced(const value_type& oldValue, const value_type& newValue) const&
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

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::replaced(const value_type& oldValue, const value_type& newValue)&&
	{
		replace(oldValue, newValue);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::replace_if(Fty f, const value_type& newValue)
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

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::replaced_if(Fty f, const value_type& newValue) const&
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

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::replaced_if(Fty f, const value_type& newValue)&&
	{
		replace_if(f, newValue);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::reverse()
	{
		std::reverse(begin(), end());

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::reversed() const&
	{
		return Array(rbegin(), rend());
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::reversed()&&
	{
		reverse();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::reverse_each(Fty f)
	{
		for (auto it = rbegin(); it != rend(); ++it)
		{
			f(*it);
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline const Array<Type, Allocator>& Array<Type, Allocator>::reverse_each(Fty f) const
	{
		for (auto it = rbegin(); it != rend(); ++it)
		{
			f(*it);
		}

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::rotate(std::ptrdiff_t count)
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

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::rotated(const std::ptrdiff_t count) const&
	{
		return Array(*this).rotate(count);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::rotated(const std::ptrdiff_t count)&&
	{
		rotate(count);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasGreaterThan_v<T>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::rsort()
	{
		std::sort(begin(), end(), std::greater<>());

		return *this;
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasGreaterThan_v<T>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::rsorted() const&
	{
		return Array(*this).rsort();
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasGreaterThan_v<T>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::rsorted()&&
	{
		rsort();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::shuffle()
	{
		return shuffle(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline Array<Type, Allocator>& Array<Type, Allocator>::shuffle(URBG&& rbg)
	{
		std::shuffle(begin(), end(), std::forward<URBG>(rbg));

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::shuffled() const&
	{
		return shuffled(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::shuffled()&&
	{
		return shuffled(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline Array<Type, Allocator> Array<Type, Allocator>::shuffled(URBG&& rbg) const&
	{
		return Array(*this).shuffle(std::forward<URBG>(rbg));
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline Array<Type, Allocator> Array<Type, Allocator>::shuffled(URBG&& rbg)&&
	{
		shuffle(std::forward<URBG>(rbg));

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::slice(const size_t index) const
	{
		if (index >= size())
		{
			return Array();
		}

		return Array(begin() + index, end());
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::slice(const size_t index, const size_t length) const
	{
		if (index >= size())
		{
			return Array();
		}

		return Array(begin() + index, begin() + Min(index + length, size()));
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::sort()
	{
		std::sort(begin(), end());

		return *this;
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::stable_sort()
	{
		std::stable_sort(begin(), end());

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::sort_by(Fty f)
	{
		std::sort(begin(), end(), f);

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Array<Type, Allocator>& Array<Type, Allocator>::stable_sort_by(Fty f)
	{
		std::stable_sort(begin(), end(), f);

		return *this;
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::sorted() const&
	{
		return Array(*this).sort();
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::stable_sorted() const&
	{
		return Array(*this).stable_sort();
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::sorted()&&
	{
		sort();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::stable_sorted()&&
	{
		stable_sort();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::sorted_by(Fty f) const&
	{
		return Array(*this).sort_by(f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::stable_sorted_by(Fty f) const&
	{
		return Array(*this).stable_sort_by(f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::sorted_by(Fty f)&&
	{
		sort_by(f);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::stable_sorted_by(Fty f)&&
	{
		stable_sort_by(f);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasPlus_v<T>>*>
	inline auto Array<Type, Allocator>::sum() const
	{
		decltype(std::declval<T>() + std::declval<T>()) result{};

		if constexpr (Meta::HasPlusAssign_v<Type>)
		{
			for (const auto& v : *this)
			{
				result += v;
			}
		}
		else
		{
			for (const auto& v : *this)
			{
				result = result + v;
			}
		}

		return result;
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<std::is_floating_point_v<T>>*>
	inline auto Array<Type, Allocator>::sumF() const
	{
		KahanSummation<T> sum;

		for (const auto& v : *this)
		{
			sum += v;
		}

		return sum.value();
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::take(const size_t n) const
	{
		return Array(begin(), begin() + Min(n, size()));
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::take_while(Fty f) const
	{
		return Array(begin(), std::find_if_not(begin(), end(), f));
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::stable_unique()
	{
		// [Siv3D ToDo: 最適化]
		return *this = stable_uniqued();
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::stable_uniqued() const
	{
		Array result;

		detail::StableUniqueHelper<value_type> pred;

		std::copy_if(begin(), end(), std::back_inserter(result), std::ref(pred));

		return result;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::sort_and_unique()
	{
		sort();

		erase(std::unique(begin(), end()), end());

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::sorted_and_uniqued() const&
	{
		return Array(*this).sort_and_unique();
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::sorted_and_uniqued()&&
	{
		sort();

		erase(std::unique(begin(), end()), end());

		shrink_to_fit();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::unique_consecutive()
	{
		erase(std::unique(begin(), end()), end());

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::uniqued_consecutive() const&
	{
		String result;

		std::unique_copy(begin(), end(), std::back_inserter(result));

		return result;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::uniqued_consecutive()&&
	{
		erase(std::unique(begin(), end()), end());

		shrink_to_fit();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator> Array<Type, Allocator>::values_at(std::initializer_list<size_t> indices) const
	{
		Array new_array;

		new_array.reserve(indices.size());

		for (auto index : indices)
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::values_at(): index out of range");
			}

			new_array.push_back(operator[](index));
		}

		return new_array;
	}

# ifndef SIV3D_NO_CONCURRENT_API

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline size_t Array<Type, Allocator>::parallel_count_if(Fty f) const
	{
	# if SIV3D_PLATFORM(WINDOWS)

		return std::count_if(std::execution::par, begin(), end(), f);

	# else

		if (isEmpty())
		{
			return 0;
		}

		const size_t numThreads = Threading::GetConcurrency();

		if (numThreads <= 1)
		{
			return count_if(f);
		}

		const size_t countPerthread = Max<size_t>(1, (size() + (numThreads - 1)) / numThreads);

		Array<std::future<std::ptrdiff_t>> futures;

		auto it = begin();
		size_t countLeft = size();

		for (size_t i = 0; i < (numThreads - 1); ++i)
		{
			const size_t n = Min(countPerthread, countLeft);

			if (n == 0)
			{
				break;
			}

			futures.emplace_back(std::async(std::launch::async, [=, &f]()
			{
				return std::count_if(it, it + n, f);
			}));

			it += n;
			countLeft -= n;
		}

		size_t result = 0;
		
		if (countLeft)
		{
			result = std::count_if(it, it + countLeft, f);
		}

		for (auto& future : futures)
		{
			result += future.get();
		}

		return result;

	# endif
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>*>
	inline void Array<Type, Allocator>::parallel_each(Fty f)
	{
	# if SIV3D_PLATFORM(WINDOWS)

		std::for_each(std::execution::par, begin(), end(), f);

	# else

		if (isEmpty())
		{
			return;
		}

		const size_t numThreads = Threading::GetConcurrency();

		if (numThreads <= 1)
		{
			return each(f);
		}

		const size_t countPerthread = Max<size_t>(1, (size() + (numThreads - 1)) / numThreads);

		Array<std::future<std::ptrdiff_t>> futures;

		auto it = begin();
		size_t countLeft = size();

		for (size_t i = 0; i < (numThreads - 1); ++i)
		{
			const size_t n = Min(countPerthread, countLeft);

			if (n == 0)
			{
				break;
			}

			futures.emplace_back(std::async(std::launch::async, [=, &f]()
			{
				std::for_each(it, it + n, f);
			}));

			it += n;
			countLeft -= n;
		}

		if (countLeft)
		{
			std::for_each(it, it + countLeft, f);
		}

		for (auto& future : futures)
		{
			future.get();
		}

	# endif
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline void Array<Type, Allocator>::parallel_each(Fty f) const
	{
	# if SIV3D_PLATFORM(WINDOWS)

		std::for_each(std::execution::par, begin(), end(), f);

	# else

		if (isEmpty())
		{
			return;
		}

		const size_t numThreads = Threading::GetConcurrency();

		if (numThreads <= 1)
		{
			return each(f);
		}

		const size_t countPerthread = Max<size_t>(1, (size() + (numThreads - 1)) / numThreads);

		Array<std::future<std::ptrdiff_t>> futures;

		auto it = begin();
		size_t countLeft = size();

		for (size_t i = 0; i < (numThreads - 1); ++i)
		{
			const size_t n = Min(countPerthread, countLeft);

			if (n == 0)
			{
				break;
			}

			futures.emplace_back(std::async(std::launch::async, [=, &f]()
			{
				std::for_each(it, it + n, f);
			}));

			it += n;
			countLeft -= n;
		}

		if (countLeft)
		{
			std::for_each(it, it + countLeft, f);
		}

		for (auto& future : futures)
		{
			future.get();
		}

	# endif
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline auto Array<Type, Allocator>::parallel_map(Fty f) const
	{
		using Ret = std::decay_t<std::invoke_result_t<Fty, Type>>;

		if (isEmpty())
		{
			return Array<Ret>{};
		}

		const size_t numThreads = Threading::GetConcurrency();

		if (numThreads <= 1)
		{
			return map(f);
		}

		Array<Ret> new_array(size());

		const size_t countPerthread = Max<size_t>(1, (size() + (numThreads - 1)) / numThreads);

		Array<std::future<void>> futures;

		auto itDst = new_array.begin();
		auto itSrc = begin();
		size_t countLeft = size();

		for (size_t i = 0; i < (numThreads - 1); ++i)
		{
			const size_t n = Min(countPerthread, countLeft);

			if (n == 0)
			{
				break;
			}

			futures.emplace_back(std::async(std::launch::async, [=, &f]() mutable
			{
				const auto itSrcEnd = itSrc + n;

				while (itSrc != itSrcEnd)
				{
					*itDst++ = f(*itSrc++);
				}
			}));

			itDst += n;
			itSrc += n;
			countLeft -= n;
		}

		if (countLeft)
		{
			const auto itSrcEnd = end();

			while (itSrc != itSrcEnd)
			{
				*itDst++ = f(*itSrc++);
			}
		}

		for (auto& future : futures)
		{
			future.get();
		}

		return new_array;
	}

# endif

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::Generate(const size_type size, Fty generator)
	{
		Array new_array;
		new_array.reserve(size);

		for (size_type i = 0; i < size; ++i)
		{
			new_array.push_back(generator());
		}

		return new_array;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::IndexedGenerate(const size_type size, Fty indexedGenerator)
	{
		Array new_array;
		new_array.reserve(size);

		for (size_type i = 0; i < size; ++i)
		{
			new_array.push_back(indexedGenerator(i));
		}

		return new_array;
	}

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
		return (b < a);
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
	inline void swap(Array<Type, Allocator>& a, Array<Type, Allocator>& b) noexcept
	{
		a.swap(b);
	}

	template <class T0, class... Ts>
	inline auto MakeArray(T0&& first, Ts&&... args)
	{
		using Type = std::decay_t<T0>;
		return Array<Type>{ std::forward<T0>(first), std::forward<Ts>(args)... };
	}
}
