//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include <vector>
# ifndef SIV3D_NO_CONCURRENT_API
	# include <future>
	# if SIV3D_PLATFORM(WINDOWS)
	#	include <execution>
	# endif
# endif
# include "String.hpp"
# include "Meta.hpp"
# include "Threading.hpp"
# include "FormatData.hpp"
# include "Format.hpp"
# include "FormatLiteral.hpp"
# include "Shuffle.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 動的配列
	/// @tparam Type 要素の型
	/// @tparam Allocator アロケータ
	template <class Type, class Allocator = std::allocator<Type>>
	class Array : protected std::vector<Type, Allocator>
	{
	private:

		using base_type = std::vector<Type, Allocator>;

	public:

		/// @brief 配列の要素の型
		using value_type				= typename base_type::value_type;

		using pointer					= typename base_type::pointer;
		using const_pointer				= typename base_type::const_pointer;
		using reference					= typename base_type::reference;
		using const_reference			= typename base_type::const_reference;
		using iterator					= typename base_type::iterator;
		using const_iterator			= typename base_type::const_iterator;
		using reverse_iterator			= typename base_type::reverse_iterator;
		using const_reverse_iterator	= typename base_type::const_reverse_iterator;
		using size_type					= typename base_type::size_type;
		using difference_type			= typename base_type::difference_type;
		using allocator_type			= typename base_type::allocator_type;

		using base_type::vector;
		using base_type::operator=;
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
		using base_type::emplace;
		using base_type::erase;
		using base_type::push_back;
		using base_type::emplace_back;
		using base_type::pop_back;
		using base_type::resize;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Array() = default;

		/// @brief コピーコンストラクタ
		/// @param other コピーする配列
		SIV3D_NODISCARD_CXX20
		Array(const Array&) = default;

		/// @brief ムーブコンストラクタ
		/// @param other ムーブする配列
		SIV3D_NODISCARD_CXX20
		Array(Array&&) = default;

		template <class ArrayIsh, std::enable_if_t<Meta::HasAsArray<ArrayIsh>::value>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit Array(ArrayIsh&& a);

		/// @brief ジェネレータ関数を使って配列を作成します。
		/// @tparam Fty ジェネレータ関数の型
		/// @param size 作成する配列の要素数
		/// @param generator ジェネレータ関数
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Array(size_type size, Arg::generator_<Fty> generator);

		/// @brief インデックス指定ジェネレータ関数を使って配列を作成します。
		/// @tparam Fty ジェネレータ関数の型
		/// @param size 作成する配列の要素数
		/// @param indexedGenerator インデックス指定ジェネレータ関数
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Array(size_type size, Arg::indexedGenerator_<Fty> indexedGenerator);

		/// @brief 配列を作成し、`reserve()` します。
		/// @param size `reserve()` するサイズ
		SIV3D_NODISCARD_CXX20
		explicit Array(Arg::reserve_<size_type> size);

		/// @brief コピー代入演算子
		/// @param other コピーする配列
		/// @return *this
		Array& operator =(const Array&) = default;

		/// @brief ムーブ代入演算子
		/// @param other ムーブする配列
		/// @return *this
		Array& operator =(Array&&) = default;

		/// @brief 他の配列と要素を入れ替えます。
		/// @param other 入れ替える配列
		void swap(Array& other) noexcept;

		/// @brief 配列が空であるかを返します。
		/// @return 配列が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief 配列が要素を持っているかを返します。
		/// @return 配列が要素を持っている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 配列の要素を全て消去し、メモリも解放します。
		void release();

		/// @brief 配列の要素の合計サイズ（バイト）を返します。
		/// @return 配列の要素の合計サイズ（バイト）
		[[nodiscard]]
		size_t size_bytes() const noexcept;

		/// @brief 配列の先頭に要素を追加します。
		/// @param value 追加する値
		void push_front(const value_type& value);

		/// @brief 配列の先頭に要素を追加します。
		/// @param value 追加する値
		void push_front(value_type&& value);

		/// @brief 配列の先頭から要素を削除します。
		void pop_front();

		/// @brief 配列の先頭から指定した個数の要素を削除します。
		/// @param n 削除する個数
		/// @remark n が `size()` より多い場合は全ての要素を削除します。
		void pop_front_N(size_t n);

		/// @brief 配列の末尾から指定した個数の要素を削除します。
		/// @param n 削除する個数
		/// @remark n が `size()` より多い場合は全ての要素を削除します。
		void pop_back_N(size_t n);

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		[[nodiscard]]
		const value_type& operator[](size_t index) const;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		[[nodiscard]]
		value_type& operator[](size_t index);

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @throw std::out_of_range 範囲外アクセスの場合 throw
		/// @return 要素への参照
		const value_type& at(size_t index) const;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		value_type& at(size_t index);

		/// @brief 配列の末尾に要素を追加します。
		/// @param value 追加する値
		/// @return *this
		Array& operator <<(const value_type& value);

		/// @brief 配列の末尾に要素を追加します。
		/// @param value 追加する値
		/// @return *this
		Array& operator <<(value_type&& value);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		auto operator >>(Fty f) const;

		/// @brief 全ての要素が条件を満たすかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 全ての要素が条件を満たすか、配列が空の場合 true, それ以外の場合は false
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool all(Fty f = Identity) const;

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool any(Fty f = Identity) const;

		Array& append(const Array& other_array);

		[[nodiscard]]
		value_type& choice();

		[[nodiscard]]
		const value_type& choice() const;

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		value_type& choice(URBG&& rbg);

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		const value_type& choice(URBG&& rbg) const;

		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		Array choice(Int n) const;

	# if __cpp_lib_concepts
		template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
	# else
		template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>* = nullptr,
			std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
	# endif
		[[nodiscard]]
		Array choice(Size_t n, URBG&& rbg) const;

		[[nodiscard]]
		Array<Array<value_type>> chunk(size_t n) const;

		[[nodiscard]]
		size_t count(const value_type& value) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		size_t count_if(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		Array& each(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		const Array& each(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, Type&>>* = nullptr>
		Array& each_index(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, Type>>* = nullptr>
		const Array& each_index(Fty f) const;

		[[nodiscard]]
		const value_type& fetch(size_t index, const value_type& defaultValue) const;

		Array& fill(const value_type& value);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array filter(Fty f) const;

		[[nodiscard]]
		Array<Array<value_type>> in_groups(size_t group) const;

		[[nodiscard]]
		bool includes(const value_type& value) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool includes_if(Fty f) const;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		bool isSorted() const;

		[[nodiscard]]
		String join(StringView sep = U", "_sv, StringView begin = U"{"_sv, StringView end = U"}"_sv) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		auto map(Fty f) const;

		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool none(Fty f = Identity) const;

		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, Type, Type>>>
		auto reduce(Fty f, R init) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type, Type>>* = nullptr>
		auto reduce1(Fty f) const;

		Array& remove(const value_type& value);

		[[nodiscard]]
		Array removed(const value_type& value) const&;

		[[nodiscard]]
		Array removed(const value_type& value)&&;

		Array& remove_at(size_t index);

		[[nodiscard]]
		Array removed_at(size_t index) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		Array& remove_if(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array removed_if(Fty f) const&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array removed_if(Fty f)&&;

		Array& replace(const value_type& oldValue, const value_type& newValue);

		[[nodiscard]]
		Array replaced(const value_type& oldValue, const value_type& newValue) const&;

		[[nodiscard]]
		Array replaced(const value_type& oldValue, const value_type& newValue)&&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		Array& replace_if(Fty f, const value_type& newValue);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array replaced_if(Fty f, const value_type& newValue) const&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array replaced_if(Fty f, const value_type& newValue)&&;

		Array& reverse();

		[[nodiscard]]
		Array reversed() const&;

		[[nodiscard]]
		Array reversed()&&;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		Array& reverse_each(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		const Array& reverse_each(Fty f) const;

		Array& rotate(std::ptrdiff_t count = 1);

		[[nodiscard]]
		Array rotated(std::ptrdiff_t count = 1) const&;

		[[nodiscard]]
		Array rotated(std::ptrdiff_t count = 1)&&;

		template <class T = Type, std::enable_if_t<Meta::HasGreaterThan_v<T>>* = nullptr>
		Array& rsort();

		template <class T = Type, std::enable_if_t<Meta::HasGreaterThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array rsorted() const&;

		template <class T = Type, std::enable_if_t<Meta::HasGreaterThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array rsorted()&&;

		Array& shuffle();

		SIV3D_CONCEPT_URBG
		Array& shuffle(URBG&& rbg);

		[[nodiscard]]
		Array shuffled() const&;

		[[nodiscard]]
		Array shuffled()&&;

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		Array shuffled(URBG&& rbg) const&;

		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		Array shuffled(URBG&& rbg)&&;

		[[nodiscard]]
		Array slice(size_t index) const;

		[[nodiscard]]
		Array slice(size_t index, size_t length) const;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		Array& sort();

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		Array& stable_sort();

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		Array& sort_by(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		Array& stable_sort_by(Fty f);

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array sorted() const&;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted() const&;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array sorted()&&;

		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted()&&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Array sorted_by(Fty f) const&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted_by(Fty f) const&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Array sorted_by(Fty f)&&;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted_by(Fty f)&&;

		template <class T = Type, std::enable_if_t<Meta::HasPlus_v<T>>* = nullptr>
		[[nodiscard]]
		auto sum() const;

		template <class T = Type, std::enable_if_t<not Meta::HasPlus_v<T>>* = nullptr>
		void sum() const = delete;

		template <class T = Type, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
		[[nodiscard]]
		auto sumF() const;

		template <class T = Type, std::enable_if_t<not std::is_floating_point_v<T>>* = nullptr>
		[[nodiscard]]
		auto sumF() const = delete;

		[[nodiscard]]
		Array take(size_t n) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array take_while(Fty f) const;

		Array& stable_unique();

		[[nodiscard]]
		Array stable_uniqued() const;

		Array& sort_and_unique();

		[[nodiscard]]
		Array sorted_and_uniqued() const&;

		[[nodiscard]]
		Array sorted_and_uniqued()&&;

		Array& unique_consecutive();

		[[nodiscard]]
		Array uniqued_consecutive() const&;

		[[nodiscard]]
		Array uniqued_consecutive()&&;

		[[nodiscard]]
		Array values_at(std::initializer_list<size_t> indices) const;

	# ifndef SIV3D_NO_CONCURRENT_API

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		size_t parallel_count_if(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		void parallel_each(Fty f);

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		void parallel_each(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		auto parallel_map(Fty f) const;

	# endif

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

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		[[nodiscard]]
		static Array Generate(size_type size, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		[[nodiscard]]
		static Array IndexedGenerate(size_type size, Fty indexedGenerator);
	};

	template <class Type, class Allocator>
	[[nodiscard]]
	inline bool operator ==(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b);

	template <class Type, class Allocator>
	[[nodiscard]]
	inline bool operator !=(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b);

	template <class Type, class Allocator>
	[[nodiscard]]
	inline bool operator <(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b);

	template <class Type, class Allocator>
	[[nodiscard]]
	inline bool operator >(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b);

	template <class Type, class Allocator>
	[[nodiscard]]
	inline bool operator <=(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b);

	template <class Type, class Allocator>
	[[nodiscard]]
	inline bool operator >=(const Array<Type, Allocator>& a, const Array<Type, Allocator>& b);

	template <class Type, class Allocator>
	inline void swap(Array<Type, Allocator>& a, Array<Type, Allocator>& b) noexcept;

	// deduction guide
	template <class Type>
	Array(std::initializer_list<Type>)->Array<Type>;

	template <class ArrayIsh, std::enable_if_t<Meta::HasAsArray<ArrayIsh>::value>* = nullptr>
	Array(const ArrayIsh& a)->Array<typename decltype(std::declval<ArrayIsh>().asArray())::value_type>;

	template <class T0, class... Ts>
	[[nodiscard]]
	inline auto MakeArray(T0&& first, Ts&&... args);
}

# include "detail/Array.ipp"
# include "detail/BoolArray.ipp"
