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
# include "Fwd.hpp"
# include "Array.hpp"
# include "Point.hpp"
# include "Format.hpp"

namespace s3d
{
	/// <summary>
	/// 可変長二次元配列
	/// </summary>
	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	class Grid
	{
	public:

		using container_type			= Array<Type, Allocator>;
		using value_type				= typename container_type::value_type;
		using pointer					= typename container_type::pointer;
		using const_pointer				= typename container_type::const_pointer;
		using reference					= typename container_type::reference;
		using const_reference			= typename container_type::const_reference;
		using iterator					= typename container_type::iterator;
		using const_iterator			= typename container_type::const_iterator;
		using reverse_iterator			= typename container_type::reverse_iterator;
		using const_reverse_iterator	= typename container_type::const_reverse_iterator;
		using size_type					= typename container_type::size_type;
		using difference_type			= typename container_type::difference_type;
		using allocator_type			= typename container_type::allocator_type;

	private:

		container_type m_data;

		size_type m_width = 0;

		size_type m_height = 0;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Grid() = default;

		Grid(const Grid& g) = default;

		Grid(Grid&& g) = default;

		/// <summary>
		/// 幅と高さを指定して二次元配列を作成します。
		/// </summary>
		/// <param name="w">
		/// 幅(列数)
		/// </param>
		/// <param name="h">
		/// 高さ(行数)
		/// </param>
		Grid(size_type w, size_type h)
			: m_data(w * h)
			, m_width(w)
			, m_height(h) {}

		/// <summary>
		/// 幅と高さと初期値を指定して二次元配列を作成します。
		/// </summary>
		/// <param name="w">
		/// 幅(列数)
		/// </param>
		/// <param name="h">
		/// 高さ(行数)
		/// </param>
		/// <param name="val">
		/// 初期値
		/// </param>
		Grid(size_type w, size_type h, const Type& val)
			: m_data(w * h, val)
			, m_width(w)
			, m_height(h) {}

		/// <summary>
		/// 幅と高さを指定して二次元配列を作成します。
		/// </summary>
		/// <param name="size">
		/// 幅(列数)と高さ(行数)
		/// </param>
		explicit Grid(const Size& size)
			: Grid(size.x, size.y) {}

		/// <summary>
		/// 幅と高さと初期値を指定して二次元配列を作成します。
		/// </summary>
		/// <param name="size">
		/// 幅(列数)と高さ(行数)
		/// </param>
		/// <param name="val">
		/// 初期値
		/// </param>
		Grid(const Size& size, const Type& val)
			: Grid(size.x, size.y, val) {}

		/// <summary>
		/// 配列から二次元配列を作成します。
		/// </summary>
		/// <param name="w">
		/// 幅(列数)
		/// </param>
		/// <param name="h">
		/// 高さ(行数)
		/// </param>
		/// <param name="data">
		/// 初期値
		/// </param>
		Grid(size_type w, size_type h, const Array<Type>& data)
			: m_data(data)
			, m_width(w)
			, m_height(h)
		{
			m_data.resize(w * h);
		}

		/// <summary>
		/// 配列から二次元配列を作成します。
		/// </summary>
		/// <param name="w">
		/// 幅(列数)
		/// </param>
		/// <param name="h">
		/// 高さ(行数)
		/// </param>
		/// <param name="data">
		/// 初期値
		/// </param>
		Grid(size_type w, size_type h, Array<Type>&& data)
			: m_data(std::move(data))
			, m_width(w)
			, m_height(h)
		{
			m_data.resize(w * h);
		}

		Grid(const Size& size, const Array<Type>& data)
			: Grid(size.x, size.y, data) {}

		Grid(const Size& size, Array<Type>&& data)
			: Grid(size.x, size.y, std::move(data)) {}

		/// <summary>
		/// Initializer-list から二次元配列を作成します。
		/// </summary>
		/// <param name="set">
		/// Initializer-list
		/// </param>
		Grid(const std::initializer_list<std::initializer_list<Type>>& set)
			: Grid(std::max_element(set.begin(), set.end(),
				[](auto& lhs, auto& rhs) { return lhs.size() < rhs.size(); })->size(), set.size())
		{
			auto dst = begin();

			for (const auto& a : set)
			{
				std::copy(a.begin(), a.end(), dst);
				dst += m_width;
			}
		}

		/// <summary>
		/// コピー代入演算子
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Grid& operator =(const Grid& other) = default;

		/// <summary>
		/// ムーブ代入演算子
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Grid& operator =(Grid&& other) = default;

		/// <summary>
		/// アロケータオブジェクトを返します。
		/// </summary>
		/// <returns>
		/// アロケータオブジェクト
		/// </returns>
		allocator_type get_allocator() const noexcept
		{
			return m_data.get_allocator();
		}

		void assign(size_type w, size_type h, const Type& value)
		{
			m_data.assign(w * h, value);
		}

		void assign(const Size& size, const Type& value)
		{
			assign(size.x, size.y, value);
		}

		void assign(const std::initializer_list<std::initializer_list<Type>>& set)
		{
			m_data.clear();

			m_data.resize(std::max_element(set.begin(), set.end(),
				[](auto& lhs, auto& rhs) { return lhs.size() < rhs.size(); })->size(), set.size());

			auto dst = begin();

			for (const auto& a : set)
			{
				std::copy(a.begin(), a.end(), dst);
				dst += m_width;
			}
		}

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <param name="x">
		/// 位置(列)
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		Type& at(size_type y, size_type x)
		{
			// See "Avoid Duplication in const and Non-const Member Function," on pp. 23,
			// in Item 3 "Use const whenever possible," in Effective C++ 3rd edition, by Scott Meyers.
			return const_cast<Type&>(static_cast<const Grid&>(*this).at(y, x));
		}
		
		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <param name="x">
		/// 位置(列)
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		const Type& at(size_type y, size_type x) const
		{
			if (!inBounds(y, x))
			{
				throw std::out_of_range("Grid::at() index out of range");
			}

			return m_data[y * m_width + x];
		}

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		Type& at(const Point& pos)
		{
			return const_cast<Type&>(static_cast<const Grid&>(*this).at(pos));
		}

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <exception cref="std::out_of_range">
		/// 範囲外アクセスの場合 throw されます。
		/// </exception>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		const Type& at(const Point& pos) const
		{
			return at(pos.y, pos.x);
		}

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="index">
		/// 位置(行)
		/// </param>
		/// <remarks>
		/// grid[y][x] で指定した要素にアクセスします。
		/// </remarks>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		Type* operator[] (size_t index)
		{
			return const_cast<Type&>(static_cast<const Grid&>(*this)[index]);
		}

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="index">
		/// 位置(行)
		/// </param>
		/// <remarks>
		/// grid[y][x] で指定した要素にアクセスします。
		/// </remarks>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		const Type* operator[] (size_t index) const
		{
			return &m_data[index * m_width];
		}

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		Type& operator[] (const Point& pos)
		{
			return const_cast<Type&>(static_cast<const Grid&>(*this)[pos]);
		}

		/// <summary>
		/// 指定した位置の要素への参照を返します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <returns>
		/// 指定した位置の要素への参照
		/// </returns>
		const Type& operator[] (const Point& pos) const
		{
			return m_data[pos.y * m_width + pos.x];
		}

		bool inBounds(int64 y, int64 x) const noexcept
		{
			return (0 <= y) && (y < static_cast<int64>(m_height)) && (0 <= x) && (x < static_cast<int64>(m_width));
		}

		/// <summary>
		/// 二次元配列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭へのポインタ
		/// </returns>
		pointer data() noexcept { return m_data.data(); }

		/// <summary>
		/// 二次元配列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭へのポインタ
		/// </returns>
		const_pointer data() const noexcept { return m_data.data(); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		iterator begin() noexcept { return m_data.begin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		iterator end() noexcept { return m_data.end(); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		const_iterator begin() const noexcept { return m_data.cbegin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		const_iterator end() const noexcept { return m_data.cend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		reverse_iterator rbegin() noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		reverse_iterator rend() noexcept { return m_data.rend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		const_reverse_iterator rbegin() const noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator rend() const noexcept { return m_data.rend(); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		const_iterator cbegin() const noexcept { return m_data.cbegin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		const_iterator cend() const noexcept { return m_data.cend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		const_reverse_iterator crbegin() const noexcept { return m_data.crbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		const_reverse_iterator crend() const noexcept { return m_data.crend(); }

		bool empty() const noexcept { return m_data.empty(); }

		bool isEmpty() const noexcept { return m_data.empty(); }

		size_type width() const noexcept { return m_width; }

		size_type height() const noexcept { return m_height; }

		Size size() const noexcept { return Size{ m_width, m_height }; }

		size_type count() const noexcept { return m_data.size(); }

		size_type size_bytes() const noexcept
		{
			static_assert(std::is_trivially_copyable<Type>::value, "Grid::size_bytes() Type must be trivially copyable.");

			return m_data.size() * sizeof(value_type);
		}

		/// <summary>
		/// Array を返します。
		/// </summary>
		/// <returns>
		/// Array
		/// </returns>
		const container_type& asArray() const noexcept { return m_data; }

		/// <summary>
		/// 二次元配列用のメモリを指定したサイズで確保します。
		/// </summary>
		/// <param name="w">
		/// 確保する幅(列数)
		/// </param>
		/// <param name="h">
		/// 確保する高さ(行数)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reserve(size_type w, size_type h) { m_data.reserve(w * h); }

		void reserve(const Size& size) { reserve(size.x, size.y); }

		size_type capacity() const noexcept { return m_data.capacity(); }

		void shrink_to_fit() { m_data.shrink_to_fit(); }

		void clear() noexcept
		{
			m_data.clear();

			m_width = m_height = 0;
		}

		void release()
		{
			clear();

			shrink_to_fit();
		}

		void swap(Grid& other)
		{
			m_data.swap(other.m_data);
			
			std::swap(m_width, other.m_width);

			std::swap(m_height, other.m_height);
		}

		/// <summary>
		/// 末尾に行を追加します。
		/// </summary>
		/// <param name="value">
		/// 追加される行の要素
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void push_back_row(const Type& value)
		{
			m_data.insert(m_data.end(), m_width, value);

			++m_height;
		}

		/// <summary>
		/// 末尾の行を削除します。
		/// </summary>
		/// <exception cref="std::out_of_range">
		/// 削除する行が無い場合 throw されます。
		/// </exception>
		/// <returns>
		/// なし
		/// </returns>
		void pop_back_row()
		{
			if (m_height == 0)
			{
				throw std::out_of_range("Grid::pop_back_row() pop_back from empty Grid");
			}

			--m_height;

			m_data.resize(m_data.size() - m_width);
		}

		/// <summary>
		/// 指定した位置に行を挿入します。
		/// </summary>
		/// <param name="pos">
		/// 挿入先の位置（行）
		/// </param>
		/// <param name="value">
		/// 追加される行の要素
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void insert_row(size_type pos, const Type& value)
		{
			insert_rows(pos, 1, value);
		}

		/// <summary>
		/// 指定した位置に行を挿入します。
		/// </summary>
		/// <param name="pos">
		/// 挿入先の位置（行）
		/// </param>
		/// <param name="rows">
		/// 挿入する行数
		/// </param>
		/// <param name="value">
		/// 追加される行の要素
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void insert_rows(size_type pos, size_type rows, const Type& value)
		{
			m_data.insert(m_data.begin() + m_width * pos, m_width * rows, value);

			m_height += rows;
		}

		/// <summary>
		/// 指定した位置の行を削除します。
		/// </summary>
		/// <param name="pos">
		/// 削除する行の位置
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void remove_row(size_type pos)
		{
			remove_rows(pos, 1);
		}

		/// <summary>
		/// 指定した位置から行を削除します。
		/// </summary>
		/// <param name="pos">
		/// 削除する行の位置
		/// </param>
		/// <param name="count">
		/// 削除する行数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void remove_rows(size_type pos, size_type count)
		{
			const auto first = m_data.begin() + m_width * pos;
			const auto last = first + m_width * count;

			m_data.erase(first, last);

			m_height -= count;
		}

		/// <summary>
		/// 二次元配列のサイズを変更します。
		/// </summary>
		/// <param name="w">
		/// 新しい幅(列数)
		/// </param>
		/// <param name="h">
		/// 新しい高さ(行数)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_type w, size_type h)
		{
			resize(w, h, Type());
		}

		/// <summary>
		/// 二次元配列のサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しい幅(列数)と高さ(行数)
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(const Size& size)
		{
			resize(size.x, size.y, Type());
		}

		/// <summary>
		/// 二次元配列のサイズを変更します。
		/// </summary>
		/// <param name="w">
		/// 新しい幅(列数)
		/// </param>
		/// <param name="h">
		/// 新しい高さ(行数)
		/// </param>
		/// <param name="val">
		/// 要素を初期化する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(size_type w, size_type h, const Type& val)
		{
			if (w == m_width && h == m_height)
			{
				return;
			}

			m_width = w;

			m_height = h;

			m_data.assign(w * h, val);
		}

		/// <summary>
		/// 二次元配列のサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しい幅(列数)と高さ(行数)
		/// </param>
		/// <param name="val">
		/// 要素を初期化する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void resize(const Size& size, const Type& val)
		{
			resize(size.x, size.y, val);
		}
	};

	template <class Type>
	inline bool operator == (const Grid<Type>& x, const Grid<Type>& y)
	{
		return x.width() == y.width()
			&& x.height() == y.height()
			&& std::equal(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Type>
	inline bool operator != (const Grid<Type>& x, const Grid<Type>& y)
	{
		return !(x == y);
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline std::ostream & operator << (std::ostream& os, const Grid<Type>& grid)
	{
		return os << Format(grid).narrow();
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline std::wostream & operator << (std::wostream& os, const Grid<Type>& grid)
	{
		return os << Format(grid);
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline void Formatter(FormatData& formatData, const Grid<Type>& grid)
	{
		formatData.string.push_back(L'{');

		bool isFirst = true;

		for (typename Grid<Type>::size_type y = 0; y < grid.height(); ++y)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				formatData.string.push_back(L',');

				formatData.string.push_back(L'\n');
			}

			Formatter(formatData, grid[y], grid[y] + grid.width());
		}

		formatData.string.push_back(L'}');
	}
}

namespace std
{
	template <class Type>
	inline void swap(s3d::Grid<Type>& a, s3d::Grid<Type>& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
}
