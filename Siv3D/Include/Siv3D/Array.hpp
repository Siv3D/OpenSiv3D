//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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
# include "AlignedAllocator.hpp"
# include "Concept.hpp"
# include "NamedParameter.hpp"
# include "Threading.hpp"
# include "String.hpp"
# include "Functor.hpp"
# include "Format.hpp"
# include "DefaultRNG.hpp"

namespace s3d
{
	/// <summary>
	/// 動的配列
	/// </summary>
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

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Array()
			: base_type() {}

		/// <summary>
		/// ジェネレータを用いて配列を作成します。
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
		template <class Fty, class R = Type, std::enable_if_t<std::is_convertible<std::result_of_t<Fty()>, R>::value>* = nullptr>
		Array(const size_type size, Arg::generator_<Fty> generator)
			: Array(Generate<Fty>(size, *generator)) {}

		/// <summary>
		/// ジェネレータを用いて配列を作成します。
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
		template <class Fty, class R = Type, std::enable_if_t<std::is_convertible<std::result_of_t<Fty()>, R>::value>* = nullptr>
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
		/// 他の配列と要素を入れ替えます。
		/// </summary>
		/// <param name="other">
		/// 入れ替える配列
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Array& other)
		{
			base_type::swap(other);
		}

		/// <summary>
		/// 配列の要素数を返します。
		/// </summary>
		/// <returns>
		/// 配列の要素数
		/// </returns>
		size_t count() const noexcept
		{
			return size();
		}

		/// <summary>
		/// 配列の要素数が 0 であるかを返します。
		/// </summary>
		/// <returns>
		/// 配列の要素数が 0 である場合 true, それ以外の場合は false
		/// </returns>
		bool isEmpty() const noexcept
		{
			return empty();
		}

		/// <summary>
		/// 配列に要素が含まれているかを返します。
		/// </summary>
		/// <returns>
		/// 配列に要素が含まれている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const noexcept
		{
			return !empty();
		}

		/// <summary>
		/// 配列の要素を全て消去し、メモリも解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release()
		{
			clear();

			shrink_to_fit();
		}

		/// <summary>
		/// 配列の要素の合計サイズ（バイト）を返します。
		/// </summary>
		/// <returns>
		/// 配列の要素の合計サイズ（バイト）
		/// </returns>
		size_t size_bytes() const noexcept
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Array::size_bytes() Type must be trivially copyable.");

			return size() * sizeof(value_type);
		}

		/// <summary>
		/// 配列の先頭に要素を追加します。
		/// </summary>
		/// <param name="value">
		/// 追加する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_front(const Type& value)
		{
			insert(begin(), value);
		}

		/// <summary>
		/// 配列の先頭に要素を追加します。
		/// </summary>
		/// <param name="value">
		/// 追加する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_front(Type&& value)
		{
			insert(begin(), std::move(value));
		}

		/// <summary>
		/// 配列の先頭から要素を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pop_front()
		{
			erase(begin());
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
		const Type& operator[](size_t index) const &
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
		Type& operator[](size_t index) &
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
		Type operator[](size_t index) &&
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
		const Type& at(size_t index) const &
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
		Type& at(size_t index) &
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
		Type at(size_t index) &&
		{
			return std::move(base_type::at(index));
		}

		/// <summary>
		/// 配列の末尾に要素を追加します。
		/// </summary>
		/// <param name="value">
		/// 追加する値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Array& operator <<(const Type& value)
		{
			push_back(value);

			return *this;
		}

		/// <summary>
		/// 配列の末尾に要素を追加します。
		/// </summary>
		/// <param name="value">
		/// 追加する値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Array& operator <<(Type&& value)
		{
			push_back(std::forward<Type>(value));

			return *this;
		}

		/// <summary>
		/// 全ての要素が条件を満たすかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たさない要素が 1 つでもあれば false, それ以外の場合は true
		/// </returns>
		template <class Fty = decltype(Id)>
		bool all(Fty f = Id) const
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

		/// <summary>
		/// 少なくとも 1 つの要素が条件を満たすかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たす要素が 1 つでもあれば true, それ以外の場合は false
		/// </returns>
		template <class Fty = decltype(Id)>
		bool any(Fty f = Id) const
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

		/// <summary>
		/// 配列の末尾に別の配列を追加します。
		/// </summary>
		/// <param name="other_array">
		/// 追加する配列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Array& append(const Array& other_array)
		{
			insert(end(), other_array.begin(), other_array.end());

			return *this;
		}

		/// <summary>
		/// 配列の要素をランダムに 1 つ選択します。
		/// </summary>
		/// <returns>
		/// ランダムに選択された要素への参照
		/// </returns>
		Type& choice()
		{
			return choice(GetDefaultRNG());
		}

		/// <summary>
		/// 配列の要素をランダムに 1 つ選択します。
		/// </summary>
		/// <returns>
		/// ランダムに選択された要素への参照
		/// </returns>
		const Type& choice() const
		{
			return choice(GetDefaultRNG());
		}

		/// <summary>
		/// 配列の要素をランダムに 1 つ選択します。
		/// </summary>
		/// <param name="rbg">
		/// 選択に用いるランダムビット列生成エンジン
		/// </param>
		/// <returns>
		/// ランダムに選択された要素への参照
		/// </returns>
		template <class URBG, std::enable_if_t<!std::is_scalar<URBG>::value>* = nullptr>
		Type& choice(URBG&& rbg)
		{
			if (empty())
			{
				throw std::out_of_range("Array::choice() choice from empty Array");
			}

			const size_t index = std::uniform_int_distribution<size_t>(0, size() - 1)(rbg);

			return operator[](index);
		}

		/// <summary>
		/// 配列の要素をランダムに 1 つ選択します。
		/// </summary>
		/// <param name="rbg">
		/// 選択に用いるランダムビット列生成エンジン
		/// </param>
		/// <returns>
		/// ランダムに選択された要素への参照
		/// </returns>
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

		/// <summary>
		/// 指定した個数の要素を重複しないようランダムに選択します。
		/// </summary>
		/// <param name="n">
		/// 選択する要素の個数
		/// </param>
		/// <remarks>
		/// 要素の順序は保存されます。n が配列の要素数より少ない場合、全ての要素を返します。
		/// </remarks>
		/// <returns>
		/// ランダムに選択された要素
		/// </returns>
		template <class Size_t, std::enable_if_t<std::is_scalar<Size_t>::value>* = nullptr>
		Array choice(const Size_t n) const
		{
			return choice(n, GetDefaultRNG());
		}

		/// <summary>
		/// 指定した個数の要素を重複しないようランダムに選択します。
		/// </summary>
		/// <param name="n">
		/// 選択する要素の個数
		/// </param>
		/// <param name="rbg">
		/// 選択に用いるランダムビット列生成エンジン
		/// </param>
		/// <remarks>
		/// 要素の順序は保存されます。n が配列の要素数より少ない場合は、全ての要素を返します。
		/// </remarks>
		/// <returns>
		/// ランダムに選択された要素
		/// </returns>
		template <class URBG>
		Array choice(const size_t n, URBG&& rbg) const
		{
			Array result;		

			result.reserve(std::min(n, size()));

			Sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));
			
			return result;
		}

		/// <summary>
		/// 配列を指定された要素数づつに分割した、配列の配列を返します。
		/// </summary>
		/// <param name="group">
		/// 一つの分割された配列に含まれる要素数
		/// </param>
		/// <returns>
		/// 指定された要素数づつに分割された配列の配列
		/// </returns>
		Array<Array<Type, Allocator>, std::allocator<Array<Type, Allocator>>> chunk(const size_t n) const
		{
			Array<Array<Type, Allocator>, std::allocator<Array<Type, Allocator>>> result;

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

		/// <summary>
		/// 指定した値を持つ要素の個数を返します。
		/// </summary>
		/// <param name="value">
		/// 検索する値
		/// </param>
		/// <returns>
		/// 指定した値を持つ要素の個数
		/// </returns>
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

		/// <summary>
		/// 指定した条件を満たす要素の個数を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// 指定した条件を満たす要素の個数
		/// </returns>
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

		/// <summary>
		/// 指定した個数だけ先頭から要素を除いた新しい配列を作成します。
		/// </summary>
		/// <param name="n">
		/// 新しい配列に含めない先頭からの要素の個数
		/// </param>
		/// <remarks>
		/// n が配列の要素数より少ない場合、要素数が 0 の配列を返します。
		/// </remarks>
		/// <returns>
		/// 指定した個数だけ先頭から要素を除いた新しい配列
		/// </returns>
		Array drop(const size_t n) const
		{
			if (n >= size())
			{
				return Array();
			}

			return Array(begin() + n, end());
		}

		/// <summary>
		/// 指定した条件が真になる要素を先頭から除いた残りの要素で新しい配列を作成します。
		/// </summary>
		/// <param name="f">
		/// 先頭から取り除く要素の条件
		/// </param>
		/// <returns>
		/// 指定した条件が真になる要素を先頭から除いた新しい配列
		/// </returns>
		template <class Fty>
		Array drop_while(Fty f) const
		{
			return Array(std::find_if_not(begin(), end(), f), end());
		}
		
		/// <summary>
		/// 配列の各要素への参照を引数に、先頭の要素から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各要素への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		Array& each(Fty f)
		{
			for (auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		/// <summary>
		/// 配列の各要素への参照を引数に、先頭の要素から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各要素への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		const Array& each(Fty f) const
		{
			for (const auto& v : *this)
			{
				f(v);
			}

			return *this;
		}

		/// <summary>
		/// インデックスと、配列の各要素への参照を引数に、先頭の要素から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 第一引数にインデックス、第二引数に各要素への参照をとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// インデックスと、配列の各要素への参照を引数に、先頭の要素から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 第一引数にインデックス、第二引数に各要素への参照をとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 配列の指定したインデックスの要素を取得します。インデックスが範囲外の場合は defaultValue を返します。
		/// </summary>
		/// <param name="index">
		/// 要素のインデックス
		/// </param>
		/// <param name="defaultValue">
		/// インデックスが範囲外だった場合に返す値
		/// </param>
		/// <returns>
		/// 指定したインデックスの要素か、インデックスが範囲外の場合は defaultValue
		/// </returns>
		const Type& fetch(const size_t index, const Type& defaultValue) const
		{
			if (index >= size())
			{
				return defaultValue;
			}

			return operator[](index);
		}

		/// <summary>
		/// 配列のすべての要素に同じ値を代入します。
		/// </summary>
		/// <param name="value">
		/// すべての要素に代入する値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Array& fill(const Type& value)
		{
			std::fill(begin(), end(), value);

			return *this;
		}

		/// <summary>
		/// 条件を満たす要素のみからなる新しい配列を返します。
		/// </summary>
		/// <param name="f">
		/// 新しい配列に含む要素の条件
		/// </param>
		/// <returns>
		/// 条件を満たす要素のみからなる新しい配列
		/// </returns>
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

		/// <summary>
		/// 配列を指定された数に分割した、配列の配列を返します。
		/// </summary>
		/// <param name="n">
		/// 配列の分割数
		/// </param>
		/// <returns>
		/// 指定された分割数に分割した配列の配列
		/// </returns>
		Array<Array<Type, Allocator>, std::allocator<Array<Type, Allocator>>> in_groups(const size_t group) const
		{
			Array<Array<Type, Allocator>, std::allocator<Array<Type, Allocator>>> result;

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

		/// <summary>
		/// 指定した要素が配列に含まれているかを返します。
		/// </summary>
		/// <param name="value">
		/// 検索する要素
		/// </param>
		/// <returns>
		/// 指定した要素を含む場合は true, それ以外の場合は false
		/// </returns>
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

		/// <summary>
		/// 指定した条件を満たす要素が配列に含まれているかを返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// 指定した条件を満たす要素が含まれる場合は true, それ以外の場合は false
		/// </returns>
		template <class Fty>
		bool include_if(Fty f) const
		{
			return any(f);
		}

		/// <summary>
		/// 配列が昇順にソートされているかを返します。
		/// </summary>
		/// <returns>
		/// 配列が昇順にソートされている場合 true, それ以外の場合 false
		/// </returns>
		template <class T = Type, std::enable_if_t<Concept::HasLessThan<T>::value>* = nullptr>
		bool isSorted() const
		{
			const size_t size_ = size();

			if (size_ <= 1)
			{
				return true;
			}

			const Type* p = data();

			for (size_t i = 0; i < size_ - 1; ++i)
			{
				if (p[i] > p[i + 1])
				{
					return false;
				}
			}

			return true;
		}

		/// <summary>
		/// 配列の各要素を指定した文字列で連結し、その文字列を返します。
		/// </summary>
		/// <param name="sep">
		/// 連結する際に使う文字列
		/// </param>
		/// <param name="begin">
		/// 先頭に挿入する文字列
		/// </param>
		/// <param name="end">
		/// 末尾に挿入する文字列
		/// </param>
		/// <returns>
		/// 要素を指定した文字列で連結した結果の文字列
		/// </returns>
		String join(const String& sep = S3DSTR(","), const String& begin = S3DSTR("{"), const String& end = S3DSTR("}")) const
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

		/// <summary>
		/// 条件を満たさない要素を削除します
		/// </summary>
		/// <param name="f">
		/// 削除しない要素の条件
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Array& keep_if(std::function<bool(const Type&)> f)
		{
			erase(std::remove_if(begin(), end(), std::not1(f)), end());

			return *this;
		}

		/// <summary>
		/// 配列の各要素に関数を適用した戻り値からなる配列を返します
		/// </summary>
		/// <param name="f">
		/// 各要素に適用する関数
		/// </param>
		/// <returns>
		/// 配列の各要素に関数を適用した戻り値からなる配列
		/// </returns>
		template <class Fty>
		auto map(Fty f) const
			-> Array<decltype(f(std::declval<value_type>()))>
		{
			Array<decltype(f(std::declval<value_type>()))> new_array;

			new_array.reserve(size());

			for (const auto& v : *this)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		/// <summary>
		/// 全ての要素が条件を満たさないかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たす要素が 1 つでもあれば false, それ以外の場合は true
		/// </returns>
		template <class Fty = decltype(Id)>
		bool none(Fty f = Id) const
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

		/// <summary>
		/// 配列の要素を、初期値を用いて左畳み込みし、単一の値を得ます。
		/// </summary>
		/// <param name="f">
		/// 関数
		/// </param>
		/// <param name="init">
		/// 初期値
		/// </param>
		/// <returns>
		/// 最終的に得られた単一の値
		/// </returns>
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

		/// <summary>
		/// 配列の要素を左畳み込みし、単一の値を得ます。
		/// </summary>
		/// <param name="f">
		/// 関数
		/// </param>
		/// <returns>
		/// 最終的に得られた単一の値
		/// </returns>
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

		/// <summary>
		/// 指定した値を持つ要素を配列から削除します。
		/// </summary>
		/// <param name="value">
		/// 検索する値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Array& remove(const Type& value)
		{
			erase(std::remove(begin(), end(), value), end());

			return *this;
		}

		/// <summary>
		/// 指定した値を持つ要素を削除した新しい配列を返します。
		/// </summary>
		/// <param name="value">
		/// 検索する値
		/// </param>
		/// <returns>
		/// 指定した値を持つ要素を配列から削除した新しい配列
		/// </returns>
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

		/// <summary>
		/// 指定した値を持つ要素を削除した新しい配列を返します。
		/// </summary>
		/// <param name="value">
		/// 検索する値
		/// </param>
		/// <returns>
		/// 指定した値を持つ要素を配列から削除した新しい配列
		/// </returns>
		Array removed(const Type& value) &&
		{
			erase(std::remove(begin(), end(), value), end());

			shrink_to_fit();

			return std::move(*this);
		}

		/// <summary>
		/// 指定したインデックスの要素を配列から削除します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Array& remove_at(const size_t index)
		{
			if (index >= size())
			{
				throw std::out_of_range("Array::remove_at() index out of range");
			}

			erase(begin() + index);

			return *this;
		}

		/// <summary>
		/// 指定したインデックスの要素を削除した新しい配列を返します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// 指定したインデックスの要素を削除した新しい配列
		/// </returns>
		Array removed_at(const size_t index) const
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

		/// <summary>
		/// 指定した条件を満たす要素を削除します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		Array& remove_if(Fty f)
		{
			erase(std::remove_if(begin(), end(), f), end());

			return *this;
		}

		/// <summary>
		/// 指定した条件を満たす要素を削除した新しい配列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// 指定した条件を満たす要素を削除した新しい配列
		/// </returns>
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

		/// <summary>
		/// 指定した条件を満たす要素を削除した新しい配列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// 指定した条件を満たす要素を削除した新しい配列
		/// </returns>
		template <class Fty>
		Array removed_if(Fty f) &&
		{
			erase(std::remove_if(begin(), end(), f), end());

			shrink_to_fit();

			return std::move(*this);
		}

		/// <summary>
		/// 指定した値を持つ要素を別の値に置き換えます。
		/// </summary>
		/// <param name="oldValue">
		/// 置換前の値
		/// </param>
		/// <param name="newValue">
		/// 置換後の値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 指定した値を持つ要素を別の値に置き換えた新しい配列を返します。
		/// </summary>
		/// <param name="oldValue">
		/// 置換前の値
		/// </param>
		/// <param name="newValue">
		/// 置換後の値
		/// </param>
		/// <returns>
		/// 指定した値を持つ要素を別の値に置き換えた新しい配列
		/// </returns>
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

		/// <summary>
		/// 指定した値を持つ要素を別の値に置き換えた新しい配列を返します。
		/// </summary>
		/// <param name="oldValue">
		/// 置換前の値
		/// </param>
		/// <param name="newValue">
		/// 置換後の値
		/// </param>
		/// <returns>
		/// 指定した値を持つ要素を別の値に置き換えた新しい配列
		/// </returns>
		Array replaced(const Type& oldValue, const Type& newValue) &&
		{
			replace(oldValue, newValue);

			return std::move(*this);
		}

		/// <summary>
		/// 指定した条件を満たす要素を別の値に置き換えます。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <param name="newValue">
		/// 置換後の値
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 指定した条件を満たす要素を別の値に置き換えた新しい配列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <param name="newValue">
		/// 置換後の値
		/// </param>
		/// <returns>
		/// 指定した条件を満たす要素を別の値に置き換えた新しい配列
		/// </returns>
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

		/// <summary>
		/// 指定した条件を満たす要素を別の値に置き換えた新しい配列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <param name="newValue">
		/// 置換後の値
		/// </param>
		/// <returns>
		/// 指定した条件を満たす要素を別の値に置き換えた新しい配列
		/// </returns>
		template <class Fty>
		Array replaced_if(Fty f, const Type& newValue) &&
		{
			replace_if(f, newValue);

			return std::move(*this);
		}

		/// <summary>
		/// 配列の要素の順番を反転させます。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Array& reverse()
		{
			std::reverse(begin(), end());

			return *this;
		}

		/// <summary>
		/// 要素の順番を反転させた新しい配列を返します。
		/// </summary>
		/// <returns>
		/// 要素の順番を反転させた新しい配列
		/// </returns>
		Array reversed() const &
		{
			return Array(rbegin(), rend());
		}

		/// <summary>
		/// 要素の順番を反転させた新しい配列を返します。
		/// </summary>
		/// <returns>
		/// 要素の順番を反転させた新しい配列
		/// </returns>
		Array reversed() &&
		{
			reverse();

			return std::move(*this);
		}

		/// <summary>
		/// 配列の各要素への参照を引数に、末尾の要素から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各要素への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		Array& reverse_each(Fty f)
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		/// <summary>
		/// 配列の各要素への参照を引数に、末尾の要素から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各要素への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		const Array& reverse_each(Fty f) const
		{
			for (auto it = rbegin(); it != rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		/// <summary>
		/// 配列の各要素の位置をシフトさせ、はみ出た要素は反対側に挿入します。
		/// </summary>
		/// <param name="count">
		/// 要素をシフトする数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 配列の各要素の位置をシフトさせ、はみ出た要素を反対側に挿入した新しい配列を返します。
		/// </summary>
		/// <param name="count">
		/// 要素をシフトする数
		/// </param>
		/// <returns>
		/// 新しい配列
		/// </returns>
		Array rotated(const std::ptrdiff_t count = 1) const &
		{
			return Array(*this).rotate(count);
		}

		/// <summary>
		/// 配列の各要素の位置をシフトさせ、はみ出た要素を反対側に挿入した新しい配列を返します。
		/// </summary>
		/// <param name="count">
		/// 要素をシフトする数
		/// </param>
		/// <returns>
		/// 新しい配列
		/// </returns>
		Array rotated(const std::ptrdiff_t count = 1) &&
		{
			rotate(count);

			return std::move(*this);
		}

		/// <summary>
		/// 配列をランダムに並び替えます。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Array& shuffle()
		{
			return shuffle(GetDefaultRNG());
		}

		/// <summary>
		/// 指定された乱数生成器を使って配列をランダムに並び替えます。
		/// </summary>
		/// <param name="rbg">
		/// 使用する乱数生成器
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class URBG>
		Array& shuffle(URBG&& rbg)
		{
			std::shuffle(begin(), end(), std::forward<URBG>(rbg));

			return *this;
		}

		/// <summary>
		/// ランダムに並び替えた新しい配列を返します。
		/// </summary>
		/// <returns>
		/// ランダムに並び替えられた配列
		/// </returns>
		Array shuffled() const &
		{
			return shuffled(GetDefaultRNG());
		}

		/// <summary>
		/// ランダムに並び替えた新しい配列を返します。
		/// </summary>
		/// <returns>
		/// ランダムに並び替えられた配列
		/// </returns>
		Array shuffled() &&
		{
			return shuffled(GetDefaultRNG());
		}

		/// <summary>
		/// 指定された乱数生成器を使ってランダムに並び替えた新しい配列を返します。
		/// </summary>
		/// <param name="rbg">
		/// 使用する乱数生成器
		/// </param>
		/// <returns>
		/// ランダムに並び替えられた配列
		/// </returns>
		template <class URBG>
		Array shuffled(URBG&& rbg) const &
		{
			return Array(*this).shuffle(std::forward<URBG>(rbg));
		}

		/// <summary>
		/// 指定された乱数生成器を使ってランダムに並び替えた新しい配列を返します。
		/// </summary>
		/// <param name="rbg">
		/// 使用する乱数生成器
		/// </param>
		/// <returns>
		/// ランダムに並び替えられた配列
		/// </returns>
		template <class URBG>
		Array shuffled(URBG&& rbg) &&
		{
			shuffle(std::forward<URBG>(rbg));

			return std::move(*this);
		}

		/// <summary>
		/// 指定されたインデックスから配列の末尾までをコピーした新しい配列を返します。
		/// </summary>
		/// <param name="index">
		/// 新しい配列の先頭要素になる要素のインデックス
		/// </param>
		/// <returns>
		/// 新しい配列
		/// </returns>
		Array slice(const size_t index) const
		{
			if (index >= size())
			{
				return Array();
			}

			return Array(begin() + index, end());
		}

		/// <summary>
		/// 指定されたインデックスから指定された要素数をコピーした新しい配列を返します。
		/// </summary>
		/// <param name="index">
		/// 新しい配列の先頭要素になる要素のインデックス
		/// </param>
		/// <param name="length">
		/// 新しい配列の要素数
		/// </param>
		/// <returns>
		/// 新しい配列
		/// </returns>
		Array slice(const size_t index, const size_t length) const
		{
			if (index >= size())
			{
				return Array();
			}

			return Array(begin() + index, begin() + std::min(index + length, size()));
		}

		/// <summary>
		/// 配列を &lt; 比較でソートします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		template <class T = Type, std::enable_if_t<Concept::HasLessThan<T>::value>* = nullptr>
		Array& sort()
		{
			std::sort(begin(), end());

			return *this;
		}

		/// <summary>
		/// 配列を指定された比較関数でソートします。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		Array& sort_by(Fty f)
		{
			std::sort(begin(), end(), f);

			return *this;
		}

		/// <summary>
		/// 配列を &lt; 比較でソートした新しい配列を返します。
		/// </summary>
		/// <returns>
		/// ソート済みの配列
		/// </returns>
		template <class T = Type, std::enable_if_t<Concept::HasLessThan<T>::value>* = nullptr>
		Array sorted() const &
		{
			return Array(*this).sort();
		}

		/// <summary>
		/// 配列を &lt; 比較でソートした新しい配列を返します。
		/// </summary>
		/// <returns>
		/// ソート済みの配列
		/// </returns>
		template <class T = Type, std::enable_if_t<Concept::HasLessThan<T>::value>* = nullptr>
		Array sorted() &&
		{
			sort();

			return std::move(*this);
		}

		/// <summary>
		/// 配列を指定された比較関数でソートした新しい配列を返します。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// ソート済みの配列
		/// </returns>
		template <class Fty>
		Array sorted_by(Fty f) const &
		{
			return Array(*this).sort_by(f);
		}

		/// <summary>
		/// 配列を指定された比較関数でソートした新しい配列を返します。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// ソート済みの配列
		/// </returns>
		template <class Fty>
		Array sorted_by(Fty f) &&
		{
			sort_by(f);

			return std::move(*this);
		}

		/// <summary>
		/// 配列の全要素の合計を返します。
		/// </summary>
		/// <returns>
		/// 配列の全要素の合計
		/// </returns>
		template <class T = Type, std::enable_if_t<Concept::HasPlus<T>::value && Concept::HasPlusAssign<T>::value>* = nullptr>
		auto sum() const
		{
			decltype(std::declval<T>() + std::declval<T>()) result{};

			for (const auto& v : *this)
			{
				result += v;
			}

			return result;
		}

		/// <summary>
		/// 配列の全要素の合計を返します。
		/// </summary>
		/// <returns>
		/// 配列の全要素の合計
		/// </returns>
		template <class T = Type, std::enable_if_t<Concept::HasPlus<T>::value && !Concept::HasPlusAssign<T>::value>* = nullptr>
		auto sum() const
		{
			decltype(std::declval<T>() + std::declval<T>()) result{};

			for (const auto& v : *this)
			{
				result = result + v;
			}

			return result;
		}

		// do nothing
		template <class T = Type, std::enable_if_t<!Concept::HasPlus<T>::value>* = nullptr>
		const Array& sum() const
		{
			return *this;
		}

		/// <summary>
		/// 精度の高い配列の全要素の合計を返します。
		/// </summary>
		/// <returns>
		/// 高精度な配列の全要素の合計
		/// </returns>
		template <class T = Type, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
		auto sumF() const &
		{
			T s = 0.0;
			T err = 0.0;

			for (const auto& v : *this)
			{
				const T y = v - err;
				const T t = s + y;
				err = (t - s) - y;
				s = t;
			}

			return static_cast<T>(s);
		}

		/// <summary>
		/// 配列の先頭から指定された要素数分取り出した新しい配列を返します。
		/// </summary>
		/// <param name="n">
		/// 取り出す要素数
		/// </param>
		/// <returns>
		/// 新しい配列
		/// </returns>
		Array take(const size_t n) const
		{
			return Array(begin(), begin() + std::min(n, size()));
		}

		/// <summary>
		/// 配列の先頭から、指定された条件を満たす連続した要素を取り出した新しい配列を返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 新しい配列
		/// </returns>
		template <class Fty>
		Array take_while(Fty f) const
		{
			return Array(begin(), std::find_if_not(begin(), end(), f));
		}

		/// <summary>
		/// 配列をソートし、重複する要素を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Array& unique()
		{
			sort();

			erase(std::unique(begin(), end()), end());

			return *this;
		}

		/// <summary>
		/// 配列をソートし、重複する要素を削除した新しい配列を返します。
		/// </summary>
		/// <returns>
		/// 新しい配列
		/// </returns>
		Array uniqued() const &
		{
			return Array(*this).unique();
		}

		/// <summary>
		/// 配列をソートし、重複する要素を削除した新しい配列を返します。
		/// </summary>
		/// <returns>
		/// 新しい配列
		/// </returns>
		Array uniqued() &&
		{
			sort();

			erase(std::unique(begin(), end()), end());

			shrink_to_fit();

			return std::move(*this);
		}

		/// <summary>
		/// 複数のインデックスを取り、それらの要素からなる新しい配列を返します。
		/// </summary>
		/// <param name="indices">
		/// 現在の配列における複数のインデックス
		/// </param>
		/// <example><code>
		/// Array &lt; int &gt; ({1, 2, 3, 4, 5}).values_at({0, 3, 4}); // => {1, 4, 5}
		/// </code></example>
		/// <returns>
		/// 新しい配列
		/// </returns>
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

		/// <summary>
		/// 条件に合う要素の個数を並列化して数えます。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <param name="numThreads">
		/// 使用するスレッド数の最大数
		/// </param>
		/// <returns>
		/// 見つかった要素の個数
		/// </returns>
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

		/// <summary>
		/// 配列の各要素への参照を引数に、並列化して関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各要素への参照を引数にとる関数
		/// </param>
		/// <param name="numThreads">
		/// 使用するスレッド数の最大数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 配列の各要素への参照を引数に、並列化して関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各要素への参照を引数にとる関数
		/// </param>
		/// <param name="numThreads">
		/// 使用するスレッド数の最大数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 配列の各要素に関数を並列化して適用し、その戻り値からなる配列を返します。
		/// </summary>
		/// <param name="f">
		/// 各要素に適用する関数
		/// </param>
		/// <param name="numThreads">
		/// 使用するスレッド数の最大数
		/// </param>
		/// <returns>
		/// 配列の各要素に関数を適用した戻り値からなる配列
		/// </returns>
		template <class Fty>
		auto parallel_map(Fty f, size_t numThreads = Threading::GetConcurrency()) const
			-> Array<decltype(f(std::declval<value_type>()))>
		{
			Array<decltype(f(std::declval<value_type>()))> new_array;

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
}

namespace std
{
	template <class Type, class Allocator>
	inline void swap(s3d::Array<Type, Allocator>& a, s3d::Array<Type, Allocator>& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
}

# include "ArrayBool.hpp"

//////////////////////////////////////////////////////////////////////////////
//
//	Formatting Array
//
//	[x] Siv3D Formatter
//	[x] ostream
//	[x] wostream
//	[ ] istream
//	[ ] wistream
//	[p] fmtlib BasicFormatter<wchar>
//
namespace s3d
{
	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline void Formatter(FormatData& formatData, const Array<Type, Allocator>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline std::ostream & operator <<(std::ostream& os, const Array<Type, Allocator>& v)
	{
		return os << Format(v).narrow();
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline std::wostream & operator <<(std::wostream& os, const Array<Type, Allocator>& v)
	{
		return os << Format(v);
	}
}
//
//////////////////////////////////////////////////////////////////////////////
