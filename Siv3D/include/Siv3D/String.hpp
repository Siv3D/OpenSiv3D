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
# include "Types.hpp"
# include "Char.hpp"
# include "StringView.hpp"

namespace s3d
{
	class String
	{
	private:

		using string_type = std::u32string;

		string_type m_string;

	public:
		
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

		[[nodiscard]] size_t num_codePoints() const;

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
		[[nodiscard]] size_t indexOf(value_type ch, size_t offset) const;

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

	};
}
