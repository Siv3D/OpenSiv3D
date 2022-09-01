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

namespace s3d
{
	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h)
		: m_data(w * h)
		, m_width{ w }
		, m_height{ h } {}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, const value_type& value)
		: m_data(w * h, value)
		, m_width{ w }
		, m_height{ h } {}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const Size size)
		: m_data(size.x * size.y)
		, m_width{ static_cast<size_type>(size.x) }
		, m_height{ static_cast<size_type>(size.y) } {}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const Size size, const value_type& value)
		: m_data(size.x * size.y, value)
		, m_width{ static_cast<size_type>(size.x) }
		, m_height{ static_cast<size_type>(size.y) } {}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, const Array<value_type>& data)
		: m_data(data)
		, m_width{ w }
		, m_height{ h }
	{
		m_data.resize(w * h);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, Array<value_type>&& data)
		: m_data(std::move(data))
		, m_width{ w }
		, m_height{ h }
	{
		m_data.resize(w * h);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(Size size, const Array<value_type>& data)
		: m_data(data)
		, m_width{ static_cast<size_type>(size.x) }
		, m_height{ static_cast<size_type>(size.y) }
	{
		assert(0 <= size.x);
		assert(0 <= size.y);
		m_data.resize(size.x * size.y);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(Size size, Array<value_type>&& data)
		: m_data(std::move(data))
		, m_width{ static_cast<size_type>(size.x) }
		, m_height{ static_cast<size_type>(size.y) }
	{
		assert(0 <= size.x);
		assert(0 <= size.y);
		m_data.resize(size.x * size.y);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const std::initializer_list<std::initializer_list<value_type>>& set)
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

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, Arg::generator_<Fty> generator)
		: Grid(Generate(w, h, *generator)) {}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Grid<Type, Allocator>::Grid(const Size size, Arg::generator_<Fty> generator)
		: Grid(Generate(size, *generator)) {}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, Point>>*>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, Arg::indexedGenerator_<Fty> indexedGenerator)
		: Grid(IndexedGenerate(w, h, *indexedGenerator)) {}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, Point>>*>
	inline Grid<Type, Allocator>::Grid(const Size size, Arg::indexedGenerator_<Fty> indexedGenerator)
		: Grid(IndexedGenerate(size, *indexedGenerator)) {}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::swap(Grid& other) noexcept
	{
		m_data.swap(other.m_data);
		std::swap(m_width, other.m_width);
		std::swap(m_height, other.m_height);
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::allocator_type Grid<Type, Allocator>::get_allocator() const noexcept
	{
		return m_data.get_allocator();
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::assign(const size_type w, const size_type h, const value_type& value)
	{
		m_data.assign(w * h, value);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::assign(const Size size, const value_type& value)
	{
		assert(0 <= size.x);
		assert(0 <= size.y);
		m_data.assign(size.x * size.y, value);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::assign(const std::initializer_list<std::initializer_list<value_type>>& set)
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

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::at(const size_type y, const size_type x)&
	{
		if (not inBounds(y, x))
		{
			throw std::out_of_range("Grid::at(): index out of range");
		}

		return m_data[(y * m_width) + x];
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::at(const size_type y, const size_type x) const&
	{
		if (not inBounds(y, x))
		{
			throw std::out_of_range("Grid::at(): index out of range");
		}

		return m_data[(y * m_width) + x];
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type Grid<Type, Allocator>::at(const size_type y, const size_type x)&&
	{
		if (not inBounds(y, x))
		{
			throw std::out_of_range("Grid::at(): index out of range");
		}

		return std::move(m_data[y * m_width + x]);
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::at(const Point pos)&
	{
		return at(pos.y, pos.x);
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::at(const Point pos) const&
	{
		return at(pos.y, pos.x);
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type Grid<Type, Allocator>::at(const Point pos)&&
	{
		return at(pos.y, pos.x);
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type* Grid<Type, Allocator>::operator[](const size_t index)
	{
		return &m_data[index * m_width];
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type* Grid<Type, Allocator>::operator[](const size_t index) const
	{
		return &m_data[index * m_width];
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::operator[](const Point pos)&
	{
		return m_data[(pos.y * m_width) + pos.x];
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::operator[](const Point pos) const&
	{
		return m_data[(pos.y * m_width) + pos.x];
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type Grid<Type, Allocator>::operator[](const Point pos)&&
	{
		return std::move(m_data[(pos.y * m_width) + pos.x]);
	}

	template <class Type, class Allocator>
	inline bool Grid<Type, Allocator>::inBounds(const int64 y, const int64 x) const noexcept
	{
		return (0 <= y) && (y < static_cast<int64>(m_height))
			&& (0 <= x) && (x < static_cast<int64>(m_width));
	}

	template <class Type, class Allocator>
	inline bool Grid<Type, Allocator>::inBounds(const Point pos) const noexcept
	{
		return (0 <= pos.y) && (pos.y < static_cast<int64>(m_height))
			&& (0 <= pos.x) && (pos.x < static_cast<int64>(m_width));
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::pointer Grid<Type, Allocator>::data() noexcept
	{
		return m_data.data();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_pointer Grid<Type, Allocator>::data() const noexcept
	{
		return m_data.data();
	}

	template <class Type, class Allocator>
	inline bool Grid<Type, Allocator>::empty() const noexcept
	{
		return m_data.empty();
	}

	template <class Type, class Allocator>
	inline bool Grid<Type, Allocator>::isEmpty() const noexcept
	{
		return m_data.empty();
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::operator bool() const noexcept
	{
		return (not m_data.empty());
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::size_type Grid<Type, Allocator>::width() const noexcept
	{
		return m_width;
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::size_type Grid<Type, Allocator>::height() const noexcept
	{
		return m_height;
	}

	template <class Type, class Allocator>
	inline Size Grid<Type, Allocator>::size() const noexcept
	{
		return{ m_width, m_height };
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::size_type Grid<Type, Allocator>::num_elements() const noexcept
	{
		return m_data.size();
	}

	template <class Type, class Allocator>
	inline size_t Grid<Type, Allocator>::size_bytes() const noexcept
	{
		static_assert(std::is_trivially_copyable_v<value_type>, "Grid::size_bytes(): value_type must be trivially copyable.");

		return m_data.size() * sizeof(value_type);
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::container_type& Grid<Type, Allocator>::asArray() const noexcept
	{
		return m_data;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::reserve(const size_type w, const size_type h)
	{
		m_data.reserve(w * h);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::reserve(const Size size)
	{
		assert(0 <= size.x);
		assert(0 <= size.y);
		m_data.reserve(size.x * size.y);
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::size_type Grid<Type, Allocator>::capacity() const noexcept
	{
		return m_data.capacity();
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::shrink_to_fit()
	{
		m_data.shrink_to_fit();
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::clear() noexcept
	{
		m_data.clear();

		m_width = m_height = 0;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::release()
	{
		clear();

		shrink_to_fit();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::iterator Grid<Type, Allocator>::begin() noexcept
	{
		return m_data.begin();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::iterator Grid<Type, Allocator>::end() noexcept
	{
		return m_data.end();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_iterator Grid<Type, Allocator>::begin() const noexcept
	{
		return m_data.begin();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_iterator Grid<Type, Allocator>::end() const noexcept
	{
		return m_data.end();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_iterator Grid<Type, Allocator>::cbegin() const noexcept
	{
		return m_data.cbegin();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_iterator Grid<Type, Allocator>::cend() const noexcept
	{
		return m_data.cend();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::reverse_iterator Grid<Type, Allocator>::rbegin() noexcept
	{
		return m_data.rbegin();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::reverse_iterator Grid<Type, Allocator>::rend() noexcept
	{
		return m_data.rend();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_reverse_iterator Grid<Type, Allocator>::rbegin() const noexcept
	{
		return m_data.rbegin();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_reverse_iterator Grid<Type, Allocator>::rend() const noexcept
	{
		return m_data.rend();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_reverse_iterator Grid<Type, Allocator>::crbegin() const noexcept
	{
		return m_data.crbegin();
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::const_reverse_iterator Grid<Type, Allocator>::crend() const noexcept
	{
		return m_data.crend();
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::push_back_row(const value_type& value)
	{
		m_data.insert(m_data.end(), m_width, value);

		++m_height;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::pop_back_row()
	{
		if (m_height == 0)
		{
			throw std::out_of_range("Grid::pop_back_row(): pop_back_row from empty Grid");
		}

		--m_height;

		m_data.resize(m_data.size() - m_width);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::pop_back_row_N(const size_t n)
	{
		m_height -= Min(n, m_height);
		
		m_data.resize(m_width * m_height);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::push_back_column(const value_type& value)
	{
		reserve((m_width + 1), m_height);

		const size_type w = (m_width + 1);

		for (size_type i = 0; i < m_height; ++i)
		{
			m_data.insert(m_data.begin() + (i * w + (w - 1)), value);
		}

		++m_width;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::pop_back_column()
	{
		if (m_width == 0)
		{
			throw std::out_of_range("Grid::pop_back_column(): pop_back from empty Grid");
		}

		remove_column(m_width - 1);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::pop_back_column_N(const size_t n)
	{
		const size_t w = Min(n, m_width);

		remove_columns((m_width - w), w);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::insert_row(const size_type pos, const value_type& value)
	{
		insert_rows(pos, 1, value);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::insert_rows(const size_type pos, const size_type rows, const value_type& value)
	{
		m_data.insert(m_data.begin() + (m_width * pos), (m_width * rows), value);

		m_height += rows;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::insert_column(const size_type pos, const value_type& value)
	{
		reserve((m_width + 1), m_height);

		const size_type w = (m_width + 1);

		for (size_type i = 0; i < m_height; ++i)
		{
			m_data.insert(m_data.begin() + (i * w + pos), value);
		}

		++m_width;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::insert_columns(const size_type pos, const size_type columns, const value_type& value)
	{
		reserve((m_width + columns), m_height);

		const size_type w = (m_width + columns);

		for (size_type i = 0; i < m_height; ++i)
		{
			m_data.insert(m_data.begin() + (i * w + pos), columns, value);
		}

		m_width += columns;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::remove_row(const size_type pos)
	{
		if (m_height <= pos)
		{
			throw std::out_of_range("Grid::remove_row(): index out of range");
		}

		remove_rows(pos, 1);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::remove_rows(const size_type pos, const size_type count)
	{
		if ((m_height <= pos)
			|| (m_height < (pos + count)))
		{
			throw std::out_of_range("Grid::remove_rows(): index out of range");
		}

		const auto first = m_data.begin() + (m_width * pos);
		const auto last = first + (m_width * count);

		m_data.erase(first, last);

		m_height -= count;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::remove_column(const size_type pos)
	{
		if (m_width <= pos)
		{
			throw std::out_of_range("Grid::remove_column(): index out of range");
		}

		size_type index = 0;

		m_data.remove_if([width = m_width, col = pos, &index](const value_type&)
		{
			return ((index++) % width == col);
		});

		--m_width;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::remove_columns(const size_type pos, const size_type count)
	{
		if (m_width <= pos || m_width < (pos + count))
		{
			throw std::out_of_range("Grid::remove_columns(): index out of range");
		}

		size_type index = 0;

		m_data.remove_if([width = m_width, a = pos, b = pos + count, &index](const value_type&)
		{
			const size_type col = (index++) % width;

			return ((a <= col) && (col < b));
		});

		m_width -= count;
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::resize(const size_type w, const size_type h)
	{
		const size_t oldWidth = m_width;
		const size_t newWidth = w;
		const size_t oldHeight = m_height;
		const size_t newHeight = h;

		// 幅か高さが 0 なら空の二次元配列にする
		if ((newWidth == 0) || (newHeight == 0))
		{
			m_data.clear();
			m_width = m_height = 0;
			return;
		}

		// 元のサイズが 0 なら
		if (m_data.isEmpty())
		{
			m_data.resize(newWidth * newHeight);
			m_width = newWidth;
			m_height = newHeight;
			return;
		}

		// 高さが違う場合
		if (oldHeight != newHeight)
		{
			m_data.resize(oldWidth * newHeight);
			m_height = newHeight;
		}

		// 幅が違う場合
		if (oldWidth != newWidth)
		{
			if (oldWidth < newWidth) // 幅を広くする場合
			{
				m_data.resize(newWidth * newHeight);

				// swap による移動
				for (size_t y = newHeight; 1 < y; --y)
				{
					auto fromEnd = (begin() + (y - 1) * oldWidth + oldWidth) - 1;
					auto toEnd = (begin() + (y - 1) * newWidth + oldWidth) - 1;
					
					for (size_t i = 0; i < oldWidth; ++i)
					{
						std::swap(*(fromEnd--), *(toEnd--));
					}
				}
			}
			else if (newWidth < oldWidth) // 幅を狭くする場合
			{
				// swap による移動
				for (size_t y = 1; y < newHeight; ++y)
				{
					auto from = (begin() + y * oldWidth);
					auto to = (begin() + y * newWidth);

					for (size_t i = 0; i < newWidth; ++i)
					{
						std::swap(*(from++), *(to++));
					}
				}

				m_data.resize(newWidth * newHeight);
			}

			m_width = newWidth;
		}
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::resize(const Size size)
	{
		resize(size.x, size.y);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::resize(const size_type w, const size_type h, const value_type& value)
	{
		const size_t oldWidth = m_width;
		const size_t newWidth = w;
		const size_t oldHeight = m_height;
		const size_t newHeight = h;

		// 幅か高さが 0 なら空の二次元配列にする
		if ((newWidth == 0) || (newHeight == 0))
		{
			m_data.clear();
			m_width = m_height = 0;
			return;
		}

		// 元のサイズが 0 なら
		if (m_data.isEmpty())
		{
			m_data.resize((newWidth * newHeight), value);
			m_width = newWidth;
			m_height = newHeight;
			return;
		}

		// 高さが違う場合
		if (oldHeight != newHeight)
		{
			m_data.resize((oldWidth * newHeight), value);
			m_height = newHeight;
		}

		// 幅が違う場合
		if (oldWidth != newWidth)
		{
			if (oldWidth < newWidth) // 幅を広くする場合
			{
				m_data.resize((newWidth * newHeight), value);

				// swap による移動
				for (size_t y = newHeight; 1 < y; --y)
				{
					auto fromEnd = (begin() + (y - 1) * oldWidth + oldWidth) - 1;
					auto toEnd = (begin() + (y - 1) * newWidth + oldWidth) - 1;

					for (size_t i = 0; i < oldWidth; ++i)
					{
						std::swap(*(fromEnd--), *(toEnd--));
					}
				}
			}
			else if (newWidth < oldWidth) // 幅を狭くする場合
			{
				// swap による移動
				for (size_t y = 1; y < newHeight; ++y)
				{
					auto from = (begin() + y * oldWidth);
					auto to = (begin() + y * newWidth);

					for (size_t i = 0; i < newWidth; ++i)
					{
						std::swap(*(from++), *(to++));
					}
				}

				m_data.resize(newWidth * newHeight);
			}

			m_width = newWidth;
		}
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::resize(const Size size, const value_type& value)
	{
		resize(size.x, size.y, value);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline auto Grid<Type, Allocator>::operator >>(Fty f) const
	{
		using ResultType = std::remove_cvref_t<decltype(f(m_data[0]))>;

		if constexpr (std::is_same_v<ResultType, void>)
		{
			each(f);
		}
		else
		{
			return map(f);
		}
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline bool Grid<Type, Allocator>::all(Fty f) const
	{
		return std::all_of(begin(), end(), f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline bool Grid<Type, Allocator>::any(Fty f) const
	{
		return std::any_of(begin(), end(), f);
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::choice()
	{
		return choice(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::choice() const
	{
		return choice(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::choice(URBG&& rbg)
	{
		const size_t size = m_data.size();

		if (size == 0)
		{
			throw std::out_of_range{ "Grid::choice(): Grid is empty" };
		}

		return m_data[RandomClosedOpen<size_t>(0, size, std::forward<URBG>(rbg))];
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::choice(URBG&& rbg) const
	{
		const size_t size = m_data.size();

		if (size == 0)
		{
			throw std::out_of_range{ "Grid::choice(): Grid is empty" };
		}

		return m_data[RandomClosedOpen<size_t>(0, size, std::forward<URBG>(rbg))];
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_INTEGRAL_
	inline Array<Type> Grid<Type, Allocator>::choice(const Int n) const
	{
		return choice(n, GetDefaultRNG());
	}

	template <class Type, class Allocator>
# if __cpp_lib_concepts
	template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>*,
		std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	inline Array<Type> Grid<Type, Allocator>::choice(const Size_t n, URBG&& rbg) const
	{
		Array<Type> result(Arg::reserve = Min<size_t>(n, num_elements()));

		std::sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));

		return result;
	}

	template <class Type, class Allocator>
	inline size_t Grid<Type, Allocator>::count(const value_type& value) const
	{
		return std::count(begin(), end(), value);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline size_t Grid<Type, Allocator>::count_if(Fty f) const
	{
		return std::count_if(begin(), end(), f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>*>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::each(Fty f)
	{
		for (auto& v : m_data)
		{
			f(v);
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline const Grid<Type, Allocator>& Grid<Type, Allocator>::each(Fty f) const
	{
		for (const auto& v : m_data)
		{
			f(v);
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Point, Type&>>*>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::each_index(Fty f)
	{
		pointer p = m_data.data();

		for (size_t y = 0; y < m_height; ++y)
		{
			for (size_t x = 0; x < m_width; ++x)
			{
				f(Point{ x, y }, *p++);
			}
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Point, Type>>*>
	inline const Grid<Type, Allocator>& Grid<Type, Allocator>::each_index(Fty f) const
	{
		const_pointer p = m_data.data();

		for (size_t y = 0; y < m_height; ++y)
		{
			for (size_t x = 0; x < m_width; ++x)
			{
				f(Point{ x, y }, *p++);
			}
		}

		return *this;
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::fetch(const size_type y, const size_type x, const value_type& defaultValue) const
	{
		if (not inBounds(y, x))
		{
			return defaultValue;
		}

		return m_data[y * m_width + x];
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::fetch(const Point pos, const value_type& defaultValue) const
	{
		return fetch(pos.y, pos.x, defaultValue);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::fill(const value_type& value)
	{
		std::fill(begin(), end(), value);

		return *this;
	}

	template <class Type, class Allocator>
	inline bool Grid<Type, Allocator>::includes(const value_type& value) const
	{
		for (const auto& v : m_data)
		{
			if (v == value)
			{
				return true;
			}
		}

		return false;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline bool Grid<Type, Allocator>::includes_if(Fty f) const
	{
		return any(f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline auto Grid<Type, Allocator>::map(Fty f) const
	{
		using ResultType = std::remove_cvref_t<decltype(f(m_data[0]))>;

		Array<ResultType> new_grid(Arg::reserve = (m_width * m_height));

		for (const auto& v : m_data)
		{
			new_grid.push_back(f(v));
		}

		return Grid<ResultType>(m_width, m_height, std::move(new_grid));
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline bool Grid<Type, Allocator>::none(Fty f) const
	{
		return std::none_of(begin(), end(), f);
	}

	template <class Type, class Allocator>
	template <class Fty, class R>
	inline auto Grid<Type, Allocator>::reduce(Fty f, R init) const
	{
		auto value = init;

		for (const auto& v : m_data)
		{
			value = f(value, v);
		}

		return value;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type, Type>>*>
	inline auto Grid<Type, Allocator>::reduce1(Fty f) const
	{
		if (empty())
		{
			throw std::out_of_range("Grid::reduce1(): Grid is empty");
		}

		auto it = begin();
		const auto itEnd = end();

		std::invoke_result_t<Fty, value_type, value_type> value = *it++;

		while (it != itEnd)
		{
			value = f(value, *it++);
		}

		return value;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::replace(const value_type& oldValue, const value_type& newValue)
	{
		m_data.replace(oldValue, newValue);

		return *this;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::replaced(const value_type& oldValue, const value_type& newValue) const&
	{
		Grid new_grid;
		new_grid.m_data		= m_data.replaced(oldValue, newValue);
		new_grid.m_width	= m_width;
		new_grid.m_height	= m_height;
		return new_grid;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::replaced(const value_type& oldValue, const value_type& newValue)&&
	{
		replace(oldValue, newValue);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::replace_if(Fty f, const value_type& newValue)
	{
		for (auto& v : m_data)
		{
			if (f(v))
			{
				v = newValue;
			}
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::replaced_if(Fty f, const value_type& newValue) const&
	{
		Grid new_grid;
		new_grid.m_data		= m_data.replaced_if(f, newValue);
		new_grid.m_width	= m_width;
		new_grid.m_height	= m_height;
		return new_grid;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::replaced_if(Fty f, const value_type& newValue)&&
	{
		replace_if(f, newValue);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::reverse()
	{
		std::reverse(begin(), end());

		return *this;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::reverse_columns()
	{
		for (size_t x = 0; x < (m_width / 2); ++x)
		{
			swap_columns(x, (m_width - x - 1));
		}

		return *this;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::reverse_rows()
	{
		for (size_t y = 0; y < (m_height / 2); ++y)
		{
			swap_rows(y, (m_height - y - 1));
		}

		return *this;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::reversed() const&
	{
		Grid new_grid;
		new_grid.m_data.assign(rbegin(), rend());
		new_grid.m_width	= m_width;
		new_grid.m_height	= m_height;
		return new_grid;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::reversed()&&
	{
		reverse();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>*>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::reverse_each(Fty f)
	{
		for (auto it = rbegin(); it != rend(); ++it)
		{
			f(*it);
		}

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline const Grid<Type, Allocator>& Grid<Type, Allocator>::reverse_each(Fty f) const
	{
		for (auto it = rbegin(); it != rend(); ++it)
		{
			f(*it);
		}

		return *this;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::rotate(const std::ptrdiff_t count)
	{
		m_data.rotate(count);

		return *this;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::rotated(const std::ptrdiff_t count) const&
	{
		return Grid(*this).rotate(count);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::rotated(const std::ptrdiff_t count)&&
	{
		rotate(count);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::rotate_rows(const std::ptrdiff_t count)
	{
		return rotate(count * static_cast<std::ptrdiff_t>(m_width));
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::rotated_rows(const std::ptrdiff_t count) const&
	{
		return rotated(count * static_cast<std::ptrdiff_t>(m_width));
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::rotated_rows(const std::ptrdiff_t count)&&
	{
		return rotated(count * static_cast<std::ptrdiff_t>(m_width));
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::shuffle()
	{
		return shuffle(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::shuffle(URBG&& rbg)
	{
		Shuffle(begin(), end(), std::forward<URBG>(rbg));

		return *this;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::shuffled() const&
	{
		return shuffled(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::shuffled()&&
	{
		return shuffled(GetDefaultRNG());
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline Grid<Type, Allocator> Grid<Type, Allocator>::shuffled(URBG&& rbg) const&
	{
		return Grid(*this).shuffle(std::forward<URBG>(rbg));
	}

	template <class Type, class Allocator>
	SIV3D_CONCEPT_URBG_
	inline Grid<Type, Allocator> Grid<Type, Allocator>::shuffled(URBG&& rbg)&&
	{
		shuffle(std::forward<URBG>(rbg));

		return std::move(*this);
	}

	template <class Type, class Allocator>
	inline Array<Type> Grid<Type, Allocator>::slice(const size_type y, const size_type x) const
	{
		if (not inBounds(y, x))
		{
			return{};
		}

		return Array<value_type>(m_data.begin() + (y * m_width + x), m_data.end());
	}

	template <class Type, class Allocator>
	inline Array<Type> Grid<Type, Allocator>::slice(const Point pos) const
	{
		return slice(pos.y, pos.x);
	}

	template <class Type, class Allocator>
	inline Array<Type> Grid<Type, Allocator>::slice(const size_type y, const size_type x, const size_t length) const
	{
		if (not inBounds(y, x))
		{
			return{};
		}

		const size_type index = (y * m_width + x);

		return Array<value_type>((m_data.begin() + index), (m_data.begin() + Min(index + length, m_data.size())));
	}

	template <class Type, class Allocator>
	inline Array<Type> Grid<Type, Allocator>::slice(const Point pos, const size_t length) const
	{
		return slice(pos.y, pos.x, length);
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::sort()
	{
		std::sort(m_data.begin(), m_data.end());

		return *this;
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::stable_sort()
	{
		std::stable_sort(m_data.begin(), m_data.end());

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::sort_by(Fty f)
	{
		std::sort(m_data.begin(), m_data.end(), f);

		return *this;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::stable_sort_by(Fty f)
	{
		std::stable_sort(m_data.begin(), m_data.end(), f);

		return *this;
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::sorted() const&
	{
		return Grid(*this).sort();
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::stable_sorted() const&
	{
		return Grid(*this).stable_sorted();
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::sorted()&&
	{
		sort();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasLessThan_v<T>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::stable_sorted()&&
	{
		stable_sort();

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::sorted_by(Fty f) const&
	{
		return Grid(*this).sort_by(f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::stable_sorted_by(Fty f) const&
	{
		return Grid(*this).stable_sort_by(f);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::sorted_by(Fty f)&&
	{
		sort_by(f);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Type, Type>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::stable_sorted_by(Fty f)&&
	{
		stable_sort_by(f);

		return std::move(*this);
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<Meta::HasPlus_v<T>>*>
	inline auto Grid<Type, Allocator>::sum() const
	{
		return m_data.sum();
	}

	template <class Type, class Allocator>
	template <class T, std::enable_if_t<std::is_floating_point_v<T>>*>
	inline auto Grid<Type, Allocator>::sumF() const
	{
		return m_data.sumF();
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::swap_columns(const size_t a, const size_t b)
	{
		if ((m_width <= a) || (m_width <= b))
		{
			throw std::out_of_range("Grid::swap_columns(): index out of range");
		}

		for (size_t y = 0; y < m_height; ++y)
		{
			using std::swap;
			swap(m_data[y * m_width + a], m_data[y * m_width + b]);
		}

		return *this;
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>& Grid<Type, Allocator>::swap_rows(const size_t a, const size_t b)
	{
		if ((m_height <= a) || (m_height <= b))
		{
			throw std::out_of_range("Grid::swap_rows(): index out of range");
		}

		for (size_t x = 0; x < m_width; ++x)
		{
			using std::swap;
			swap(m_data[a * m_width + x], m_data[b * m_width + x]);
		}

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type> Grid<Type, Allocator>::values_at(std::initializer_list<Point> indices) const
	{
		Array<Type> new_array(Arg::reserve = indices.size());

		for (auto index : indices)
		{
			if (not inBounds(index))
			{
				throw std::out_of_range("Grid::values_at(): index out of range");
			}

			new_array.push_back(operator[](index));
		}

		return new_array;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::Generate(const size_type w, const size_type h, Fty generator)
	{
		Grid new_grid;
		new_grid.m_data.reserve(w * h);
		new_grid.m_width	= w;
		new_grid.m_height	= h;

		for (size_type i = 0; i < (w * h); ++i)
		{
			new_grid.m_data.push_back(generator());
		}

		return new_grid;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::Generate(const Size size, Fty generator)
	{
		return Generate(size.x, size.y, generator);
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, Point>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::IndexedGenerate(const size_type w, const size_type h, Fty generator)
	{
		Grid new_grid;
		new_grid.m_data.reserve(w * h);
		new_grid.m_width	= w;
		new_grid.m_height	= h;

		for (size_t y = 0; y < h; ++y)
		{
			for (size_t x = 0; x < w; ++x)
			{
				new_grid.m_data.push_back(generator(Point{ x, y }));
			}
		}

		return new_grid;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, Point>>*>
	inline Grid<Type, Allocator> Grid<Type, Allocator>::IndexedGenerate(const Size size, Fty generator)
	{
		return IndexedGenerate(size.x, size.y, generator);
	}

	template <class Type, class Allocator>
	inline void swap(Grid<Type, Allocator>& a, Grid<Type, Allocator>& b) noexcept
	{
		a.swap(b);
	}
}
