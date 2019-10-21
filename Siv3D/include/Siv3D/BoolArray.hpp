//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Array.hpp"

namespace s3d
{
	/// <summary>
	/// 動的配列
	/// </summary>
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

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty>>* = nullptr>
		static Array Generate(const size_type size, Fty generator)
		{
			Array new_array(size);

			for (auto& value : new_array)
			{
				value = generator();
			}

			return new_array;
		}

		/// <summary>
		/// インデックス付きジェネレータを用いて配列を作成します。
		/// </summary>
		/// <param name="size">
		/// 配列の要素数
		/// </param>
		/// <param name="generator">
		/// ジェネレータ
		/// </param>
		/// <remarks>
		/// 各要素の値をジェネレータ関数により初期化します。
		/// </remarks>
		/// <returns>
		/// 作成した配列
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, size_t>>* = nullptr>
		static Array IndexedGenerate(const size_type size, Fty indexedGenerator)
		{
			Array new_array(size);

			size_t i = 0;

			for (auto& value : new_array)
			{
				value = indexedGenerator(i++);
			}

			return new_array;
		}

		Array();

		Array(const size_type count, const value_type& value);

		explicit Array(const size_type count);

		template <class InputIt>
		Array(InputIt first, InputIt last)
			: base_type(first, last) {}

		Array(const Array& other);

		Array(Array&& other) noexcept;

		Array(std::initializer_list<value_type> init);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty>>* = nullptr>
		Array(const size_type size, Arg::generator_<Fty> generator)
			: Array(Generate<Fty>(size, *generator)) {}

		/// <summary>
		/// インデックス付きジェネレータを用いて配列を作成します。
		/// </summary>
		/// <param name="size">
		/// 配列の要素数
		/// </param>
		/// <param name="indexedGenerator">
		/// インデックス付きジェネレータ
		/// </param>
		/// <remarks>
		/// 各要素の値をジェネレータ関数により初期化します。
		/// </remarks>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, size_t>>* = nullptr>
		Array(const size_type size, Arg::indexedGenerator_<Fty> indexedGenerator)
			: Array(IndexedGenerate<Fty>(size, *indexedGenerator)) {}

		Array& operator =(const Array& other) = default;

		Array& operator =(Array&& other) = default;

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

		void swap(Array& other);

		bool isEmpty() const noexcept;

		/// <summary>
		/// 配列に要素が含まれているかを返します。
		/// </summary>
		/// <returns>
		/// 配列に要素が含まれている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const noexcept;

		void release();

		size_t size_bytes() const noexcept;

		void push_front(const value_type& value);

		void pop_front();

		/// <summary>
		/// 要素にアクセスします。
		/// </summary>
		/// <returns>
		/// 要素へのインデックス
		/// </returns>
		/// <returns>
		/// 要素への参照
		/// </returns>
		const value_type& operator[](size_t index) const &
		{
			return base_type::operator[](index);
		}

		/// <summary>
		/// 要素にアクセスします。
		/// </summary>
		/// <returns>
		/// 要素へのインデックス
		/// </returns>
		/// <returns>
		/// 要素への参照
		/// </returns>
		value_type& operator[](size_t index) &
		{
			return base_type::operator[](index);
		}

		/// <summary>
		/// 要素を取得します。
		/// </summary>
		/// <returns>
		/// 要素へのインデックス
		/// </returns>
		/// <returns>
		/// 要素
		/// </returns>
		value_type operator[](size_t index) &&
		{
			return std::move(base_type::operator[](index));
		}

		/// <summary>
		/// 要素にアクセスします。
		/// </summary>
		/// <returns>
		/// 要素へのインデックス
		/// </returns>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 要素への参照
		/// </returns>
		const value_type& at(size_t index) const &
		{
			return base_type::at(index);
		}

		/// <summary>
		/// 要素にアクセスします。
		/// </summary>
		/// <returns>
		/// 要素へのインデックス
		/// </returns>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 要素への参照
		/// </returns>
		value_type& at(size_t index) &
		{
			return base_type::at(index);
		}

		/// <summary>
		/// 要素を取得します。
		/// </summary>
		/// <returns>
		/// 要素へのインデックス
		/// </returns>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 要素
		/// </returns>
		value_type at(size_t index) &&
		{
			return std::move(base_type::at(index));
		}

		Array& operator <<(const value_type& value);

		template <class Fty = decltype(Id), std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] bool all(Fty f = Id) const
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

		template <class Fty = decltype(Id), std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] bool any(Fty f = Id) const
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

		Array& append(const Array& other_array);

		[[nodiscard]] value_type& choice();

		[[nodiscard]] const value_type& choice() const;

		template <class URBG, std::enable_if_t<!std::is_scalar_v<URBG> && std::is_invocable_r_v<size_t, URBG>>* = nullptr>
		[[nodiscard]] value_type& choice(URBG&& rbg)
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice() choice from empty Array");
			}

			const size_t index = std::uniform_int_distribution<size_t>(0, size() - 1)(rbg);

			return operator[](index);
		}

		template <class URBG, std::enable_if_t<!std::is_scalar_v<URBG> && std::is_invocable_r_v<size_t, URBG>>* = nullptr>
		[[nodiscard]] const value_type& choice(URBG&& rbg) const
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice() choice from empty Array");
			}

			const size_t index = std::uniform_int_distribution<size_t>(0, size() - 1)(rbg);

			return operator[](index);
		}

		template <class Size_t, std::enable_if_t<std::is_integral_v<Size_t>>* = nullptr>
		[[nodiscard]] Array choice(const Size_t n) const
		{
			return choice(n, GetDefaultRNG());
		}

		template <class URBG, std::enable_if_t<!std::is_scalar_v<URBG> && std::is_invocable_r_v<size_t, URBG>>* = nullptr>
		[[nodiscard]] Array choice(const size_t n, URBG&& rbg) const
		{
			Array result;

			result.reserve(std::min(n, size()));

			std::sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));

			return result;
		}

		[[nodiscard]] Array<Array<value_type>> chunk(size_t n) const;

		[[nodiscard]] size_t count(const value_type& value) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] size_t count_if(Fty f) const
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

		Array& drop(size_t n);

		[[nodiscard]] Array dropped(size_t n) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] Array dropped_while(Fty f) const
		{
			return Array(std::find_if_not(begin(), end(), f), end());
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

		[[nodiscard]] const value_type& fetch(const size_t index, const value_type& defaultValue) const;

		Array& fill(const value_type& value);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] Array filter(Fty f) const
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

		[[nodiscard]] Array<Array<value_type>> in_groups(size_t group) const;

		[[nodiscard]] bool includes(const value_type& value) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] bool includes_if(Fty f) const
		{
			return any(f);
		}

		[[nodiscard]] bool isSorted() const;

		[[nodiscard]] String join(StringView sep = U", "_sv, StringView begin = U"{"_sv, StringView end = U"}"_sv) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		Array& keep_if(Fty f)
		{
			erase(std::remove_if(begin(), end(), std::not_fn(f)), end());

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool>>* = nullptr>
		auto map(Fty f) const
		{
			Array<std::decay_t<std::invoke_result_t<Fty, bool>>> new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		template <class Fty = decltype(Id), std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] bool none(Fty f = Id) const
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
				throw std::out_of_range("Array::reduce1() reduce from empty Array");
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

		Array& remove(const value_type& value);

		[[nodiscard]] Array removed(const value_type& value) const &;

		[[nodiscard]] Array removed(const value_type& value) &&;

		Array& remove_at(size_t index);

		[[nodiscard]] Array removed_at(size_t index) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		Array& remove_if(Fty f)
		{
			erase(std::remove_if(begin(), end(), f), end());

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] Array removed_if(Fty f) const &
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

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] Array removed_if(Fty f) &&
		{
			erase(std::remove_if(begin(), end(), f), end());

			shrink_to_fit();

			return std::move(*this);
		}

		Array& replace(const value_type& oldValue, const value_type& newValue);

		[[nodiscard]] Array replaced(const value_type& oldValue, const value_type& newValue) const &;

		[[nodiscard]] Array replaced(const value_type& oldValue, const value_type& newValue) &&;

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
		[[nodiscard]] Array replaced_if(Fty f, const value_type& newValue) const &
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

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] Array replaced_if(Fty f, const value_type& newValue) &&
		{
			replace_if(f, newValue);

			return std::move(*this);
		}

		Array& reverse();

		[[nodiscard]] Array reversed() const &;

		[[nodiscard]] Array reversed() &&;

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

		Array& rotate(std::ptrdiff_t count = 1);

		[[nodiscard]] Array rotated(std::ptrdiff_t count = 1) const &;

		[[nodiscard]] Array rotated(std::ptrdiff_t count = 1) &&;

		Array& shuffle();

		template <class URBG, std::enable_if_t<!std::is_scalar_v<URBG> && std::is_invocable_r_v<size_t, URBG>>* = nullptr>
		Array& shuffle(URBG&& rbg)
		{
			std::shuffle(begin(), end(), std::forward<URBG>(rbg));

			return *this;
		}

		[[nodiscard]] Array shuffled() const &;

		[[nodiscard]] Array shuffled() &&;

		template <class URBG, std::enable_if_t<!std::is_scalar_v<URBG> && std::is_invocable_r_v<size_t, URBG>>* = nullptr>
		[[nodiscard]] Array shuffled(URBG&& rbg) const &
		{
			return Array(*this).shuffle(std::forward<URBG>(rbg));
		}

		template <class URBG, std::enable_if_t<!std::is_scalar_v<URBG> && std::is_invocable_r_v<size_t, URBG>>* = nullptr>
		[[nodiscard]] Array shuffled(URBG&& rbg) &&
		{
			shuffle(std::forward<URBG>(rbg));

			return std::move(*this);
		}

		[[nodiscard]] Array slice(size_t index) const;

		[[nodiscard]] Array slice(size_t index, size_t length) const;

		Array& sort();

		Array& stable_sort();

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		Array& sort_by(Fty f)
		{
			std::sort(begin(), end(), f);

			return *this;
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		Array& stable_sort_by(Fty f)
		{
			std::sort(begin(), end(), f);

			return *this;
		}

		[[nodiscard]] Array sorted() const &;

		[[nodiscard]] Array stable_sorted() const &;

		[[nodiscard]] Array sorted() &&;

		[[nodiscard]] Array stable_sorted() &&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		[[nodiscard]] Array sorted_by(Fty f) const &
		{
			return Array(*this).sort_by(f);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		[[nodiscard]] Array stable_sorted_by(Fty f) const &
		{
			return Array(*this).sort_by(f);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		[[nodiscard]] Array sorted_by(Fty f) &&
		{
			sort_by(f);

			return std::move(*this);
		}

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool, bool>>* = nullptr>
		[[nodiscard]] Array stable_sorted_by(Fty f) &&
		{
			sort_by(f);

			return std::move(*this);
		}

		[[nodiscard]] size_t sum() const;

		[[nodiscard]] Array take(size_t n) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
		[[nodiscard]] Array take_while(Fty f) const
		{
			return Array(begin(), std::find_if_not(begin(), end(), f));
		}

		Array& unique();

		[[nodiscard]] Array uniqued() const &;

		[[nodiscard]] Array uniqued() &&;

		[[nodiscard]] Array values_at(std::initializer_list<size_t> indices) const;

	# ifdef SIV3D_CONCURRENT

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, bool>>* = nullptr>
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

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool&>>* = nullptr>
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

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool>>* = nullptr>
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

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, bool>>* = nullptr>
		auto parallel_map(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			Array<std::decay_t<std::invoke_result_t<Fty, bool>>> new_array;

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

	# endif
	};
}
