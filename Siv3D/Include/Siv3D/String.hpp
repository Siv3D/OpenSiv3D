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
# include <string>
# include <iostream>
# include <algorithm>
# include "Fwd.hpp"
# include "Char.hpp"
# include "Functor.hpp"
# include "DefaultRNG.hpp"
# include "StringView.hpp"
# include "Hash.hpp"

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

		String(const String& other, size_type pos)
			: m_string(other.m_string, pos) {}
		
		String(const String& other, size_type pos, size_type count)
			: m_string(other.m_string, pos, count) {}

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="str">
		/// コピーする文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		String(const value_type* str)
			: m_string(str) {}

		/// <summary>
		/// 文字列を指定した文字数だけコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="str">
		/// コピーする文字列の先頭ポインタ
		/// </param>
		/// <param name="count">
		/// コピーする文字数
		/// </param>
		String(const value_type* str, size_type count)
			: m_string(str, count) {}

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
		String(size_t count, value_type ch)
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
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="view">
		/// コピーする文字列
		/// </param>
		explicit String(StringView view)
			: m_string(view.begin(), view.end()) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~String() = default;

		operator StringView() const noexcept
		{
			return StringView(m_string.data(), m_string.size());
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
		String& operator =(const String& str) { return assign(str); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator =(const string_type& str) { return assign(str); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator =(String&& str) noexcept { return assign(std::move(str)); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="str">
		/// 新しい文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator =(string_type&& str) noexcept { return assign(std::move(str)); }

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
		String& operator =(const value_type* str) { return assign(str); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="ch">
		/// 新しい文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator =(const value_type ch) { return assign(1, ch); }

		/// <summary>
		/// 新しい文字列を代入します。
		/// </summary>
		/// <param name="ilist">
		/// 新しい文字列の初期化リスト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& operator =(std::initializer_list<value_type> ilist) { return assign(ilist); }

		String& operator =(const StringView sv) { return assign(sv); }

		String& operator <<(const value_type ch)
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
		String& assign(const value_type* str)
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
		String& assign(const size_t count, const value_type ch)
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

		String& assign(const StringView sv)
		{
			m_string.assign(sv.begin(), sv.end());

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
		String& operator += (const value_type* str) { return append(str); }

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
		String& operator += (const value_type ch) { return append(1, ch); }

		String& operator += (const StringView sv) { return append(sv); }

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
		String& append(const value_type* str)
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
		String& append(const value_type* str, const size_t count)
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
		String& append(const size_t count, const value_type ch)
		{
			m_string.append(count, ch);

			return *this;
		}

		String& append(const StringView sv)
		{
			m_string.append(sv.begin(), sv.end());

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
		String& insert(const size_t offset, const String& str)
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
		String& insert(const size_t offset, std::initializer_list<value_type> ilist)
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
		String& insert(const size_t offset, const value_type* str)
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
		String& insert(const size_t offset, const size_t count, const value_type ch)
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
		iterator insert(const_iterator where, const value_type ch)
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
		void insert(const_iterator where, const size_t count, const value_type ch)
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
		String& erase(const size_t offset = 0, const size_t count = npos)
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
		value_type& at(const size_t offset) & { return m_string.at(offset); }

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
		const value_type& at(const size_t offset) const & { return m_string.at(offset); }

		/// <summary>
		/// 指定した位置の文字を取得します。
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
		value_type at(const size_t offset) && { return m_string.at(offset); }

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		value_type& operator[](const size_t offset) & { return m_string[offset]; }

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		const value_type& operator[](const size_t offset) const & { return m_string[offset]; }

		/// <summary>
		/// 指定した位置の文字を取得します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		value_type operator[](const size_t offset) && { return std::move(m_string[offset]); }

		/// <summary>
		/// 先頭に文字を追加します。
		/// </summary>
		/// <param name="value">
		/// 追加する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_front(const value_type ch) { insert(begin(), ch); }

		/// <summary>
		/// 末尾に文字を追加します。
		/// </summary>
		/// <param name="ch">
		/// 追加する文字
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_back(const value_type ch) { m_string.push_back(ch); }

		/// <summary>
		/// 先頭の文字を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pop_front() { m_string.erase(m_string.begin()); }

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
		value_type& front() { return m_string.front(); }

		/// <summary>
		/// 先頭の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 先頭の文字への参照
		/// </returns>
		const value_type& front() const { return m_string.front(); }

		/// <summary>
		/// 末尾の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 末尾の文字への参照
		/// </returns>
		value_type& back() { return m_string.back(); }

		/// <summary>
		/// 末尾の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 末尾の文字への参照
		/// </returns>
		const value_type& back() const { return m_string.back(); }

		/// <summary>
		/// C スタイル文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// C スタイル文字列の先頭のポインタ
		/// </returns>
		const value_type* c_str() const noexcept { return m_string.c_str(); }

		/// <summary>
		/// 文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭へのポインタ
		/// </returns>
		const value_type* data() const noexcept { return m_string.data(); }

		/// <summary>
		/// 文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭へのポインタ
		/// </returns>
		value_type* data() noexcept { return &m_string[0]; }

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
		/// 終端の '\0' を含みません。
		/// </remarks>
		size_t length() const noexcept { return m_string.length(); }

		/// <summary>
		/// 文字列の長さを示します。
		/// </summary>
		/// <remarks>
		/// 終端の '\0' を含みません。
		/// </remarks>
		size_t size() const noexcept { return m_string.size(); }

		size_t size_bytes() const noexcept { return m_string.size() * sizeof(value_type); }

		size_t num_codePoints() const;

		/// <summary>
		/// 空の文字列であるかを示します。
		/// </summary>
		bool empty() const noexcept { return m_string.empty(); }

		/// <summary>
		/// 空の文字列であるかを示します。
		/// </summary>
		bool isEmpty() const noexcept { return m_string.empty(); }

		/// <summary>
		/// 文字列に要素が含まれているかを示します。
		/// </summary>
		explicit operator bool() const noexcept
		{
			return !m_string.empty();
		}

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
		void resize(const size_t newSize) { m_string.resize(newSize); }

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
		void resize(const size_t newSize, const value_type ch) { m_string.resize(newSize, ch); }

		/// <summary>
		/// 文字列用のメモリを指定したサイズで確保します。
		/// </summary>
		/// <param name="newCapacity">
		/// 確保する文字列のサイズ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reserve(const size_t newCapacity) { m_string.reserve(newCapacity); }

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
		String substr(const size_t offset = 0, const size_t count = npos) const
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
		size_t indexOf(const String& str, const size_t offset = 0) const noexcept
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
		size_t indexOf(const value_type* str, const size_t offset = 0) const
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
		size_t indexOf(const value_type ch, const size_t offset = 0) const
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
		size_t indexOfNot(const value_type ch, const size_t offset = 0) const
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
		size_t lastIndexOf(const String& str, const size_t offset = npos) const
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
		size_t lastIndexOf(const value_type* str, const size_t offset = npos) const
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
		size_t lastIndexOf(const value_type ch, const size_t offset = npos) const
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
		size_t lastIndexNotOf(const value_type ch, const size_t offset = npos) const
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
		size_t indexOfAny(const String& anyof, const size_t offset = 0) const
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
		size_t indexOfAny(const value_type* anyof, const size_t offset = 0) const
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
		size_t lastIndexOfAny(const String& anyof, const size_t offset = npos) const
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
		size_t lastIndexOfAny(const value_type* anyof, const size_t offset = npos) const
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
		size_t indexNotOfAny(const String& anyof, const size_t offset = 0) const
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
		size_t indexNotOfAny(const value_type* anyof, const size_t offset = 0) const
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
		size_t lastIndexNotOfAny(const String& anyof, const size_t offset = npos) const
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
		size_t lastIndexNotOfAny(const value_type* anyof, const size_t offset = npos) const
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

		/// <summary>
		/// 英字の大小を無視して文字列の大小を比較します。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		int32 case_insensitive_compare(const String& str) const noexcept
		{
			auto first1 = begin(), last1 = end();
			auto first2 = str.begin(), last2 = str.end();

			for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
			{
				const int32 c = CaseInsensitiveCompare(*first1, *first2);

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

		/// <summary>
		/// 英字の大小を無視して文字列を比較します。
		/// </summary>
		/// <param name="str">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 英字の大小を無視した時に文字列が等しい場合 true, それ以外の場合は false
		/// </returns>
		bool case_insensitive_equals(const String& str) const noexcept
		{
			if (length() != str.length())
			{
				return false;
			}

			auto first1 = begin(), last1 = end();
			auto first2 = str.begin(), last2 = str.end();

			for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
			{
				const int32 c = CaseInsensitiveCompare(*first1, *first2);

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
		int32 compare(const value_type* str) const
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

		/// <summary>
		/// 全ての文字が条件を満たすかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たさない文字が 1 つでもあれば false, それ以外の場合は true
		/// </returns>
		template <class Fty = decltype(Id)>
		bool all(Fty f = Id) const
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

		/// <summary>
		/// 少なくとも 1 つの文字が条件を満たすかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たす文字が 1 つでもあれば true, それ以外の場合は false
		/// </returns>
		template <class Fty = decltype(Id)>
		bool any(Fty f = Id) const
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

		/// <summary>
		/// 最初に登場する英字を大文字にします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 最初に登場する英字を大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String capitalized() &&
		{
			capitalize();

			return std::move(*this);
		}

		/// <summary>
		/// 文字列の長さを返します。
		/// </summary>
		/// <remarks>
		/// 絵文字などが使用されている場合、必ずしも見かけ上の文字数と一致しない事に注意してください。
		/// </remarks>
		/// <returns>
		/// 文字列の長さ
		/// </returns>
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
		size_t count(const value_type ch) const
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
		/// "aaa" から "aa" を検索する場合の結果は 2 です。
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

		/// <summary>
		/// 指定された数だけ先頭の文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="n">
		/// 削除する文字数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String drop(const size_t n) const
		{
			if (n >= m_string.size())
			{
				return String();
			}

			return String(m_string.begin() + n, m_string.end());
		}

		/// <summary>
		/// 文字列の先頭から、指定された条件を満たす連続した文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		template <class Fty>
		String drop_while(Fty f) const
		{
			return String(std::find_if_not(m_string.begin(), m_string.end(), f), m_string.end());
		}

		/// <summary>
		/// 文字列の各文字への参照を引数に、先頭の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		String& each(Fty f)
		{
			for (auto& v : m_string)
			{
				f(v);
			}

			return *this;
		}

		/// <summary>
		/// 文字列の各文字への参照を引数に、先頭の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		const String& each(Fty f) const
		{
			for (const auto v : m_string)
			{
				f(v);
			}

			return *this;
		}

		/// <summary>
		/// 文字列の各文字のインデックスと参照を引数に、先頭の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字のインデックスと参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 文字列の各文字のインデックスと参照を引数に、先頭の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字のインデックスと参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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
		bool ends_with(const value_type ch) const
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
		String expand_tabs(const size_t tabSize = 4) const
		{
			const size_t new_size = m_string.length() + (count(value_type('\t')) * tabSize);

			String result(new_size, value_type('\0'));

			value_type* dst = &result[0];

			for (const auto v : m_string)
			{
				if (v == value_type('\t'))
				{
					for (size_t i = 0; i < tabSize; ++i)
					{
						*dst++ = value_type(' ');
					}
				}
				else
				{
					*dst++ = v;
				}
			}

			return result;
		}

		/// <summary>
		/// 指定した位置の文字への参照を返します。指定されたインデックスが存在しない場合はデフォルト値を返します。
		/// </summary>
		/// <param name="index">
		/// 位置
		/// </param>
		/// <param name="defaultValue">
		/// インデックスが存在しない場合に返されるデフォルト値
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照、もしくはデフォルト値
		/// </returns>
		const value_type& fetch(const size_t index, const value_type& defaultValue) const
		{
			if (index >= size())
			{
				return defaultValue;
			}

			return m_string[index];
		}

		/// <summary>
		/// 文字列のサイズを変えずに、全文字を指定された文字で置換します。
		/// </summary>
		/// <param name="value">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& fill(const value_type value)
		{
			std::fill(m_string.begin(), m_string.end(), value);

			return *this;
		}

		/// <summary>
		/// 指定した条件に合う文字のみを含む新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
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
		bool includes(const value_type ch) const
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
		bool includes(const value_type* str) const
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

		String& keep_if(std::function<bool(value_type)> f)
		{
			m_string.erase(std::remove_if(m_string.begin(), m_string.end(), std::not1(f)), m_string.end());

			return *this;
		}

		/// <summary>
		/// 指定した 1 行の文字数で改行するようにした新しい文字列を返します。
		/// </summary>
		/// <param name="width">
		/// 1 行の文字数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String layout(const size_t width) const
		{
			String result;

			result.reserve(m_string.length());

			size_t count = 0;

			for (const auto v : m_string)
			{
				if (v == value_type('\n'))
				{
					result.push_back(value_type('\n'));
					
					count = 0;
				}
				else if (v != value_type('\r'))
				{
					if (width <= count)
					{
						result.push_back(value_type('\n'));
						
						count = 0;
					}

					result.push_back(v);
					
					++count;
				}
			}

			return result;
		}

		/// <summary>
		/// 英字をすべて小文字にします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
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
		/// 英字をすべて小文字にした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String lowercased() const &
		{
			return String(*this).lowercase();
		}

		/// <summary>
		/// 英字をすべて小文字にした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String lowercased() &&
		{
			lowercase();

			return std::move(*this);
		}

		/// <summary>
		/// 文字列を指定された文字で左詰めします。
		/// </summary>
		/// <param name="length">
		/// 左詰めした後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 左詰め用の埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、変更は行われません。 
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& lpad(const size_t length, const value_type fillChar = value_type(' '))
		{
			if (length <= m_string.length())
			{
				return *this;
			}

			m_string.insert(m_string.begin(), length - m_string.length(), fillChar);

			return *this;
		}

		/// <summary>
		/// 文字列を指定された文字で左詰めした新しい文字列を返します。
		/// </summary>
		/// <param name="length">
		/// 左詰めした後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 左詰め用の埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、元の文字列のコピーが返ります。 
		/// </remarks>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String lpadded(const size_t length, const value_type fillChar = value_type(' ')) const &
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

		/// <summary>
		/// 文字列を指定された文字で左詰めした新しい文字列を返します。
		/// </summary>
		/// <param name="length">
		/// 左詰めした後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 左詰め用の埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、元の文字列のコピーが返ります。 
		/// </remarks>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String lpadded(const size_t length, const value_type fillChar = value_type(' ')) &&
		{
			lpad(length, fillChar);

			return std::move(*this);
		}

		/// <summary>
		/// 文字列の先頭にある空白文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& ltrim()
		{
			m_string.erase(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable));

			return *this;
		}

		/// <summary>
		/// 文字列の先頭にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String ltrimmed() const &
		{
			return String(std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable), m_string.end());
		}

		/// <summary>
		/// 文字列の先頭にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String ltrimmed() &&
		{
			ltrim();

			return std::move(*this);
		}

		/// <summary>
		/// 文字列の各文字に関数を適用した戻り値からなる配列を返します。
		/// </summary>
		/// <param name="f">
		/// 各文字に適用する関数
		/// </param>
		/// <returns>
		/// 文字列の各文字に関数を適用した戻り値からなる配列
		/// </returns>
		template <class Fty>
		auto map(Fty f) const
		{
			using ValueType = std::result_of_t<Fty(value_type)>;
            
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

		/// <summary>
		/// 全ての文字が条件を満たさないかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たす文字が 1 つでもあれば false, それ以外の場合は true
		/// </returns>
		template <class Fty = decltype(Id)>
		bool none(Fty f = Id) const
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

		/// <summary>
		/// 指定した文字を文字列から削除します。
		/// </summary>
		/// <param name="ch">
		/// 削除する文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& remove(const value_type ch)
		{
			m_string.erase(std::remove(m_string.begin(), m_string.end(), ch), m_string.end());
			
			return *this;
		}

		/// <summary>
		/// 指定した文字列をもとの文字列から削除します。
		/// </summary>
		/// <param name="str">
		/// 削除する文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& remove(const StringView str)
		{
			return *this = removed(str);
		}

		/// <summary>
		/// 指定した文字を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="ch">
		/// 除去対象の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String removed(const value_type ch) const &
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

		/// <summary>
		/// 指定した文字を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="ch">
		/// 除去対象の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String removed(const value_type ch) &&
		{
			remove(ch);

			return std::move(*this);
		}

		/// <summary>
		/// 指定した文字列を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="str">
		/// 除去対象の文字列
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String removed(const StringView str) const;

		/// <summary>
		/// 指定したインデックスの文字を文字列から削除します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& remove_at(const size_t index)
		{
			if (m_string.size() <= index)
			{
				throw std::out_of_range("String::remove_at() index out of range");
			}

			m_string.erase(m_string.begin() + index);

			return *this;
		}

		/// <summary>
		/// 指定したインデックスの文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String removed_at(const size_t index) const &
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

		/// <summary>
		/// 指定したインデックスの文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String removed_at(const size_t index) &&
		{
			remove_at(index);

			return std::move(*this);
		}

		/// <summary>
		/// 指定した条件を満たす文字を削除します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		String& remove_if(Fty f)
		{
			m_string.erase(std::remove_if(m_string.begin(), m_string.end(), f), m_string.end());

			return *this;
		}

		/// <summary>
		/// 指定した条件を満たす文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
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

		/// <summary>
		/// 指定した条件を満たす文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		template <class Fty>
		String removed_if(Fty f) &&
		{
			remove_if(f);

			return std::move(*this);
		}

		/// <summary>
		/// 指定した文字を置換します。
		/// </summary>
		/// <param name="oldChar">
		/// 置換対象の文字
		/// </param>
		/// <param name="newChar">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& replace(const value_type oldChar, const value_type newChar)
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

		/// <summary>
		/// 指定した文字列を置換します。
		/// </summary>
		/// <param name="oldStr">
		/// 置換対象の文字列
		/// </param>
		/// <param name="newStr">
		/// 置換後の文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& replace(const String& oldStr, const String& newStr)
		{
			return *this = replaced(oldStr, newStr);
		}

		/// <summary>
		/// 指定した文字を置換した新しい文字列を返します。
		/// </summary>
		/// <param name="oldChar">
		/// 置換対象の文字
		/// </param>
		/// <param name="newChar">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String replaced(const value_type oldChar, const value_type newChar) const &
		{
			return String(*this).replace(oldChar, newChar);
		}

		/// <summary>
		/// 指定した文字を置換した新しい文字列を返します。
		/// </summary>
		/// <param name="oldChar">
		/// 置換対象の文字
		/// </param>
		/// <param name="newChar">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String replaced(const value_type oldChar, const value_type newChar) &&
		{
			replace(oldChar, newChar);

			return std::move(*this);
		}

		/// <summary>
		/// 指定した文字列を置換した新しい文字列を返します。
		/// </summary>
		/// <param name="oldStr">
		/// 置換対象の文字列
		/// </param>
		/// <param name="newChar">
		/// 置換後の文字列
		/// </param>
		/// <returns>
		/// 新しい文字列
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

		/// <summary>
		/// 指定した条件を満たす文字を別の文字に置き換えます。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <param name="newChar">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		String& replace_if(Fty f, const value_type newChar)
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

		/// <summary>
		/// 指定した条件を満たす文字を別の文字に置き換えます。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <param name="newChar">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		String replaced_if(Fty f, const value_type newChar) const &&
		{
			return String(*this).replace_if(f, newChar);
		}

		/// <summary>
		/// 指定した条件を満たす文字を別の文字に置き換えた新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <param name="newChar">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// 指定した条件を満たす文字を別の文字に置き換えた新しい文字列
		/// </returns>
		template <class Fty>
		String replaced_if(Fty f, const value_type newChar) &
		{
			replace_if(f, newChar);

			return std::move(*this);
		}

		/// <summary>
		/// 文字列を反転します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 反転した文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String reversed() &&
		{
			reverse();

			return *this;
		}

		/// <summary>
		/// 文字列の各文字への参照を引数に、末尾の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		String& reverse_each(Fty f)
		{
			for (auto it = m_string.rbegin(); it != m_string.rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		/// <summary>
		/// 文字列の各文字への参照を引数に、末尾の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		const String& reverse_each(Fty f) const
		{
			for (auto it = m_string.rbegin(); it != m_string.rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		/// <summary>
		/// 文字列の各文字の位置をシフトさせ、はみ出た文字は反対側に挿入します。
		/// </summary>
		/// <param name="count">
		/// 文字をシフトする数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 文字列の各文字の位置をシフトさせ、はみ出た文字を反対側に挿入した新しい文字列を返します。
		/// </summary>
		/// <param name="count">
		/// 文字をシフトする数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String rotated(const std::ptrdiff_t count = 1) const &
		{
			return String(*this).rotate(count);
		}

		/// <summary>
		/// 文字列の各文字の位置をシフトさせ、はみ出た文字を反対側に挿入した新しい文字列を返します。
		/// </summary>
		/// <param name="count">
		/// 文字をシフトする数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String rotated(const std::ptrdiff_t count = 1) &&
		{
			rotate(count);

			return std::move(*this);
		}

		/// <summary>
		/// 文字列を指定された文字で右詰めします。
		/// </summary>
		/// <param name="length">
		/// 右詰めした後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 右詰め用の埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、変更は行われません。
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& rpad(const size_t length, const value_type fillChar = value_type(' '))
		{
			if (length <= m_string.length())
			{
				return *this;
			}

			m_string.append(length - m_string.length(), fillChar);

			return *this;
		}

		/// <summary>
		/// 文字列を指定された文字で右詰めした新しい文字列を返します。
		/// </summary>
		/// <param name="length">
		/// 右詰めした後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 右詰め用の埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、元の文字列のコピーが返ります。 
		/// </remarks>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String rpadded(const size_t length, const value_type fillChar = value_type(' ')) const &
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

		/// <summary>
		/// 文字列を指定された文字で右詰めした新しい文字列を返します。
		/// </summary>
		/// <param name="length">
		/// 右詰めした後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 右詰め用の埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、元の文字列のコピーが返ります。 
		/// </remarks>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String rpadded(const size_t length, const value_type fillChar = value_type(' ')) &&
		{
			rpad(length, fillChar);

			return std::move(*this);
		}

		/// <summary>
		/// 文字列の末尾にある空白文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& rtrim()
		{
			m_string.erase(std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base(), m_string.end());

			return *this;
		}

		/// <summary>
		/// 文字列の末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String rtrimmed() const &
		{
			return String(m_string.begin(), std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base());
		}

		/// <summary>
		/// 文字列の末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String rtrimmed() &&
		{
			rtrim();

			return std::move(*this);
		}

		/// <summary>
		/// 文字列をランダムに並び替えます。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& shuffle()
		{
			return shuffle(GetDefaultRNG());
		}

		/// <summary>
		/// 指定された乱数生成器を使って文字列をランダムに並び替えます。
		/// </summary>
		/// <param name="rbg">
		/// 使用する乱数生成器
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class URBG>
		String& shuffle(URBG&& rbg)
		{
			std::shuffle(m_string.begin(), m_string.end(), std::forward<URBG>(rbg));

			return *this;
		}

		/// <summary>
		/// ランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String shuffled() const &
		{
			return shuffled(GetDefaultRNG());
		}

		/// <summary>
		/// ランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// ランダムに並び替えられた文字列
		/// </returns>
		String shuffled() &&
		{
			return shuffled(GetDefaultRNG());
		}

		/// <summary>
		/// 指定された乱数生成器を使ってランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <param name="rbg">
		/// 使用する乱数生成器
		/// </param>
		/// <returns>
		/// ランダムに並び替えられた文字列
		/// </returns>
		template <class URBG>
		String shuffled(URBG&& rbg) const &
		{
			return String(*this).shuffle(std::forward<URBG>(rbg));
		}

		/// <summary>
		/// 指定された乱数生成器を使ってランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <param name="rbg">
		/// 使用する乱数生成器
		/// </param>
		/// <returns>
		/// ランダムに並び替えられた文字列
		/// </returns>
		template <class URBG>
		String shuffled(URBG&& rbg) &&
		{
			std::shuffle(m_string.begin(), m_string.end(), std::forward<URBG>(rbg));

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
		Array<String, std::allocator<String>> split(value_type ch) const;

		std::pair<String, String> split_at(const size_t pos) const
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
		bool starts_with(const value_type ch) const
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
		bool starts_with(const StringView str) const;

		/// <summary>
		/// 英字の大文字と小文字を入れ替えます。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 英字の大文字と小文字を入れ替えた文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String swapcased() &&
		{
			swapcase();

			return std::move(*this);
		}

		/// <summary>
		/// 文字列の先頭と末尾にある空白文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& trim()
		{
			m_string.erase(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable));

			m_string.erase(std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base(), m_string.end());

			return *this;
		}

		/// <summary>
		/// 文字列の先頭と末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String trimmed() const &
		{
			return String(std::find_if_not(m_string.begin(), m_string.end(), detail::IsTrimmable), std::find_if_not(m_string.rbegin(), m_string.rend(), detail::IsTrimmable).base());
		}

		/// <summary>
		/// 文字列の先頭と末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String trimmed() &&
		{
			trim();

			return std::move(*this);
		}

		/// <summary>
		/// 英字をすべて大文字にします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
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

		/// <summary>
		/// 英字をすべて大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String uppercased() &&
		{
			uppercase();

			return std::move(*this);
		}

		/// <summary>
		/// 文字列を UTF8 の std::string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF8 でエンコードされた std::string
		/// </returns>
		std::string toUTF8() const;

		/// <summary>
		/// 文字列を UTF16 の std::u16string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF16 でエンコードされた std::u16string
		/// </returns>
		std::u16string toUTF16() const;

		/// <summary>
		/// 文字列を UTF32 の std::u32string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF32 でエンコードされた std::u32string
		/// </returns>
		std::u32string toUTF32() const;

		/// <summary>
		/// 文字列を辞書順でソートします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& sort()
		{
			std::sort(m_string.begin(), m_string.end());

			return *this;
		}

		/// <summary>
		/// 文字列を指定された比較関数でソートします。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty>
		String& sort_by(Fty f)
		{
			std::sort(m_string.begin(), m_string.end(), f);

			return *this;
		}

		/// <summary>
		/// 文字列を辞書順でソートした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		String sorted() const &
		{
			return String(*this).sort();
		}

		/// <summary>
		/// 文字列を辞書順でソートした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		String sorted() &&
		{
			std::sort(m_string.begin(), m_string.end());

			return std::move(*this);
		}

		/// <summary>
		/// 文字列を指定された比較関数でソートした新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		template <class Fty>
		String sorted_by(Fty f) const &
		{
			return String(*this).sort_by(f);
		}

		/// <summary>
		/// 文字列を指定された比較関数でソートした新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		template <class Fty>
		String sorted_by(Fty f) &&
		{
			std::sort(m_string.begin(), m_string.end(), f);

			return std::move(*this);
		}

		/// <summary>
		/// 文字列の先頭から指定された文字数分取り出した新しい文字列を返します。
		/// </summary>
		/// <param name="n">
		/// 取り出す文字数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String take(size_t n) const
		{
			return String(m_string.begin(), m_string.begin() + std::min(n, m_string.size()));
		}

		/// <summary>
		/// 文字列の先頭から、指定された条件を満たす連続した文字を取り出した新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		template <class Fty>
		String take_while(Fty f) const
		{
			return String(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), f));
		}

		/// <summary>
		/// 文字列をソートし、重複する文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& unique()
		{
			sort();

			m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

			return *this;
		}

		/// <summary>
		/// 文字列をソートし、重複する文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String uniqued() const &
		{
			return String(*this).unique();
		}

		/// <summary>
		/// 文字列をソートし、重複する文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		String uniqued() &&
		{
			sort();

			m_string.erase(std::unique(m_string.begin(), m_string.end()), m_string.end());

			m_string.shrink_to_fit();

			return std::move(*this);
		}

		/// <summary>
		/// 複数のインデックスを取り、それらの文字からなる新しい文字列を返します。
		/// </summary>
		/// <param name="indices">
		/// 現在の文字列における複数のインデックス
		/// </param>
		/// <example><code>
		/// String("abcde").values_at({0, 3, 4}); // => "ade"
		/// </code></example>
		/// <returns>
		/// 新しい文字列
		/// </returns>
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

		/// <summary>
		/// 文字列に XML エスケープを行います。
		/// </summary>
		/// <remarks>
		/// &quot;, \, &amp;, &gt;, &lt; をエスケープ文字に置換します
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
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
				case value_type('\"'):
					new_string.append(S3DSTR("&quot;"), 6);
					break;
				case value_type('&'):
					new_string.append(S3DSTR("&amp;"), 5);
					break;
				case value_type('\''):
					new_string.append(S3DSTR("&apos;"), 6);
					break;
				case value_type('<'):
					new_string.append(S3DSTR("&lt;"), 4);
					break;
				case value_type('>'):
					new_string.append(S3DSTR("&gt;"), 4);
					break;
				default:
					new_string.push_back(v);
					break;
				}
			}

			return new_string;
		}
	};

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

	inline String operator +(const String::value_type* lhs, const String& rhs)
	{
		return lhs + rhs.str();
	}

	inline String operator +(const String::value_type lhs, const String& rhs)
	{
		return lhs + rhs.str();
	}

	inline String operator +(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() + rhs;
	}

	inline String operator +(const String& lhs, const String::value_type rhs)
	{
		return lhs.str() + rhs;
	}

	inline bool operator ==(const String::value_type* lhs, const String& rhs)
	{
		return lhs == rhs.str();
	}

	inline bool operator ==(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() == rhs;
	}

	inline bool operator !=(const String::value_type* lhs, const String& rhs)
	{
		return lhs != rhs.str();
	}

	inline bool operator !=(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() != rhs;
	}

	inline bool operator <(const String::value_type* lhs, const String& rhs)
	{
		return lhs < rhs.str();
	}

	inline bool operator <(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() < rhs;
	}

	inline bool operator >(const String::value_type* lhs, const String& rhs)
	{
		return lhs > rhs.str();
	}

	inline bool operator >(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() > rhs;
	}

	inline bool operator <=(const String::value_type* lhs, const String& rhs)
	{
		return lhs <= rhs.str();
	}

	inline bool operator <=(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() <= rhs;
	}

	inline bool operator >=(const String::value_type* lhs, const String& rhs)
	{
		return lhs >= rhs.str();
	}

	inline bool operator >=(const String& lhs, const String::value_type* rhs)
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
		size_t operator()(const s3d::String& keyVal) const
		{
			return hash<s3d::String::string_type>()(keyVal.str());
		}
	};
}

# include "CharacterSet.hpp"

namespace s3d
{
	inline size_t String::num_codePoints() const
	{
		return CharacterSet::CountCodePoints(*this);
	}

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

	inline String String::removed(const StringView str) const
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

	inline bool String::starts_with(const StringView str) const
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

	inline std::istream& operator >>(std::istream& input, String& str)
	{
		std::string t;
		input >> t;
		str = CharacterSet::Widen(t);
		return input;
	}

	inline std::ostream& operator <<(std::ostream& os, const StringView str)
	{
		return os << CharacterSet::Narrow(str);
	}

	template <>
	struct FNV1aHash<String>
	{
		size_t operator()(const String& keyVal) const
		{
			return Hash::FNV1a(keyVal);
		}
	};

	template <>
	struct Murmur2Hash<String>
	{
		size_t operator()(const String& keyVal) const
		{
			return Hash::Murmur2(keyVal);
		}
	};

	using FilePath = String;

# if defined(SIV3D_TARGET_WINDOWS)

	using U32String = std::u32string;

# else

	using U32String = String;

# endif	
}
