//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <string>
# include <cwctype>
# include "Fwd.hpp"
# include "Char.hpp"
# include "StringView.hpp"
# include "Functor.hpp"

namespace s3d
{
	class String
	{
	public:
		
		using string_type				= std::u32string;
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

	private:

		string_type m_string;

	public:

		static constexpr size_type npos = size_type{ static_cast<size_type>(-1) };
		
		/// <summary>
		/// default constructor
		/// </summary>
		String() = default;

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="text">
		/// コピーする文字列
		/// </param>
		String(const String& text)
			: m_string(text.m_string) {}

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="text">
		/// コピーする文字列
		/// </param>
		String(const string_type& text)
			: m_string(text) {}

		String(const String& text, size_type pos)
			: m_string(text.m_string, pos) {}

		String(const String& text, size_type pos, size_type count)
			: m_string(text.m_string, pos, count) {}

		String(const value_type* text)
			: m_string(text) {}

		String(const value_type* text, size_type count)
			: m_string(text, count) {}

		String(std::initializer_list<value_type> ilist)
			: m_string(ilist) {}

		String(size_t count, value_type ch)
			: m_string(count, ch) {}

		template <class Iterator>
		String(Iterator first, Iterator last)
			: m_string(first, last) {}

		String(String&& text) noexcept
			: m_string(std::move(text.m_string)) {}

		String(string_type&& text) noexcept
			: m_string(std::move(text)) {}

		explicit String(StringView view)
			: m_string(view.begin(), view.end()) {}

		operator StringView() const noexcept
		{
			return StringView(m_string.data(), m_string.size());
		}

		String& operator =(const String& text)
		{
			return assign(text);
		}

		String& operator =(const string_type& text)
		{
			return assign(text);
		}

		String& operator =(String&& text) noexcept
		{
			return assign(std::move(text));
		}

		String& operator =(string_type&& text) noexcept
		{
			return assign(std::move(text));
		}

		String& operator =(const value_type* text)
		{
			return assign(text);
		}

		String& operator =(std::initializer_list<value_type> ilist)
		{
			return assign(ilist);
		}

		String& operator =(StringView view)
		{
			return assign(view);
		}

		String& operator <<(value_type ch)
		{
			m_string.push_back(ch);

			return *this;
		}

		String& assign(const String& text);

		String& assign(const string_type& text);

		String& assign(const value_type* text);

		String& assign(size_t count, value_type ch);

		String& assign(String&& text) noexcept;

		String& assign(string_type&& text) noexcept;

		String& assign(std::initializer_list<value_type> ilist);

		String& assign(StringView view);

		template <class Iterator>
		String& assign(Iterator first, Iterator last)
		{
			m_string.assign(first, last);

			return *this;
		}

		String& operator +=(const String& text)
		{
			return append(text);
		}

		String& operator +=(const string_type& text)
		{
			return append(text);
		}

		String& operator +=(const value_type ch)
		{
			return append(ch);
		}

		String& operator +=(const value_type* text)
		{
			return append(text);
		}

		String& operator +=(std::initializer_list<value_type> ilist)
		{
			return append(ilist);
		}

		String& operator +=(StringView view)
		{
			return append(view);
		}

		String& append(const String& text);

		String& append(const string_type& text);

		String& append(const value_type ch);

		String& append(const value_type* text);

		String& append(const value_type* text, size_t count);

		String& append(std::initializer_list<value_type> ilist);

		String& append(size_t count, value_type ch);

		String& append(StringView view);

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
		/// <param name="text">
		/// 挿入する文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& insert(size_t offset, const String& text);

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
		String& insert(size_t offset, std::initializer_list<value_type> ilist);

		/// <summary>
		/// 指定した位置に文字列を挿入します。
		/// </summary>
		/// <param name="offset">
		/// 挿入する位置
		/// </param>
		/// <param name="text">
		/// 挿入する文字列
		/// </param>
		/// <remarks>
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& insert(size_t offset, const value_type* text);

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
		String& insert(size_t offset, size_t count, value_type ch);

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
		iterator insert(const_iterator where, value_type ch);

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
		void insert(const_iterator where, size_t count, value_type ch);

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
		String& erase(size_t offset = 0, size_t count = npos);

		/// <summary>
		/// 指定した位置の文字を削除します。
		/// </summary>
		/// <param name="where">
		/// 削除する位置
		/// </param>
		/// <returns>
		/// 削除した直後の位置へのイテレータ
		/// </returns>
		iterator erase(const_iterator where);

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
		iterator erase(const_iterator first, const_iterator last);

		/// <summary>
		/// 文字列を消去し、空の文字列にします。
		/// </summary>
		/// <remarks>
		/// メモリを解放したい場合は shrink_to_fit() を呼びます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void clear() noexcept;

		/// <summary>
		/// 文字列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] iterator begin() noexcept
		{
			return m_string.begin();
		}

		/// <summary>
		/// 文字列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator begin() const noexcept
		{
			return m_string.begin();
		}

		/// <summary>
		/// 文字列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator cbegin() const noexcept
		{
			return m_string.cbegin();
		}

		/// <summary>
		/// 文字列の終了位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] iterator end() noexcept
		{
			return m_string.end();
		}

		/// <summary>
		/// 文字列の終了位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator end() const noexcept
		{
			return m_string.end();
		}

		/// <summary>
		/// 文字列の終了位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator cend() const noexcept
		{
			return m_string.cend();
		}

		/// <summary>
		/// 文字列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の末尾のリバースイテレータ
		/// </returns>
		[[nodiscard]] reverse_iterator rbegin() noexcept
		{
			return m_string.rbegin();
		}

		/// <summary>
		/// 文字列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の末尾のリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept
		{
			return m_string.rbegin();
		}

		/// <summary>
		/// 文字列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の末尾のリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept
		{
			return m_string.crbegin();
		}

		/// <summary>
		/// 文字列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] reverse_iterator rend() noexcept
		{
			return m_string.rend();
		}

		/// <summary>
		/// 文字列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator rend() const noexcept
		{
			return m_string.rend();
		}

		/// <summary>
		/// 文字列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator crend() const noexcept
		{
			return m_string.crend();
		}

		/// <summary>
		/// 文字列の不要なメモリを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void shrink_to_fit();

		/// <summary>
		/// 文字列を消去し、メモリを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release();

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
		[[nodiscard]] value_type& at(size_t offset) &
		{
			return m_string.at(offset);
		}

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
		[[nodiscard]] const value_type& at(size_t offset) const &
		{
			return m_string.at(offset);
		}

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
		[[nodiscard]] value_type at(size_t offset) &&
		{
			return m_string.at(offset);
		}

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		[[nodiscard]] value_type& operator[](size_t offset) &
		{
			return m_string[offset];
		}

		/// <summary>
		/// 指定した位置の文字への参照を返します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		[[nodiscard]] const value_type& operator[](size_t offset) const &
		{
			return m_string[offset];
		}

		/// <summary>
		/// 指定した位置の文字を取得します。
		/// </summary>
		/// <param name="offset">
		/// 位置
		/// </param>
		/// <returns>
		/// 指定した位置の文字への参照
		/// </returns>
		[[nodiscard]] value_type operator[](size_t offset) &&
		{
			return std::move(m_string[offset]);
		}

		/// <summary>
		/// 先頭に文字を追加します。
		/// </summary>
		/// <param name="value">
		/// 追加する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_front(value_type ch)
		{
			insert(begin(), ch);
		}

		/// <summary>
		/// 末尾に文字を追加します。
		/// </summary>
		/// <param name="ch">
		/// 追加する文字
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_back(value_type ch)
		{
			m_string.push_back(ch);
		}

		/// <summary>
		/// 先頭の文字を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pop_front()
		{
			m_string.erase(m_string.begin());
		}

		/// <summary>
		/// 末尾の文字を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pop_back()
		{
			m_string.pop_back();
		}

		/// <summary>
		/// 先頭の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 先頭の文字への参照
		/// </returns>
		[[nodiscard]] value_type& front()
		{
			return m_string.front();
		}

		/// <summary>
		/// 先頭の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 先頭の文字への参照
		/// </returns>
		[[nodiscard]] const value_type& front() const
		{
			return m_string.front();
		}

		/// <summary>
		/// 末尾の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 末尾の文字への参照
		/// </returns>
		[[nodiscard]] value_type& back()
		{
			return m_string.back();
		}

		/// <summary>
		/// 末尾の文字への参照を返します。
		/// </summary>
		/// <returns>
		/// 末尾の文字への参照
		/// </returns>
		[[nodiscard]] const value_type& back() const
		{
			return m_string.back();
		}

		/// <summary>
		/// C スタイル文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// C スタイル文字列の先頭のポインタ
		/// </returns>
		[[nodiscard]] const value_type* c_str() const noexcept
		{
			return m_string.c_str();
		}

		/// <summary>
		/// 文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭へのポインタ
		/// </returns>
		[[nodiscard]] const value_type* data() const noexcept
		{
			return m_string.data();
		}

		/// <summary>
		/// 文字列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 文字列の先頭へのポインタ
		/// </returns>
		[[nodiscard]] value_type* data() noexcept
		{
			return m_string.data();
		}

		/// <summary>
		/// wstring 型の内部データの参照を返します。
		/// </summary>
		/// <returns>
		/// wstring 型の内部データの参照
		/// </returns>
		[[nodiscard]] string_type& str()
		{
			return m_string;
		}

		/// <summary>
		/// wstring 型の内部データの参照を返します。
		/// </summary>
		/// <returns>
		/// wstring 型の内部データの参照
		/// </returns>
		[[nodiscard]] const string_type& str() const noexcept
		{
			return m_string;
		}

		/// <summary>
		/// 文字列の長さを示します。
		/// </summary>
		/// <remarks>
		/// 終端の '\0' を含みません。
		/// </remarks>
		[[nodiscard]] size_t length() const noexcept
		{
			return m_string.length();
		}

		/// <summary>
		/// 文字列の長さを示します。
		/// </summary>
		/// <remarks>
		/// 終端の '\0' を含みません。
		/// </remarks>
		[[nodiscard]] size_t size() const noexcept
		{
			return m_string.size();
		}

		[[nodiscard]] size_t size_bytes() const noexcept
		{
			return m_string.size() * sizeof(value_type);
		}

		/// <summary>
		/// 空の文字列であるかを示します。
		/// </summary>
		[[nodiscard]] bool empty() const noexcept
		{
			return m_string.empty();
		}

		/// <summary>
		/// 空の文字列であるかを示します。
		/// </summary>
		[[nodiscard]] bool isEmpty() const noexcept
		{
			return m_string.empty();
		}

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
		[[nodiscard]] size_t maxSize() const noexcept
		{
			return m_string.max_size();
		}

		/// <summary>
		/// メモリを再確保せずに持てる文字列の長さを示します。
		/// </summary>
		[[nodiscard]] size_t capacity() const noexcept
		{
			return m_string.capacity();
		}

		/// <summary>
		/// 文字列のサイズを変更します。
		/// </summary>
		/// <param name="newSize">
		/// 新しいサイズ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_t newSize);

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
		void resize(size_t newSize, value_type ch);

		/// <summary>
		/// 文字列用のメモリを指定したサイズで確保します。
		/// </summary>
		/// <param name="newCapacity">
		/// 確保する文字列のサイズ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reserve(size_t newCapacity);

		/// <summary>
		/// 文字列を別の文字列と交換します。
		/// </summary>
		/// <param name="text">
		/// 交換する文字列
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(String& text) noexcept
		{
			m_string.swap(text.m_string);
		}

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
		[[nodiscard]] String substr(size_t offset = 0, size_t count = npos) const;

		/// <summary>
		/// 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="text">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]] size_t indexOf(const String& text, size_t offset = 0) const noexcept;

		/// <summary>
		/// 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="text">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <remarks>
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]] size_t indexOf(const value_type* text, size_t offset = 0) const;

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
		[[nodiscard]] size_t indexOf(value_type ch, size_t offset = 0) const;

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
		[[nodiscard]] size_t indexOfNot(value_type ch, size_t offset = 0) const;

		/// <summary>
		/// 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="text">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]] size_t lastIndexOf(const String& text, size_t offset = npos) const;

		/// <summary>
		/// 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="text">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <remarks>
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]] size_t lastIndexOf(const value_type* text, size_t offset = npos) const;

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
		[[nodiscard]] size_t lastIndexOf(value_type ch, size_t offset = npos) const;

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
		[[nodiscard]] size_t lastIndexNotOf(value_type ch, size_t offset = npos) const;

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
		[[nodiscard]] size_t indexOfAny(const String& anyof, size_t offset = 0) const;

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
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]] size_t indexOfAny(const value_type* anyof, size_t offset = 0) const;

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
		[[nodiscard]] size_t lastIndexOfAny(const String& anyof, size_t offset = npos) const;

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
		/// anyof は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]] size_t lastIndexOfAny(const value_type* anyof, size_t offset = npos) const;

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
		[[nodiscard]] size_t indexNotOfAny(const String& anyof, size_t offset = 0) const;

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
		/// anyof は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]] size_t indexNotOfAny(const value_type* anyof, size_t offset = 0) const;

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
		[[nodiscard]] size_t lastIndexNotOfAny(const String& anyof, size_t offset = npos) const;

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
		/// anyof は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]] size_t lastIndexNotOfAny(const value_type* anyof, size_t offset = npos) const;

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]] int32 compare(const String& text) const noexcept
		{
			return m_string.compare(text.m_string);
		}

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]] int32 compare(StringView view) const noexcept
		{
			return m_string.compare(std::u32string_view(view.data(), view.size()));
		}

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <remarks>
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]] int32 compare(const value_type* text) const
		{
			return m_string.compare(text);
		}

		/// <summary>
		/// 英字の大小を無視して文字列の大小を比較します。
		/// </summary>
		/// <param name="view">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]] int32 case_insensitive_compare(StringView view) const noexcept;

		/// <summary>
		/// 英字の大小を無視して文字列を比較します。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 英字の大小を無視した時に文字列が等しい場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool case_insensitive_equals(StringView view) const noexcept;

		/// <summary>
		/// 文字列が等しいかを調べます。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 等しければ true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator ==(const String& text) const
		{
			return m_string == text.m_string;
		}

		/// <summary>
		/// 文字列が等しくないかを調べます。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 等しくなければ true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator !=(const String& text) const
		{
			return m_string != text.m_string;
		}

		/// <summary>
		/// 文字列の &lt; 比較を行います。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		[[nodiscard]] bool operator <(const String& text) const
		{
			return m_string < text.m_string;
		}

		/// <summary>
		/// 文字列の &gt; 比較を行います。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		[[nodiscard]] bool operator >(const String& text) const
		{
			return m_string > text.m_string;
		}

		/// <summary>
		/// 文字列の &lt;= 比較を行います。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		[[nodiscard]] bool operator <=(const String& text) const
		{
			return m_string <= text.m_string;
		}

		/// <summary>
		/// 文字列の &gt;= 比較を行います。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果
		/// </returns>
		[[nodiscard]] bool operator >=(const String& text) const
		{
			return m_string >= text.m_string;
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
		[[nodiscard]] bool all(Fty f = Id) const
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
		[[nodiscard]] bool any(Fty f = Id) const
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
		String& capitalize() noexcept;

		/// <summary>
		/// 最初に登場する英字を大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String capitalized() const &;

		/// <summary>
		/// 最初に登場する英字を大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String capitalized() && ;

		/// <summary>
		/// 文字列の長さを返します。
		/// </summary>
		/// <remarks>
		/// 絵文字などが使用されている場合、必ずしも見かけ上の文字数と一致しない事に注意してください。
		/// </remarks>
		/// <returns>
		/// 文字列の長さ
		/// </returns>
		[[nodiscard]] size_t count() const noexcept
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
		[[nodiscard]] size_t count(value_type ch) const noexcept;

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
		[[nodiscard]] size_t count(StringView view) const;

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
		[[nodiscard]] size_t count_if(Fty f) const
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
		[[nodiscard]] String drop(size_t n) const;

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
		[[nodiscard]] String drop_while(Fty f) const
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
		[[nodiscard]] bool ends_with(value_type ch) const noexcept;

		/// <summary>
		/// 指定した文字列で終わるかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <returns>
		/// 指定した文字列で終わる場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool ends_with(StringView view) const;

		/// <summary>
		/// タブ文字を半角空白に置換した文字列を返します。
		/// </summary>
		/// <param name="tabSize">
		/// タブ置換後の半角空白の数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String expand_tabs(size_t tabSize = 4) const;

		/// <summary>
		/// 指定した位置の文字を返します。指定されたインデックスが存在しない場合はデフォルト値を返します。
		/// </summary>
		/// <param name="index">
		/// 位置
		/// </param>
		/// <param name="defaultValue">
		/// インデックスが存在しない場合に返されるデフォルト値
		/// </param>
		/// <returns>
		/// 指定した位置の文字、もしくはデフォルト値
		/// </returns>
		[[nodiscard]] value_type fetch(size_t index, value_type defaultValue) const noexcept;

		/// <summary>
		/// 文字列のサイズを変えずに、全文字を指定された文字で置換します。
		/// </summary>
		/// <param name="value">
		/// 置換後の文字
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& fill(value_type value);

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
		[[nodiscard]] String filter(Fty f) const
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
		[[nodiscard]] bool includes(value_type ch) const;

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
		[[nodiscard]] bool includes(const value_type* str) const;

		/// <summary>
		/// 指定した文字列が含まれているかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <returns>
		/// 検索した文字列が見つかった場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool includes(const String& str) const;

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
		[[nodiscard]] bool includes_if(Fty f) const
		{
			return any(f);
		}

		String& keep_if(std::function<bool(value_type)> f);

		/// <summary>
		/// 指定した 1 行の文字数で改行するようにした新しい文字列を返します。
		/// </summary>
		/// <param name="width">
		/// 1 行の文字数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String layout(size_t width) const;

		/// <summary>
		/// 英字をすべて小文字にします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& lowercase() noexcept;

		/// <summary>
		/// 英字をすべて小文字にした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String lowercased() const &;

		/// <summary>
		/// 英字をすべて小文字にした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String lowercased() && ;

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
		String& lpad(size_t length, value_type fillChar = U' ');

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
		[[nodiscard]] String lpadded(size_t length, value_type fillChar = U' ') const &;

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
		[[nodiscard]] String lpadded(size_t length, value_type fillChar = U' ') &&;

		/// <summary>
		/// 文字列の先頭にある空白文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& ltrim();

		/// <summary>
		/// 文字列の先頭にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String ltrimmed() const &;

		/// <summary>
		/// 文字列の先頭にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String ltrimmed() && ;

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
		[[nodiscard]] std::string narrow() const;

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
		[[nodiscard]] bool none(Fty f = Id) const
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
		String& remove(value_type ch);

		/// <summary>
		/// 指定した文字列をもとの文字列から削除します。
		/// </summary>
		/// <param name="view">
		/// 削除する文字列
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& remove(StringView view);

		/// <summary>
		/// 指定した文字を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="ch">
		/// 除去対象の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String removed(value_type ch) const &;

		/// <summary>
		/// 指定した文字を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="ch">
		/// 除去対象の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String removed(value_type ch) &&;

		/// <summary>
		/// 指定した文字列を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="str">
		/// 除去対象の文字列
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String removed(StringView view) const;

		/// <summary>
		/// 指定したインデックスの文字を文字列から削除します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		String& remove_at(size_t index);

		/// <summary>
		/// 指定したインデックスの文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String removed_at(size_t index) const &;

		/// <summary>
		/// 指定したインデックスの文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String removed_at(size_t index) &&;

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
		[[nodiscard]] String removed_if(Fty f) const &
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
		[[nodiscard]] String removed_if(Fty f) &&
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
		String& replace(value_type oldChar, value_type newChar);

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
		String& replace(const String& oldStr, const String& newStr);

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
		[[nodiscard]] String replaced(value_type oldChar, value_type newChar) const &;

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
		[[nodiscard]] String replaced(value_type oldChar, value_type newChar) &&;

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
		[[nodiscard]] String replaced(const String& oldStr, const String& newStr) const;

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
		[[nodiscard]] String replaced_if(Fty f, const value_type newChar) const &&
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
		[[nodiscard]] String replaced_if(Fty f, const value_type newChar) &
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
		String& reverse();

		/// <summary>
		/// 反転した文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String reversed() const &;

		/// <summary>
		/// 反転した文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String reversed() &&;

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
		String& rotate(std::ptrdiff_t count = 1);

		/// <summary>
		/// 文字列の各文字の位置をシフトさせ、はみ出た文字を反対側に挿入した新しい文字列を返します。
		/// </summary>
		/// <param name="count">
		/// 文字をシフトする数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String rotated(std::ptrdiff_t count = 1) const &;

		/// <summary>
		/// 文字列の各文字の位置をシフトさせ、はみ出た文字を反対側に挿入した新しい文字列を返します。
		/// </summary>
		/// <param name="count">
		/// 文字をシフトする数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String rotated(std::ptrdiff_t count = 1) &&;

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
		String& rpad(size_t length, value_type fillChar = U' ');

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
		[[nodiscard]] String rpadded(size_t length, value_type fillChar = U' ') const &;

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
		[[nodiscard]] String rpadded(size_t length, value_type fillChar = U' ') &&;

		/// <summary>
		/// 文字列の末尾にある空白文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& rtrim();

		/// <summary>
		/// 文字列の末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String rtrimmed() const &;

		/// <summary>
		/// 文字列の末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String rtrimmed() &&;

		/// <summary>
		/// 文字列をランダムに並び替えます。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& shuffle();

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
		[[nodiscard]] String shuffled() const &;

		/// <summary>
		/// ランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// ランダムに並び替えられた文字列
		/// </returns>
		[[nodiscard]] String shuffled() &&;

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
		[[nodiscard]] String shuffled(URBG&& rbg) const &
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
		[[nodiscard]] String shuffled(URBG&& rbg) &&
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
		[[nodiscard]] Array<String, std::allocator<String>> split(value_type ch) const;

		[[nodiscard]] std::pair<String, String> split_at(size_t pos) const;

		[[nodiscard]] Array<String, std::allocator<String>> split_lines() const;

		/// <summary>
		/// 指定した文字から始まるかを調べます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 指定した文字から始まる場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool starts_with(value_type ch) const noexcept;

		/// <summary>
		/// 指定した文字列から始まるかを調べます。
		/// </summary>
		/// <param name="str">
		/// 検索する文字列
		/// </param>
		/// <returns>
		/// 指定した文字列から始まる場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool starts_with(StringView view) const;

		/// <summary>
		/// 英字の大文字と小文字を入れ替えます。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& swapcase() noexcept;

		/// <summary>
		/// 英字の大文字と小文字を入れ替えた文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String swapcased() const &;

		/// <summary>
		/// 英字の大文字と小文字を入れ替えた文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String swapcased() &&;

		/// <summary>
		/// 文字列の先頭と末尾にある空白文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& trim();

		/// <summary>
		/// 文字列の先頭と末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String trimmed() const &;

		/// <summary>
		/// 文字列の先頭と末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String trimmed() &&;

		/// <summary>
		/// 英字をすべて大文字にします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& uppercase() noexcept;

		/// <summary>
		/// 英字をすべて大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String uppercased() const &;

		/// <summary>
		/// 英字をすべて大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String uppercased() &&;

		/// <summary>
		/// 文字列を UTF8 の std::string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF8 でエンコードされた std::string
		/// </returns>
		[[nodiscard]] std::string toUTF8() const;

		/// <summary>
		/// 文字列を UTF16 の std::u16string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF16 でエンコードされた std::u16string
		/// </returns>
		[[nodiscard]] std::u16string toUTF16() const;

		/// <summary>
		/// 文字列を UTF32 の std::u32string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF32 でエンコードされた std::u32string
		/// </returns>
		[[nodiscard]] const std::u32string& toUTF32() const;

		/// <summary>
		/// 文字列を std::wstring にエンコードします。
		/// </summary>
		/// <returns>
		/// 変換された std::wstring
		/// </returns>
		[[nodiscard]] std::wstring toWstr() const;

		/// <summary>
		/// 文字列を辞書順でソートします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& sort();

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
		[[nodiscard]] String sorted() const &;

		/// <summary>
		/// 文字列を辞書順でソートした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		[[nodiscard]] String sorted() &&;

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
		[[nodiscard]] String sorted_by(Fty f) const &
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
		[[nodiscard]] String sorted_by(Fty f) &&
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
		[[nodiscard]] String take(size_t n) const;

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
		[[nodiscard]] String take_while(Fty f) const
		{
			return String(m_string.begin(), std::find_if_not(m_string.begin(), m_string.end(), f));
		}

		/// <summary>
		/// 文字列をソートし、重複する文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& unique();

		/// <summary>
		/// 文字列をソートし、重複する文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String uniqued() const &;

		/// <summary>
		/// 文字列をソートし、重複する文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String uniqued() &&;

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
		[[nodiscard]] String values_at(std::initializer_list<size_t> indices) const;

		/// <summary>
		/// 文字列に XML エスケープを行います。
		/// </summary>
		/// <remarks>
		/// &quot;, \, &amp;, &gt;, &lt; をエスケープ文字に置換します
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& xml_escape();

		/// <summary>
		/// XML エスケープした文字列を返します。
		/// </summary>
		/// <remarks>
		/// &quot;, \, &amp;, &gt;, &lt; をエスケープ文字に置換します
		/// </remarks>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]] String xml_escaped() const;
	};

	[[nodiscard]] inline String operator +(const String& lhs, const String& rhs)
	{
		return lhs.str() + rhs.str();
	}

	[[nodiscard]]inline String operator +(const String::value_type* lhs, const String& rhs)
	{
		return lhs + rhs.str();
	}

	[[nodiscard]]inline String operator +(const String::value_type lhs, const String& rhs)
	{
		return lhs + rhs.str();
	}

	[[nodiscard]]inline String operator +(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() + rhs;
	}

	[[nodiscard]]inline String operator +(const String& lhs, const String::value_type rhs)
	{
		return lhs.str() + rhs;
	}

	[[nodiscard]] inline String operator +(String&& lhs, const String& rhs)
	{
		return std::move(lhs.append(rhs));
	}

	[[nodiscard]] inline String operator +(const String& lhs, String&& rhs)
	{
		return std::move(rhs.insert(0, lhs));
	}

	[[nodiscard]] inline String operator +(String&& lhs, String&& rhs)
	{
		if (rhs.size() <= lhs.capacity() - lhs.size() || rhs.capacity() - rhs.size() < lhs.size())
		{
			return std::move(lhs.append(rhs));
		}
		else
		{
			return std::move(rhs.insert(0, lhs));
		}
	}

	[[nodiscard]]inline String operator +(const String::value_type* lhs, String&& rhs)
	{
		return std::move(rhs.insert(0, lhs));
	}

	[[nodiscard]]inline String operator +(const String::value_type lhs, String&& rhs)
	{
		rhs.push_front(lhs);

		return std::move(rhs);
	}

	[[nodiscard]]inline String operator +(String&& lhs, const String::value_type* rhs)
	{
		return std::move(lhs.append(rhs));
	}

	[[nodiscard]]inline String operator +(String&& lhs, const String::value_type rhs)
	{
		return std::move(lhs << rhs);
	}

	[[nodiscard]]inline bool operator ==(const String::value_type* lhs, const String& rhs)
	{
		return lhs == rhs.str();
	}

	[[nodiscard]]inline bool operator ==(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() == rhs;
	}

	[[nodiscard]]inline bool operator !=(const String::value_type* lhs, const String& rhs)
	{
		return lhs != rhs.str();
	}

	[[nodiscard]]inline bool operator !=(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() != rhs;
	}

	[[nodiscard]]inline bool operator <(const String::value_type* lhs, const String& rhs)
	{
		return lhs < rhs.str();
	}

	[[nodiscard]]inline bool operator <(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() < rhs;
	}

	[[nodiscard]]inline bool operator >(const String::value_type* lhs, const String& rhs)
	{
		return lhs > rhs.str();
	}

	[[nodiscard]]inline bool operator >(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() > rhs;
	}

	[[nodiscard]]inline bool operator <=(const String::value_type* lhs, const String& rhs)
	{
		return lhs <= rhs.str();
	}

	[[nodiscard]]inline bool operator <=(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() <= rhs;
	}

	[[nodiscard]]inline bool operator >=(const String::value_type* lhs, const String& rhs)
	{
		return lhs >= rhs.str();
	}

	[[nodiscard]]inline bool operator >=(const String& lhs, const String::value_type* rhs)
	{
		return lhs.str() >= rhs;
	}

	using FilePath = String;
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	std::ostream& operator <<(std::ostream& output, const String& value);

	std::wostream& operator <<(std::wostream& output, const String& value);

	std::istream& operator >>(std::istream& input, String& value);

	std::wistream& operator >>(std::wistream& input, String& value);
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::String>
	{
		[[nodiscard]] size_t operator()(const s3d::String& value) const noexcept
		{
			return s3d::Hash::FNV1a(s3d::ByteArrayView(value.data(), value.size_bytes()));
		}
	};
}

//////////////////////////////////////////////////
//
//	Swap
//
//////////////////////////////////////////////////

namespace std
{
	inline void swap(s3d::String& a, s3d::String& b) noexcept
	{
		a.swap(b);
	}
}
