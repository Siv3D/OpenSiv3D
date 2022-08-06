//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# if  __has_include(<compare>)
#	include <compare>
# endif
# include <functional>
# include <string>
# include <unordered_set>
# include "Common.hpp"
# include "StringView.hpp"
# include "Utility.hpp"
# include "Random.hpp"
# include "Char.hpp"
# include "Shuffle.hpp"

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

		template <class StringViewIsh>
		using IsStringViewIsh = std::enable_if_t<
			std::conjunction_v<std::is_convertible<const StringViewIsh&, StringView>,
			std::negation<std::is_convertible<const StringViewIsh&, const char32*>>>>;

		static constexpr size_type npos{ static_cast<size_type>(-1) };

		/// @brief デフォルトコンストラクタ | default constructor
		SIV3D_NODISCARD_CXX20
		String();

		/// @brief 文字列をコピーして新しい文字列を作成します。
		/// @param other コピーする文字列
		SIV3D_NODISCARD_CXX20
		String(const String& other);

		/// @brief 文字列をコピーして新しい文字列を作成します。
		/// @param s コピーする文字列
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
		allocator_type get_allocator() const noexcept;

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

		/// @brief 格納している文字列を消去し、空の文字列にします。
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
		value_type& operator [](size_t offset) & noexcept;

		[[nodiscard]]
		const value_type& operator [](size_t offset) const& noexcept;

		[[nodiscard]]
		value_type operator [](size_t offset) && noexcept;

		/// @brief 先頭に文字を追加します。
		/// @param ch 追加する文字
		void push_front(value_type ch);

		/// @brief 末尾に文字を追加します。
		/// @param ch 追加する文字
		void push_back(value_type ch);

		/// @brief 先頭の文字を削除します。
		void pop_front();

		/// @brief 先頭の n 文字を削除します。
		/// @remark n が現在の文字数より大きい場合は空の文字列にします。
		/// @param n 削除する文字数
		void pop_front_N(size_t n);

		/// @brief 末尾の文字を削除します。
		void pop_back() noexcept;

		/// @brief 末尾の n 文字を削除します。
		/// @remark n が現在の文字数より大きい場合は空の文字列にします。
		/// @param n 削除する文字数
		void pop_back_N(size_t n) noexcept;

		/// @brief 先頭の文字への参照を返します。
		/// @remark 空の文字列に対しては使えません。
		/// @return 先頭の文字への参照
		[[nodiscard]]
		value_type& front() noexcept;

		/// @brief 先頭の文字への参照を返します。
		/// @remark 空の文字列に対しては使えません。
		/// @return 先頭の文字への参照
		[[nodiscard]]
		const value_type& front() const noexcept;

		/// @brief 末尾の文字への参照を返します。
		/// @remark 空の文字列に対しては使えません。
		/// @return 末尾の文字への参照
		[[nodiscard]]
		value_type& back() noexcept;

		/// @brief 末尾の文字への参照を返します。
		/// @remark 空の文字列に対しては使えません。
		/// @return 末尾の文字への参照
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

		/// @brief 文字列の長さ（要素数）を返します。
		/// @return 文字列の長さ（要素数）
		[[nodiscard]]
		size_t length() const noexcept;

		/// @brief 文字列の長さ（要素数）を返します。
		/// @remark `.length()` と同じです。
		/// @return 文字列の長さ（要素数）
		[[nodiscard]]
		size_t size() const noexcept;

		/// @brief 文字列のデータサイズ（バイト）を返します。
		/// @remark `sizeof(value_type) * length()` です。
		/// @return 文字列のデータサイズ（バイト）
		[[nodiscard]]
		size_t size_bytes() const noexcept;

		/// @brief 文字列が空であるかを返します。
		/// @return 文字列が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool empty() const noexcept;

		/// @brief 文字列が空であるかを返します。
		/// @remark `empty()` と同じです。
		/// @return 文字列が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief 文字列が空でないかを返します。
		/// @return 文字列が空でない場合 true, それ以外の場合は false
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

		/// @brief 部分文字列を取得します。
		/// @param offset 開始インデックス
		/// @param count 取得する文字数。末尾までの場合 npos
		/// @return 部分文字列
		[[nodiscard]]
		String substr(size_t offset = 0, size_t count = npos) const;

		/// @brief 部分文字列へのビューを取得します。
		/// @param offset 開始インデックス
		/// @param count 取得する文字数。末尾までの場合 npos
		/// @return 部分文字列へのビュー
		[[nodiscard]]
		StringView substrView(size_t offset = 0, size_t count = npos) const&;

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

		/// @brief 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// @param s 検索する文字列
		/// @param offset 検索を開始する位置
		/// @return 	検索した文字列が最初に現れた位置。見つからなかった場合は npos
		[[nodiscard]]
		size_t indexOf(StringView s, size_t offset = 0) const noexcept;

		/// @brief 文字を指定した位置から検索し、最初に現れた位置を返します。
		/// @param ch 検索する文字
		/// @param offset 検索を開始する位置
		/// @return 検索した文字が最初に現れた位置。見つからなかった場合は npos
		[[nodiscard]]
		size_t indexOf(value_type ch, size_t offset = 0) const noexcept;

		/// @brief 文字を指定した位置から検索し、最初にそれとは異なる文字が現れた位置を返します。
		/// @param ch 検索する文字
		/// @param offset 検索を開始する位置
		/// @return 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		[[nodiscard]]
		size_t indexOfNot(value_type ch, size_t offset = 0) const noexcept;

		/// @brief 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// @param s 検索する文字列
		/// @param offset 検索を開始する位置。npos の場合は終端から
		/// @return 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		[[nodiscard]]
		size_t lastIndexOf(StringView s, size_t offset = npos) const noexcept;

		/// @brief 文字を後方から逆順に検索し、最初に現れた位置を返します。
		/// @param ch 検索する文字
		/// @param offset 検索を開始する位置。npos の場合は終端から
		/// @return 検索した文字が最初に現れた位置。見つからなかった場合は npos	
		[[nodiscard]]
		size_t lastIndexOf(value_type ch, size_t offset = npos) const noexcept;

		/// @brief 文字を後方から逆順に検索し、最初にそれとは異なる文字が現れた位置を返します。
		/// @param ch 検索する文字
		/// @param offset 検索を開始する位置。npos の場合は終端から
		/// @return 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos		
		[[nodiscard]]
		size_t lastIndexNotOf(value_type ch, size_t offset = npos) const noexcept;

		/// @brief 検索する文字のいずれかが最初に現れた位置を返します。
		/// @param anyof 検索する文字の集合
		/// @param offset 検索を開始する位置
		/// @return 検索した文字が最初に現れた位置。見つからなかった場合は npos	
		[[nodiscard]]
		size_t indexOfAny(StringView anyof, size_t offset = 0) const noexcept;

		/// @brief 文字を後方から逆順に検索し、検索する文字のいずれかが最初に現れた位置を返します。
		/// @param anyof 検索する文字の集合
		/// @param offset 検索を開始する位置。npos の場合は終端から
		/// @return 検索した文字が最初に現れた位置。見つからなかった場合は npos
		[[nodiscard]]
		size_t lastIndexOfAny(StringView anyof, size_t offset = npos) const noexcept;

		/// @brief 検索する文字に含まれない文字が最初に現れた位置を返します。
		/// @param anyof 検索する文字の集合
		/// @param offset 検索を開始する位置
		/// @return 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		[[nodiscard]]
		size_t indexNotOfAny(StringView anyof, size_t offset = 0) const;

		/// @brief 文字を後方から逆順に検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// @param anyof 検索する文字の集合
		/// @param offset 検索を開始する位置。npos の場合は終端から
		/// @return 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		[[nodiscard]]
		size_t lastIndexNotOfAny(StringView anyof, size_t offset = npos) const;

		/// @brief 文字列の大小を比較します。
		/// @param s 比較対象の文字列
		/// @return 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		[[nodiscard]]
		int32 compare(const String& s) const noexcept;

		/// @brief 文字列の大小を比較します。
		/// @param s 比較対象の文字列
		/// @return 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		[[nodiscard]]
		int32 compare(StringView s) const noexcept;

		/// @brief 文字列の大小を比較します。
		/// @param s 比較対象の文字列
		/// @remark s は NULL 終端されている必要があります。
		/// @return 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		[[nodiscard]]
		int32 compare(const value_type* s) const noexcept;

		/// @brief 英字の大小を無視して文字列の大小を比較します。
		/// @param s 比較対象の文字列
		/// @return 比較結果。等しければ 0, 小さければ -1, 大きければ 1		
		[[nodiscard]]
		int32 case_insensitive_compare(StringView s) const noexcept;

		/// @brief 英字の大小を無視して文字列を比較します。
		/// @param s 比較対象の文字列
		/// @return 英字の大小を無視した時に文字列が等しい場合 true, それ以外の場合は false	
		[[nodiscard]]
		bool case_insensitive_equals(StringView s) const noexcept;

		/// @brief 全ての要素が条件を満たすかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 全ての要素が条件を満たすか、配列が空の場合 true, それ以外の場合は false
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		bool all(Fty f = Identity) const;

		/// @brief 条件を満たす要素があるかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 条件を満たす要素が 1 つでもあれば true, 俺以外の場合は false
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		bool any(Fty f = Identity) const;

		/// @brief 最初に登場する英字を大文字にします。
		/// @return *this
		String& capitalize() noexcept;

		/// @brief 最初に登場する英字を大文字にした文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String capitalized() const&;

		/// @brief 最初に登場する英字を大文字にした文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String capitalized()&&;

		/// @brief 指定した値と等しい要素の個数を返します。
		/// @param ch 検索する値
		/// @return 指定した値と等しい要素の個数	
		[[nodiscard]]
		size_t count(value_type ch) const noexcept;

		/// @brief 指定した文字列の個数を数えます。
		/// @param s 検索する文字列
		/// @remark `"aaa"` から `"aa"` を検索する場合の結果は 2 です。
		/// @return 見つかった文字列の個数
		[[nodiscard]]
		size_t count(StringView s) const;

		/// @brief 条件を満たす要素の個数を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 条件を満たす要素の個数	
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		size_t count_if(Fty f) const;

		/// @brief 全ての要素を順番に引数にして関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @remark `for (auto& ch : s) f(ch);` と同じです。
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32&>>* = nullptr>
		String& each(Fty f);

		/// @brief 全ての要素を順番に引数にして関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @remark `for (const auto& ch : s) f(ch);` と同じです。
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>* = nullptr>
		const String& each(Fty f) const;

		/// @brief 全ての要素とそのインデックスを順番に引数にして関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @remark `for (size_t i = 0; auto& ch : s) f(i++, ch);` と同じです。
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, char32&>>* = nullptr>
		String& each_index(Fty f);

		/// @brief 全ての要素とそのインデックスを順番に引数にして関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @remark `for (size_t i = 0; const auto& ch : s) f(i++, ch);` と同じです。
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, char32>>* = nullptr>
		const String& each_index(Fty f) const;

		/// @brief タブ文字を半角空白に置換した文字列を返します。
		/// @param tabSize タブ置換後の半角空白の数
		/// @return 新しい文字列	
		[[nodiscard]]
		String expandTabs(size_t tabSize = 4) const;

		/// @brief 指定したインデックスにある要素を返します。インデックスが範囲外の場合デフォルト値を返します。
		/// @param index インデックス
		/// @param defaultValue インデックスが範囲外の場合に返すデフォルト値
		/// @return  指定したインデックスにある要素、範囲外の場合 defaultValue	
		[[nodiscard]]
		value_type fetch(size_t index, value_type defaultValue) const noexcept;

		/// @brief 指定した値を全ての要素に代入します。
		/// @param value 代入する値
		/// @return *this
		String& fill(value_type value);

		/// @brief 指定した条件を満たす要素だけを集めた新しい文字列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @remark 結果において、要素の前後関係は維持されます。
		/// @return 指定した条件を満たす要素を集めた新しい文字列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String filter(Fty f) const;

		/// @brief 指定した値と等しい要素があるかを返します。
		/// @param value 検索する値
		/// @return 指定した値と等しい要素がある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool includes(value_type ch) const;

		/// @brief 指定した文字列を含むかを返します。
		/// @param ch 検索する文字列
		/// @return 指定した文字列を含む場合 true, それ以外の場合は false
		[[nodiscard]]
		bool includes(StringView s) const;

		/// @brief 指定した条件を満たす要素があるかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @remark `.any(f)` と同じです。
		/// @return 条件を満たす要素が 1 つでもあれば true, 俺以外の場合は false
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		bool includes_if(Fty f) const;

		/// @brief 指定した条件を満たす要素のみを残して、それ以外を文字列から削除します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		String& keep_if(Fty f);

		/// @brief 指定した 1 行の文字数で改行するようにした新しい文字列を返します。
		/// @param width 1 行の文字数
		/// @return 新しい文字列	
		[[nodiscard]]
		String layout(size_t width) const;

		/// @brief 別の文字列とのレーベンシュタイン距離を計算して返します。
		/// @param other 別の文字列
		/// @return 別の文字列とのレーベンシュタイン距離
		[[nodiscard]]
		size_t levenshteinDistanceFrom(StringView other) const noexcept;

		/// @brief 英字をすべて小文字にします。
		/// @return *this
		String& lowercase() noexcept;

		/// @brief 英字をすべて小文字にした新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String lowercased() const&;

		/// @brief 英字をすべて小文字にした新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String lowercased()&&;

		/// @brief 文字列の左を埋め文字で埋めます。
		/// @param length 文字列の左を埋め文字で埋めた後の文字列の長さ
		/// @param fillChar 埋め文字
		/// @remark 元の文字列の長さが `length` より大きい場合、変更は行われません。 
		/// @return *this
		String& lpad(size_t length, value_type fillChar = U' ');

		/// @brief 文字列の左を埋め文字で埋めた新しい文字列を返します。
		/// @param length 文字列の左を埋め文字で埋めた後の文字列の長さ
		/// @param fillChar 埋め文字
		/// @remark 元の文字列の長さが `length` より大きい場合、元の文字列のコピーが返ります。 
		/// @return 新しい文字列
		[[nodiscard]]
		String lpadded(size_t length, value_type fillChar = U' ') const&;

		/// @brief 文字列の左を埋め文字で埋めた新しい文字列を返します。
		/// @param length 文字列の左を埋め文字で埋めた後の文字列の長さ
		/// @param fillChar 埋め文字
		/// @remark 元の文字列の長さが `length` より大きい場合、元の文字列のコピーが返ります。 
		/// @return 新しい文字列
		[[nodiscard]]
		String lpadded(size_t length, value_type fillChar = U' ')&&;

		/// @brief 文字列の先頭にある空白文字を削除します。
		/// @return *this
		String& ltrim();

		/// @brief 文字列の先頭にある空白文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String ltrimmed() const&;

		/// @brief 文字列の先頭にある空白文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String ltrimmed()&&;

		/// @brief 文字列の各要素に関数を適用した戻り値からなる配列を返します。
		/// @tparam Fty 各文字に適用する関数の型
		/// @param f 各文字に適用する関数
		/// @return 文字列の各要素に関数を適用した戻り値からなる配列
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>* = nullptr>
		auto map(Fty f) const;

		/// @brief 条件を満たす要素が存在しないかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 条件を満たす要素数が 0 個の場合 true, それ以外の場合は false
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		bool none(Fty f = Identity) const;

		/// @brief 指定した文字を文字列から削除します。
		/// @param ch 削除する文字
		/// @return *this
		String& remove(value_type ch);

		/// @brief 指定した文字列をもとの文字列から削除します。
		/// @param s 削除する文字列
		/// @return *this
		String& remove(StringView s);

		/// @brief 指定した文字を除去した新しい文字列を返します。
		/// @param ch 除去対象の文字
		/// @return 新しい文字列	
		[[nodiscard]]
		String removed(value_type ch) const&;
		
		/// @brief 指定した文字を除去した新しい文字列を返します。
		/// @param ch 除去対象の文字
		/// @return 新しい文字列	
		[[nodiscard]]
		String removed(value_type ch)&&;

		/// @brief 指定した文字列を除去した新しい文字列を返します。
		/// @param s 除去対象の文字列
		/// @return 新しい文字列
		[[nodiscard]]
		String removed(StringView s) const;

		/// @brief 指定したインデックスにある要素を文字列から削除します。
		/// @param index インデックス
		/// @return *this
		String& remove_at(size_t index);

		/// @brief 定したインデックスにある要素を削除した新しい文字列を返します。
		/// @param index インデックス
		/// @return 新しい文字列
		[[nodiscard]]
		String removed_at(size_t index) const&;

		/// @brief 定したインデックスにある要素を削除した新しい文字列を返します。
		/// @param index インデックス
		/// @return 新しい文字列
		[[nodiscard]]
		String removed_at(size_t index)&&;

		/// @brief 指定した条件を満たす文字を削除します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		String& remove_if(Fty f);

		/// @brief 指定した条件を満たす文字を削除した新しい文字列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 新しい文字列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String removed_if(Fty f) const&;

		/// @brief 指定した条件を満たす文字を削除した新しい文字列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 新しい文字列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String removed_if(Fty f)&&;

		/// @brief 指定した文字を置換します。
		/// @param oldChar 置換対象の文字
		/// @param newChar 置換後の文字
		/// @return *this
		String& replace(value_type oldChar, value_type newChar);

		/// @brief 指定した文字列を置換します。
		/// @param oldStr 置換対象の文字列
		/// @param newStr 置換後の文字列
		/// @return *this
		String& replace(const StringView oldStr, const StringView newStr);

		String& replace(size_type pos, size_type count, const String& s);

		String& replace(size_type pos, size_type count, const value_type* s);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& replace(size_type pos, size_type count, const StringViewIsh& s);

		String& replace(const_iterator first, const_iterator last, const String& s);

		String& replace(const_iterator first, const_iterator last, const value_type* s);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& replace(const_iterator first, const_iterator last, const StringViewIsh& s);

		template <class Iterator>
		String& replace(const_iterator first, const_iterator last, Iterator first2, Iterator last2);

		/// @brief 指定した文字を置換した新しい文字列を返します。
		/// @param oldChar 置換対象の文字
		/// @param newChar 置換後の文字
		/// @return 新しい文字列
		[[nodiscard]]
		String replaced(value_type oldChar, value_type newChar) const&;

		/// @brief 指定した文字を置換した新しい文字列を返します。
		/// @param oldChar 置換対象の文字
		/// @param newChar 置換後の文字
		/// @return 新しい文字列
		[[nodiscard]]
		String replaced(value_type oldChar, value_type newChar)&&;

		/// @brief 指定した文字列を置換した新しい文字列を返します。
		/// @param oldStr 置換対象の文字列
		/// @param newStr 置換後の文字列
		/// @return 新しい文字列
		[[nodiscard]]
		String replaced(StringView oldStr, StringView newStr) const;

		/// @brief 指定した条件を満たす文字を別の文字に置き換えます。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @param newChar 置換後の文字
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		String& replace_if(Fty f, const value_type newChar);

		/// @brief 指定した条件を満たす文字を別の文字に置き換えた新しい文字列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @param newChar 置換後の文字
		/// @return 新しい文字列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String replaced_if(Fty f, const value_type newChar) const&;

		/// @brief 指定した条件を満たす文字を別の文字に置き換えた新しい文字列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @param newChar 置換後の文字
		/// @return 新しい文字列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String replaced_if(Fty f, const value_type newChar)&&;

		/// @brief 文字列を反転します。
		/// @return *this
		String& reverse();

		/// @brief 反転した文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String reversed() const&;

		/// @brief 反転した文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String reversed()&&;

		/// @brief 文字列の各文字への参照を引数に、末尾の文字から順に関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32&>>* = nullptr>
		String& reverse_each(Fty f);

		/// @brief 文字列の各文字への参照を引数に、末尾の文字から順に関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, char32>>* = nullptr>
		const String& reverse_each(Fty f) const;

		/// @brief 文字列の各文字の位置をシフトさせ、はみ出た文字は反対側に挿入します。
		/// @param count 文字をシフトする数
		/// @return *this
		String& rotate(std::ptrdiff_t count = 1);

		/// @brief 文字列の各文字の位置をシフトさせ、はみ出た文字を反対側に挿入した新しい文字列を返します。
		/// @param count 文字をシフトする数
		/// @return 新しい文字列	
		[[nodiscard]]
		String rotated(std::ptrdiff_t count = 1) const&;

		/// @brief 文字列の各文字の位置をシフトさせ、はみ出た文字を反対側に挿入した新しい文字列を返します。
		/// @param count 文字をシフトする数
		/// @return 新しい文字列	
		[[nodiscard]]
		String rotated(std::ptrdiff_t count = 1)&&;

		/// @brief 文字列の右を埋め文字で埋めます。
		/// @param length 文字列の右を埋め文字で埋めた後の文字列の長さ
		/// @param fillChar 埋め文字
		/// @remark 元の文字列の長さが `length` より大きい場合、変更は行われません。 
		/// @return *this
		String& rpad(size_t length, value_type fillChar = U' ');

		/// @brief 文字列を指定された文字で右詰めした新しい文字列を返します。
		/// @param length 右詰めした後の文字列の長さ
		/// @param fillChar 埋め文字
		/// @remark 元の文字列の長さが `length` より大きい場合、元の文字列のコピーを返します。
		/// @return 新しい文字列	
		[[nodiscard]]
		String rpadded(size_t length, value_type fillChar = U' ') const&;

		/// @brief 文字列を指定された文字で右詰めした新しい文字列を返します。
		/// @param length 右詰めした後の文字列の長さ
		/// @param fillChar 埋め文字
		/// @remark 元の文字列の長さが `length` より大きい場合、元の文字列のコピーを返します。
		/// @return 新しい文字列	
		[[nodiscard]]
		String rpadded(size_t length, value_type fillChar = U' ')&&;

		/// @brief 文字列の末尾にある空白文字を削除します。
		/// @return *this
		String& rtrim();

		/// @brief 文字列の末尾にある空白文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String rtrimmed() const&;

		/// @brief 文字列の末尾にある空白文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String rtrimmed()&&;

		/// @brief 文字列をランダムに並び替えます。
		/// @return *this
		String& shuffle();

		/// @brief 指定された乱数生成器を使って文字列をランダムに並び替えます。
		/// @param rbg 使用する乱数生成器
		/// @return *this
		SIV3D_CONCEPT_URBG
		String& shuffle(URBG&& rbg);

		/// @brief ランダムに並び替えた新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String shuffled() const&;

		/// @brief ランダムに並び替えた新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String shuffled()&&;

		/// @brief 指定された乱数生成器を使ってランダムに並び替えた新しい文字列を返します。
		/// @param rbg 用する乱数生成器
		/// @return 新しい文字列
		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		String shuffled(URBG&& rbg) const&;

		/// @brief 指定された乱数生成器を使ってランダムに並び替えた新しい文字列を返します。
		/// @param rbg 用する乱数生成器
		/// @return 新しい文字列
		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		String shuffled(URBG&& rbg)&&;

		/// @brief 指定した区切り文字で文字列を分割します。
		/// @param ch 区切り文字
		/// @return 分割された文字列
		[[nodiscard]]
		Array<String, std::allocator<String>> split(value_type ch) const;

		[[nodiscard]]
		std::pair<String, String> split_at(size_t pos) const;

		[[nodiscard]]
		Array<String, std::allocator<String>> split_lines() const;

		/// @brief 英字の大文字と小文字を入れ替えます。
		/// @return *this
		String& swapcase() noexcept;

		/// @brief 英字の大文字と小文字を入れ替えた文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String swapcased() const&;

		/// @brief 英字の大文字と小文字を入れ替えた文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String swapcased()&&;

		/// @brief 文字列の先頭と末尾にある空白文字を削除します。
		/// @return *this
		String& trim();

		/// @brief 文字列の先頭と末尾にある空白文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String trimmed() const&;

		/// @brief 文字列の先頭と末尾にある空白文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String trimmed()&&;

		/// @brief 英字をすべて大文字にします。
		/// @return *this
		String& uppercase() noexcept;

		/// @brief 英字をすべて大文字にした文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String uppercased() const&;

		/// @brief 英字をすべて大文字にした文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String uppercased()&&;

		String& rsort() noexcept;

		[[nodiscard]]
		String rsorted() const&;

		[[nodiscard]]
		String rsorted()&&;

		/// @brief 文字列をソートします。
		/// @return *this
		String& sort() noexcept;

		/// @brief 文字列を指定された比較関数でソートします。
		/// @tparam Fty 使用する比較関数の型
		/// @param f 使用する比較関数
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>* = nullptr>
		String& sort_by(Fty f);

		/// @brief 文字列をソートした新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String sorted() const&;

		/// @brief 文字列をソートした新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String sorted()&&;

		/// @brief 文字列を指定された比較関数でソートした新しい文字列を返します。
		/// @tparam Fty 使用する比較関数の型
		/// @param f 使用する比較関数
		/// @return 新しい文字列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>* = nullptr>
		[[nodiscard]]
		String sorted_by(Fty f) const&;

		/// @brief 文字列を指定された比較関数でソートした新しい文字列を返します。
		/// @tparam Fty 使用する比較関数の型
		/// @param f 使用する比較関数
		/// @return 新しい文字列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32, char32>>* = nullptr>
		[[nodiscard]]
		String sorted_by(Fty f)&&;

		/// @brief 文字列の先頭から指定された文字数分取り出した新しい文字列を返します。
		/// @param n 取り出す文字数
		/// @return 新しい文字列
		[[nodiscard]]
		String take(size_t n) const;

		/// @brief 文字列の先頭から、指定された条件を満たす連続した文字を取り出した新しい文字列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 新しい文字列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, char32>>* = nullptr>
		[[nodiscard]]
		String take_while(Fty f) const;

		/// @brief 文字列をソートせずに、重複する文字を削除します。
		/// @return *this
		String& stable_unique();

		/// @brief 文字列をソートせずに、重複する文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String stable_uniqued() const;

		/// @brief 文字列をソートし、重複する文字を削除します。
		/// @return *this
		String& sort_and_unique();

		/// @brief 文字列をソートし、重複する文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String sorted_and_uniqued() const&;

		/// @brief 文字列をソートし、重複する文字を削除した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String sorted_and_uniqued()&&;

		/// @brief 同じ文字が連続する場合、その先頭以外を除去します。
		/// @return *this
		String& unique_consecutive();

		/// @brief 同じ文字が連続する場合、その先頭以外を除去した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String uniqued_consecutive() const&;

		/// @brief 同じ文字が連続する場合、その先頭以外を除去した新しい文字列を返します。
		/// @return 新しい文字列
		[[nodiscard]]
		String uniqued_consecutive()&&;

		/// @brief 複数のインデックスを取り、それらの文字からなる新しい文字列を返します。
		/// @param indices インデックス
		/// @remark `String("abcde").values_at({0, 3, 4}); // "ade"`
		/// @return 新しい文字列
		[[nodiscard]]
		String values_at(std::initializer_list<size_t> indices) const;

		/// @brief 文字列に XML エスケープを行います。
		/// @remark &quot;, \, &amp;, &gt;, &lt; などのエスケープを行います
		/// @return *this
		String& xml_escape();

		/// @brief  XML エスケープした文字列を返します。
		/// @remark &quot;, \, &amp;, &gt;, &lt; などのエスケープを行います
		/// @return 新しい文字列
		[[nodiscard]]
		String xml_escaped() const;

		friend bool operator ==(const String& lhs, const value_type* rhs);

#if __cpp_impl_three_way_comparison

		bool operator ==(const String& rhs) const noexcept = default;

		std::strong_ordering operator <=>(const String& rhs) const noexcept = default;

		friend std::strong_ordering operator <=>(const String& lhs, const value_type* rhs);

#else

		friend bool operator ==(const String & lhs, const String & rhs) noexcept;

		friend bool operator ==(const value_type * lhs, const String & rhs);

		friend bool operator !=(const String& lhs, const String& rhs) noexcept;

		friend bool operator !=(const value_type* lhs, const String& rhs);

		friend bool operator !=(const String& lhs, const value_type* rhs);


		friend bool operator <(const String& lhs, const String& rhs) noexcept;

		friend bool operator <(const value_type* lhs, const String& rhs);

		friend bool operator <(const String& lhs, const value_type* rhs);


		friend bool operator >(const String& lhs, const String& rhs) noexcept;

		friend bool operator >(const value_type* lhs, const String& rhs);

		friend bool operator >(const String& lhs, const value_type* rhs);


		friend bool operator <=(const String& lhs, const String& rhs) noexcept;

		friend bool operator <=(const value_type* lhs, const String& rhs);

		friend bool operator <=(const String& lhs, const value_type* rhs);


		friend bool operator >=(const String& lhs, const String& rhs) noexcept;

		friend bool operator >=(const value_type* lhs, const String& rhs);

		friend bool operator >=(const String& lhs, const value_type* rhs);

#endif

		friend String operator +(const value_type lhs, const String& rhs);

		friend String operator +(const value_type lhs, String&& rhs);

		friend String operator +(const value_type* lhs, const String& rhs);

		friend String operator +(const value_type* lhs, String&& rhs);

		friend String operator +(StringView lhs, const String& rhs);

		friend String operator +(StringView lhs, String&& rhs);

		friend String operator +(const String& lhs, const value_type rhs);

		friend String operator +(const String& lhs, const value_type* rhs);

		friend String operator +(const String& lhs, StringView rhs);

		friend String operator +(const String& lhs, const String& rhs);

		friend String operator +(const String& lhs, String&& rhs);

		friend String operator +(String&& lhs, const value_type rhs);

		friend String operator +(String&& lhs, const value_type* rhs);

		friend String operator +(String&& lhs, StringView rhs);

		friend String operator +(String&& lhs, const String& rhs);

		friend String operator +(String&& lhs, String&& rhs);

		friend std::ostream& operator <<(std::ostream& output, const String& value);

		friend std::wostream& operator <<(std::wostream& output, const String& value);

		friend std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const String& value);

		friend std::istream& operator >>(std::istream& input, String& value);

		friend std::wistream& operator >>(std::wistream& input, String& value);

		friend void Formatter(FormatData& formatData, const String& s);

	private:

		string_type m_string;
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
	size_t operator ()(const s3d::String& value) const noexcept
	{
		return value.hash();
	}
};

# include "detail/String.ipp"
