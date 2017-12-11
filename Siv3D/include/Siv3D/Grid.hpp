﻿//-----------------------------------------------
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
# include "Array.hpp"
# include "PointVector.hpp"
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
		Grid(size_type w, size_type h, const value_type& val)
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
		Grid(const Size& size, const value_type& val)
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
		Grid(size_type w, size_type h, const Array<value_type>& data)
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
		Grid(size_type w, size_type h, Array<value_type>&& data)
			: m_data(std::move(data))
			, m_width(w)
			, m_height(h)
		{
			m_data.resize(w * h);
		}

		Grid(const Size& size, const Array<value_type>& data)
			: Grid(size.x, size.y, data) {}

		Grid(const Size& size, Array<value_type>&& data)
			: Grid(size.x, size.y, std::move(data)) {}

		/// <summary>
		/// Initializer-list から二次元配列を作成します。
		/// </summary>
		/// <param name="set">
		/// Initializer-list
		/// </param>
		Grid(const std::initializer_list<std::initializer_list<value_type>>& set)
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
		[[nodiscard]] allocator_type get_allocator() const noexcept
		{
			return m_data.get_allocator();
		}

		void assign(const size_type w, const size_type h, const value_type& value)
		{
			m_data.assign(w * h, value);
		}

		void assign(const Size& size, const value_type& value)
		{
			assign(size.x, size.y, value);
		}

		void assign(const std::initializer_list<std::initializer_list<value_type>>& set)
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
		value_type& at(const size_type y, const size_type x) &
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
		const value_type& at(const size_type y, const size_type x) const &
		{
			if (!inBounds(y, x))
			{
				throw std::out_of_range("Grid::at() index out of range");
			}

			return m_data[y * m_width + x];
		}

		/// <summary>
		/// 指定した位置の要素を取得します。
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
		value_type at(const size_type y, const size_type x) &&
		{
			if (!inBounds(y, x))
			{
				throw std::out_of_range("Grid::at() index out of range");
			}

			return std::move(m_data[y * m_width + x]);
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
		value_type& at(const Point& pos) &
		{
			return at(pos.y, pos.x);
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
		const value_type& at(const Point& pos) const &
		{
			return at(pos.y, pos.x);
		}

		/// <summary>
		/// 指定した位置の要素を取得します。
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
		value_type at(const Point& pos) &&
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
		[[nodiscard]] value_type* operator[](const size_t index)
		{
			return &m_data[index * m_width];
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
		[[nodiscard]] const value_type* operator[](const size_t index) const
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
		[[nodiscard]] value_type& operator[](const Point& pos) &
		{
			return m_data[pos.y * m_width + pos.x];
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
		[[nodiscard]] const value_type& operator[](const Point& pos) const &
		{
			return m_data[pos.y * m_width + pos.x];
		}

		/// <summary>
		/// 指定した位置の要素を取得します。
		/// </summary>
		/// <param name="pos">
		/// 位置(列と行)
		/// </param>
		/// <returns>
		/// 指定した位置の要素
		/// </returns>
		[[nodiscard]] value_type operator[](const Point& pos) &&
		{
			return std::move(m_data[pos.y * m_width + pos.x]);
		}

		[[nodiscard]] bool inBounds(const int64 y, const int64 x) const noexcept
		{
			return (0 <= y) && (y < static_cast<int64>(m_height)) && (0 <= x) && (x < static_cast<int64>(m_width));
		}

		/// <summary>
		/// 二次元配列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭へのポインタ
		/// </returns>
		[[nodiscard]] pointer data() noexcept { return m_data.data(); }

		/// <summary>
		/// 二次元配列の先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭へのポインタ
		/// </returns>
		[[nodiscard]] const_pointer data() const noexcept { return m_data.data(); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] iterator begin() noexcept { return m_data.begin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] iterator end() noexcept { return m_data.end(); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator begin() const noexcept { return m_data.cbegin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator end() const noexcept { return m_data.cend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		[[nodiscard]] reverse_iterator rbegin() noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] reverse_iterator rend() noexcept { return m_data.rend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator rbegin() const noexcept { return m_data.rbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator rend() const noexcept { return m_data.rend(); }

		/// <summary>
		/// 二次元配列の先頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator cbegin() const noexcept { return m_data.cbegin(); }

		/// <summary>
		/// 二次元配列の終了頭位置のイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の終了位置のイテレータ
		/// </returns>
		[[nodiscard]] const_iterator cend() const noexcept { return m_data.cend(); }

		/// <summary>
		/// 二次元配列の末尾のリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の末尾のリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator crbegin() const noexcept { return m_data.crbegin(); }

		/// <summary>
		/// 二次元配列の先頭の前へのリバースイテレータを返します。
		/// </summary>
		/// <returns>
		/// 二次元配列の先頭の前へのリバースイテレータ
		/// </returns>
		[[nodiscard]] const_reverse_iterator crend() const noexcept { return m_data.crend(); }

		[[nodiscard]] bool empty() const noexcept { return m_data.empty(); }

		[[nodiscard]] bool isEmpty() const noexcept { return m_data.empty(); }

		/// <summary>
		/// 配列に要素が含まれているかを返します。
		/// </summary>
		/// <returns>
		/// 配列に要素が含まれている場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] explicit operator bool() const noexcept
		{
			return !m_data.empty();
		}

		[[nodiscard]] size_type width() const noexcept { return m_width; }

		[[nodiscard]] size_type height() const noexcept { return m_height; }

		[[nodiscard]] Size size() const noexcept { return Size{ m_width, m_height }; }

		[[nodiscard]] size_type count() const noexcept { return m_data.size(); }

		[[nodiscard]] size_type size_elements() const noexcept { return m_data.size(); }

		[[nodiscard]] size_type size_bytes() const noexcept
		{
			static_assert(std::is_trivially_copyable_v<value_type>, "Grid::size_bytes() value_type must be trivially copyable.");

			return m_data.size() * sizeof(value_type);
		}

		/// <summary>
		/// Array を返します。
		/// </summary>
		/// <returns>
		/// Array
		/// </returns>
		[[nodiscard]] const container_type& asArray() const noexcept { return m_data; }

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
		void reserve(const size_type w, const size_type h) { m_data.reserve(w * h); }

		void reserve(const Size& size) { reserve(size.x, size.y); }

		[[nodiscard]] size_type capacity() const noexcept { return m_data.capacity(); }

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

		void swap(Grid& other) noexcept
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
		void push_back_row(const value_type& value)
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

		void push_back_column(const value_type& value)
		{
			reserve(m_width + 1, m_height);

			const size_type w = m_width + 1;

			for (size_type i = 0; i < m_height; ++i)
			{
				m_data.insert(m_data.begin() + i * w + (w - 1), value);
			}

			++m_width;
		}

		void pop_back_column()
		{
			if (m_width == 0)
			{
				throw std::out_of_range("Grid::pop_back_column() pop_back from empty Grid");
			}

			remove_column(m_width - 1);
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
		void insert_row(const size_type pos, const value_type& value)
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
		void insert_rows(const size_type pos, const size_type rows, const value_type& value)
		{
			m_data.insert(m_data.begin() + m_width * pos, m_width * rows, value);

			m_height += rows;
		}

		void insert_column(const size_type pos, const value_type& value)
		{
			reserve(m_width + 1, m_height);

			const size_type w = m_width + 1;

			for (size_type i = 0; i < m_height; ++i)
			{
				m_data.insert(m_data.begin() + i * w + pos, value);
			}

			++m_width;
		}

		void insert_columns(const size_type pos, const size_type columns, const value_type& value)
		{
			reserve(m_width + columns, m_height);

			const size_type w = m_width + columns;

			for (size_type i = 0; i < m_height; ++i)
			{
				for (size_type k = 0; k < columns; ++k)
				{
					m_data.insert(m_data.begin() + i * w + pos + k, value);
				}
			}

			m_width += columns;
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
		void remove_row(const size_type pos)
		{
			if (m_height <= pos)
			{
				throw std::out_of_range("Grid::remove_row() index out of range");
			}

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
		void remove_rows(const size_type pos, const size_type count)
		{
			if (m_height <= pos || m_height <= (pos + count))
			{
				throw std::out_of_range("Grid::remove_rows() index out of range");
			}

			const auto first = m_data.begin() + m_width * pos;
			const auto last = first + m_width * count;

			m_data.erase(first, last);

			m_height -= count;
		}

		/// <summary>
		/// 指定した位置の列を削除します。
		/// </summary>
		/// <param name="pos">
		/// 削除する列の位置
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void remove_column(const size_type pos)
		{
			if (m_width <= pos)
			{
				throw std::out_of_range("Grid::remove_column() index out of range");
			}

			size_type index = 0;

			m_data.remove_if([width = m_width, col = pos, &index](const value_type&)
			{
				return ((index++) % width == col);
			});

			--m_width;
		}

		void remove_columns(const size_type pos, const size_type count)
		{
			if (m_width <= pos || m_width <= (pos + count))
			{
				throw std::out_of_range("Grid::remove_rows() index out of range");
			}

			size_type index = 0;

			m_data.remove_if([width = m_width, a = pos, b = pos + count, &index](const value_type&)
			{
				const size_type col = (index++) % width;

				return a <= col && col < b;
			});

			m_width -= count;
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
		void resize(const size_type w, const size_type h)
		{
			resize(w, h, value_type());
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
			resize(size.x, size.y, value_type());
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
		void resize(const size_type w, const size_type h, const value_type& val)
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
		void resize(const Size& size, const value_type& val)
		{
			resize(size.x, size.y, val);
		}

		template <class Fty = decltype(Id)>
		[[nodiscard]] bool all(Fty f = Id) const
		{
			return m_data.all(f);
		}

		template <class Fty = decltype(Id)>
		[[nodiscard]] bool any(Fty f = Id) const
		{
			return m_data.any(f);
		}

		[[nodiscard]] const value_type& choice() const
		{
			return m_data.choice();
		}

		template <class URBG, std::enable_if_t<!std::is_scalar_v<URBG>>* = nullptr>
		[[nodiscard]] const value_type& choice(URBG&& rbg) const
		{
			return m_data.choice(std::forward<URBG>(rbg));
		}

		template <class Size_t, std::enable_if_t<std::is_scalar_v<Size_t>>* = nullptr>
		[[nodiscard]] Array<value_type> choice(const Size_t n) const
		{
			return m_data.choice(n);
		}

		template <class URBG>
		[[nodiscard]] Array<value_type> choice(const size_t n, URBG&& rbg) const
		{
			return m_data.choice(n, std::forward<URBG>(rbg));
		}

		[[nodiscard]] size_t count(const value_type& value) const
		{
			return m_data.count(value);
		}

		template <class Fty>
		[[nodiscard]] size_t count_if(Fty f) const
		{
			return m_data.count_if(f);
		}

		template <class Fty>
		Grid& each(Fty f)
		{
			m_data.each(f);

			return *this;
		}

		template <class Fty>
		const Grid& each(Fty f) const
		{
			m_data.each(f);

			return *this;
		}

		template <class Fty>
		Grid& each_index(Fty f)
		{
			if (!m_data.empty())
			{
				pointer p = m_data.data();

				for (size_t y = 0; y < m_height; ++y)
				{
					for (size_t x = 0; x < m_width; ++x)
					{
						f({ x,y }, *p++);
					}
				}
			}

			return *this;
		}

		template <class Fty>
		const Grid& each_index(Fty f) const
		{
			if (!m_data.empty())
			{
				const_pointer p = m_data.data();

				for (size_t y = 0; y < m_height; ++y)
				{
					for (size_t x = 0; x < m_width; ++x)
					{
						f({ x,y }, *p++);
					}
				}
			}

			return *this;
		}

		[[nodiscard]] const value_type& fetch(size_type y, size_type x, const value_type& defaultValue) const
		{
			if (!inBounds(y, x))
			{
				return defaultValue;
			}

			return m_data[y * m_width + x];
		}

		[[nodiscard]] const value_type& fetch(const Point& pos, const value_type& defaultValue) const
		{
			return fetch(pos.y, pos.x, defaultValue);
		}

		Grid& fill(const value_type& value)
		{
			m_data.fill(value);

			return *this;
		}

		[[nodiscard]] bool include(const value_type& value) const
		{
			return m_data.include(value);
		}

		template <class Fty>
		[[nodiscard]] bool include_if(Fty f) const
		{
			return m_data.include_if(f);
		}

		template <class Fty>
		auto map(Fty f) const
		{
			Array<std::result_of_t<Fty(value_type)>> data;

			data.reserve(m_width * m_height);

			for (const auto& v : m_data)
			{
				data.push_back(f(v));
			}

			return Grid<std::result_of_t<Fty(value_type)>>(m_width, m_height, std::move(data));
		}

		template <class Fty = decltype(Id)>
		[[nodiscard]] bool none(Fty f = Id) const
		{
			return m_data.none(f);
		}

		template <class Fty>
		auto reduce(Fty f, std::result_of_t<Fty(value_type, value_type)> init) const
		{
			return m_data.reduce(f, init);
		}

		template <class Fty>
		auto reduce1(Fty f) const
		{
			if (m_data.empty())
			{
				throw std::out_of_range("Grid::reduce1() reduce from empty Grid");
			}

			return m_data.reduce1(f);
		}

		Grid& replace(const value_type& oldValue, const value_type& newValue)
		{
			m_data.replace(oldValue, newValue);

			return *this;
		}

		[[nodiscard]] Grid replaced(const value_type& oldValue, const value_type& newValue) const &
		{
			Grid new_grid;

			new_grid.reserve(m_width, m_height);

			for (const auto& v : m_data)
			{
				if (v == oldValue)
				{
					new_grid.push_back(newValue);
				}
				else
				{
					new_grid.push_back(v);
				}
			}

			return new_grid;
		}

		[[nodiscard]] Grid replaced(const value_type& oldValue, const value_type& newValue) &&
		{
			replace(oldValue, newValue);

			return std::move(*this);
		}

		template <class Fty>
		Grid& replace_if(Fty f, const value_type& newValue)
		{
			m_data.replace_if(f, newValue);

			return *this;
		}

		template <class Fty>
		[[nodiscard]] Grid replaced_if(Fty f, const value_type& newValue) const &
		{
			Grid new_grid;

			new_grid.reserve(m_width, m_height);

			for (const auto& v : m_data)
			{
				if (f(v))
				{
					new_grid.push_back(newValue);
				}
				else
				{
					new_grid.push_back(v);
				}
			}

			new_grid.m_width = m_width;
			new_grid.m_height = m_height;

			return new_grid;
		}

		template <class Fty>
		[[nodiscard]] Grid replaced_if(Fty f, const value_type& newValue) &&
		{
			replace_if(f, newValue);

			return std::move(*this);
		}

		Grid& reverse()
		{
			std::reverse(m_data.begin(), m_data.end());

			return *this;
		}

		[[nodiscard]] Grid reversed() const &
		{
			Grid new_grid;

			new_grid.m_data.assign(m_data.rbegin(), m_data.rend());

			new_grid.m_width = m_width;

			new_grid.m_height = m_height;

			return new_grid;
		}

		[[nodiscard]] Grid reversed() &&
		{
			reverse();

			return std::move(*this);
		}

		template <class Fty>
		Grid& reverse_each(Fty f)
		{
			for (auto it = m_data.rbegin(); it != m_data.rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		template <class Fty>
		const Grid& reverse_each(Fty f) const
		{
			for (auto it = m_data.rbegin(); it != m_data.rend(); ++it)
			{
				f(*it);
			}

			return *this;
		}

		Grid& rotate(std::ptrdiff_t count = 1)
		{
			if (empty())
			{
				;
			}
			else if (count > 0) // rotation to the left
			{
				if (static_cast<size_t>(count) > m_data.size())
				{
					count %= m_data.size();
				}

				std::rotate(m_data.begin(), m_data.begin() + count, m_data.end());
			}
			else if (count < 0) // rotation to the right
			{
				count = -count;

				if (static_cast<size_t>(count) > m_data.size())
				{
					count %= m_data.size();
				}

				std::rotate(m_data.rbegin(), m_data.rbegin() + count, m_data.rend());
			}

			return *this;
		}

		[[nodiscard]] Grid rotated(const std::ptrdiff_t count = 1) const &
		{
			return Grid(*this).rotate(count);
		}

		[[nodiscard]] Grid rotated(const std::ptrdiff_t count = 1) &&
		{
			rotate(count);

			return std::move(*this);
		}

		Grid& rotate_rows(const std::ptrdiff_t count = 1)
		{
			return rotate(count * static_cast<std::ptrdiff_t>(m_width));
		}

		[[nodiscard]] Grid rotated_rows(const std::ptrdiff_t count = 1) const &
		{
			return rotated(count * static_cast<std::ptrdiff_t>(m_width));
		}

		[[nodiscard]] Grid rotated_rows(const std::ptrdiff_t count = 1) &&
		{
			return rotated(count * static_cast<std::ptrdiff_t>(m_width));
		}

		Grid& shuffle()
		{
			return shuffle(GetDefaultRNG());
		}

		template <class URBG>
		Grid& shuffle(URBG&& rbg)
		{
			std::shuffle(begin(), end(), std::forward<URBG>(rbg));

			return *this;
		}

		[[nodiscard]] Grid shuffled() const &
		{
			return shuffled(GetDefaultRNG());
		}

		[[nodiscard]] Grid shuffled() &&
		{
			return shuffled(GetDefaultRNG());
		}

		template <class URBG>
		[[nodiscard]] Grid shuffled(URBG&& rbg) const &
		{
			return Grid(*this).shuffle(std::forward<URBG>(rbg));
		}

		template <class URBG>
		[[nodiscard]] Grid shuffled(URBG&& rbg) &&
		{
			shuffle(std::forward<URBG>(rbg));

			return std::move(*this);
		}

		[[nodiscard]] Array<value_type> slice(const size_type y, const size_type x) const
		{
			if (!inBounds(y, x))
			{
				return Array<value_type>();
			}

			return Array<value_type>(m_data.begin() + (y * m_width + x), m_data.end());
		}

		[[nodiscard]] Array<value_type> slice(const Point& pos) const
		{
			return slice(pos.y, pos.x);
		}

		[[nodiscard]] Array<value_type> slice(const size_type y, const size_type x, const size_t length) const
		{
			if (!inBounds(y, x))
			{
				return Array<value_type>();
			}

			const size_type index = (y * m_width + x);

			return Array<value_type>(m_data.begin() + index, m_data.begin() + std::min(index + length, m_data.size()));
		}

		[[nodiscard]] Array<value_type> slice(const Point& pos, const size_t length) const
		{
			return slice(pos.y, pos.x, length);
		}

		Grid& sort()
		{
			std::sort(m_data.begin(), m_data.end());

			return *this;
		}

		template <class Fty>
		Grid& sort_by(Fty f)
		{
			std::sort(m_data.begin(), m_data.end(), f);

			return *this;
		}

		[[nodiscard]] Grid sorted() const &
		{
			return Grid(*this).sort();
		}

		[[nodiscard]] Grid sorted() &&
		{
			sort();

			return std::move(*this);
		}

		template <class Fty>
		[[nodiscard]] Grid sorted_by(Fty f) const &
		{
			return Grid(*this).sort_by(f);
		}

		template <class Fty>
		[[nodiscard]] Grid sorted_by(Fty f) &&
		{
			sort_by(f);

			return std::move(*this);
		}

		[[nodiscard]] Array<value_type> values_at(std::initializer_list<Point> indices) const
		{
			Array<value_type> new_array;

			new_array.reserve(indices.size());

			for (auto index : indices)
			{
				if (index >= size())
				{
					throw std::out_of_range("Grid::values_at() index out of range");
				}

				new_array.push_back(operator[](index));
			}

			return new_array;
		}
	};

	template <class Type>
	[[nodiscard]] inline bool operator ==(const Grid<Type>& x, const Grid<Type>& y)
	{
		return x.width() == y.width()
			&& x.height() == y.height()
			&& std::equal(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Type>
	[[nodiscard]] inline bool operator !=(const Grid<Type>& x, const Grid<Type>& y)
	{
		return !(x == y);
	}
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline void Formatter(FormatData& formatData, const Grid<Type, Allocator>& value)
	{
		formatData.string.push_back(U'{');

		bool isFirst = true;

		for (typename Grid<Type>::size_type y = 0; y < value.height(); ++y)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				formatData.string.push_back(U',');

				formatData.string.push_back(U'\n');
			}

			Formatter(formatData, value[y], value[y] + value.width());
		}

		formatData.string.push_back(U'}');
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline std::ostream & operator <<(std::ostream& output, const Grid<Type, Allocator>& value)
	{
		return output << Format(value).narrow();
	}

	template <class Type, class Allocator = typename DefaultAllocator<Type>::type>
	inline std::wostream & operator <<(std::wostream& output, const Grid<Type, Allocator>& value)
	{
		return output << Format(value).toWstr();
	}
}

//////////////////////////////////////////////////
//
//	Swap
//
//////////////////////////////////////////////////

namespace std
{
	template <class Type>
	inline void swap(s3d::Grid<Type>& a, s3d::Grid<Type>& b) noexcept
	{
		a.swap(b);
	}
}
