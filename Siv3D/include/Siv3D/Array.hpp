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
# include "Common.hpp"
# if  __has_include(<compare>)
#	include <compare>
# endif
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
# include "KahanSummation.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 動的配列
	/// @tparam Type 要素の型
	/// @tparam Allocator アロケータ
	template <class Type, class Allocator = std::allocator<Type>>
	class Array
	{
	public:

		using container_type			= std::vector<Type, Allocator>;

		/// @brief 配列の要素の型
		using value_type				= typename container_type::value_type;

		/// @brief 要素のポインタ型
		using pointer					= typename container_type::pointer;
		
		/// @brief 要素の const ポインタ型
		using const_pointer				= typename container_type::const_pointer;
		
		/// @brief 要素の参照型
		using reference					= typename container_type::reference;
		
		/// @brief 要素の const 参照型
		using const_reference			= typename container_type::const_reference;
		
		/// @brief イテレータ型
		using iterator					= typename container_type::iterator;
		
		/// @brief const イテレータ型
		using const_iterator			= typename container_type::const_iterator;
		
		/// @brief リバース・イテレータ型
		using reverse_iterator			= typename container_type::reverse_iterator;
		
		/// @brief const リバース・イテレータ型
		using const_reverse_iterator	= typename container_type::const_reverse_iterator;
		
		/// @brief 要素の個数を表現する型
		using size_type					= typename container_type::size_type;
		
		/// @brief 2 つの要素間の距離を表現する型
		using difference_type			= typename container_type::difference_type;
		
		/// @brief アロケータの型
		using allocator_type			= typename container_type::allocator_type;

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

		/// @brief std::vector からのコピーで配列を作成します。
		/// @param other コピーする配列
		SIV3D_NODISCARD_CXX20
		Array(const container_type& other);

		/// @brief std::vector からのムーブで配列を作成します。
		/// @param other ムーブする配列
		SIV3D_NODISCARD_CXX20
		Array(container_type&& other);

		/// @brief 
		/// @param alloc 
		SIV3D_NODISCARD_CXX20
		explicit Array(const Allocator& alloc) noexcept;

		/// @brief count 個の value で配列を作成します。
		/// @param count 個数
		/// @param value 要素
		/// @param alloc アロケータ
		SIV3D_NODISCARD_CXX20
		Array(size_type count, const value_type& value, const Allocator& alloc = Allocator{});

		/// @brief count 個の Type() で配列を作成します。
		/// @param count 個数
		/// @param alloc アロケータ
		SIV3D_NODISCARD_CXX20
		explicit Array(size_type count, const Allocator& alloc = Allocator{});

		/// @brief イテレータが指す範囲の要素から配列を作成します。
		/// @tparam Iterator イテレータ
		/// @param first 範囲の開始位置を指すイテレータ
		/// @param last 範囲の終端位置を指すイテレータ
		/// @param alloc アロケータ
		template <class Iterator>
		SIV3D_NODISCARD_CXX20
		Array(Iterator first, Iterator last, const Allocator& alloc = Allocator{});

		/// @brief 
		/// @param other 
		/// @param alloc 
		SIV3D_NODISCARD_CXX20
		Array(const Array& other, const Allocator& alloc);

		/// @brief 
		/// @param other 
		/// @param alloc 
		SIV3D_NODISCARD_CXX20
		Array(Array&& other, const Allocator& alloc);

		/// @brief 
		/// @param other 
		/// @param alloc 
		SIV3D_NODISCARD_CXX20
		Array(const container_type& other, const Allocator& alloc);

		/// @brief 
		/// @param other 
		/// @param alloc 
		SIV3D_NODISCARD_CXX20
		Array(container_type&& other, const Allocator& alloc);

		/// @brief 初期化リストから配列を作成します。
		/// @param ilist 初期化リスト
		/// @param alloc アロケータ
		SIV3D_NODISCARD_CXX20
		Array(std::initializer_list<value_type> ilist, const Allocator& alloc = Allocator{});

		/// @brief `asArray()` を持つ型から配列を作成します。
		/// @tparam ArrayIsh `asArray()` を持つ型
		/// @param a `asArray()` を持つ型のオブジェクト
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

		Array& operator =(const container_type& other);

		Array& operator =(container_type&& other);

		Array& operator =(std::initializer_list<value_type> ilist);

		template <class ArrayIsh, std::enable_if_t<Meta::HasAsArray<ArrayIsh>::value>* = nullptr>
		Array& operator =(const ArrayIsh& a);

		Array& assign(size_type count, const value_type & value);

		template <class Iterator>
		Array& assign(Iterator first, Iterator last);

		Array& assign(std::initializer_list<value_type> ilist);

		[[nodiscard]]
		allocator_type get_allocator() const noexcept;

		[[nodiscard]]
		const container_type& getContainer() const noexcept;

		[[nodiscard]]
		operator container_type() const noexcept;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @throw std::out_of_range 範囲外アクセスの場合 throw
		/// @return 要素への参照
		const value_type& at(size_t index) const;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		value_type& at(size_t index);

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		[[nodiscard]]
		const value_type& operator [](size_t index) const;

		/// @brief 要素にアクセスします。
		/// @param index 要素へのインデックス
		/// @return 要素への参照
		[[nodiscard]]
		value_type& operator [](size_t index);

		/// @brief 先頭の要素への参照を返します。
		/// @return 先頭の要素への参照
		[[nodiscard]]
		reference front();

		/// @brief 先頭の要素への参照を返します。
		/// @return 先頭の要素への参照
		[[nodiscard]]
		const_reference front() const;

		/// @brief 末尾の要素への参照を返します。
		/// @return 末尾の要素への参照
		[[nodiscard]]
		reference back();

		/// @brief 末尾の要素への参照を返します。
		/// @return 末尾の要素への参照
		[[nodiscard]]
		const_reference back() const;

		/// @brief 先頭の要素を指すポインタを返します。
		/// @return 先頭の要素を指すポインタ
		[[nodiscard]]
		value_type* data() noexcept;

		/// @brief 先頭の要素を指すポインタを返します。
		/// @return 先頭の要素を指すポインタ
		[[nodiscard]]
		const value_type* data() const noexcept;

		/// @brief 配列の先頭位置を指すイテレータを返します。
		/// @return 配列の先頭位置を指すイテレータ
		[[nodiscard]]
		iterator begin() noexcept;

		/// @brief 配列の終端位置を指すイテレータを返します。
		/// @remark 有効な範囲は [begin, end) であるため、この位置に要素は存在しません
		/// @return 配列の終端位置を指すイテレータ
		[[nodiscard]]
		iterator end() noexcept;

		/// @brief 配列の先頭位置を指すイテレータを返します。
		/// @return 配列の先頭位置を指すイテレータ
		[[nodiscard]]
		const_iterator begin() const noexcept;

		/// @brief 配列の終端位置を指すイテレータを返します。
		/// @remark 有効な範囲は [begin, end) であるため、この位置に要素は存在しません
		/// @return 配列の終端位置を指すイテレータ
		[[nodiscard]]
		const_iterator end() const noexcept;

		/// @brief 配列の先頭位置を指すイテレータを返します。
		/// @return 配列の先頭位置を指すイテレータ
		[[nodiscard]]
		const_iterator cbegin() const noexcept;

		/// @brief 配列の終端位置を指すイテレータを返します。
		/// @remark 有効な範囲は [begin, end) であるため、この位置に要素は存在しません
		/// @return 配列の終端位置を指すイテレータ
		[[nodiscard]]
		const_iterator cend() const noexcept;

		/// @brief 配列の末尾位置を指すリバース・イテレータを返します。
		/// @return 配列の末尾位置を指すリバース・イテレータ
		[[nodiscard]]
		reverse_iterator rbegin() noexcept;

		/// @brief 配列の先端位置を指すリバース・イテレータを返します。
		/// @remark 有効な範囲は [rbegin, rend) であるため、この位置に要素は存在しません
		/// @return 配列の先端位置を指すリバース・イテレータ
		[[nodiscard]]
		reverse_iterator rend() noexcept;

		/// @brief 配列の末尾位置を指すリバース・イテレータを返します。
		/// @return 配列の末尾位置を指すリバース・イテレータ
		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept;

		/// @brief 配列の先端位置を指すリバース・イテレータを返します。
		/// @remark 有効な範囲は [rbegin, rend) であるため、この位置に要素は存在しません
		/// @return 配列の先端位置を指すリバース・イテレータ
		[[nodiscard]]
		const_reverse_iterator rend() const noexcept;

		/// @brief 配列の末尾位置を指すリバース・イテレータを返します。
		/// @return 配列の末尾位置を指すリバース・イテレータ
		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept;

		/// @brief 配列の先端位置を指すリバース・イテレータを返します。
		/// @remark 有効な範囲は [rbegin, rend) であるため、この位置に要素は存在しません
		/// @return 配列の先端位置を指すリバース・イテレータ
		[[nodiscard]]
		const_reverse_iterator crend() const noexcept;

		/// @brief 配列が空であるかを返します。
		/// @return 配列が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool empty() const noexcept;

		/// @brief 配列が空であるかを返します。
		/// @remark `empty()` と同じです。
		/// @return 配列が空である場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isEmpty() const noexcept;

		/// @brief 配列が要素を持っているかを返します。
		/// @return 配列が要素を持っている場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 配列の要素数を返します。
		/// @return 配列の要素数
		[[nodiscard]]
		size_type size() const noexcept;

		/// @brief 配列の要素数の最大値を返します。
		/// @return 配列の要素数の最大値
		[[nodiscard]]
		size_type max_size() const noexcept;

		/// @brief 要素数 n までメモリの再確保無しで格納できるよう、必要に応じてメモリを再確保します
		/// @param n メモリを確保する要素数
		void reserve(size_type n);

		/// @brief メモリの再確保無しで格納できる要素数を返します。
		/// @return メモリの再確保無しで格納できる要素数
		[[nodiscard]]
		size_type capacity() const noexcept;

		/// @brief capacity() を size() まで減らすようにします。
		/// @remark この関数の呼び出しの後で capacity() == size() になるとは限りません。
		void shrink_to_fit();

		void clear() noexcept;

		iterator insert(const_iterator pos, const value_type& value);

		iterator insert(const_iterator pos, value_type&& value);

		iterator insert(const_iterator pos, size_type count, const value_type& value);

		template <class Iterator>
		iterator insert(const_iterator pos, Iterator first, Iterator last);

		iterator insert(const_iterator pos, std::initializer_list<value_type> ilist);

		template <class... Args>
		iterator emplace(const_iterator pos, Args&&... args);

		iterator erase(const_iterator pos);

		iterator erase(const_iterator first, const_iterator last);

		/// @brief 配列の末尾に要素を追加します。
		/// @param value 追加する値
		void push_back(const value_type& value);

		/// @brief 配列の末尾に要素を追加します。
		/// @param value 追加する値
		void push_back(value_type&& value);

		template <class... Args>
		reference emplace_back(Args&&... args);

		/// @brief 配列の末尾の要素を削除します。
		/// @remark 配列が空の時に呼んではいけません。
		void pop_back();

		void resize(size_type count);

		void resize(size_type count, const value_type& value);

		/// @brief 他の配列と要素を入れ替えます。
		/// @param other 入れ替える配列
		void swap(Array& other) noexcept;

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

		/// @brief 配列の末尾に要素を追加します。
		/// @param value 追加する値
		/// @return *this
		Array& operator <<(const value_type& value);

		/// @brief 配列の末尾に要素を追加します。
		/// @param value 追加する値
		/// @return *this
		Array& operator <<(value_type&& value);

		/// @brief 各要素に関数を適用します。
		/// @tparam Fty 適用する関数の型
		/// @param f 適用する関数
		/// @remark Fty が戻り値を持たない場合 `.each(f), 戻り値を持つ場合は `.map(f)` と同じです。
		/// @return 各要素に関数を適用した結果の配列。Fty が戻り値を持たない場合 void
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		auto operator >>(Fty f) const;

		/// @brief 全ての要素が条件を満たすかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 全ての要素が条件を満たすか、配列が空の場合 true, それ以外の場合は false
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool all(Fty f = Identity) const;

		/// @brief 条件を満たす要素があるかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 条件を満たす要素が 1 つでもあれば true, それ以外の場合は false
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool any(Fty f = Identity) const;

		/// @brief 配列の末尾に別の配列を追加します。
		/// @param other_array 追加する配列
		/// @return *this
		Array& append(const Array& other_array);

		/// @brief 配列の要素を 1 つランダムに返します。
		/// @return 配列からランダムに選ばれた要素への参照
		[[nodiscard]]
		value_type& choice();

		/// @brief 配列の要素を 1 つランダムに返します。
		/// @return 配列からランダムに選ばれた要素への参照
		[[nodiscard]]
		const value_type& choice() const;

		/// @brief 指定した乱数エンジンを用いて、配列の要素を 1 つランダムに返します。
		/// @tparam URBG 使用する乱数エンジンの型
		/// @param rbg 使用する乱数エンジン
		/// @return 配列からランダムに選ばれた要素への参照
		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		value_type& choice(URBG&& rbg);

		/// @brief 指定した乱数エンジンを用いて、配列の要素を 1 つランダムに返します。
		/// @tparam URBG 使用する乱数エンジンの型
		/// @param rbg 使用する乱数エンジン
		/// @return 配列からランダムに選ばれた要素への参照
		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		const value_type& choice(URBG&& rbg) const;

		/// @brief 配列の要素から指定した個数だけ重複なくランダムに選んで返します。
		/// @tparam Int 個数に使う整数型
		/// @param n 選択する個数
		/// @return ランダムに選ばれた要素の配列
		SIV3D_CONCEPT_INTEGRAL
		[[nodiscard]]
		Array choice(Int n) const;

		/// @brief 指定した乱数エンジンを用いて、 配列の要素から指定した個数だけ重複なくランダムに選んで返します。
		/// @tparam Size_t 個数に使う整数型
		/// @param n 選択する個数
		/// @param rbg 使用する乱数エンジン
		/// @return ランダムに選ばれた要素の配列
	# if __cpp_lib_concepts
		template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
	# else
		template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>* = nullptr,
			std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>* = nullptr>
	# endif
		[[nodiscard]]
		Array choice(Size_t n, URBG&& rbg) const;

		/// @brief 指定した個数の要素を持つ配列のグループに分割します。最後のグループの要素数は n 個未満になることがあります。
		/// @param n 1 つのグループが持つ要素数
		/// @remark { 0, 1, 2, 3, 4, 5, 6 } を 3 個の要素を持つ配列のグループに分割すると { { 0, 1, 2 }, { 3, 4, 5 }, { 6 }} になります。
		/// @return 分割されたグループ
		[[nodiscard]]
		Array<Array<value_type>> chunk(size_t n) const;

		/// @brief 指定した値と等しい要素の個数を返します。
		/// @param value 検索する値
		/// @return 指定した値と等しい要素の個数
		[[nodiscard]]
		size_t count(const value_type& value) const;

		/// @brief 条件を満たす要素の個数を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 条件を満たす要素の個数
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		size_t count_if(Fty f) const;

		/// @brief 全ての要素を順番に引数にして関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @remark `for (auto& x : xs) f(x);` と同じです。
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		Array& each(Fty f);

		/// @brief 全ての要素を順番に引数にして関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @remark `for (const auto& x : xs) f(x);` と同じです。
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		const Array& each(Fty f) const;

		/// @brief 全ての要素とそのインデックスを順番に引数にして関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @remark `for (size_t i = 0; auto& x : xs) f(i++, x);` と同じです。
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, Type&>>* = nullptr>
		Array& each_index(Fty f);

		/// @brief 全ての要素とそのインデックスを順番に引数にして関数を呼び出します。
		/// @tparam Fty 呼び出す関数の型
		/// @param f 呼び出す関数
		/// @remark `for (size_t i = 0; const auto& x : xs) f(i++, x);` と同じです。
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, Type>>* = nullptr>
		const Array& each_index(Fty f) const;

		/// @brief 指定したインデックスにある要素を返します。インデックスが範囲外の場合デフォルト値を返します。
		/// @param index インデックス
		/// @param defaultValue インデックスが範囲外の場合に返すデフォルト値
		/// @return 指定したインデックスにある要素、範囲外の場合 defaultValue
		[[nodiscard]]
		const value_type& fetch(size_t index, const value_type& defaultValue) const;

		/// @brief 指定した値を全ての要素に代入します。
		/// @param value 代入する値
		/// @return *this
		Array& fill(const value_type& value);

		/// @brief 指定した条件を満たす要素だけを集めた新しい配列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @remark 結果において、要素の前後関係は維持されます。
		/// @return 指定した条件を満たす要素を集めた新しい配列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array filter(Fty f) const;

		/// @brief 要素を指定したグループ数に分割します。
		/// @param group グループ数
		/// @remark { 0, 1, 2, 3, 4, 5, 6 } を 3 グループに分割すると { { 0, 1, 2 }, { 3, 4 }, { 5, 6 }} になります。
		/// @return 分割したグループ
		[[nodiscard]]
		Array<Array<value_type>> in_groups(size_t group) const;

		/// @brief 指定した値と等しい要素があるかを返します。
		/// @param value 検索する値
		/// @return 指定した値と等しい要素がある場合 true, それ以外の場合は false
		[[nodiscard]]
		bool includes(const value_type& value) const;

		/// @brief 指定した条件を満たす要素があるかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @remark `.any(f)` と同じです。
		/// @return 条件を満たす要素が 1 つでもあれば true, それ以外の場合は false
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool includes_if(Fty f) const;

		/// @brief 配列の要素が昇順にソートされているかを返します。
		/// @return 配列の要素が昇順にソートされている場合 true, それ以外の場合は false
		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		bool isSorted() const;

		/// @brief 
		/// @param sep 
		/// @param begin 
		/// @param end 
		/// @return 
		[[nodiscard]]
		String join(StringView sep = U", "_sv, StringView begin = U"{"_sv, StringView end = U"}"_sv) const;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		auto map(Fty f) const;

		/// @brief 条件を満たす要素が存在しないかを返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 条件を満たす要素数が 0 個の場合 true, それ以外の場合は false
		template <class Fty = decltype(Identity), std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		bool none(Fty f = Identity) const;

		/// @brief 条件を満たすすべての要素を、条件を満たさないすべての要素より前に移動させます。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 区分化された境界を指すイテレータ
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		auto partition(Fty f);

		/// @brief 
		/// @tparam Fty 
		/// @tparam R 
		/// @param f 
		/// @param init 
		/// @return 
		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, Type, Type>>>
		auto reduce(Fty f, R init) const;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type, Type>>* = nullptr>
		auto reduce1(Fty f) const;

		/// @brief 
		/// @param value 
		/// @return 
		Array& remove(const value_type& value);

		/// @brief 
		/// @param value 
		/// @return 
		[[nodiscard]]
		Array removed(const value_type& value) const&;

		/// @brief 
		/// @param value 
		/// @return 
		[[nodiscard]]
		Array removed(const value_type& value)&&;

		/// @brief 
		/// @param index 
		/// @return 
		Array& remove_at(size_t index);

		/// @brief 
		/// @param index 
		/// @return 
		[[nodiscard]]
		Array removed_at(size_t index) const;

		/// @brief 条件を満たす要素を配列から削除します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件
		/// @return *this
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		Array& remove_if(Fty f);

		/// @brief 条件を満たす要素を配列から削除した新しい配列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件
		/// @return 新しい配列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array removed_if(Fty f) const&;

		/// @brief 条件を満たす要素を配列から削除した新しい配列を返します。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件
		/// @return 新しい配列
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array removed_if(Fty f)&&;

		/// @brief 
		/// @param oldValue 
		/// @param newValue 
		/// @return 
		Array& replace(const value_type& oldValue, const value_type& newValue);

		/// @brief 
		/// @param oldValue 
		/// @param newValue 
		/// @return 
		[[nodiscard]]
		Array replaced(const value_type& oldValue, const value_type& newValue) const&;

		/// @brief 
		/// @param oldValue 
		/// @param newValue 
		/// @return 
		[[nodiscard]]
		Array replaced(const value_type& oldValue, const value_type& newValue)&&;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @param newValue 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		Array& replace_if(Fty f, const value_type& newValue);

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @param newValue 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array replaced_if(Fty f, const value_type& newValue) const&;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @param newValue 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array replaced_if(Fty f, const value_type& newValue)&&;

		/// @brief 配列の要素を逆順に並び替えます。
		/// @return *this
		Array& reverse();

		/// @brief 配列の要素を逆順に並び替えた新しい配列を返します。
		/// @return 新しい配列
		[[nodiscard]]
		Array reversed() const&;

		/// @brief 配列の要素を逆順に並び替えた新しい配列を返します。
		/// @return 新しい配列
		[[nodiscard]]
		Array reversed()&&;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		Array& reverse_each(Fty f);

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		const Array& reverse_each(Fty f) const;

		/// @brief 
		/// @param count 
		/// @return 
		Array& rotate(std::ptrdiff_t count = 1);

		/// @brief 
		/// @param count 
		/// @return 
		[[nodiscard]]
		Array rotated(std::ptrdiff_t count = 1) const&;

		/// @brief 
		/// @param count 
		/// @return 
		[[nodiscard]]
		Array rotated(std::ptrdiff_t count = 1)&&;

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasGreaterThan_v<T>>* = nullptr>
		Array& rsort();

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasGreaterThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array rsorted() const&;

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasGreaterThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array rsorted()&&;

		/// @brief 配列の要素の並び順をランダムにシャッフルします。
		/// @return *this
		Array& shuffle();

		/// @brief 
		/// @param rbg 
		/// @return 
		SIV3D_CONCEPT_URBG
		Array& shuffle(URBG&& rbg);

		/// @brief 
		/// @return 
		[[nodiscard]]
		Array shuffled() const&;

		/// @brief 
		/// @return 
		[[nodiscard]]
		Array shuffled()&&;

		/// @brief 
		/// @tparam URBG 
		/// @param rbg 
		/// @return 
		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		Array shuffled(URBG&& rbg) const&;

		/// @brief 
		/// @tparam URBG 
		/// @param rbg 
		/// @return 
		SIV3D_CONCEPT_URBG
		[[nodiscard]]
		Array shuffled(URBG&& rbg)&&;

		/// @brief 
		/// @param index 
		/// @return 
		[[nodiscard]]
		Array slice(size_t index) const;

		/// @brief 
		/// @param index 
		/// @param length 
		/// @return 
		[[nodiscard]]
		Array slice(size_t index, size_t length) const;

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		Array& sort();

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		Array& stable_sort();

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		Array& sort_by(Fty f);

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		Array& stable_sort_by(Fty f);

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array sorted() const&;

		/// @brief 相対順序を保ちながら、条件を満たすすべての要素を、条件を満たさないすべての要素より前に移動させます。
		/// @tparam Fty 条件を記述した関数の型
		/// @param f 条件を記述した関数
		/// @return 区分化された境界を指すイテレータ
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		auto stable_partition(Fty f);

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted() const&;

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array sorted()&&;

		/// @brief 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasLessThan_v<T>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted()&&;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Array sorted_by(Fty f) const&;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted_by(Fty f) const&;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Array sorted_by(Fty f)&&;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>* = nullptr>
		[[nodiscard]]
		Array stable_sorted_by(Fty f)&&;

		/// @brief 
		/// @tparam T 
		/// @return 
		template <class T = Type, std::enable_if_t<Meta::HasPlus_v<T>>* = nullptr>
		[[nodiscard]]
		auto sum() const;

		/// @brief 
		/// @tparam T 
		template <class T = Type, std::enable_if_t<not Meta::HasPlus_v<T>>* = nullptr>
		void sum() const = delete;

		/// @brief 
		/// @tparam T 
		/// @return 
		template <class T = Type, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
		[[nodiscard]]
		auto sumF() const;

		/// @brief 
		/// @tparam T 
		/// @return 
		template <class T = Type, std::enable_if_t<not std::is_floating_point_v<T>>* = nullptr>
		[[nodiscard]]
		auto sumF() const = delete;

		/// @brief 
		/// @param n 
		/// @return 
		[[nodiscard]]
		Array take(size_t n) const;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		Array take_while(Fty f) const;

		/// @brief 
		/// @return 
		Array& stable_unique();

		/// @brief 
		/// @return 
		[[nodiscard]]
		Array stable_uniqued() const;

		/// @brief 
		/// @return 
		Array& sort_and_unique();

		/// @brief 
		/// @return 
		[[nodiscard]]
		Array sorted_and_uniqued() const&;

		/// @brief 
		/// @return 
		[[nodiscard]]
		Array sorted_and_uniqued()&&;

		/// @brief 
		/// @return 
		Array& unique_consecutive();

		/// @brief 
		/// @return 
		[[nodiscard]]
		Array uniqued_consecutive() const&;

		/// @brief 
		/// @return 
		[[nodiscard]]
		Array uniqued_consecutive()&&;

		/// @brief 
		/// @param indices 
		/// @return 
		[[nodiscard]]
		Array values_at(std::initializer_list<size_t> indices) const;

	# ifndef SIV3D_NO_CONCURRENT_API

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>* = nullptr>
		[[nodiscard]]
		size_t parallel_count_if(Fty f) const;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>* = nullptr>
		void parallel_each(Fty f);

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		void parallel_each(Fty f) const;

		/// @brief 
		/// @tparam Fty 
		/// @param f 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>* = nullptr>
		auto parallel_map(Fty f) const;

	# endif

		/// @brief 
		/// @param output 
		/// @param value 
		/// @return 
		friend std::ostream& operator <<(std::ostream& output, const Array& value)
		{
			return (output << Format(value).narrow());
		}

		/// @brief 
		/// @param output 
		/// @param value 
		/// @return 
		friend std::wostream& operator <<(std::wostream& output, const Array& value)
		{
			return (output << Format(value).toWstr());
		}

		/// @brief 
		/// @param output 
		/// @param value 
		/// @return 
		friend std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const Array& value)
		{
			const String s = Format(value);
			return output.write(s.data(), s.size());
		}

		/// @brief 
		/// @param formatData 
		/// @param value 
		friend void Formatter(FormatData& formatData, const Array& value)
		{
			Formatter(formatData, value.begin(), value.end());
		}

		/// @brief 
		/// @tparam Fty 
		/// @param size 
		/// @param generator 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		[[nodiscard]]
		static Array Generate(size_type size, Fty generator);

		/// @brief 
		/// @tparam Fty 
		/// @param size 
		/// @param indexedGenerator 
		/// @return 
		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		[[nodiscard]]
		static Array IndexedGenerate(size_type size, Fty indexedGenerator);

#if __cpp_impl_three_way_comparison

		[[nodiscard]]
		auto operator <=>(const Array& rhs) const {
			return m_container <=> rhs.m_container;
		};

#endif

	private:

		container_type m_container;
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

	/// @brief 
	/// @tparam T0 
	/// @tparam ...Ts 
	/// @param first 
	/// @param ...args 
	/// @return 
	template <class T0, class... Ts>
	[[nodiscard]]
	inline auto MakeArray(T0&& first, Ts&&... args);
}

# include "detail/Array.ipp"
# include "detail/BoolArray.ipp"
