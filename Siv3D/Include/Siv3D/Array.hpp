//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <vector>
# include <string>
# include <algorithm>
# include <future>
# include "Fwd.hpp"
# include "Allocator.hpp"
# include "Concept.hpp"
# include "Threading.hpp"
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
		using base_type::crend;
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

        Array()
            : base_type() {}

		void swap(Array& other)
		{
			base_type::swap(other);
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
			push_back(std::forward<Type>(value));

			return *this;
		}

		template <class Fty = decltype(Id())>
		bool all(Fty f = Id()) const
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

		template <class Fty = decltype(Id())>
		bool any(Fty f = Id()) const
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
			return choice(GetDefaultRBG());
		}

		template <class URBG, std::enable_if_t<!std::is_scalar<URBG>::value>* = nullptr>
		const Type& choice(URBG&& rbg) const
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice() choice from empty Array");
			}

			const size_t index = std::uniform_int_distribution<size_t>(0, size() - 1)(rbg);

			return operator[](index);
		}

		template <class Size_t, std::enable_if_t<std::is_scalar<Size_t>::value>* = nullptr>
		Array choice(Size_t n) const
		{
			return choice(n, GetDefaultRBG());
		}

		template <class URBG>
		Array choice(size_t n, URBG&& rbg) const
		{
			Array result;		

			result.reserve(std::min(n, size()));

			Sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));
			
			return result;
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

		template <class Fty>
		size_t count_if(Fty f) const
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

		template <class Fty>
		Array& drop_while(Fty f)
		{
			erase(begin(), std::find_if_not(begin(), end(), f));

			return *this;
		}

		template <class Fty>
		Array dropped_while(Fty f) const
		{
			return Array(std::find_if_not(begin(), end(), f), end());
		}

		template <class Fty>
		Array& each(Fty f)
		{
			for (auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		template <class Fty>
		const Array& each(Fty f) const
		{
			for (const auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		template <class Fty>
		Array& each_index(Fty f)
		{
			size_t i = 0;

			for (auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		template <class Fty>
		const Array& each_index(Fty f) const
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

		template <class Fty>
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

		template <class Fty>
		bool include_if(Fty f) const
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
			Array<std::result_of_t<Fty(Type)>> new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		template <class Fty = decltype(Id())>
		bool none(Fty f = Id()) const
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
		auto reduce(Fty f, std::result_of_t<Fty(Type, Type)> init) const
		{
			auto value = init;

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

			std::result_of_t<Fty(Type, Type)> value = *it++;

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

		template <class Fty>
		Array& remove_if(Fty f)
		{
			erase(std::remove_if(begin(), end(), f), end());

			return *this;
		}

		template <class Fty>
		Array removed_if(Fty f) const &
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

		template <class Fty>
		Array removed_if(Fty f) &&
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

		template <class Fty>
		Array& replace_if(Fty f, const Type& newValue)
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

		template <class Fty>
		Array replaced_if(Fty f, const Type& newValue) const &
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

		template <class Fty>
		Array replaced_if(Fty f, const Type& newValue) &&
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

		template <class Fty>
		Array& reverse_each(Fty f)
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		template <class Fty>
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
			return shuffle(GetDefaultRBG());
		}

		template <class URBG>
		Array& shuffle(URBG&& rbg)
		{
			std::shuffle(begin(), end(), std::forward<URBG>(rbg));

			return *this;
		}

		Array shuffled() const &
		{
			return shuffled(GetDefaultRBG());
		}

		Array shuffled() &&
		{
			return shuffled(GetDefaultRBG());
		}

		template <class URBG>
		Array shuffled(URBG&& rbg) const &
		{
			return Array(*this).shuffle(std::forward<URBG>(rbg));
		}

		template <class URBG>
		Array shuffled(URBG&& rbg) &&
		{
			shuffle(std::forward<URBG>(rbg));

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

		template <class Fty>
		Array& sort_by(Fty f)
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

		template <class Fty>
		Array sorted_by(Fty f) const &
		{
			return Array(*this).sort_by(f);
		}

		template <class Fty>
		Array sorted_by(Fty f) &&
		{
			sort_by(f);

			return std::move(*this);
		}

		template <class T = Type, std::enable_if_t<Concept::HasPlus<T>::value && Concept::HasPlusAssign<T>::value>* = nullptr>
		auto sum() const
		{
			decltype(std::declval<Type>() + std::declval<Type>()) result{};

			for (const auto& v : *this)
			{
				result += v;
			}

			return result;
		}

		template <class T = Type, std::enable_if_t<Concept::HasPlus<T>::value && !Concept::HasPlusAssign<T>::value>* = nullptr>
		auto sum() const
		{
			decltype(std::declval<Type>() + std::declval<Type>()) result{};

			for (const auto& v : *this)
			{
				result = result + v;
			}

			return result;
		}

		template <class T = Type, std::enable_if_t<!Concept::HasPlus<T>::value>* = nullptr>
		const Array& sum() const
		{
			return *this;
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

		template <class Fty>
		Array& take_while(Fty f)
		{
			erase(std::find_if_not(begin(), end(), f), end());

			return *this;
		}

		template <class Fty>
		Array taken_while(Fty f) const
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

		template <class Fty>
		size_t parallel_count_if(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			if (isEmpty())
			{
				return 0;
			}

			const size_t n = std::max<size_t>(1, size() / std::max<size_t>(1, numThreads));

			Array<std::future<std::ptrdiff_t>> futures;

			auto it = begin();
			const auto last = end();

			for (; it < last - n; it += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]()
				{
					return std::count_if(it, it + n, f);
				}));
			}

			std::for_each(it, last, f);

			size_t result = 0;

			for (auto& future : futures)
			{
				result += future.get();
			}

			return result;
		}

		template <class Fty>
		Array& parallel_each(Fty f, size_t numThreads = Threading::GetConcurrency())
		{
			if (isEmpty())
			{
				return *this;
			}

			numThreads = std::max<size_t>(1, numThreads);

			const size_t n = std::max<size_t>(1, size() / numThreads);

			Array<std::future<void>> futures;

			auto it = begin();
			const auto last = end();

			for (; it < last - n; it += n)
			{
				//Log(L"###", n);

				futures.emplace_back(std::async(std::launch::async, [=, &f]()
				{
					std::for_each(it, it + n, f);
				}));
			}

			//Log(L"##", last - it);

			std::for_each(it, last, f);

			for (auto& future : futures)
			{
				future.wait();
			}

			return *this;
		}

		template <class Fty>
		const Array& parallel_each(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			if (isEmpty())
			{
				return *this;
			}

			const size_t n = std::max<size_t>(1, size() / std::max<size_t>(1, numThreads));

			Array<std::future<void>> futures;

			auto it = begin();
			const auto last = end();

			for (; it < last - n; it += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]()
				{
					std::for_each(it, it + n, f);
				}));
			}

			std::for_each(it, last, f);

			for (auto& future : futures)
			{
				future.wait();
			}

			return *this;
		}

		template <class Fty>
		auto parallel_map(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			Array<std::result_of_t<Fty(Type)>> new_array;

			if (isEmpty())
			{
				return new_array;
			}

			new_array.resize(size());

			const size_t n = std::max<size_t>(1, size() / std::max<size_t>(1, numThreads));

			Array<std::future<void>> futures;

			auto itSrc = begin();
			const auto itSrcEnd = end();
			auto itDst = new_array.begin();

			for (; itSrc < itSrcEnd - n; itSrc += n, itDst += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]() mutable
				{
					const auto itSrcEnd = itSrc + n;

					while (itSrc != itSrcEnd)
					{
						*itDst++ = f(*itSrc++);
					}
				}));
			}

			while (itSrc != itSrcEnd)
			{
				*itDst++ = f(*itSrc++);
			}

			for (auto& future : futures)
			{
				future.wait();
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

		Array()
            : base_type() {}

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

		void swap(Array& other)
		{
			base_type::swap(other);
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

		Array& operator <<(bool value)
		{
			push_back(value);

			return *this;
		}

		template <class Fty = decltype(Id())>
		bool all(Fty f = Id()) const
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

		template <class Fty = decltype(Id())>
		bool any(Fty f = Id()) const
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
			return choice(GetDefaultRBG());
		}

		template <class URBG, std::enable_if_t<!std::is_scalar<URBG>::value>* = nullptr>
		const bool& choice(URBG&& rbg) const
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice() choice from empty Array");
			}

			const size_t index = std::uniform_int_distribution<size_t>(0, size() - 1)(rbg);

			return operator[](index);
		}

		template <class Size_t, std::enable_if_t<std::is_scalar<Size_t>::value>* = nullptr>
		Array choice(Size_t n) const
		{
			return choice(n, GetDefaultRBG());
		}

		template <class URBG>
		Array choice(size_t n, URBG&& rbg) const
		{
			Array result;

			result.reserve(std::min(n, size()));

			Sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));

			return result;
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

		template <class Fty>
		size_t count_if(Fty f) const
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

		template <class Fty>
		Array& drop_while(Fty f)
		{
			erase(begin(), std::find_if_not(begin(), end(), f));

			return *this;
		}

		template <class Fty>
		Array dropped_while(Fty f) const
		{
			return Array(std::find_if_not(begin(), end(), f), end());
		}

		template <class Fty>
		Array& each(Fty f)
		{
			for (auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		template <class Fty>
		const Array& each(Fty f) const
		{
			for (const auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		template <class Fty>
		Array& each_index(Fty f)
		{
			size_t i = 0;

			for (auto& v : *this)
			{
				f(i++, v);
			}

			return *this;
		}

		template <class Fty>
		const Array& each_index(Fty f) const
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

		template <class Fty>
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

		template <class Fty>
		bool include_if(Fty f) const
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

		Array& keep_if(std::function<bool(bool)> f)
		{
			erase(std::remove_if(begin(), end(), std::not1(f)), end());

			return *this;
		}

		template <class Fty>
		auto map(Fty f) const
		{
			Array<std::result_of_t<Fty(bool)>> new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		template <class Fty = decltype(Id())>
		bool none(Fty f = Id()) const
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
		auto reduce(Fty f, std::result_of_t<Fty(bool, bool)> init) const
		{
			auto value = init;

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

			std::result_of_t<Fty(bool, bool)> value = *it++;

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

		template <class Fty>
		Array& remove_if(Fty f)
		{
			erase(std::remove_if(begin(), end(), f), end());

			return *this;
		}

		template <class Fty>
		Array removed_if(Fty f) const &
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

		template <class Fty>
		Array removed_if(Fty f) &&
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

		template <class Fty>
		Array& replace_if(Fty f, const bool& newValue)
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

		template <class Fty>
		Array replaced_if(Fty f, const bool& newValue) const &
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

		template <class Fty>
		Array replaced_if(Fty f, const bool& newValue) &&
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

		template <class Fty>
		Array& reverse_each(Fty f)
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		template <class Fty>
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
			return shuffle(GetDefaultRBG());
		}

		template <class URBG>
		Array& shuffle(URBG&& rbg)
		{
			std::shuffle(begin(), end(), std::forward<URBG>(rbg));

			return *this;
		}

		Array shuffled() const &
		{
			return shuffled(GetDefaultRBG());
		}

		Array shuffled() &&
		{
			return shuffled(GetDefaultRBG());
		}

		template <class URBG>
		Array shuffled(URBG&& rbg) const &
		{
			return Array(*this).shuffle(std::forward<URBG>(rbg));
		}

		template <class URBG>
		Array shuffled(URBG&& rbg) &&
		{
			shuffle(std::forward<URBG>(rbg));

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

		template <class Fty>
		Array& sort_by(Fty f)
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

		template <class Fty>
		Array sorted_by(Fty f) const &
		{
			return Array(*this).sort_by(f);
		}

		template <class Fty>
		Array sorted_by(Fty f) &&
		{
			sort_by(f);

			return std::move(*this);
		}

		size_t sum() const
		{
			return count(true);
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

		template <class Fty>
		Array& take_while(Fty f)
		{
			erase(std::find_if_not(begin(), end(), f), end());

			return *this;
		}

		template <class Fty>
		Array taken_while(Fty f) const
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

		template <class Fty>
		size_t parallel_count_if(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			if (isEmpty())
			{
				return 0;
			}

			const size_t n = std::max<size_t>(1, size() / std::max<size_t>(1, numThreads));

			Array<std::future<std::ptrdiff_t>> futures;

			auto it = begin();
			const auto last = end();

			for (; it < last - n; it += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]()
				{
					return std::count_if(it, it + n, f);
				}));
			}

			std::for_each(it, last, f);

			size_t result = 0;

			for (auto& future : futures)
			{
				result += future.get();
			}

			return result;
		}

		template <class Fty>
		Array& parallel_each(Fty f, size_t numThreads = Threading::GetConcurrency())
		{
			if (isEmpty())
			{
				return *this;
			}

			const size_t n = std::max<size_t>(1, size() / std::max<size_t>(1, numThreads));

			Array<std::future<void>> futures;

			auto it = begin();
			const auto last = end();

			for (; it < last - n; it += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]()
				{
					std::for_each(it, it + n, f);
				}));
			}

			std::for_each(it, last, f);

			for (auto& future : futures)
			{
				future.wait();
			}

			return *this;
		}

		template <class Fty>
		const Array& parallel_each(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			if (isEmpty())
			{
				return *this;
			}

			const size_t n = std::max<size_t>(1, size() / std::max<size_t>(1, numThreads));

			Array<std::future<void>> futures;

			auto it = begin();
			const auto last = end();

			for (; it < last - n; it += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]()
				{
					std::for_each(it, it + n, f);
				}));
			}

			std::for_each(it, last, f);

			for (auto& future : futures)
			{
				future.wait();
			}

			return *this;
		}

		template <class Fty>
		auto parallel_map(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			Array<std::result_of_t<Fty(bool)>> new_array;

			if (isEmpty())
			{
				return new_array;
			}

			new_array.resize(size());

			const size_t n = std::max<size_t>(1, size() / std::max<size_t>(1, numThreads));

			Array<std::future<void>> futures;

			auto itSrc = begin();
			const auto itSrcEnd = end();
			auto itDst = new_array.begin();

			for (; itSrc < itSrcEnd - n; itSrc += n, itDst += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]() mutable
				{
					const auto itSrcEnd = itSrc + n;

					while (itSrc != itSrcEnd)
					{
						*itDst++ = f(*itSrc++);
					}
				}));
			}

			while (itSrc != itSrcEnd)
			{
				*itDst++ = f(*itSrc++);
			}

			for (auto& future : futures)
			{
				future.wait();
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
