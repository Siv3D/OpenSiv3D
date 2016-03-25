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
# include <string>
# include <iostream>
# include "Fwd.hpp"

namespace s3d
{
	class String
	{
	private:

		std::wstring m_string;

	public:

		using string_type				= std::wstring;
		using traits_type				= string_type::traits_type;
		using allocator_type			= string_type::allocator_type;
		using value_type				= string_type::value_type;
		using size_type					= string_type::size_type;
		using difference_type			= string_type::difference_type;
		using pointer					= string_type::pointer;
		using const_pointer				= string_type::const_pointer;
		using reference					= string_type::reference;
		using const_reference			= string_type::const_reference;
		using iterator					= string_type::iterator;
		using const_iterator			= string_type::const_iterator;
		using reverse_iterator			= string_type::reverse_iterator;
		using const_reverse_iterator	= string_type::const_reverse_iterator;

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
		size_t indexOf(const String& str, size_t offset = 0) const
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
	};

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
	inline std::wistream& operator >> (std::wistream& input, String& str)
	{
		return input >> str.str();
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
	inline std::wostream& operator << (std::wostream& output, const String& str)
	{
		return output << str.str();
	}

	inline String operator + (const String& lhs, const String& rhs)
	{
		return lhs.str() + rhs.str();
	}

	inline String operator + (const wchar* lhs, const String& rhs)
	{
		return lhs + rhs.str();
	}

	inline String operator + (const wchar lhs, const String& rhs)
	{
		return lhs + rhs.str();
	}

	inline String operator + (const String& lhs, const wchar* rhs)
	{
		return lhs.str() + rhs;
	}

	inline String operator + (const String& lhs, const wchar rhs)
	{
		return lhs.str() + rhs;
	}

	inline bool operator == (const wchar* lhs, const String& rhs)
	{
		return lhs == rhs.str();
	}

	inline bool operator == (const String& lhs, const wchar* rhs)
	{
		return lhs.str() == rhs;
	}

	inline bool operator != (const wchar* lhs, const String& rhs)
	{
		return lhs != rhs.str();
	}

	inline bool operator != (const String& lhs, const wchar* rhs)
	{
		return lhs.str() != rhs;
	}

	inline bool operator < (const wchar* lhs, const String& rhs)
	{
		return lhs < rhs.str();
	}

	inline bool operator < (const String& lhs, const wchar* rhs)
	{
		return lhs.str() < rhs;
	}

	inline bool operator > (const wchar* lhs, const String& rhs)
	{
		return lhs > rhs.str();
	}

	inline bool operator > (const String& lhs, const wchar* rhs)
	{
		return lhs.str() > rhs;
	}

	inline bool operator <= (const wchar* lhs, const String& rhs)
	{
		return lhs <= rhs.str();
	}

	inline bool operator <= (const String& lhs, const wchar* rhs)
	{
		return lhs.str() <= rhs;
	}

	inline bool operator >= (const wchar* lhs, const String& rhs)
	{
		return lhs >= rhs.str();
	}

	inline bool operator >= (const String& lhs, const wchar* rhs)
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
