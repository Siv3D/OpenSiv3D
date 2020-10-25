//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <string>
# include "Common.hpp"
# include "StringView.hpp"
# include "Unicode.hpp"
# include "Utility.hpp"

namespace s3d
{
	template <class Type, class Allocator> class Array;

	/// @brief 文字列
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

		template <class StringViewIsh>
		using IsStringViewIsh = std::enable_if_t<
			std::conjunction_v<std::is_convertible<const StringViewIsh&, StringView>,
			std::negation<std::is_convertible<const StringViewIsh&, const char32*>>>>;

		static constexpr size_type npos{ static_cast<size_type>(-1) };
		
		/// <summary>
		/// default constructor
		/// </summary>
		SIV3D_NODISCARD_CXX20
		String();

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="other">
		/// コピーする文字列
		/// </param>
		SIV3D_NODISCARD_CXX20
		String(const String& other);

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="s">
		/// コピーする文字列
		/// </param>
		SIV3D_NODISCARD_CXX20
		String(const string_type& s);

		SIV3D_NODISCARD_CXX20
		String(const String& other, size_type pos);

		SIV3D_NODISCARD_CXX20
		String(const String& other, size_type pos, size_type count);

		SIV3D_NODISCARD_CXX20
		String(const value_type* s);

		SIV3D_NODISCARD_CXX20
		String(const value_type* s, size_type count);

		SIV3D_NODISCARD_CXX20
		String(std::initializer_list<value_type> ilist);

		SIV3D_NODISCARD_CXX20
		String(size_t count, value_type ch);

		template <class Iterator>
		SIV3D_NODISCARD_CXX20
		String(Iterator first, Iterator last);

		SIV3D_NODISCARD_CXX20
		String(String&& other) noexcept;

		SIV3D_NODISCARD_CXX20
		String(string_type&& s) noexcept;

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		SIV3D_NODISCARD_CXX20
		explicit String(const StringViewIsh& s);

		operator StringView() const noexcept;

		String& operator =(const String& other);

		String& operator =(const string_type& s);

		String& operator =(String&& other) noexcept;

		String& operator =(string_type&& s) noexcept;

		String& operator =(const value_type* s);

		String& operator =(std::initializer_list<value_type> ilist);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& operator =(const StringViewIsh& s);

		String& assign(const String& s);

		String& assign(const string_type& s);

		String& assign(const value_type* s);

		String& assign(size_t count, value_type ch);

		String& assign(String&& s) noexcept;

		String& assign(string_type&& s) noexcept;

		String& assign(std::initializer_list<value_type> ilist);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& assign(const StringViewIsh& s);

		template <class Iterator>
		String& assign(Iterator first, Iterator last);
		
		[[nodiscard]]
		allocator_type get_allocator() const;

		String& operator <<(value_type ch);

		String& operator +=(const String& s);

		String& operator +=(const string_type& s);

		String& operator +=(value_type ch);

		String& operator +=(const value_type* s);

		String& operator +=(std::initializer_list<value_type> ilist);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& operator +=(const StringViewIsh& s);

		String& append(const String& s);

		String& append(const string_type& s);

		String& append(value_type ch);

		String& append(const value_type* s);

		String& append(const value_type* s, size_t count);

		String& append(std::initializer_list<value_type> ilist);

		String& append(size_t count, value_type ch);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& append(const StringViewIsh& s);

		template <class Iterator>
		String& append(Iterator first, Iterator last);

		String& insert(size_t offset, const String& s);

		String& insert(size_t offset, std::initializer_list<value_type> ilist);

		String& insert(size_t offset, const value_type* s);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& insert(size_t offset, const StringViewIsh& s);

		String& insert(size_t offset, size_t count, value_type ch);

		iterator insert(const_iterator where, value_type ch);

		iterator insert(const_iterator where, size_t count, value_type ch);

		template <class Iterator>
		iterator insert(const_iterator where, Iterator first, Iterator last);

		template <class Iterator>
		String& insert(const_iterator first1, const_iterator last1, Iterator first2, Iterator last2);

		String& erase(size_t offset = 0, size_t count = npos);

		iterator erase(const_iterator where) noexcept;

		iterator erase(const_iterator first, const_iterator last) noexcept;

		void clear() noexcept;

		[[nodiscard]]
		iterator begin() noexcept;

		[[nodiscard]]
		iterator end() noexcept;

		[[nodiscard]]
		const_iterator begin() const noexcept;

		[[nodiscard]]
		const_iterator end() const noexcept;

		[[nodiscard]]
		const_iterator cbegin() const noexcept;

		[[nodiscard]]
		const_iterator cend() const noexcept;

		[[nodiscard]]
		reverse_iterator rbegin() noexcept;

		[[nodiscard]]
		reverse_iterator rend() noexcept;

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept;

		void shrink_to_fit();

		void release();

		[[nodiscard]]
		value_type& at(size_t offset) &;

		[[nodiscard]]
		const value_type& at(size_t offset) const&;

		[[nodiscard]]
		value_type at(size_t offset) &&;

		[[nodiscard]]
		value_type& operator[](size_t offset) & noexcept;

		[[nodiscard]]
		const value_type& operator[](size_t offset) const& noexcept;

		[[nodiscard]]
		value_type operator[](size_t offset) && noexcept;

		void push_front(value_type ch);

		void push_back(value_type ch);

		void pop_front();

		void pop_front_N(size_t n);

		void pop_back() noexcept;

		void pop_back_N(size_t n) noexcept;

		[[nodiscard]]
		value_type& front() noexcept;

		[[nodiscard]]
		const value_type& front() const noexcept;

		[[nodiscard]]
		value_type& back() noexcept;

		[[nodiscard]]
		const value_type& back() const noexcept;

		[[nodiscard]]
		const value_type* c_str() const noexcept;

		[[nodiscard]]
		const value_type* data() const noexcept;

		[[nodiscard]]
		value_type* data() noexcept;

		[[nodiscard]]
		string_type& str() noexcept;

		[[nodiscard]]
		const string_type& str() const noexcept;

		[[nodiscard]]
		size_t length() const noexcept;

		[[nodiscard]]
		size_t size() const noexcept;

		[[nodiscard]]
		size_t size_bytes() const noexcept;

		[[nodiscard]]
		bool empty() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		size_t max_size() const noexcept;

		[[nodiscard]]
		size_t capacity() const noexcept;

		void resize(size_t newSize);

		void resize(size_t newSize, value_type ch);

		void reserve(size_t newCapacity);

		void swap(String& other) noexcept;

		/// @brief 文字列が指定した文字から始まるかを返します。
		/// @param ch 検索する文字
		/// @return 指定した文字から始まる場合 true, それ以外の場合は false	
		[[nodiscard]]
		bool starts_with(value_type ch) const noexcept;

		/// @brief 文字列が指定した文字列から始まるかを返します。
		/// @param s 検索する文字列
		/// @return 指定した文字列から始まる場合 true, それ以外の場合は false
		[[nodiscard]]
		bool starts_with(StringView s) const;

		/// @brief 文字列が指定した文字で終わるかを返します。
		/// @param ch 検索する文字
		/// @return 指定した文字で終わる場合 true, それ以外の場合は false
		[[nodiscard]]
		bool ends_with(value_type ch) const noexcept;

		/// @brief 文字列が指定した文字列で終わるかを返します。
		/// @param s 検索する文字列
		/// @return 指定した文字列で終わる場合 true, それ以外の場合は false
		[[nodiscard]]
		bool ends_with(StringView s) const;

		/// @brief 
		/// @param offset 
		/// @param count 
		/// @return 
		[[nodiscard]]
		String substr(size_t offset = 0, size_t count = npos) const;

		/// @brief 
		/// @param offset 
		/// @param count 
		/// @return 
		[[nodiscard]]
		StringView substrView(size_t offset = 0, size_t count = npos) const&;

		/// @brief 
		/// @param offset 
		/// @param count 
		/// @return 
		[[nodiscard]]
		StringView substrView(size_t offset = 0, size_t count = npos)&& = delete;

		/// @brief 文字列を std::string に変換します。
		/// @return 変換された文字列
		[[nodiscard]]
		std::string narrow() const;

		/// @brief 文字列を std::wstring に変換します。
		/// @return 変換された文字列
		[[nodiscard]]
		std::wstring toWstr() const;

		/// @brief 文字列を UTF-8 文字列に変換します。
		/// @return 変換された文字列
		[[nodiscard]]
		std::string toUTF8() const;

		/// @brief 文字列を UTF-16 文字列に変換します。
		/// @return 変換された文字列
		[[nodiscard]]
		std::u16string toUTF16() const;

		/// @brief 文字列を UTF-32 文字列に変換します。
		/// @return 変換された文字列
		[[nodiscard]]
		const std::u32string& toUTF32() const noexcept;

		/// @brief 文字列のハッシュを返します。
		/// @return 文字列のハッシュ
		[[nodiscard]]
		uint64 hash() const noexcept;

		/// <summary>
		/// 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="s">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexOf(StringView s, size_t offset = 0) const noexcept;

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
		[[nodiscard]]
		size_t indexOf(value_type ch, size_t offset = 0) const noexcept;

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
		[[nodiscard]]
		size_t indexOfNot(value_type ch, size_t offset = 0) const noexcept;

		/// <summary>
		/// 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="s">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexOf(StringView s, size_t offset = npos) const noexcept;

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
		[[nodiscard]]
		size_t lastIndexOf(value_type ch, size_t offset = npos) const noexcept;

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
		[[nodiscard]]
		size_t lastIndexNotOf(value_type ch, size_t offset = npos) const noexcept;

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
		[[nodiscard]]
		size_t indexOfAny(StringView anyof, size_t offset = 0) const noexcept;

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
		[[nodiscard]]
		size_t lastIndexOfAny(StringView anyof, size_t offset = npos) const noexcept;

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
		[[nodiscard]]
		size_t indexNotOfAny(StringView anyof, size_t offset = 0) const;

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
		[[nodiscard]]
		size_t lastIndexNotOfAny(StringView anyof, size_t offset = npos) const;

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="s">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]]
		int32 compare(const String& s) const noexcept;

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="s">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]]
		int32 compare(StringView s) const noexcept;

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="s">
		/// 比較対象の文字列
		/// </param>
		/// <remarks>
		/// s は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]]
		int32 compare(const value_type* s) const noexcept;

		/// <summary>
		/// 英字の大小を無視して文字列の大小を比較します。
		/// </summary>
		/// <param name="s">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ -1, 大きければ 1
		/// </returns>
		[[nodiscard]]
		int32 case_insensitive_compare(StringView s) const noexcept;

		/// <summary>
		/// 英字の大小を無視して文字列を比較します。
		/// </summary>
		/// <param name="s">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 英字の大小を無視した時に文字列が等しい場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		bool case_insensitive_equals(StringView s) const noexcept;

		/// <summary>
		/// 全ての文字が条件を満たすかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たさない文字が 1 つでもあれば false, それ以外の場合は true
		/// </returns>
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		bool all(Fty f = Identity) const;

		/// <summary>
		/// 少なくとも 1 つの文字が条件を満たすかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たす文字が 1 つでもあれば true, それ以外の場合は false
		/// </returns>
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		bool any(Fty f = Identity) const;

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
		[[nodiscard]]
		String capitalized() const&;

		/// <summary>
		/// 最初に登場する英字を大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String capitalized()&&;

		/// <summary>
		/// 指定した文字の個数を数えます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 見つかった文字の個数
		/// </returns>
		[[nodiscard]]
		size_t count(value_type ch) const noexcept;

		/// <summary>
		/// 指定した文字列の個数を数えます。
		/// </summary>
		/// <param name="s">
		/// 検索する文字列
		/// </param>
		/// <remarks>
		/// "aaa" から "aa" を検索する場合の結果は 2 です。
		/// </remarks>
		/// <returns>
		/// 見つかった文字列の個数
		/// </returns>
		[[nodiscard]]
		size_t count(StringView s) const;

		/// <summary>
		/// 条件に合う文字の個数を数えます。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 見つかった文字の個数
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		size_t count_if(Fty f) const;

		/// <summary>
		/// 文字列の各文字への参照を引数に、先頭の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32&>>* = nullptr>
		String& each(Fty f);

		/// <summary>
		/// 文字列の各文字への参照を引数に、先頭の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>* = nullptr>
		const String& each(Fty f) const;

		/// <summary>
		/// 文字列の各文字のインデックスと参照を引数に、先頭の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字のインデックスと参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, char32&>>* = nullptr>
		String& each_index(Fty f);

		/// <summary>
		/// 文字列の各文字のインデックスと参照を引数に、先頭の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字のインデックスと参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, char32>>* = nullptr>
		const String& each_index(Fty f) const;

		/// <summary>
		/// タブ文字を半角空白に置換した文字列を返します。
		/// </summary>
		/// <param name="tabSize">
		/// タブ置換後の半角空白の数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String expandTabs(size_t tabSize = 4) const;

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
		[[nodiscard]]
		value_type fetch(size_t index, value_type defaultValue) const noexcept;

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
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String filter(Fty f) const;

		/// <summary>
		/// 指定した文字が含まれているかを調べます。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <returns>
		/// 検索した文字が見つかった場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		bool includes(value_type ch) const;

		/// <summary>
		/// 指定した文字列が含まれているかを調べます。
		/// </summary>
		/// <param name="s">
		/// 検索する文字列
		/// </param>
		/// <remarks>
		/// str は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字列が見つかった場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		bool includes(StringView s) const;

		/// <summary>
		/// 指定した条件に合う文字が含まれているかを調べます。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 検索した文字が見つかった場合 true, それ以外の場合は false
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		bool includes_if(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		String& keep_if(Fty f);

		/// <summary>
		/// 指定した 1 行の文字数で改行するようにした新しい文字列を返します。
		/// </summary>
		/// <param name="width">
		/// 1 行の文字数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String layout(size_t width) const;

		[[nodiscard]]
		size_t levenshteinDistanceFrom(StringView other) const noexcept;

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
		[[nodiscard]]
		String lowercased() const&;

		/// <summary>
		/// 英字をすべて小文字にした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String lowercased()&&;

		/// <summary>
		/// 文字列の左を埋め文字で埋めます。
		/// </summary>
		/// <param name="length">
		/// 文字列の左を埋め文字で埋めた後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、変更は行われません。 
		/// </remarks>
		/// <returns>
		/// *this
		/// </returns>
		String& lpad(size_t length, value_type fillChar = U' ');

		/// <summary>
		/// 文字列の左を埋め文字で埋めた新しい文字列を返します。
		/// </summary>
		/// <param name="length">
		/// 文字列の左を埋め文字で埋めた後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、元の文字列のコピーが返ります。 
		/// </remarks>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String lpadded(size_t length, value_type fillChar = U' ') const&;

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
		[[nodiscard]]
		String lpadded(size_t length, value_type fillChar = U' ')&&;

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
		[[nodiscard]]
		String ltrimmed() const&;

		/// <summary>
		/// 文字列の先頭にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String ltrimmed()&&;

		/// <summary>
		/// 文字列の各文字に関数を適用した戻り値からなる配列を返します。
		/// </summary>
		/// <param name="f">
		/// 各文字に適用する関数
		/// </param>
		/// <returns>
		/// 文字列の各文字に関数を適用した戻り値からなる配列
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>* = nullptr>
		auto map(Fty f) const;

		/// <summary>
		/// 全ての文字が条件を満たさないかを返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 条件を満たす文字が 1 つでもあれば false, それ以外の場合は true
		/// </returns>
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		bool none(Fty f = Identity) const;

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
		String& remove(StringView s);

		/// <summary>
		/// 指定した文字を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="ch">
		/// 除去対象の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String removed(value_type ch) const&;

		/// <summary>
		/// 指定した文字を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="ch">
		/// 除去対象の文字
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String removed(value_type ch)&&;

		/// <summary>
		/// 指定した文字列を除去した新しい文字列を返します。
		/// </summary>
		/// <param name="str">
		/// 除去対象の文字列
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String removed(StringView s) const;

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
		[[nodiscard]]
		String removed_at(size_t index) const&;

		/// <summary>
		/// 指定したインデックスの文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="index">
		/// インデックス
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String removed_at(size_t index)&&;

		/// <summary>
		/// 指定した条件を満たす文字を削除します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		String& remove_if(Fty f);

		/// <summary>
		/// 指定した条件を満たす文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String removed_if(Fty f) const&;

		/// <summary>
		/// 指定した条件を満たす文字を削除した新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 検索する条件
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String removed_if(Fty f)&&;

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
		String& replace(const StringView oldStr, const StringView newStr);

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
		[[nodiscard]]
		String replaced(value_type oldChar, value_type newChar) const&;

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
		[[nodiscard]]
		String replaced(value_type oldChar, value_type newChar)&&;

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
		[[nodiscard]]
		String replaced(StringView oldStr, StringView newStr) const;

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
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		String& replace_if(Fty f, const value_type newChar);

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
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String replaced_if(Fty f, const value_type newChar) const&&;

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
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String replaced_if(Fty f, const value_type newChar)&;

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
		[[nodiscard]]
		String reversed() const&;

		/// <summary>
		/// 反転した文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String reversed()&&;

		/// <summary>
		/// 文字列の各文字への参照を引数に、末尾の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32&>>* = nullptr>
		String& reverse_each(Fty f);

		/// <summary>
		/// 文字列の各文字への参照を引数に、末尾の文字から順に関数を呼び出します。
		/// </summary>
		/// <param name="f">
		/// 各文字への参照を引数にとる関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>* = nullptr>
		const String& reverse_each(Fty f) const;

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
		[[nodiscard]]
		String rotated(std::ptrdiff_t count = 1) const&;

		/// <summary>
		/// 文字列の各文字の位置をシフトさせ、はみ出た文字を反対側に挿入した新しい文字列を返します。
		/// </summary>
		/// <param name="count">
		/// 文字をシフトする数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String rotated(std::ptrdiff_t count = 1)&&;

		/// <summary>
		/// 文字列の右を埋め文字で埋めます。
		/// </summary>
		/// <param name="length">
		/// 文字列の右を埋め文字で埋めた後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 埋め文字
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
		[[nodiscard]]
		String rpadded(size_t length, value_type fillChar = U' ') const&;

		/// <summary>
		/// 文字列の右を埋め文字で埋めた新しい文字列を返します。
		/// </summary>
		/// <param name="length">
		/// 文字列の右を埋め文字で埋めた後の文字列の長さ
		/// </param>
		/// <param name="fillChar">
		/// 埋め文字
		/// </param>
		/// <remarks>
		/// 元の文字列の長さが <paramref name="length"/> より大きい場合、元の文字列のコピーが返ります。 
		/// </remarks>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String rpadded(size_t length, value_type fillChar = U' ')&&;

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
		[[nodiscard]]
		String rtrimmed() const&;

		/// <summary>
		/// 文字列の末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String rtrimmed()&&;

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
	# if __cpp_lib_concepts
		template <Concept::UniformRandomBitGenerator URBG>
	# else
		template <class URBG, std::enable_if_t<std::is_invocable_v<URBG&> && std::is_unsigned_v<std::invoke_result_t<URBG&>>>* = nullptr>
	# endif
		String& shuffle(URBG&& rbg);

		/// <summary>
		/// ランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		[[nodiscard]]
		String shuffled() const&;

		/// <summary>
		/// ランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// ランダムに並び替えられた文字列
		/// </returns>
		[[nodiscard]]
		String shuffled()&&;

		/// <summary>
		/// 指定された乱数生成器を使ってランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <param name="rbg">
		/// 使用する乱数生成器
		/// </param>
		/// <returns>
		/// ランダムに並び替えられた文字列
		/// </returns>
	# if __cpp_lib_concepts
		template <Concept::UniformRandomBitGenerator URBG>
	# else
		template <class URBG, std::enable_if_t<std::is_invocable_v<URBG&> && std::is_unsigned_v<std::invoke_result_t<URBG&>>>* = nullptr>
	# endif
		[[nodiscard]]
		String shuffled(URBG&& rbg) const&;

		/// <summary>
		/// 指定された乱数生成器を使ってランダムに並び替えた新しい文字列を返します。
		/// </summary>
		/// <param name="rbg">
		/// 使用する乱数生成器
		/// </param>
		/// <returns>
		/// ランダムに並び替えられた文字列
		/// </returns>
	# if __cpp_lib_concepts
		template <Concept::UniformRandomBitGenerator URBG>
	# else
		template <class URBG, std::enable_if_t<std::is_invocable_v<URBG&> && std::is_unsigned_v<std::invoke_result_t<URBG&>>>* = nullptr>
	# endif
		[[nodiscard]]
		String shuffled(URBG&& rbg)&&;

		/// <summary>
		/// 指定した区切り文字で文字列を分割します。
		/// </summary>
		/// <param name="ch">
		/// 区切り文字
		/// </param>
		/// <returns>
		/// 分割された文字列
		/// </returns>
		[[nodiscard]]
		Array<String, std::allocator<String>> split(value_type ch) const;

		[[nodiscard]]
		std::pair<String, String> split_at(size_t pos) const;

		[[nodiscard]]
		Array<String, std::allocator<String>> split_lines() const;

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
		[[nodiscard]]
		String swapcased() const&;

		/// <summary>
		/// 英字の大文字と小文字を入れ替えた文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String swapcased()&&;

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
		[[nodiscard]]
		String trimmed() const&;

		/// <summary>
		/// 文字列の先頭と末尾にある空白文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String trimmed()&&;

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
		[[nodiscard]]
		String uppercased() const&;

		/// <summary>
		/// 英字をすべて大文字にした文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String uppercased()&&;

		String& rsort() noexcept;

		[[nodiscard]]
		String rsorted() const&;

		[[nodiscard]]
		String rsorted()&&;

		/// <summary>
		/// 文字列を辞書順でソートします。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& sort() noexcept;

		/// <summary>
		/// 文字列を指定された比較関数でソートします。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>* = nullptr>
		String& sort_by(Fty f);

		/// <summary>
		/// 文字列を辞書順でソートした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		[[nodiscard]]
		String sorted() const&;

		/// <summary>
		/// 文字列を辞書順でソートした新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		[[nodiscard]]
		String sorted()&&;

		/// <summary>
		/// 文字列を指定された比較関数でソートした新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>* = nullptr>
		[[nodiscard]]
		String sorted_by(Fty f) const&;

		/// <summary>
		/// 文字列を指定された比較関数でソートした新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 使用する比較関数
		/// </param>
		/// <returns>
		/// ソート済みの文字列
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>* = nullptr>
		[[nodiscard]]
		String sorted_by(Fty f)&&;

		/// <summary>
		/// 文字列の先頭から指定された文字数分取り出した新しい文字列を返します。
		/// </summary>
		/// <param name="n">
		/// 取り出す文字数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String take(size_t n) const;

		/// <summary>
		/// 文字列の先頭から、指定された条件を満たす連続した文字を取り出した新しい文字列を返します。
		/// </summary>
		/// <param name="f">
		/// 条件を記述した関数
		/// </param>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String take_while(Fty f) const;

		/// <summary>
		/// 文字列をソートせずに、重複する文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& stable_unique();

		/// <summary>
		/// 文字列をソートせずに、重複する文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String stable_uniqued() const;

		/// <summary>
		/// 文字列をソートし、重複する文字を削除します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& sort_and_unique();

		/// <summary>
		/// 文字列をソートし、重複する文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String sorted_and_uniqued() const&;

		/// <summary>
		/// 文字列をソートし、重複する文字を削除した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String sorted_and_uniqued()&&;

		/// <summary>
		/// 同じ文字が連続する場合、その先頭以外を除去します。
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		String& unique_consecutive();

		/// <summary>
		/// 同じ文字が連続する場合、その先頭以外を除去した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String uniqued_consecutive() const&;

		/// <summary>
		/// 同じ文字が連続する場合、その先頭以外を除去した新しい文字列を返します。
		/// </summary>
		/// <returns>
		/// 新しい文字列
		/// </returns>
		[[nodiscard]]
		String uniqued_consecutive()&&;

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
		[[nodiscard]]
		String values_at(std::initializer_list<size_t> indices) const;

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
		[[nodiscard]]
		String xml_escaped() const;

		/// <summary>
		/// 文字列が等しいかを調べます。
		/// </summary>
		/// <param name="lhs">
		/// 比較する文字列
		/// </param>
		/// <param name="rhs">
		/// 比較する文字列
		/// </param>
		/// <returns>
		/// 等しければ true, それ以外の場合は false
		/// </returns>	
		[[nodiscard]]
		friend bool operator ==(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string == rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator ==(const value_type* lhs, const String& rhs)
		{
			return (lhs == rhs.str());
		}

		[[nodiscard]]
		friend bool operator ==(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() == rhs);
		}

		/// <summary>
		/// 文字列が等しくないかを調べます。
		/// </summary>
		/// <param name="lhs">
		/// 比較する文字列
		/// </param>
		/// <param name="rhs">
		/// 比較する文字列
		/// </param>
		/// <returns>
		/// 等しくなければ true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		friend bool operator !=(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string != rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator !=(const value_type* lhs, const String& rhs)
		{
			return (lhs != rhs.str());
		}

		[[nodiscard]]
		friend bool operator !=(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() != rhs);
		}

		[[nodiscard]]
		friend bool operator <(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string < rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator <(const value_type* lhs, const String& rhs)
		{
			return (lhs < rhs.str());
		}

		[[nodiscard]]
		friend bool operator <(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() < rhs);
		}

		[[nodiscard]]
		friend bool operator >(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string > rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator >(const value_type* lhs, const String& rhs)
		{
			return (lhs > rhs.str());
		}

		[[nodiscard]]
		friend bool operator >(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() > rhs);
		}

		[[nodiscard]]
		friend bool operator <=(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string <= rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator <=(const value_type* lhs, const String& rhs)
		{
			return (lhs <= rhs.str());
		}

		[[nodiscard]]
		friend bool operator <=(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() <= rhs);
		}

		[[nodiscard]]
		friend bool operator >=(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string >= rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator >=(const value_type* lhs, const String& rhs)
		{
			return (lhs >= rhs.str());
		}

		[[nodiscard]]
		friend bool operator >=(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() >= rhs);
		}


		[[nodiscard]]
		friend String operator +(const value_type lhs, const String& rhs)
		{
			String result;
			result.reserve(1 + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const value_type lhs, String&& rhs)
		{
			rhs.push_front(lhs);
			return std::move(rhs);
		}

		[[nodiscard]]
		friend String operator +(const value_type* lhs, const String& rhs)
		{
			const size_t len = std::char_traits<value_type>::length(lhs);
			String result;
			result.reserve(len + rhs.size());
			result.append(lhs, len);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const value_type* lhs, String&& rhs)
		{
			return std::move(rhs.insert(0, lhs));
		}

		[[nodiscard]]
		friend String operator +(StringView lhs, const String& rhs)
		{
			String result;
			result.reserve(lhs.size() + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(StringView lhs, String&& rhs)
		{
			return std::move(rhs.insert(0, lhs));
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, const value_type rhs)
		{
			String result;
			result.reserve(lhs.size() + 1);
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, const value_type* rhs)
		{
			const size_t len = std::char_traits<value_type>::length(rhs);
			String result;
			result.reserve(lhs.size() + len);
			result.append(lhs);
			result.append(rhs, len);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, StringView rhs)
		{
			String result;
			result.reserve(lhs.size() + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, const String& rhs)
		{
			String result;
			result.reserve(lhs.size() + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, String&& rhs)
		{
			return std::move(rhs.insert(0, lhs));
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, const value_type rhs)
		{
			return std::move(lhs << rhs);
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, const value_type* rhs)
		{
			return std::move(lhs.append(rhs));
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, StringView rhs)
		{
			return std::move(lhs.append(rhs));
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, const String& rhs)
		{
			return std::move(lhs.append(rhs));
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, String&& rhs)
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

		friend std::ostream& operator <<(std::ostream& output, const String& value)
		{
			return (output << value.narrow());
		}

		friend std::wostream& operator <<(std::wostream& output, const String& value)
		{
			return (output << value.toWstr());
		}

		friend std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const String& value)
		{
			return output.write(value.data(), value.size());
		}

		friend std::istream& operator >>(std::istream& input, String& value)
		{
			std::string s;

			input >> s;

			value = Unicode::Widen(s);

			return input;
		}

		friend std::wistream& operator >>(std::wistream& input, String& value)
		{
			std::wstring s;

			input >> s;

			value = Unicode::FromWstring(s);

			return input;
		}
	};

	[[nodiscard]]
	inline String operator +(const String::value_type lhs, StringView rhs);

	[[nodiscard]]
	inline String operator +(const String::value_type* lhs, StringView rhs);

	[[nodiscard]]
	inline String operator +(StringView lhs, const String::value_type* rhs);

	[[nodiscard]]
	inline String operator +(StringView lhs, StringView rhs);

	[[nodiscard]]
	inline String operator +(StringView lhs, const String::value_type rhs);

	inline void swap(String& a, String& b) noexcept;

	inline namespace Literals
	{
		inline namespace StringLiterals
		{
			[[nodiscard]]
			inline String operator ""_s(const char32_t* s, size_t length);
		}
	}

	using FilePath = String;
}

template <>
inline void std::swap(s3d::String& a, s3d::String& b) noexcept;

template <>
struct std::hash<s3d::String>
{
	[[nodiscard]]
	size_t operator()(const s3d::String& value) const noexcept
	{
		return value.hash();
	}
};

# include "detail/String.ipp"
