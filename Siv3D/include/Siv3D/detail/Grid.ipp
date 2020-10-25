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

namespace s3d
{
	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h)
		: m_data(w * h)
		, m_width(w)
		, m_height(h) {}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, const value_type& value)
		: m_data(w* h, value)
		, m_width(w)
		, m_height(h) {}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const Size size)
		: m_data(size.x * size.y)
		, m_width(size.x)
		, m_height(size.y) {}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const Size size, const value_type& value)
		: m_data(size.x* size.y, value)
		, m_width(size.x)
		, m_height(size.y) {}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, const Array<value_type>& data)
		: m_data(data)
		, m_width(w)
		, m_height(h)
	{
		m_data.resize(w * h);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, Array<value_type>&& data)
		: m_data(std::move(data))
		, m_width(w)
		, m_height(h)
	{
		m_data.resize(w * h);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(Size size, const Array<value_type>& data)
		: m_data(data)
		, m_width(size.x)
		, m_height(size.y)
	{
		assert(0 <= size.x);
		assert(0 <= size.y);
		m_data.resize(size.x * size.y);
	}

	template <class Type, class Allocator>
	inline Grid<Type, Allocator>::Grid(Size size, Array<value_type>&& data)
		: m_data(std::move(data))
		, m_width(size.x)
		, m_height(size.y)
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
		: Grid(Generate(w, h, generator)) {}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Grid<Type, Allocator>::Grid(const Size size, Arg::generator_<Fty> generator)
		: Grid(Generate(size, generator)) {}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>*>
	inline Grid<Type, Allocator>::Grid(const size_type w, const size_type h, Arg::indexedGenerator_<Fty> indexedGenerator)
		: Grid(IndexedGenerate(w, h, indexedGenerator)) {}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>*>
	inline Grid<Type, Allocator>::Grid(const Size size, Arg::indexedGenerator_<Fty> indexedGenerator)
		: Grid(IndexedGenerate(size, indexedGenerator)) {}

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
		if (!inBounds(y, x))
		{
			throw std::out_of_range("Grid::at(): index out of range");
		}

		return m_data[(y * m_width) + x];
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::at(const size_type y, const size_type x) const&
	{
		if (!inBounds(y, x))
		{
			throw std::out_of_range("Grid::at(): index out of range");
		}

		return m_data[(y * m_width) + x];
	}

	template <class Type, class Allocator>
	inline typename Grid<Type, Allocator>::value_type Grid<Type, Allocator>::at(const size_type y, const size_type x)&&
	{
		if (!inBounds(y, x))
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
		return &m_data[(pos.y * m_width) + pos.x];
	}

	template <class Type, class Allocator>
	inline const typename Grid<Type, Allocator>::value_type& Grid<Type, Allocator>::operator[](const Point pos) const&
	{
		return &m_data[(pos.y * m_width) + pos.x];
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
	inline typename Grid<Type, Allocator>::size_type Grid<Type, Allocator>::size_elements() const noexcept
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
		resize(w, h, value_type{});
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::resize(const Size size)
	{
		resize(size.x, size.y);
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::resize(const size_type w, const size_type h, const value_type& value)
	{
		if (m_width < w)
		{
			insert_columns(m_width, (w - m_width), value);
		}
		else if (m_width > w)
		{
			remove_columns(w, (m_width - w));
		}

		if (m_height < h)
		{
			insert_rows(m_height, (h - m_height), value);
		}
		else if (m_height > h)
		{
			remove_rows(h, (m_height - h));
		}
	}

	template <class Type, class Allocator>
	inline void Grid<Type, Allocator>::resize(const Size size, const value_type& value)
	{
		resize(size.x, size.y, value);
	}









	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline auto Grid<Type, Allocator>::map(Fty f) const
	{
		using ResultType = std::decay_t<std::invoke_result_t<Fty, Type>>;

		Array<ResultType> new_grid;

		new_grid.reserve(m_width * m_height);

		for (const auto& v : m_data)
		{
			new_grid.push_back(f(v));
		}

		return Grid<ResultType>(m_width, m_height, std::move(new_grid));
	}



	template <class Type, class Allocator>
	inline void swap(Grid<Type, Allocator>& a, Grid<Type, Allocator>& b) noexcept
	{
		a.swap(b);
	}
}
