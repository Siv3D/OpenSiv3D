//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/FormatBool.hpp>

namespace s3d
{
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
		using base_type::front;
		using base_type::back;
		using base_type::data;
		using base_type::begin;
		using base_type::end;
		using base_type::cbegin;
		using base_type::cend;
		using base_type::rbegin;
		using base_type::rend;
		using base_type::crbegin;
		using base_type::crend;
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

		SIV3D_NODISCARD_CXX20
		Array() = default;

		SIV3D_NODISCARD_CXX20
		Array(const Array&) = default;

		SIV3D_NODISCARD_CXX20
		Array(Array&&) = default;

		SIV3D_NODISCARD_CXX20
		Array(const size_type count, const value_type& value)
			: base_type(count, value) {}

		SIV3D_NODISCARD_CXX20
		explicit Array(const size_type count)
			: base_type(count, false) {}

		template <class InputIt>
		SIV3D_NODISCARD_CXX20
		Array(InputIt first, InputIt last)
			: base_type(first, last) {}

		SIV3D_NODISCARD_CXX20
		Array(std::initializer_list<bool> init)
			: base_type(init.begin(), init.end()) {}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Array(size_type size, Arg::generator_<Fty> generator)
			: Array(Generate<Fty>(size, *generator)) {}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, size_t>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Array(size_type size, Arg::indexedGenerator_<Fty> indexedGenerator)
			: Array(IndexedGenerate<Fty>(size, *indexedGenerator)) {}

		SIV3D_NODISCARD_CXX20
		explicit Array(const Arg::reserve_<size_type> size)
		{
			base_type::reserve(*size);
		}

		Array& operator =(const Array&) = default;

		Array& operator =(Array&&) = default;

		template<class... Args>
		iterator emplace(const_iterator pos, Args&&... args)
		{
			value_type tmp(std::forward<Args>(args)...);
			return (insert(pos, tmp));
		}

		template<class... Args>
		void emplace_back(Args&&... args)
		{
			value_type tmp(std::forward<Args>(args)...);
			push_back(tmp);
		}

		void swap(Array& other) noexcept
		{
			base_type::swap(other);
		}

		[[nodiscard]]
		bool isEmpty() const noexcept
		{
			return base_type::empty();
		}

		[[nodiscard]]
		explicit operator bool() const noexcept
		{
			return (not base_type::empty());
		}

		void release()
		{
			clear();

			shrink_to_fit();
		}

		[[nodiscard]]
		size_t size_bytes() const noexcept
		{
			return size() * sizeof(value_type);
		}

		void push_front(value_type value)
		{
			insert(begin(), value);
		}

		void pop_front()
		{
			erase(begin());
		}

		void pop_front_N(const size_t n)
		{
			erase(begin(), begin() + Min(n, size()));
		}

		void pop_back_N(const size_t n)
		{
			erase(end() - Min(n, size()), end());
		}

		[[nodiscard]]
		const value_type& operator[](const size_t index) const
		{
			return base_type::operator[](index);
		}

		[[nodiscard]]
		value_type& operator[](const size_t index)
		{
			return base_type::operator[](index);
		}

		const value_type& at(const size_t index) const
		{
			return base_type::operator[](index);
		}

		value_type& at(const size_t index)
		{
			return base_type::at(index);
		}

		Array& operator <<(value_type value)
		{
			push_back(value);

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool>>* = nullptr>
		auto operator >>(Fty f) const
		{
			using Ret = std::remove_cvref_t<decltype(f((*this)[0]))>;

			if constexpr (std::is_same_v<Ret, void>)
			{
				each(f);
			}
			else
			{
				return map(f);
			}
		}

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		bool all(Fty f = Identity) const
		{
			return std::all_of(begin(), end(), f);
		}

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		bool any(Fty f = Identity) const
		{
			return std::any_of(begin(), end(), f);
		}

		Array& append(const Array& other_array)
		{
			insert(end(), other_array.begin(), other_array.end());

			return *this;
		}

		[[nodiscard]]
		value_type& choice()
		{
			return choice(GetDefaultRNG());
		}

		[[nodiscard]]
		const value_type& choice() const
		{
			return choice(GetDefaultRNG());
		}

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		value_type& choice(URBG&& rbg)
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice(): Array is empty");
			}

			const size_t index = UniformIntDistribution<size_t>(0, size() - 1)(rbg);

			return operator[](index);
		}

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		const value_type& choice(URBG&& rbg) const
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice(): Array is empty");
			}

			const size_t index = UniformIntDistribution<size_t>(0, size() - 1)(rbg);

			return operator[](index);
		}

		SIV3D_CONCEPT_INTEGRAL	
		[[nodiscard]]
		Array choice(const Int n) const
		{
			return choice(n, GetDefaultRNG());
		}

	# if __cpp_lib_concepts
		template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
	# else
		template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>* = nullptr,
			std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
	# endif
		[[nodiscard]]
		Array choice(const Size_t n, URBG&& rbg) const
		{
			Array result(Arg::reserve = Min(n, size()));

			std::sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));

			return result;
		}

		[[nodiscard]]
		Array<Array<value_type>> chunk(const size_t n) const
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

		[[nodiscard]]
		size_t count(const value_type& value) const
		{
			return std::count(begin(), end(), value);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		size_t count_if(Fty f) const
		{
			return std::count_if(begin(), end(), f);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool&>>* = nullptr>
		Array& each(Fty f)
		{
			for (auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool>>* = nullptr>
		const Array& each(Fty f) const
		{
			for (const auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, bool&>>* = nullptr>
		Array& each_index(Fty f)
		{
			size_t i = 0;

			for (auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, bool>>* = nullptr>
		const Array& each_index(Fty f) const
		{
			size_t i = 0;

			for (const auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		[[nodiscard]]
		const value_type& fetch(size_t index, const value_type& defaultValue) const
		{
			if (index >= size())
			{
				return defaultValue;
			}

			return operator[](index);
		}

		Array& fill(const value_type& value)
		{
			std::fill(begin(), end(), value);

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		Array filter(Fty f) const
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

		[[nodiscard]]
		Array<Array<value_type>> in_groups(size_t group) const
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

		[[nodiscard]]
		bool includes(const value_type& value) const
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

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		bool includes_if(Fty f) const
		{
			return any(f);
		}

		template <class T = bool, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		bool isSorted() const
		{
			return std::is_sorted(begin(), end());
		}

		[[nodiscard]]
		String join(const StringView sep = U", "_sv, const StringView begin = U"{"_sv, const StringView end = U"}"_sv) const
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

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool>>* = nullptr>
		auto map(Fty f) const
		{
			Array<std::remove_cvref_t<decltype(f((*this)[0]))>> new_array(Arg::reserve = size());

			for (const auto& v : *this)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		bool none(Fty f = Identity) const
		{
			return std::none_of(begin(), end(), f);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		auto partition(Fty f)
		{
			return std::partition(begin(), end(), f);
		}

		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, bool, bool>>>
		auto reduce(Fty f, R init) const
		{
			auto value = init;

			for (const auto& v : *this)
			{
				value = f(value, v);
			}

			return value;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool, bool>>* = nullptr>
		auto reduce1(Fty f) const
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

		Array& remove(const value_type& value)
		{
			erase(std::remove(begin(), end(), value), end());

			return *this;
		}

		[[nodiscard]]
		Array removed(const value_type& value) const&
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

		[[nodiscard]]
		Array removed(const value_type& value)&&
		{
			erase(std::remove(begin(), end(), value), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array& remove_at(const size_t index)
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::remove_at(): index out of range");
			}

			erase(begin() + index);

			return *this;
		}

		[[nodiscard]]
		Array removed_at(const size_t index) const
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::removed_at(): index out of range");
			}

			Array new_array(Arg::reserve = (size() - 1));

			new_array.insert(new_array.end(), begin(), begin() + index);

			new_array.insert(new_array.end(), begin() + index + 1, end());

			return new_array;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		Array& remove_if(Fty f)
		{
			erase(std::remove_if(begin(), end(), f), end());

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		Array removed_if(Fty f) const&
		{
			Array new_array;

			for (const auto& v : *this)
			{
				if (not f(v))
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		Array removed_if(Fty f)&&
		{
			erase(std::remove_if(begin(), end(), f), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array& replace(const value_type& oldValue, const value_type& newValue)
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

		[[nodiscard]]
		Array replaced(const value_type& oldValue, const value_type& newValue) const&
		{
			Array new_array(Arg::reserve = size());

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

		[[nodiscard]]
		Array replaced(const value_type& oldValue, const value_type& newValue)&&
		{
			replace(oldValue, newValue);

			return std::move(*this);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		Array& replace_if(Fty f, const value_type& newValue)
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

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		Array replaced_if(Fty f, const value_type& newValue) const&
		{
			Array new_array(Arg::reserve = size());

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

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		Array replaced_if(Fty f, const value_type& newValue)&&
		{
			replace_if(f, newValue);

			return std::move(*this);
		}

		Array& reverse()
		{
			std::reverse(begin(), end());

			return *this;
		}

		[[nodiscard]]
		Array reversed() const&
		{
			return Array(rbegin(), rend());
		}

		[[nodiscard]]
		Array reversed()&&
		{
			reverse();

			return std::move(*this);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool&>>* = nullptr>
		Array& reverse_each(Fty f)
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool>>* = nullptr>
		const Array& reverse_each(Fty f) const
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

		[[nodiscard]]
		Array rotated(std::ptrdiff_t count = 1) const&
		{
			return Array(*this).rotate(count);
		}

		[[nodiscard]]
		Array rotated(std::ptrdiff_t count = 1)&&
		{
			rotate(count);

			return std::move(*this);
		}

		Array& rsort()
		{
			std::sort(begin(), end(), std::greater<>());

			return *this;
		}

		[[nodiscard]]
		Array rsorted() const&
		{
			return Array(*this).rsort();
		}

		[[nodiscard]]
		Array rsorted()&&
		{
			rsort();

			return std::move(*this);
		}

		Array& shuffle()
		{
			return shuffle(GetDefaultRNG());
		}

		SIV3D_CONCEPT_URBG
		Array& shuffle(URBG&& rbg)
		{
			Shuffle(begin(), end(), std::forward<URBG>(rbg));

			return *this;
		}

		[[nodiscard]]
		Array shuffled() const&
		{
			return shuffled(GetDefaultRNG());
		}

		[[nodiscard]]
		Array shuffled()&&
		{
			return shuffled(GetDefaultRNG());
		}

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		Array shuffled(URBG&& rbg) const&
		{
			return Array(*this).shuffle(std::forward<URBG>(rbg));
		}

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		Array shuffled(URBG&& rbg)&&
		{
			shuffle(std::forward<URBG>(rbg));

			return std::move(*this);
		}

		[[nodiscard]]
		Array slice(size_t index) const
		{
			if (index >= size())
			{
				return Array();
			}

			return Array(begin() + index, end());
		}

		[[nodiscard]]
		Array slice(size_t index, size_t length) const
		{
			if (index >= size())
			{
				return Array();
			}

			return Array(begin() + index, begin() + Min(index + length, size()));
		}

		Array& sort()
		{
			std::sort(begin(), end());

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		auto stable_partition(Fty f)
		{
			return std::stable_partition(begin(), end(), f);
		}

		Array& stable_sort()
		{
			std::stable_sort(begin(), end());

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		Array& sort_by(Fty f)
		{
			std::sort(begin(), end(), f);

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		Array& stable_sort_by(Fty f)
		{
			std::stable_sort(begin(), end(), f);

			return *this;
		}

		[[nodiscard]]
		Array sorted() const&
		{
			return Array(*this).sort();
		}

		[[nodiscard]]
		Array stable_sorted() const&
		{
			return Array(*this).stable_sort();
		}

		[[nodiscard]]
		Array sorted()&&
		{
			sort();

			return std::move(*this);
		}

		[[nodiscard]]
		Array stable_sorted()&&
		{
			stable_sort();

			return std::move(*this);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		[[nodiscard]]
		Array sorted_by(Fty f) const&
		{
			return Array(*this).sort_by(f);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted_by(Fty f) const&
		{
			return Array(*this).stable_sort_by(f);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		[[nodiscard]]
		Array sorted_by(Fty f)&&
		{
			sort_by(f);

			return std::move(*this);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted_by(Fty f)&&
		{
			stable_sort_by(f);

			return std::move(*this);
		}

		[[nodiscard]]
		Array take(const size_t n) const
		{
			return Array(begin(), begin() + Min(n, size()));
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]]
		Array take_while(Fty f) const
		{
			return Array(begin(), std::find_if_not(begin(), end(), f));
		}

		Array& stable_unique()
		{
			return *this = stable_uniqued();
		}

		[[nodiscard]]
		Array stable_uniqued() const
		{
			Array result;

			if (empty())
			{
				return result;
			}

			auto it = begin();
			const bool first = *it++;
			result << first;

			for (; it != end(); ++it)
			{
				if (*it != first)
				{
					result << !(first);
					break;
				}
			}

			return result;
		}

		Array& sort_and_unique()
		{
			return *this = stable_uniqued().sort();
		}

		[[nodiscard]]
		Array sorted_and_uniqued() const&
		{
			return stable_uniqued().sort();
		}

		[[nodiscard]]
		Array sorted_and_uniqued()&&
		{
			return stable_uniqued().sort();
		}

		Array& unique_consecutive()
		{
			erase(std::unique(begin(), end()), end());

			return *this;
		}

		[[nodiscard]]
		Array uniqued_consecutive() const&
		{
			Array result;

			std::unique_copy(begin(), end(), std::back_inserter(result));

			return result;
		}

		[[nodiscard]]
		Array uniqued_consecutive()&&
		{
			erase(std::unique(begin(), end()), end());

			shrink_to_fit();

			return std::move(*this);
		}

		[[nodiscard]]
		Array values_at(std::initializer_list<size_t> indices) const
		{
			Array new_array(Arg::reserve = indices.size());

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

		friend std::ostream& operator <<(std::ostream& output, const Array& value)
		{
			return (output << Format(value).narrow());
		}

		friend std::wostream& operator <<(std::wostream& output, const Array& value)
		{
			return (output << Format(value).toWstr());
		}

		friend std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const Array& value)
		{
			const String s = Format(value);
			return output.write(s.data(), s.size());
		}

		friend void Formatter(FormatData& formatData, const Array& value)
		{
			Formatter(formatData, value.begin(), value.end());
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty>>* = nullptr>
		[[nodiscard]]
		static Array Generate(const size_type size, Fty generator)
		{
			Array new_array(Arg::reserve = size);

			for (size_type i = 0; i < size; ++i)
			{
				new_array.push_back(generator());
			}

			return new_array;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, size_t>>* = nullptr>
		[[nodiscard]]
		static Array IndexedGenerate(const size_type size, Fty indexedGenerator)
		{
			Array new_array(Arg::reserve = size);

			for (size_type i = 0; i < size; ++i)
			{
				new_array.push_back(indexedGenerator(i));
			}

			return new_array;
		}
	};
}
