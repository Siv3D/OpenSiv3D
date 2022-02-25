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
	inline LineString::LineString(const allocator_type& alloc) noexcept
		: m_data(alloc) {}

	inline LineString::LineString(const size_t count, const value_type& value, const allocator_type& alloc)
		: m_data(count, value, alloc) {}

	inline LineString::LineString(const size_t count, const allocator_type& alloc)
		: m_data(count, alloc) {}

	template <class Iterator>
	inline LineString::LineString(Iterator first, Iterator last, const allocator_type& alloc)
		: m_data(first, last, alloc) {}

	inline LineString::LineString(const LineString& lines)
		: m_data(lines.begin(), lines.end()) {}

	inline LineString::LineString(const LineString& lines, const allocator_type& alloc)
		: m_data(lines.begin(), lines.end(), alloc) {}

	inline LineString::LineString(LineString&& lines) noexcept
		: m_data(std::move(lines.m_data)) {}

	inline LineString::LineString(std::initializer_list<value_type> init, const allocator_type& alloc)
		: m_data(init, alloc) {}

	inline LineString::LineString(const Array<Point>& points)
		: m_data(points.begin(), points.end()) {}

	inline LineString::LineString(const Array<Vec2>& points)
		: m_data(points) {}

	inline LineString::LineString(Array<Vec2>&& points) noexcept
		: m_data(std::move(points)) {}

	inline LineString::LineString(const Arg::reserve_<size_type> size)
		: m_data(size) {}

	inline LineString& LineString::operator =(const Array<Point>& other)
	{
		m_data.assign(other.begin(), other.end());

		return *this;
	}

	inline LineString& LineString::operator =(const Array<Vec2>& other)
	{
		m_data = other;

		return *this;
	}

	inline LineString& LineString::operator =(Array<Vec2>&& other) noexcept
	{
		m_data = std::move(other);

		return *this;
	}

	inline LineString& LineString::operator =(const LineString& other)
	{
		m_data = other.m_data;

		return *this;
	}

	inline LineString& LineString::operator =(LineString&& other) noexcept
	{
		m_data = std::move(other.m_data);

		return *this;
	}

	inline const Array<LineString::value_type>& LineString::asArray() const noexcept
	{
		return m_data;
	}

	inline LineString::operator const Array<LineString::value_type>& () const noexcept
	{
		return m_data;
	}

	template <class Iterator>
	inline void LineString::assign(Iterator first, Iterator last)
	{
		m_data.assign(first, last);
	}

	inline void LineString::assign(size_type n, const value_type& value)
	{
		m_data.assign(n, value);
	}

	inline void LineString::assign(std::initializer_list<value_type> il)
	{
		m_data.assign(il);
	}

	inline void LineString::assign(const Array<Point>& other)
	{
		m_data.assign(other.begin(), other.end());
	}

	inline void LineString::assign(const Array<Vec2>& other)
	{
		m_data = other;
	}

	inline void LineString::assign(Array<Vec2>&& other) noexcept
	{
		m_data = std::move(other);
	}

	inline void LineString::assign(const LineString& other)
	{
		m_data = other.m_data;
	}

	inline void LineString::assign(LineString&& other) noexcept
	{
		m_data = std::move(other.m_data);
	}

	inline LineString::allocator_type LineString::get_allocator() const noexcept
	{
		return m_data.get_allocator();
	}

	inline LineString::value_type& LineString::at(const size_t index)&
	{
		return m_data.at(index);
	}

	inline const LineString::value_type& LineString::at(const size_t index) const&
	{
		return m_data.at(index);
	}

	inline LineString::value_type LineString::at(const size_t index)&&
	{
		return m_data.at(index);
	}

	inline LineString::value_type& LineString::operator[](const size_t index) & noexcept
	{
		return m_data[index];
	}

	inline const LineString::value_type& LineString::operator[](const size_t index) const& noexcept
	{
		return m_data[index];
	}

	inline LineString::value_type LineString::operator[](const size_t index) && noexcept
	{
		return std::move(m_data[index]);
	}

	inline void LineString::push_front(const value_type& value)
	{
		m_data.push_front(value);
	}

	inline void LineString::push_back(const value_type& value)
	{
		m_data.push_back(value);
	}

	inline void LineString::pop_front()
	{
		m_data.pop_front();
	}

	inline void LineString::pop_front_N(const size_t n)
	{
		m_data.pop_front_N(n);
	}

	inline void LineString::pop_back() noexcept
	{
		m_data.pop_back();
	}

	inline void LineString::pop_back_N(const size_t n)
	{
		m_data.pop_back_N(n);
	}

	inline LineString& LineString::operator <<(const value_type& value)
	{
		m_data.push_back(value);

		return *this;
	}

	template <class... Args>
	LineString::iterator LineString::emplace(const_iterator position, Args&&... args)
	{
		return m_data.emplace(position, std::forward<Args>(args)...);
	}

	template <class... Args>
	decltype(auto) LineString::emplace_back(Args&&... args)
	{
		return m_data.emplace_back(std::forward<Args>(args)...);
	}

	inline LineString::value_type& LineString::front() noexcept
	{
		return m_data.front();
	}

	inline const LineString::value_type& LineString::front() const noexcept
	{
		return m_data.front();
	}

	inline LineString::value_type& LineString::back() noexcept
	{
		return m_data.back();
	}

	inline const LineString::value_type& LineString::back() const noexcept
	{
		return m_data.back();
	}

	inline void LineString::swap(LineString& other) noexcept
	{
		m_data.swap(other.m_data);
	}

	inline const LineString::value_type* LineString::data() const noexcept
	{
		return m_data.data();
	}

	inline LineString::value_type* LineString::data() noexcept
	{
		return m_data.data();
	}

	inline LineString::iterator LineString::begin() noexcept
	{
		return m_data.begin();
	}

	inline LineString::iterator LineString::end() noexcept
	{
		return m_data.end();
	}

	inline LineString::const_iterator LineString::begin() const noexcept
	{
		return m_data.begin();
	}

	inline LineString::const_iterator LineString::end() const noexcept
	{
		return m_data.end();
	}

	inline LineString::const_iterator LineString::cbegin() const noexcept
	{
		return m_data.cbegin();
	}

	inline LineString::const_iterator LineString::cend() const noexcept
	{
		return m_data.cend();
	}

	inline LineString::reverse_iterator LineString::rbegin() noexcept
	{
		return m_data.rbegin();
	}

	inline LineString::reverse_iterator LineString::rend() noexcept
	{
		return m_data.rend();
	}

	inline LineString::const_reverse_iterator LineString::rbegin() const noexcept
	{
		return m_data.rbegin();
	}

	inline LineString::const_reverse_iterator LineString::rend() const noexcept
	{
		return m_data.rend();
	}

	inline LineString::const_reverse_iterator LineString::crbegin() const noexcept
	{
		return m_data.crbegin();
	}

	inline LineString::const_reverse_iterator LineString::crend() const noexcept
	{
		return m_data.crend();
	}

	inline bool LineString::empty() const noexcept
	{
		return m_data.empty();
	}

	inline bool LineString::isEmpty() const noexcept
	{
		return m_data.empty();
	}

	inline LineString::operator bool() const noexcept
	{
		return (not m_data.empty());
	}

	inline size_t LineString::size() const noexcept
	{
		return m_data.size();
	}

	inline size_t LineString::size_bytes() const noexcept
	{
		return (m_data.size() * sizeof(value_type));
	}

	inline size_t LineString::max_size() const noexcept
	{
		return m_data.max_size();
	}

	inline void LineString::reserve(const size_t newCapacity)
	{
		m_data.reserve(newCapacity);
	}

	inline size_t LineString::capacity() const noexcept
	{
		return m_data.capacity();
	}

	inline void LineString::shrink_to_fit()
	{
		m_data.shrink_to_fit();
	}

	inline void LineString::clear() noexcept
	{
		m_data.clear();
	}

	inline void LineString::release()
	{
		clear();

		shrink_to_fit();
	}

	inline LineString::iterator LineString::insert(const_iterator where, const value_type& value)
	{
		return m_data.insert(where, value);
	}

	inline LineString::iterator LineString::insert(const_iterator where, const size_t count, const value_type& value)
	{
		return m_data.insert(where, count, value);
	}

	template <class Iterator>
	inline LineString::iterator LineString::insert(const_iterator where, Iterator first, Iterator last)
	{
		return m_data.insert(where, first, last);
	}

	inline LineString::iterator LineString::insert(const_iterator where, std::initializer_list<value_type> il)
	{
		return m_data.insert(where, il);
	}

	inline LineString::iterator LineString::erase(const_iterator where) noexcept
	{
		return m_data.erase(where);
	}

	inline LineString::iterator LineString::erase(const_iterator first, const_iterator last) noexcept
	{
		return m_data.erase(first, last);
	}

	inline void LineString::resize(const size_t newSize)
	{
		m_data.resize(newSize);
	}

	inline void LineString::resize(const size_t newSize, const value_type& value)
	{
		m_data.resize(newSize, value);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, LineString::value_type>>*>
	inline bool LineString::all(Fty f) const
	{
		return std::all_of(m_data.begin(), m_data.end(), f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, LineString::value_type>>*>
	inline bool LineString::any(Fty f) const
	{
		return std::any_of(m_data.begin(), m_data.end(), f);
	}

	inline LineString::value_type& LineString::choice()
	{
		return choice(GetDefaultRNG());
	}

	inline const LineString::value_type& LineString::choice() const
	{
		return choice(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline LineString::value_type& LineString::choice(URBG&& rbg)
	{
		if (empty())
		{
			throw std::out_of_range("LineString::choice(): Array is empty");
		}

		const size_t index = UniformIntDistribution<size_t>(0, size() - 1)(rbg);

		return operator[](index);
	}

	SIV3D_CONCEPT_URBG_
	inline const LineString::value_type& LineString::choice(URBG&& rbg) const
	{
		if (empty())
		{
			throw std::out_of_range("LineString::choice(): Array is empty");
		}

		const size_t index = UniformIntDistribution<size_t>(0, size() - 1)(rbg);

		return operator[](index);
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline LineString LineString::choice(const Int n) const
	{
		return choice(n, GetDefaultRNG());
	}

# if __cpp_lib_concepts
	template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>*,
		std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	inline LineString LineString::choice(const Size_t n, URBG&& rbg) const
	{
		LineString result(Arg::reserve = Min<size_t>(n, size()));

		std::sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));

		return result;
	}

	inline size_t LineString::count(const value_type& value) const
	{
		return m_data.count(value);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, LineString::value_type>>*>
	inline size_t LineString::count_if(Fty f) const
	{
		return m_data.count_if(f);
	}

	inline LineString& LineString::fill(const value_type& value)
	{
		m_data.fill(value);

		return *this;
	}

	inline String LineString::join(const StringView sep, const StringView begin, const StringView end) const
	{
		return m_data.join(sep, begin, end);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, LineString::value_type>>*>
	inline bool LineString::none(Fty f) const
	{
		return std::none_of(m_data.begin(), m_data.end(), f);
	}

	inline LineString& LineString::append(const Array<value_type>& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	inline LineString& LineString::append(const LineString& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	inline LineString& LineString::remove(const value_type& value)
	{
		m_data.remove(value);

		return *this;
	}

	inline LineString& LineString::remove_at(const size_t index)
	{
		m_data.remove_at(index);

		return *this;
	}

	template <class Fty>
	inline LineString& LineString::remove_if(Fty f)
	{
		m_data.remove_if(f);

		return *this;
	}

	inline LineString& LineString::reverse()
	{
		m_data.reverse();

		return *this;
	}

	inline LineString LineString::reversed() const
	{
		return LineString(rbegin(), rend());
	}

	inline LineString& LineString::shuffle()
	{
		m_data.shuffle();

		return *this;
	}

	SIV3D_CONCEPT_URBG_
	inline LineString& LineString::shuffle(URBG&& rbg)
	{
		m_data.shuffle(std::forward<URBG>(rbg));

		return *this;
	}

	inline LineString LineString::slice(const size_t index) const
	{
		if (index >= size())
		{
			return{};
		}

		return LineString(begin() + index, end());
	}

	inline LineString LineString::slice(const size_t index, const size_t length) const
	{
		if (index >= size())
		{
			return{};
		}

		return LineString(begin() + index, begin() + Min(index + length, size()));
	}

	inline size_t LineString::num_points() const noexcept
	{
		return size();
	}

	inline size_t LineString::num_lines(const CloseRing closeRing) const noexcept
	{
		if (const size_t s = size();
			s < 2)
		{
			return 0;
		}
		else
		{
			return (s - 1 + static_cast<bool>(closeRing));
		}
	}

	inline Line LineString::line(const size_t index, const CloseRing closeRing) const
	{
		if (num_lines(closeRing) <= index)
		{
			throw std::out_of_range("LineString::line() index out of range");
		}

		const Vec2* pData = data();

		if (closeRing)
		{
			if ((index + 1) == size())
			{
				return{ pData[index], pData[0] };
			}
			else
			{
				return{ pData[index], pData[index + 1] };
			}
		}
		else
		{
			return{ pData[index], pData[index + 1] };
		}
	}

	inline LineString LineString::movedBy(const double x, const double y) const
	{
		LineString lines{ *this };
		
		lines.moveBy(x, y);
		
		return lines;
	}

	inline LineString LineString::movedBy(const Vec2 v) const
	{
		return movedBy(v.x, v.y);
	}

	inline LineString& LineString::moveBy(const double x, const double y) noexcept
	{
		for (auto& point : *this)
		{
			point.moveBy(x, y);
		}

		return *this;
	}

	inline LineString& LineString::moveBy(const Vec2 v) noexcept
	{
		return moveBy(v.x, v.y);
	}

	inline LineString LineString::scaled(const double s) const
	{
		LineString result{ *this };

		for (auto& point : result)
		{
			point *= s;
		}

		return result;
	}

	inline LineString LineString::scaled(const double sx, const double sy) const
	{
		return scaled(Vec2{ sx, sy });
	}

	inline LineString LineString::scaled(const Vec2 s) const
	{
		LineString result{ *this };

		for (auto& point : result)
		{
			point *= s;
		}

		return result;
	}

	inline LineString& LineString::scale(const double s)
	{
		for (auto& point : m_data)
		{
			point *= s;
		}

		return *this;
	}

	inline LineString& LineString::scale(const double sx, const double sy)
	{
		return scale(Vec2{ sx, sy });
	}

	inline LineString& LineString::scale(const Vec2 s)
	{
		for (auto& point : m_data)
		{
			point *= s;
		}

		return *this;
	}

	inline LineString LineString::scaledAt(const Vec2 pos, const double s) const
	{
		LineString result{ *this };

		for (auto& point : result)
		{
			point = (pos + (point - pos) * s);
		}

		return result;
	}

	inline LineString LineString::scaledAt(const Vec2 pos, const double sx, const double sy) const
	{
		return scaledAt(pos, Vec2{ sx, sy });
	}

	inline LineString LineString::scaledAt(const Vec2 pos, const Vec2 s) const
	{
		LineString result{ *this };

		for (auto& point : result)
		{
			point = (pos + (point - pos) * s);
		}

		return result;
	}

	inline LineString& LineString::scaleAt(const Vec2 pos, const double s)
	{
		for (auto& point : m_data)
		{
			point = (pos + (point - pos) * s);
		}

		return *this;
	}

	inline LineString& LineString::scaleAt(const Vec2 pos, const double sx, const double sy)
	{
		return scaleAt(pos, Vec2{ sx, sy });
	}

	inline LineString& LineString::scaleAt(const Vec2 pos, const Vec2 s)
	{
		for (auto& point : m_data)
		{
			point = (pos + (point - pos) * s);
		}

		return *this;
	}

	template <class Shape2DType>
	inline constexpr bool LineString::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> LineString::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}
}

template <>
void std::swap(s3d::LineString& a, s3d::LineString& b) noexcept
{
	a.swap(b);
}
