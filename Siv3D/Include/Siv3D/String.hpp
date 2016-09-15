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
# include <string>
# include <iostream>
# include <algorithm>
# include "Fwd.hpp"
# include "Char.hpp"
# include "Functor.hpp"
# include "Random.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr bool IsTrimmable(const uint32 ch)
		{
			return (ch <= 0x20u) || ((ch - 0x7Fu) <= (0x9Fu - 0x7Fu));
		};
	}

	class String
	{
	private:

		std::wstring m_string;

	public:

		using string_type				= std::wstring;
		using traits_type				= typename string_type::traits_type;
		using allocator_type			= typename string_type::allocator_type;
		using value_type				= typename string_type::value_type;
		using size_type					= typename string_type::size_type;
		using difference_type			= typename string_type::difference_type;
		using pointer					= typename string_type::pointer;
		using const_pointer				= typename string_type::const_pointer;
		using reference					= typename string_type::reference;
		using const_reference			= typename string_type::const_reference;
		using iterator					= typename string_type::iterator;
		using const_iterator			= typename string_type::const_iterator;
		using reverse_iterator			= typename string_type::reverse_iterator;
		using const_reverse_iterator	= typename string_type::const_reverse_iterator;

		/// <summary>
		/// 特別な値。用途によって意味が異なります。
		/// </summary>
		const static size_type npos = size_type(-1);

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		String() = default;

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="str">
		/// コピーする文字列
		/// </param>
		String(const String& str)
			: m_string(str.m_string) {}

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="str">
		/// コピーする文字列
		/// </param>
		String(const string_type& str)
			: m_string(str) {}

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="str">
		/// コピーする文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		String(const wchar* str)
			: m_string(str) {}

		/// <summary>
		/// 文字列を指定した文字数だけコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="str">
		/// コピーする文字列の先頭ポインタ
		/// </param>
		/// <param name="length">
		/// コピーする文字数
		/// </param>
		String(const wchar* str, size_type length)
			: m_string(str, length) {}

		/// <summary>
		/// 初期化リストから新しい文字列を作成します。
		/// </summary>
		/// <param name="ilist">
		/// 新しい文字列の初期化リスト
		/// </param>
		String(std::initializer_list<value_type> ilist)
			: m_string(ilist) {}

		/// <summary>
		/// 文字を指定した数だけコピーした文字列を作成します。
		/// </summary>
		/// <param name="count">
		/// コピーする個数
		/// </param>
		/// <param name="ch">
		/// コピーする文字
		/// </param>
		String(size_t count, wchar ch)
			: m_string(count, ch) {}

		/// <summary>
		/// 指定した範囲の文字列をコピーした文字列を作成します。
		/// </summary>
		/// <param name="first">
		/// コピーする文字列の開始位置
		/// </param>
		/// <param name="last">
		/// コピーする文字列の終了位置
		/// </param>
		template <class Iterator>
		String(Iterator first, Iterator last)
			: m_string(first, last) {}

		/// <summary>
		/// 文字列を別の文字列からムーブして初期化します。
		/// </summary>
		/// <param name="str">
		/// 初期化に使う文字列
		/// </param>
		String(String&& str) noexcept
			: m_string(std::move(str.m_string)) {}

		/// <summary>
		/// 文字列を別の文字列からムーブして初期化します。
		/// </summary>
		/// <param name="str">
		/// 初期化に使う文字列
		/// </param>
		String(string_type&& str) noexcept
			: m_string(std::move(str)) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~String() = default;

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator = (const String& str) { return assign(str); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator = (const string_type& str) { return assign(str); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator = (String&& str) noexcept { return assign(std::move(str)); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator = (string_type&& str) noexcept { return assign(std::move(str)); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& operator = (const wchar* str) { return assign(str); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="ch">
		/// 新しい文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator = (wchar ch) { return assign(1, ch); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="ilist">
		/// 新しい文字列の初期化リスト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator = (std::initializer_list<value_type> ilist) { return assign(ilist); }

		String& operator <<(const wchar ch)
		{
			push_back(ch);

			return *this;
		}

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& assign(const String& str)
		{
			m_string.assign(str.m_string);

			return *this;
		}

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& assign(const string_type& str)
		{
			m_string.assign(str);

			return *this;
		}

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& assign(const wchar* str)
		{
			m_string.assign(str);

			return *this;
		}

		/// <summary>
		/// 文字を指定した数だけコピーした新しい文字列を代入します。
		/// </summary>
		/// <param name="count">
		/// 文字をコピーする個数
		/// </param>
		/// <param name="ch">
		/// コピーする文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& assign(size_t count, wchar ch)
		{
			m_string.assign(count, ch);

			return *this;
		}

		/// <summary>
		/// 新しい文字列をムーブ代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& assign(String&& str) noexcept
		{
			m_string.assign(std::move(str.m_string));

			return *this;
		}

		/// <summary>
		/// 新しい文字列をムーブ代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& assign(string_type&& str) noexcept
		{
			m_string.assign(std::move(str));

			return *this;
		}

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="ilist">
		/// 新しい文字列の初期化リスト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& assign(std::initializer_list<value_type> ilist)
		{
			m_string.assign(ilist);

			return *this;
		}

		/// <summary>
		/// 指定した範囲の文字列を代入します。
		/// </summary>
		/// <param name="first">
		/// 範囲の開始位置
		/// </param>
		/// <param name="last">
		/// 範囲の終了位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Iterator>
		String& assign(Iterator first, Iterator last)
		{
			m_string.assign(first, last);

			return *this;
		}

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="str">
		/// 追加する文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator += (const String& str) { return append(str); }

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="str">
		/// 追加する文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator += (const string_type& str) { return append(str); }

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="str">
		/// 追加する文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& operator += (const wchar* str) { return append(str); }

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="ilist">
		/// 追加する文字列の初期化リスト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator += (std::initializer_list<value_type> ilist) { return append(ilist); }

		/// <summary>
		/// 文字を終端に追加します。
		/// </summary>
		/// <param name="ch">
		/// 追加する文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator += (wchar ch) { return append(1, ch); }

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="str">
		/// 追加する文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& append(const String& str)
		{
			m_string.append(str.m_string);

			return *this;
		}

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="str">
		/// 追加する文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& append(const string_type& str)
		{
			m_string.append(str);

			return *this;
		}

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="str">
		/// 追加する文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& append(const wchar* str)
		{
			m_string.append(str);

			return *this;
		}

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="str">
		/// 追加する文字列の先頭ポインタ
		/// </param>
		/// <param name="count">
		/// コピーする文字数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& append(const wchar* str, size_t count)
		{
			m_string.append(str, count);

			return *this;
		}

		/// <summary>
		/// 文字列を終端に追加します。
		/// </summary>
		/// <param name="ilist">
		/// 追加する文字列の初期化リスト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& append(std::initializer_list<value_type> ilist)
		{
			m_string.append(ilist);

			return *this;
		}

		/// <summary>
		/// 文字を指定した個数だけ終端に追加します。
		/// </summary>
		/// <param name="count">
		/// 文字の個数
		/// </param>
		/// <param name="ch">
		/// 追加する文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& append(size_t count, wchar ch)
		{
			m_string.append(count, ch);

			return *this;
		}

		/// <summary>
		/// 指定した範囲の文字列を終端に追加します。
		/// </summary>
		/// <param name="first">
		/// 範囲の開始位置
		/// </param>
		/// <param name="last">
		/// 範囲の終了位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Iterator>
		String& append(Iterator first, Iterator last)
		{
			m_string.append(first, last);

			return *this;
		}

		/// <summary>
		/// 指定した位置に文字列を挿入します。
		/// </summary>
		/// <param name="offset">
		/// 挿入する位置
		/// </param>
		/// <param name="str">
		/// 挿入する文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& insert(size_t offset, const String& str)
		{
			m_string.insert(offset, str.m_string);

			return *this;
		}

		/// <summary>
		/// 指定した位置に文字列を挿入します。
		/// </summary>
		/// <param name="offset">
		/// 挿入する位置
		/// </param>
		/// <param name="ilist">
		/// 挿入する文字列の初期化リスト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& insert(size_t offset, std::initializer_list<value_type> ilist)
		{
			m_string.insert(offset, ilist);

			return *this;
		}

		/// <summary>
		/// 指定した位置に文字列を挿入します。
		/// </summary>
		/// <param name="offset">
		/// 挿入する位置
		/// </param>
		/// <param name="str">
		/// 挿入する文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& insert(size_t offset, const wchar* str)
		{
			m_string.insert(offset, str);

			return *this;
		}

		/// <summary>
		/// 指定した位置に文字を指定した個数だけ挿入します。
		/// </summary>
		/// <param name="offset">
		/// 挿入する位置
		/// </param>
		/// <param name="count">
		/// 文字の個数
		/// </param>
		/// <param name="ch">
		/// 挿入する文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& insert(size_t offset, size_t count, wchar ch)
		{
			m_string.insert(offset, count, ch);

			return *this;
		}

		/// <summary>
		/// 指定した位置に文字を挿入します。
		/// </summary>
		/// <param name="where">
		/// 挿入する位置
		/// </param>
		/// <param name="ch">
		/// 挿入する文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		iterator insert(const_iterator where, wchar ch)
		{
			return m_string.insert(where, ch);
		}

		/// <summary>
		/// 指定した位置に文字を指定した個数挿入します。
		/// </summary>
		/// <param name="where">
		/// 挿入する位置
		/// </param>
		/// <param name="count">
		/// 文字の個数
		/// </param>
		/// <param name="ch">
		/// 挿入する文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		void insert(const_iterator where, size_t count, wchar ch)
		{
			m_string.insert(where, count, ch);
		}

		/// <summary>
		/// 指定した位置に指定した範囲の文字列を挿入します。
		/// </summary>
		/// <param name="where">
		/// 挿入する位置
		/// </param>
		/// <param name="first">
		/// 範囲の開始位置
		/// </param>
		/// <param name="last">
		/// 範囲の終了位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Iterator>
		void insert(const_iterator where, Iterator first, Iterator last)
		{
			m_string.insert(where, first, last);
		}

		/// <summary>
		/// 指定した範囲を削除し、新しい文字列を挿入します。
		/// </summary>
		/// <param name="first1">
		/// 削除する範囲の開始位置
		/// </param>
		/// <param name="last1">
		/// 削除する範囲の終了位置
		/// </param>
		/// <param name="first2">
		/// 挿入する範囲の開始位置
		/// </param>
		/// <param name="last2">
		/// 挿入する範囲の終了位置
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Iterator>
		String& insert(const_iterator first1, const_iterator last1, Iterator first2, Iterator last2)
		{
			m_string.insert(first1, last1, first2, last2);

			return *this;
		}

		/// <summary>
		/// 指定した位置から指定した個数の文字を削除します。
		/// </summary>
		/// <param name="offset">
		/// 削除開始する位置
		/// </param>
		/// <param name="count">
		/// 削除する文字数。 npos の場合は終端まですべて
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& erase(size_t offset = 0, size_t count = npos)
		{
			m_string.erase(offset, count);

			return *this;
		}

		/// <summary>
		/// 指定した位置の文字を削除します。
		/// </summary>
		/// <param name="where">
		/// 削除する位置
		/// </param>
		/// <returns>
		/// 削除した直後の位置へのイテレータ
		/// </returns>
		iterator erase(const_iterator where)
		{
			return m_string.erase(where);
		}

		/// <summary>
		/// 指定した範囲の文字列を削除します。
		/// </summary>
		/// <param name="first">
		/// 削除する範囲の開始位置
		/// </param>
		/// <param name="last">
		/// 削除する範囲の終了位置
		/// </param>
		/// <returns>
		/// 削除した直後の位置へのイテレータ
		/// </returns>
		iterator erase(const_iterator first, const_iterator last)
		{
			return m_string.erase(first, last);
		}

		/// <summary>
		/// 文字列を消去し、空の文字列にします。
		/// </summary>
		/// <remarks>
		/// メモリを解放したい場合は shrink_to_fit() を呼びます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void clear() noexcept { m_string.clear(); }

		/// <summary>
		/// 文字列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭位置のイテレータ
		/// </returns>
		iterator begin() noexcept { return m_string.begin(); }

		/// <summary>
		/// 文字列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭位置のイテレータ
		/// </returns>
		const_iterator begin() const noexcept { return m_string.begin(); }

		/// <summary>
		/// 文字列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭位置のイテレータ
		/// </returns>
		const_iterator cbegin() const noexcept { return m_string.cbegin(); }

		/// <summary>
		/// 文字列の終了位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の終了位置のイテレータ
		/// </returns>
		iterator end() noexcept { return m_string.end(); }

		/// <summary>
		/// 文字列の終了位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の終了位置のイテレータ
		/// </returns>
		const_iterator end() const noexcept { return m_string.end(); }

		/// <summary>
		/// 文字列の終了位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の終了位置のイテレータ
		/// </returns>
		const_iterator cend() const noexcept { return m_string.cend(); }

		/// <summary>
		/// 文字列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の末尾のリバースイテレータ
		/// </returns>
		reverse_iterator rbegin() noexcept { return m_string.rbegin(); }

		/// <summary>
		/// 文字列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の末尾のリバースイテレータ
		/// </returns>
		const_reverse_iterator rbegin() const noexcept { return m_string.rbegin(); }

		/// <summary>
		/// 文字列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の末尾のリバースイテレータ
		/// </returns>
		const_reverse_iterator crbegin() const noexcept { return m_string.crbegin(); }

		/// <summary>
		/// 文字列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭の前へのリバースイテレータ
		/// </returns>
		reverse_iterator rend() noexcept { return m_string.rend(); }

		/// <summary>
		/// 文字列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator rend() const noexcept { return m_string.rend(); }

		/// <summary>
		/// 文字列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator crend() const noexcept { return m_string.crend(); }

		/// <summary>
		/// 文字列の不要なメモリを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void shrink_to_fit() { m_string.shrink_to_fit(); }

		/// <summary>
		/// 文字列を消去し、メモリを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release() { clear(); shrink_to_fit(); }

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		wchar& at(size_t offset) { return m_string.at(offset); }

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		const wchar& at(size_t offset) const { return m_string.at(offset); }

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		wchar& operator[](size_t offset) { return m_string[offset]; }

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		const wchar& operator[](size_t offset) const { return m_string[offset]; }

		/// <summary>
		/// 末尾に文字を追加します。
		/// </summary>
		/// <param name="ch">
		/// 追加する文字
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_back(wchar ch) { m_string.push_back(ch); }

		/// <summary>
		/// 末尾の文字を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pop_back() { m_string.pop_back(); }

		/// <summary>
		/// 先頭の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 先頭の文字への参照
		/// </returns>
		wchar& front() { return m_string.front(); }

		/// <summary>
		/// 先頭の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 先頭の文字への参照
		/// </returns>
		const wchar& front() const { return m_string.front(); }

		/// <summary>
		/// 末尾の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 末尾の文字への参照
		/// </returns>
		wchar& back() { return m_string.back(); }

		/// <summary>
		/// 末尾の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 末尾の文字への参照
		/// </returns>
		const wchar& back() const { return m_string.back(); }

		/// <summary>
		/// C スタイル文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// C スタイル文字列の先頭のポインタ
		/// </returns>
		const wchar* c_str() const noexcept { return m_string.c_str(); }

		/// <summary>
		/// 文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭へのポインタ
		/// </returns>
		const wchar* data() const noexcept { return m_string.data(); }

		/// <summary>
		/// wstring 型の内部データの参照を返します。
		/// </summary>
		/// <returns>
		/// wstring 型の内部データの参照
		/// </returns>
		string_type& str() { return m_string; }

		/// <summary>
		/// wstring 型の内部データの参照を返します。
		/// </summary>
		/// <returns>
		/// wstring 型の内部データの参照
		/// </returns>
		const string_type& str() const noexcept { return m_string; }

		/// <summary>
		/// 文字列の長さを示します。
		/// </summary>
		/// <remarks>
		/// 終端の L'\0' を含みません。
		/// </remarks>
		size_t length() const noexcept { return m_string.length(); }

		/// <summary>
		/// 文字列の長さを示します。
		/// </summary>
		/// <remarks>
		/// 終端の L'\0' を含みません。
		/// </remarks>
		size_t size() const noexcept { return m_string.size(); }

		size_t size_bytes() const noexcept { return m_string.size() * sizeof(value_type); }

		/// <summary>
		/// 空の文字列であるかを示します。
		/// </summary>
		bool empty() const noexcept { return m_string.empty(); }

		/// <summary>
		/// 空の文字列であるかを示します。
		/// </summary>
		bool isEmpty() const noexcept { return m_string.empty(); }

		/// <summary>
		/// メモリ上に確保可能な最大の文字列の長さを示します。
		/// </summary>
		size_t maxSize() const noexcept { return m_string.max_size(); }

		/// <summary>
		/// メモリを再確保せずに持てる文字列の長さを示します。
		/// </summary>
		size_t capacity() const noexcept { return m_string.capacity(); }

		/// <summary>
		/// 文字列のサイズを変更します。
		/// </summary>
		/// <param name="newSize">
		/// 新しいサイズ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_t newSize) { m_string.resize(newSize); }

		/// <summary>
		/// 文字列のサイズを変更します。
		/// </summary>
		/// <param name="newSize">
		/// 新しいサイズ
		/// </param>
		/// <param name="ch">
		/// 追加した領域を埋める文字
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_t newSize, wchar ch) { m_string.resize(newSize, ch); }

		/// <summary>
		/// 文字列用のメモリを指定したサイズで確保します。
		/// </summary>
		/// <param name="newCapacity">
		/// 確保する文字列のサイズ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reserve(size_t newCapacity) { m_string.reserve(newCapacity); }

		/// <summary>
		/// 文字列を別の文字列と交換します。
		/// </summary>
		/// <param name="str">
		/// 交換する文字列
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(String& str) noexcept { m_string.swap(str.m_string); }

		/// <summary>
		/// 指定した範囲の文字列を返します。
		/// </summary>
		/// <param name="offset">
		/// 範囲の開始位置
		/// </param>
		/// <param name="count">
		/// 範囲の長さ。npos の場合は文字列の終端まで
		/// </param>
		/// <returns>
		/// 指定した範囲の文字列
		/// </returns>
		String substr(size_t offset = 0, size_t count = npos) const
		{
			return m_string.substr(offset, count);
		}

		/// <summary>
		/// 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t indexOf(const String& str, size_t offset = 0) const noexcept
		{
			return m_string.find(str.data(), offset, str.length());
		}

		/// <summary>
		/// 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t indexOf(const wchar* str, size_t offset = 0) const
		{
			return m_string.find(str, offset, traits_type::length(str));
		}

		/// <summary>
		/// 文字を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t indexOf(wchar ch, size_t offset = 0) const
		{
			return m_string.find(ch, offset);
		}

		/// <summary>
		/// 文字を指定した位置から検索し、最初にそれとは異なる文字が現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t indexOfNot(wchar ch, size_t offset = 0) const
		{
			return m_string.find_first_not_of(ch, offset);
		}

		/// <summary>
		/// 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t lastIndexOf(const String& str, size_t offset = npos) const
		{
			return m_string.rfind(str.data(), offset, str.length());
		}

		/// <summary>
		/// 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t lastIndexOf(const wchar* str, size_t offset = npos) const
		{
			return m_string.rfind(str, offset, traits_type::length(str));
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t lastIndexOf(wchar ch, size_t offset = npos) const
		{
			return m_string.rfind(ch, offset);
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、最初にそれとは異なる文字が現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t lastIndexNotOf(wchar ch, size_t offset = npos) const
		{
			return m_string.find_last_not_of(ch, offset);
		}

		/// <summary>
		/// 検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t indexOfAny(const String& anyof, size_t offset = 0) const
		{
			return m_string.find_first_of(anyof.data(), offset, anyof.length());
		}

		/// <summary>
		/// 検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t indexOfAny(const wchar* anyof, size_t offset = 0) const
		{
			return m_string.find_first_of(anyof, offset, traits_type::length(anyof));
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t lastIndexOfAny(const String& anyof, size_t offset = npos) const
		{
			return m_string.find_last_of(anyof.data(), offset, anyof.length());
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t lastIndexOfAny(const wchar* anyof, size_t offset = npos) const
		{
			return m_string.find_last_of(anyof, offset, traits_type::length(anyof));
		}

		/// <summary>
		/// 検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t indexNotOfAny(const String& anyof, size_t offset = 0) const
		{
			return m_string.find_first_not_of(anyof.data(), offset, anyof.length());
		}

		/// <summary>
		/// 検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t indexNotOfAny(const wchar* anyof, size_t offset = 0) const
		{
			return m_string.find_first_not_of(anyof, offset, traits_type::length(anyof));
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t lastIndexNotOfAny(const String& anyof, size_t offset = npos) const
		{
			return m_string.find_last_not_of(anyof.data(), offset, anyof.length());
		}

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		size_t lastIndexNotOfAny(const wchar* anyof, size_t offset = npos) const
		{
			return m_string.find_last_not_of(anyof, offset, traits_type::length(anyof));
		}

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		int32 compare(const String& str) const noexcept
		{
			return m_string.compare(str.m_string);
		}

		int32 case_compare(const String& str) const noexcept
		{
			auto first1 = begin(), last1 = end();
			auto first2 = str.begin(), last2 = str.end();

			for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
			{
				const int32 c = CaseCompare(*first1, *first2);

				if (c != 0)
				{
					return c;
				}
			}

			if ((first1 == last1) && (first2 != last2))
			{
				return -1;
			}
			else if ((first1 != last1) && (first2 == last2))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}

		bool case_equals(const String& str) const noexcept
		{
			if (length() != str.length())
			{
				return false;
			}

			auto first1 = begin(), last1 = end();
			auto first2 = str.begin(), last2 = str.end();

			for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
			{
				const int32 c = CaseCompare(*first1, *first2);

				if (c != 0)
				{
					return false;
				}
			}

			return true;
		}

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		int32 compare(const wchar* str) const
		{
			return m_string.compare(str);
		}

		/// <summary>
		/// 文字列が等しいかを調べます。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 等しければ true, それ以外の場合は false
		/// </returns>
		bool operator == (const String& str) const
		{
			return m_string == str.m_string;
		}

		/// <summary>
		/// 文字列が等しくないかを調べます。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 等しくなければ true, それ以外の場合は false
		/// </returns>
		bool operator != (const String& str) const
		{
			return m_string != str.m_string;
		}

		/// <summary>
		/// 文字列の &lt; 比較を行います。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		bool operator < (const String& str) const
		{
			return m_string < str.m_string;
		}

		/// <summary>
		/// 文字列の &gt; 比較を行います。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		bool operator > (const String& str) const
		{
			return m_string > str.m_string;
		}

		/// <summary>
		/// 文字列の &lt;= 比較を行います。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		bool operator <= (const String& str) const
		{
			return m_string <= str.m_string;
		}

		/// <summary>
		/// 文字列の &gt;= 比較を行います。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		bool operator >= (const String& str) const
		{
			return m_string >= str.m_string;
		}

		template <class Fty = decltype(Id())>
		bool all(Fty f = Id()) const
		{
			for (const auto v : m_string)
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
			for (const auto v : m_string)
			{
				if (f(v))
				{
					return true;
				}
			}

			return false;
		}

		String& capitalize()
		{
			for (auto& v : m_string)
			{
				if (IsAlpha(v))
				{
					if (IsLower(v))
					{
						v -= 32;
					}

					break;
				}
			}

			return *this;
		}

		/// <summary>
		/// 最初に登場する英字を大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String capitalized() const &
		{
			return String(*this).capitalize();
		}

		String capitalized() &&
		{
			capitalize();

			return std::move(*this);
		}

		size_t count() const noexcept
		{
			return m_string.length();
		}

		/// <summary>
		/// 指定した文字の個数を数えます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 見つかった文字の個数
		/// </returns>
		size_t count(wchar ch) const
		{
			size_t count = 0;

			for (const auto v : m_string)
			{
				if (v == ch)
				{
					++count;
				}
			}

			return count;
		}

		/// <summary>
		/// 指定した文字列の個数を数えます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <remarks>
		/// L"aaa" から L"aa" を検索する場合の結果は 2 です。
		/// </remarks>
		/// <returns>
		/// 見つかった文字列の個数
		/// </returns>
		size_t count(StringView str) const;

		/// <summary>
		/// 条件に合う文字の個数を数えます。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 見つかった文字の個数
		/// </returns>
		template <class Fty>
		size_t count_if(Fty f) const
		{
			size_t result = 0;

			for (const auto v : m_string)
			{
				if (f(v))
				{
					++result;
				}
			}

			return result;
		}

		String& drop(size_t n)
		{
			if (n >= size())
			{
				m_string.clear();
			}
			else
			{
				m_string.erase(m_string.begin(), m_string.begin() + n);
			}

			return *this;
		}

		String dropped(size_t n) const
		{
			if (n >= m_string.size())
			{
				return String();
			}

			return String(m_string.begin() + n, m_string.end());
		}

		template <class Fty>
		String& drop_while(Fty f)
		{
			m_string.erase(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), f));

			return *this;
		}

		template <class Fty>
		String dropped_while(Fty f) const
		{
			return String(std::find_if_not(m_string.begin(), m_string.end(), f), m_string.end());
		}

		template <class Fty>
		String& each(Fty f)
		{
			for (auto& v : m_string)
			{
				f(v);
			}

			return *this;
		}

		template <class Fty>
		const String& each(Fty f) const
		{
			for (const auto v : m_string)
			{
				f(v);
			}

			return *this;
		}

		template <class Fty>
		String& each_index(Fty f)
		{
			size_t i = 0;

			for (auto& v : m_string)
			{
				f(i++, v);
			}

			return *this;
		}

		template <class Fty>
		const String& each_index(Fty f) const
		{
			size_t i = 0;

			for (const auto v : m_string)
			{
				f(i++, v);
			}

			return *this;
		}

		/// <summary>
		/// 指定した文字で終わるかを調べます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 指定した文字で終わる場合 true, それ以外の場合は false
		/// </returns>
		bool ends_with(wchar ch) const
		{
			return !m_string.empty() && (m_string[m_string.size() - 1] == ch);
		}

		/// <summary>
		/// 指定した文字列で終わるかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <returns>
		/// 指定した文字列で終わる場合 true, それ以外の場合は false
		/// </returns>
		bool ends_with(StringView str) const;

		/// <summary>
		/// タブ文字を半角空白に置換した文字列を返します。
		/// </summary>
		/// <param name="tabSize">
		/// タブ置換後の半角空白の数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String expand_tabs(size_t tabSize = 4) const
		{
			const size_t new_size = m_string.length() + (count(L'\t') * tabSize);

			String result(new_size, L'\0');

			wchar* dst = &result[0];

			for (const auto v : m_string)
			{
				if (v == L'\t')
				{
					for (size_t i = 0; i < tabSize; ++i)
					{
						*dst++ = L' ';
					}
				}
				else
				{
					*dst++ = v;
				}
			}

			return result;
		}

		const wchar& fetch(size_t index, const wchar& defaultValue) const
		{
			if (index >= size())
			{
				return defaultValue;
			}

			return m_string[index];
		}

		String& fill(wchar value)
		{
			std::fill(m_string.begin(), m_string.end(), value);

			return *this;
		}

		template <class Fty>
		String filter(Fty f) const
		{
			String new_array;

			for (const auto& v : m_string)
			{
				if (f(v))
				{
					new_array.push_back(v);
				}
			}

			return new_array;
		}

		/// <summary>
		/// 指定した文字が含まれているかを調べます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 検索した文字が見つかった場合 true, それ以外の場合は false
		/// </returns>
		bool includes(wchar ch) const
		{
			return indexOf(ch) != String::npos;
		}

		/// <summary>
		/// 指定した文字列が含まれているかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字列が見つかった場合 true, それ以外の場合は false
		/// </returns>
		bool includes(const wchar* str) const
		{
			return indexOf(str) != String::npos;
		}

		/// <summary>
		/// 指定した文字列が含まれているかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <returns>
		/// 検索した文字列が見つかった場合 true, それ以外の場合は false
		/// </returns>
		bool includes(const String& str) const
		{
			return indexOf(str) != String::npos;
		}

		/// <summary>
		/// 指定した条件に合う文字が含まれているかを調べます。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 検索した文字が見つかった場合 true, それ以外の場合は false
		/// </returns>
		template <class Fty>
		bool includes_if(Fty f) const
		{
			return any(f);
		}

		String& keep_if(std::function<bool(wchar)> f)
		{
			m_string.erase(std::remove_if(m_string.begin(), m_string.end(), std::not1(f)), m_string.end());

			return *this;
		}

		/// <summary>
		/// 指定した 1 行の文字数で改行するようにした文字列を返します。
		/// </summary>
		/// <param name="width">
		/// 1 行の文字数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String layout(size_t width) const
		{
			String result;

			result.reserve(m_string.length());

			size_t count = 0;

			for (const auto v : m_string)
			{
				if (v == L'\n')
				{
					result.push_back(L'\n');
					
					count = 0;
				}
				else if (v != L'\r')
				{
					if (width <= count)
					{
						result.push_back(L'\n');
						
						count = 0;
					}

					result.push_back(v);
					
					++count;
				}
			}

			return result;
		}

		String& lowercase()
		{
			for (auto& v : m_string)
			{
				if (IsUpper(v))
				{
					v += 32;
				}
			}

			return *this;
		}

		/// <summary>
		/// 英字をすべて小文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String lowercased() const &
		{
			return String(*this).lowercase();
		}

		String lowercased() &&
		{
			lowercase();

			return std::move(*this);
		}

		String& lpad(size_t length, wchar fillChar = L' ')
		{
			if (length <= m_string.length())
			{
				return *this;
			}

			m_string.insert(m_string.begin(), length - m_string.length(), fillChar);

			return *this;
		}

		String lpadded(size_t length, wchar fillChar = L' ') const &
		{
			if (length <= m_string.length())
			{
				return *this;
			}

			String new_string;

			new_string.reserve(length);

			new_string.assign(length - m_string.length(), fillChar);

			new_string.append(m_string);

			return new_string;
		}

		String lpadded(size_t length, wchar fillChar = L' ') &&
		{
			lpad(length, fillChar);

			return std::move(*this);
		}

		String& ltrim()
		{
			m_string.erase(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable));

			return *this;
		}

		String ltrimmed() const &
		{
			return String(std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable), m_string.end());
		}

		String ltrimmed() &&
		{
			ltrim();

			return std::move(*this);
		}

		template <class Fty>
		auto map(Fty f) const
		{
			using ValueType = std::result_of_t<Fty(wchar)>;
            
			Array<ValueType, typename DefaultAllocator<ValueType>::type> new_array;

			new_array.reserve(size());

			for (const auto v : m_string)
			{
				new_array.push_back(f(v));
			}

			return new_array;
		}

		/// <summary>
		/// マルチバイト文字列に変換します。
		/// </summary>
		/// <returns>
		/// 変換されたマルチバイト文字列
		/// </returns>
		std::string narrow() const;

		template <class Fty = decltype(Id())>
		bool none(Fty f = Id()) const
		{
			for (const auto v : m_string)
			{
				if (f(v))
				{
					return false;
				}
			}

			return true;
		}

		String& remove(wchar ch)
		{
			m_string.erase(std::remove(m_string.begin(), m_string.end(), ch), m_string.end());
			
			return *this;
		}

		/// <summary>
		/// 指定した文字を除去した文字列を返します。
		/// </summary>
		/// <param name="ch">
		/// 除去対象の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String removed(wchar ch) const &
		{
			String new_string;

			for (const auto v : m_string)
			{
				if (v != ch)
				{
					new_string.push_back(v);
				}
			}

			return new_string;
		}

		String removed(wchar ch) &&
		{
			remove(ch);

			return std::move(*this);
		}

		String& remove(const StringView& str)
		{
			return *this = removed(str);
		}

		/// <summary>
		/// 指定した文字列を除去した文字列を返します。
		/// </summary>
		/// <param name="str">
		/// 除去対象の文字列
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String removed(const StringView& str) const;

		String& remove_at(size_t index)
		{
			if (m_string.size() <= index)
			{
				throw std::out_of_range("String::remove_at() index out of range");
			}

			m_string.erase(m_string.begin() + index);

			return *this;
		}

		String removed_at(size_t index) const &
		{
			if (m_string.size() <= index)
			{
				throw std::out_of_range("String::removed_at() index out of range");
			}

			String new_string;

			new_string.reserve(m_string.length() - 1);

			new_string.assign(m_string.begin(), m_string.begin() + index);

			new_string.append(m_string.begin() + index + 1, m_string.end());

			return new_string;
		}

		String removed_at(size_t index) &&
		{
			remove_at(index);

			return std::move(*this);
		}

		template <class Fty>
		String& remove_if(Fty f)
		{
			m_string.erase(std::remove_if(m_string.begin(), m_string.end(), f), m_string.end());

			return *this;
		}

		/// <summary>
		/// 条件に合う文字を除去した文字列を返します。
		/// </summary>
		/// <param name="function">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		template <class Fty>
		String removed_if(Fty f) const &
		{
			String new_string;

			for (const auto v : m_string)
			{
				if (!f(v))
				{
					new_string.push_back(v);
				}
			}

			return new_string;
		}

		template <class Fty>
		String removed_if(Fty f) &&
		{
			remove_if(f);

			return std::move(*this);
		}

		String& replace(wchar oldChar, wchar newChar)
		{
			for (auto& v : m_string)
			{
				if (v == oldChar)
				{
					v = newChar;
				}
			}

			return *this;
		}

		String& replace(const String& oldStr, const String& newStr)
		{
			return *this = replaced(oldStr, newStr);
		}

		/// <summary>
		/// 指定した文字を置換した文字列を返します。
		/// </summary>
		/// <param name="oldChar">
		/// 置換対象の文字
		/// </param>
		/// <param name="newChar">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// 置換後の文字列
		/// </returns>
		String replaced(wchar oldChar, wchar newChar) const &
		{
			return String(*this).replace(oldChar, newChar);
		}

		String replaced(wchar oldChar, wchar newChar) &&
		{
			replace(oldChar, newChar);

			return std::move(*this);
		}

		/// <summary>
		/// 指定した文字列を置換した文字列を返します。
		/// </summary>
		/// <param name="oldStr">
		/// 置換対象の文字列
		/// </param>
		/// <param name="newStr">
		/// 置換後の文字列
		/// </param>
		/// <returns>
		/// 置換後の文字列
		/// </returns>
		String replaced(const String& oldStr, const String& newStr) const
		{
			String new_string;

			if (newStr.length() >= oldStr.length())
			{
				new_string.reserve(m_string.length());
			}

			const auto itEnd = m_string.end();
			auto itCurrent = m_string.begin();
			auto itNext = std::search(itCurrent, itEnd, oldStr.begin(), oldStr.end());

			while (itNext != itEnd)
			{
				new_string.append(itCurrent, itNext);
				new_string.append(newStr);
				itCurrent = itNext + oldStr.length();
				itNext = std::search(itCurrent, itEnd, oldStr.begin(), oldStr.end());
			}

			new_string.append(itCurrent, itNext);

			return new_string;
		}

		template <class Fty>
		String& replace_if(Fty f, wchar newChar)
		{
			for (auto& v : m_string)
			{
				if (f(v))
				{
					v = newChar;
				}
			}

			return *this;
		}

		template <class Fty>
		String replaced_if(Fty f, wchar newChar) const &&
		{
			return String(*this).replace_if(f, newChar);
		}

		template <class Fty>
		String replaced_if(Fty f, wchar newChar) &
		{
			replace_if(f, newChar);

			return std::move(*this);
		}

		String& reverse()
		{
			std::reverse(m_string.begin(), m_string.end());

			return *this;
		}

		/// <summary>
		/// 反転した文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String reversed() const &
		{
			return String(m_string.rbegin(), m_string.rend());
		}

		String reversed() &&
		{
			reverse();

			return *this;
		}

		template <class Fty>
		String& reverse_each(Fty f)
		{
			for (auto it = m_string.rbegin(); it != m_string.rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		template <class Fty>
		const String& reverse_each(Fty f) const
		{
			for (auto it = m_string.rbegin(); it != m_string.rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		String& rotate(std::ptrdiff_t count = 1)
		{
			if (m_string.empty())
			{
				;
			}
			else if (count > 0) // rotation to the left
			{
				if (static_cast<size_t>(count) > m_string.size())
				{
					count %= m_string.size();
				}

				std::rotate(m_string.begin(), m_string.begin() + count, m_string.end());
			}
			else if (count < 0) // rotation to the right
			{
				count = -count;

				if (static_cast<size_t>(count) > m_string.size())
				{
					count %= m_string.size();
				}

				std::rotate(m_string.rbegin(), m_string.rbegin() + count, m_string.rend());
			}

			return *this;
		}

		String rotated(std::ptrdiff_t count = 1) const &
		{
			return String(*this).rotate(count);
		}

		String rotated(std::ptrdiff_t count = 1) &&
		{
			rotate(count);

			return std::move(*this);
		}

		String& rpad(size_t length, wchar fillChar = L' ')
		{
			if (length <= m_string.length())
			{
				return *this;
			}

			m_string.append(length - m_string.length(), fillChar);

			return *this;
		}

		String rpadded(size_t length, wchar fillChar = L' ') const &
		{
			if (length <= m_string.length())
			{
				return *this;
			}

			String new_string;

			new_string.reserve(length);

			new_string.assign(m_string);

			new_string.append(length - m_string.length(), fillChar);

			return new_string;
		}

		String rpadded(size_t length, wchar fillChar = L' ') &&
		{
			rpad(length, fillChar);

			return std::move(*this);
		}

		String& rtrim()
		{
			m_string.erase(std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base(), m_string.end());

			return *this;
		}

		String rtrimmed() const &
		{
			return String(m_string.begin(), std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base());
		}

		String rtrimmed() &&
		{
			rtrim();

			return std::move(*this);
		}

		String& shuffle()
		{
			return shuffle(GetDefaultRNG());
		}

		template <class URNG>
		String& shuffle(URNG&& rng)
		{
			std::shuffle(m_string.begin(), m_string.end(), rng);

			return *this;
		}

		String shuffled() const &
		{
			return shuffled(GetDefaultRNG());
		}

		String shuffled() &&
		{
			return shuffled(GetDefaultRNG());
		}

		template <class URNG>
		String shuffled(URNG&& rng) const &
		{
			return String(*this).shuffle(rng);
		}

		template <class URNG>
		String shuffled(URNG&& rng) &&
		{
			std::shuffle(m_string.begin(), m_string.end(), rng);

			return std::move(*this);
		}

		/// <summary>
		/// 指定した区切り文字で文字列を分割します。
		/// </summary>
		/// <param name="ch">
		/// 区切り文字
		/// </param>
		/// <returns>
		/// 分割された文字列
		/// </returns>
		Array<String, std::allocator<String>> split(wchar ch) const;

		std::pair<String, String> split_at(size_t pos) const
		{
			return{ substr(0, pos), substr(pos) };
		}

		Array<String, std::allocator<String>> split_lines() const;

		/// <summary>
		/// 指定した文字から始まるかを調べます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 指定した文字から始まる場合 true, それ以外の場合は false
		/// </returns>
		bool starts_with(wchar ch) const
		{
			return !m_string.empty() && (m_string[0] == ch);
		}

		/// <summary>
		/// 指定した文字列から始まるかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <returns>
		/// 指定した文字列から始まる場合 true, それ以外の場合は false
		/// </returns>
		bool starts_with(const StringView& str) const;

		String& swapcase()
		{
			for (auto& v : m_string)
			{
				if (IsLower(v))
				{
					v -= 32;
				}
				else if (IsUpper(v))
				{
					v += 32;
				}
			}

			return *this;
		}

		/// <summary>
		/// 英字の大文字と小文字を入れ替えた文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String swapcased() const &
		{
			return String(*this).swapcase();
		}

		String swapcased() &&
		{
			swapcase();

			return std::move(*this);
		}

		String& trim()
		{
			m_string.erase(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable));

			m_string.erase(std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base(), m_string.end());

			return *this;
		}

		String trimmed() const &
		{
			return String(std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable), std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base());
		}

		String trimmed() &&
		{
			trim();

			return std::move(*this);
		}

		String& uppercase()
		{
			for (auto& v : m_string)
			{
				if (IsLower(v))
				{
					v -= 32;
				}
			}

			return *this;
		}

		/// <summary>
		/// 英字をすべて大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String uppercased() const &
		{
			return String(*this).uppercase();
		}

		String uppercased() &&
		{
			uppercase();

			return std::move(*this);
		}

		std::string toUTF8() const;

		std::u16string toUTF16() const;

		std::u32string toUTF32() const;

		String& sort()
		{
			std::sort(m_string.begin(), m_string.end());

			return *this;
		}

		template <class Fty>
		String& sort_by(Fty f)
		{
			std::sort(m_string.begin(), m_string.end(), f);

			return *this;
		}

		String sorted() const &
		{
			return String(*this).sort();
		}

		String sorted() &&
		{
			std::sort(m_string.begin(), m_string.end());

			return std::move(*this);
		}

		template <class Fty>
		String sorted_by(Fty f) const &
		{
			return String(*this).sort_by(f);
		}

		template <class Fty>
		String sorted_by(Fty f) &&
		{
			std::sort(m_string.begin(), m_string.end(), f);

			return std::move(*this);
		}

		String& take(size_t n)
		{
			m_string.erase(m_string.begin() + std::min(n, m_string.size()), m_string.end());

			return *this;
		}

		String taken(size_t n) const
		{
			return String(m_string.begin(), m_string.begin() + std::min(n, m_string.size()));
		}

		template <class Fty>
		String& take_while(Fty f)
		{
			m_string.erase(std::find_if_not(m_string.begin(), m_string.end(), f), m_string.end());

			return *this;
		}

		template <class Fty>
		String taken_while(Fty f) const
		{
			return String(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), f));
		}

		String& unique()
		{
			sort();

			m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

			return *this;
		}

		String uniqued() const &
		{
			return String(*this).unique();
		}

		String uniqued() &&
		{
			sort();

			m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

			m_string.shrink_to_fit();

			return std::move(*this);
		}

		String values_at(std::initializer_list<size_t> indices) const
		{
			String new_array;

			new_array.reserve(indices.size());

			for (auto index : indices)
			{
				if (index >= m_string.size())
				{
					throw std::out_of_range("String::values_at() index out of range");
				}

				new_array.push_back(m_string[index]);
			}

			return new_array;
		}

		String& xml_escape()
		{
			return *this = xml_escaped();
		}

		/// <summary>
		/// XML エスケープした文字列を返します。
		/// </summary>
		/// <remarks>
		/// &quot;, \, &amp;, &gt;, &lt; をエスケープ文字に置換します
		/// </remarks>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String xml_escaped() const
		{
			String new_string;

			new_string.reserve(m_string.length());

			for (const auto v : m_string)
			{
				switch (v)
				{
				case L'\"':
					new_string.append(L"&quot;", 6);
					break;
				case L'&':
					new_string.append(L"&amp;", 5);
					break;
				case L'\'':
					new_string.append(L"&apos;", 6);
					break;
				case L'<':
					new_string.append(L"&lt;", 4);
					break;
				case L'>':
					new_string.append(L"&gt;", 4);
					break;
				default:
					new_string.push_back(v);
					break;
				}
			}

			return new_string;
		}
	};

	inline std::ostream& operator <<(std::ostream& output, const String& str)
	{
		return output << str.narrow();
	}

	/// <summary>
	/// 出力ストリームに文字列を渡します。
	/// </summary>
	/// <param name="output">
	/// 出力ストリーム
	/// </param>
	/// <param name="str">
	/// 文字列
	/// </param>
	/// <returns>
	/// 渡した後の出力ストリーム
	/// </returns>
	inline std::wostream& operator <<(std::wostream& output, const String& str)
	{
		return output << str.str();
	}

	/// <summary>
	/// 入力ストリームに文字列を渡します。
	/// </summary>
	/// <param name="input">
	/// 入力ストリーム
	/// </param>
	/// <param name="str">
	/// 文字列
	/// </param>
	/// <returns>
	/// 渡した後の入力ストリーム
	/// </returns>
	inline std::wistream& operator >>(std::wistream& input, String& str)
	{
		return input >> str.str();
	}



	inline String operator +(const String& lhs, const String& rhs)
	{
		return lhs.str() + rhs.str();
	}

	inline String operator +(const wchar* lhs, const String& rhs)
	{
		return lhs + rhs.str();
	}

	inline String operator +(const wchar lhs, const String& rhs)
	{
		return lhs + rhs.str();
	}

	inline String operator +(const String& lhs, const wchar* rhs)
	{
		return lhs.str() + rhs;
	}

	inline String operator +(const String& lhs, const wchar rhs)
	{
		return lhs.str() + rhs;
	}

	inline bool operator ==(const wchar* lhs, const String& rhs)
	{
		return lhs == rhs.str();
	}

	inline bool operator ==(const String& lhs, const wchar* rhs)
	{
		return lhs.str() == rhs;
	}

	inline bool operator !=(const wchar* lhs, const String& rhs)
	{
		return lhs != rhs.str();
	}

	inline bool operator !=(const String& lhs, const wchar* rhs)
	{
		return lhs.str() != rhs;
	}

	inline bool operator <(const wchar* lhs, const String& rhs)
	{
		return lhs < rhs.str();
	}

	inline bool operator <(const String& lhs, const wchar* rhs)
	{
		return lhs.str() < rhs;
	}

	inline bool operator >(const wchar* lhs, const String& rhs)
	{
		return lhs > rhs.str();
	}

	inline bool operator >(const String& lhs, const wchar* rhs)
	{
		return lhs.str() > rhs;
	}

	inline bool operator <=(const wchar* lhs, const String& rhs)
	{
		return lhs <= rhs.str();
	}

	inline bool operator <=(const String& lhs, const wchar* rhs)
	{
		return lhs.str() <= rhs;
	}

	inline bool operator >=(const wchar* lhs, const String& rhs)
	{
		return lhs >= rhs.str();
	}

	inline bool operator >=(const String& lhs, const wchar* rhs)
	{
		return lhs.str() >= rhs;
	}
}

namespace std
{
	inline void swap(s3d::String& a, s3d::String& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

	template <>
	struct hash<s3d::String>
	{
		size_t operator () (const s3d::String& keyVal) const
		{
			return hash<s3d::String::string_type>()(keyVal.str());
		}
	};
}

# include "StringView.hpp"
# include "CharacterSet.hpp"

namespace s3d
{
	inline size_t String::count(const StringView str) const
	{
		size_t count = 0;

		for (auto it = m_string.begin();; ++it, ++count)
		{
			it = std::search(it, m_string.end(), str.begin(), str.end());

			if (it == m_string.end())
			{
				return count;
			}
		}
	}

	inline bool String::ends_with(const StringView str) const
	{
		return (length() >= str.length()) && std::equal(str.begin(), str.end(), m_string.end() - str.length());
	}

	inline std::string String::narrow() const
	{
		return CharacterSet::Narrow(*this);
	}

	inline String String::removed(const StringView& str) const
	{
		String new_string;

		for (auto it = m_string.begin(); it != m_string.end();)
		{
			const auto it2 = it;
			
			new_string.append(it2, it = std::search(it, m_string.end(), str.begin(), str.end()));

			if (it != m_string.end())
			{
				it += str.length();
			}
		}

		return new_string;
	}

	inline bool String::starts_with(const StringView& str) const
	{
		return (m_string.length() >= str.length()) && std::equal(str.begin(), str.end(), m_string.begin());
	}

	inline std::string String::toUTF8() const
	{
		return CharacterSet::ToUTF8(*this);
	}

	inline std::u16string String::toUTF16() const
	{
		return CharacterSet::ToUTF16(*this);
	}

	inline std::u32string String::toUTF32() const
	{
		return CharacterSet::ToUTF32(*this);
	}

	inline std::istream& operator >> (std::istream& input, String& str)
	{
		std::string t;
		input >> t;
		str = CharacterSet::Widen(t);
		return input;
	}

	inline std::ostream& operator << (std::ostream& os, const StringView& str)
	{
		return os << CharacterSet::Narrow(str);
	}

	using FilePath = String;
}
