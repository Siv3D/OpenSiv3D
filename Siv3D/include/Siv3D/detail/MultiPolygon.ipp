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
	inline MultiPolygon::MultiPolygon(const allocator_type& alloc) noexcept
		: m_data(alloc) {}

	inline MultiPolygon::MultiPolygon(const size_t count, const value_type& value, const allocator_type& alloc)
		: m_data(count, value, alloc) {}

	inline MultiPolygon::MultiPolygon(const size_t count, const allocator_type& alloc)
		: m_data(count, alloc) {}

	template <class Iterator>
	inline MultiPolygon::MultiPolygon(Iterator first, Iterator last, const allocator_type& alloc)
		: m_data(first, last, alloc) {}

	inline MultiPolygon::MultiPolygon(const MultiPolygon& polygons)
		: m_data(polygons.begin(), polygons.end()) {}

	inline MultiPolygon::MultiPolygon(const MultiPolygon& polygons, const allocator_type& alloc)
		: m_data(polygons.begin(), polygons.end(), alloc) {}

	inline MultiPolygon::MultiPolygon(MultiPolygon&& lines) noexcept
		: m_data(std::move(lines.m_data)) {}

	inline MultiPolygon::MultiPolygon(std::initializer_list<value_type> init, const allocator_type& alloc)
		: m_data(init, alloc) {}

	inline MultiPolygon::MultiPolygon(const Array<Polygon>& polygons)
		: m_data(polygons) {}

	inline MultiPolygon::MultiPolygon(Array<Polygon>&& polygons) noexcept
		: m_data(std::move(polygons)) {}

	inline MultiPolygon::MultiPolygon(const Arg::reserve_<size_type> size)
		: m_data(size) {}

	inline MultiPolygon& MultiPolygon::operator =(const Array<value_type>& other)
	{
		m_data.assign(other.begin(), other.end());

		return *this;
	}

	inline MultiPolygon& MultiPolygon::operator =(Array<value_type>&& other) noexcept
	{
		m_data = other;

		return *this;
	}

	inline MultiPolygon& MultiPolygon::operator =(const MultiPolygon& other)
	{
		m_data = other.m_data;

		return *this;
	}

	inline MultiPolygon& MultiPolygon::operator =(MultiPolygon&& other) noexcept
	{
		m_data = std::move(other.m_data);

		return *this;
	}

	inline const Array<MultiPolygon::value_type>& MultiPolygon::asArray() const noexcept
	{
		return m_data;
	}

	inline MultiPolygon::operator const Array<MultiPolygon::value_type>& () const noexcept
	{
		return m_data;
	}

	template <class Iterator>
	inline void MultiPolygon::assign(Iterator first, Iterator last)
	{
		m_data.assign(first, last);
	}

	inline void MultiPolygon::assign(size_type n, const value_type& value)
	{
		m_data.assign(n, value);
	}

	inline void MultiPolygon::assign(std::initializer_list<value_type> il)
	{
		m_data.assign(il);
	}

	inline void MultiPolygon::assign(const Array<Polygon>& other)
	{
		m_data = other;
	}

	inline void MultiPolygon::assign(Array<Polygon>&& other)
	{
		m_data = std::move(other);
	}

	inline void MultiPolygon::assign(const MultiPolygon& other)
	{
		m_data = other.m_data;
	}

	inline void MultiPolygon::assign(MultiPolygon&& other) noexcept
	{
		m_data = std::move(other.m_data);
	}

	inline MultiPolygon::allocator_type MultiPolygon::get_allocator() const noexcept
	{
		return m_data.get_allocator();
	}

	inline MultiPolygon::value_type& MultiPolygon::at(const size_t index)&
	{
		return m_data.at(index);
	}

	inline const MultiPolygon::value_type& MultiPolygon::at(const size_t index) const&
	{
		return m_data.at(index);
	}

	inline MultiPolygon::value_type MultiPolygon::at(const size_t index)&&
	{
		return m_data.at(index);
	}

	inline MultiPolygon::value_type& MultiPolygon::operator[](const size_t index) & noexcept
	{
		return m_data[index];
	}

	inline const MultiPolygon::value_type& MultiPolygon::operator[](const size_t index) const& noexcept
	{
		return m_data[index];
	}

	inline MultiPolygon::value_type MultiPolygon::operator[](const size_t index) && noexcept
	{
		return std::move(m_data[index]);
	}

	inline void MultiPolygon::push_front(const value_type& value)
	{
		m_data.push_front(value);
	}

	inline void MultiPolygon::push_front(value_type&& value)
	{
		m_data.push_front(std::move(value));
	}

	inline void MultiPolygon::push_back(const value_type& value)
	{
		m_data.push_back(value);
	}

	inline void MultiPolygon::push_back(value_type&& value)
	{
		m_data.push_back(std::move(value));
	}

	inline void MultiPolygon::pop_front()
	{
		m_data.pop_front();
	}

	inline void MultiPolygon::pop_front_N(const size_t n)
	{
		m_data.pop_front_N(n);
	}

	inline void MultiPolygon::pop_back() noexcept
	{
		m_data.pop_back();
	}

	inline void MultiPolygon::pop_back_N(const size_t n)
	{
		m_data.pop_back_N(n);
	}

	inline MultiPolygon& MultiPolygon::operator <<(const value_type& value)
	{
		m_data.push_back(value);

		return *this;
	}

	inline MultiPolygon& MultiPolygon::operator <<(value_type&& value)
	{
		m_data.push_back(std::move(value));

		return *this;
	}

	template <class... Args>
	MultiPolygon::iterator MultiPolygon::emplace(const_iterator position, Args&&... args)
	{
		return m_data.emplace(position, std::forward<Args>(args)...);
	}

	template <class... Args>
	decltype(auto) MultiPolygon::emplace_back(Args&&... args)
	{
		return m_data.emplace_back(std::forward<Args>(args)...);
	}

	inline MultiPolygon::value_type& MultiPolygon::front() noexcept
	{
		return m_data.front();
	}

	inline const MultiPolygon::value_type& MultiPolygon::front() const noexcept
	{
		return m_data.front();
	}

	inline MultiPolygon::value_type& MultiPolygon::back() noexcept
	{
		return m_data.back();
	}

	inline const MultiPolygon::value_type& MultiPolygon::back() const noexcept
	{
		return m_data.back();
	}

	inline void MultiPolygon::swap(MultiPolygon& other) noexcept
	{
		m_data.swap(other.m_data);
	}

	inline const MultiPolygon::value_type* MultiPolygon::data() const noexcept
	{
		return m_data.data();
	}

	inline MultiPolygon::value_type* MultiPolygon::data() noexcept
	{
		return m_data.data();
	}

	inline MultiPolygon::iterator MultiPolygon::begin() noexcept
	{
		return m_data.begin();
	}

	inline MultiPolygon::iterator MultiPolygon::end() noexcept
	{
		return m_data.end();
	}

	inline MultiPolygon::const_iterator MultiPolygon::begin() const noexcept
	{
		return m_data.begin();
	}

	inline MultiPolygon::const_iterator MultiPolygon::end() const noexcept
	{
		return m_data.end();
	}

	inline MultiPolygon::const_iterator MultiPolygon::cbegin() const noexcept
	{
		return m_data.cbegin();
	}

	inline MultiPolygon::const_iterator MultiPolygon::cend() const noexcept
	{
		return m_data.cend();
	}

	inline MultiPolygon::reverse_iterator MultiPolygon::rbegin() noexcept
	{
		return m_data.rbegin();
	}

	inline MultiPolygon::reverse_iterator MultiPolygon::rend() noexcept
	{
		return m_data.rend();
	}

	inline MultiPolygon::const_reverse_iterator MultiPolygon::rbegin() const noexcept
	{
		return m_data.rbegin();
	}

	inline MultiPolygon::const_reverse_iterator MultiPolygon::rend() const noexcept
	{
		return m_data.rend();
	}

	inline MultiPolygon::const_reverse_iterator MultiPolygon::crbegin() const noexcept
	{
		return m_data.crbegin();
	}

	inline MultiPolygon::const_reverse_iterator MultiPolygon::crend() const noexcept
	{
		return m_data.crend();
	}

	inline bool MultiPolygon::empty() const noexcept
	{
		return m_data.empty();
	}

	inline bool MultiPolygon::isEmpty() const noexcept
	{
		return m_data.empty();
	}

	inline MultiPolygon::operator bool() const noexcept
	{
		return (not m_data.empty());
	}

	inline size_t MultiPolygon::size() const noexcept
	{
		return m_data.size();
	}

	inline size_t MultiPolygon::size_bytes() const noexcept
	{
		return (m_data.size() * sizeof(value_type));
	}

	inline size_t MultiPolygon::max_size() const noexcept
	{
		return m_data.max_size();
	}

	inline void MultiPolygon::reserve(const size_t newCapacity)
	{
		m_data.reserve(newCapacity);
	}

	inline size_t MultiPolygon::capacity() const noexcept
	{
		return m_data.capacity();
	}

	inline void MultiPolygon::shrink_to_fit()
	{
		m_data.shrink_to_fit();
	}

	inline void MultiPolygon::clear() noexcept
	{
		m_data.clear();
	}

	inline void MultiPolygon::release()
	{
		clear();

		shrink_to_fit();
	}

	inline MultiPolygon::iterator MultiPolygon::insert(const_iterator where, const value_type& value)
	{
		return m_data.insert(where, value);
	}

	inline MultiPolygon::iterator MultiPolygon::insert(const_iterator where, value_type&& value)
	{
		return m_data.insert(where, std::move(value));
	}

	inline MultiPolygon::iterator MultiPolygon::insert(const_iterator where, const size_t count, const value_type& value)
	{
		return m_data.insert(where, count, value);
	}

	template <class Iterator>
	inline MultiPolygon::iterator MultiPolygon::insert(const_iterator where, Iterator first, Iterator last)
	{
		return m_data.insert(where, first, last);
	}

	inline MultiPolygon::iterator MultiPolygon::insert(const_iterator where, std::initializer_list<value_type> il)
	{
		return m_data.insert(where, il);
	}

	inline MultiPolygon::iterator MultiPolygon::erase(const_iterator where) noexcept
	{
		return m_data.erase(where);
	}

	inline MultiPolygon::iterator MultiPolygon::erase(const_iterator first, const_iterator last) noexcept
	{
		return m_data.erase(first, last);
	}

	inline void MultiPolygon::resize(const size_t newSize)
	{
		m_data.resize(newSize);
	}

	inline void MultiPolygon::resize(const size_t newSize, const value_type& value)
	{
		m_data.resize(newSize, value);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, MultiPolygon::value_type>>*>
	inline bool MultiPolygon::all(Fty f) const
	{
		return std::all_of(m_data.begin(), m_data.end(), f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, MultiPolygon::value_type>>*>
	inline bool MultiPolygon::any(Fty f) const
	{
		return std::any_of(m_data.begin(), m_data.end(), f);
	}

	SIV3D_CONCEPT_URBG_
	inline MultiPolygon::value_type& MultiPolygon::choice(URBG&& rbg)
	{
		if (empty())
		{
			throw std::out_of_range("MultiPolygon::choice(): Array is empty");
		}

		const size_t index = UniformIntDistribution<size_t>(0, size() - 1)(rbg);

		return operator[](index);
	}

	SIV3D_CONCEPT_URBG_
	inline const MultiPolygon::value_type& MultiPolygon::choice(URBG&& rbg) const
	{
		if (empty())
		{
			throw std::out_of_range("MultiPolygon::choice(): Array is empty");
		}

		const size_t index = UniformIntDistribution<size_t>(0, size() - 1)(rbg);

		return operator[](index);
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline MultiPolygon MultiPolygon::choice(const Int n) const
	{
		return choice(n, GetDefaultRNG());
	}

# if __cpp_lib_concepts
	template <Concept::Integral Size_t, Concept::UniformRandomBitGenerator URBG>
# else
	template <class Size_t, class URBG, std::enable_if_t<std::is_integral_v<Size_t>>*,
		std::enable_if_t<std::conjunction_v<std::is_invocable<URBG&>, std::is_unsigned<std::invoke_result_t<URBG&>>>>*>
# endif
	inline MultiPolygon MultiPolygon::choice(const Size_t n, URBG&& rbg) const
	{
		MultiPolygon result(Arg::reserve = Min<size_t>(n, size()));

		std::sample(begin(), end(), std::back_inserter(result), n, std::forward<URBG>(rbg));

		return result;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, MultiPolygon::value_type>>*>
	inline size_t MultiPolygon::count_if(Fty f) const
	{
		return m_data.count_if(f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, MultiPolygon::value_type>>*>
	inline bool MultiPolygon::none(Fty f) const
	{
		return std::none_of(m_data.begin(), m_data.end(), f);
	}

	template <class Fty>
	inline MultiPolygon& MultiPolygon::remove_if(Fty f)
	{
		m_data.remove_if(f);

		return *this;
	}

	SIV3D_CONCEPT_URBG_
	inline MultiPolygon& MultiPolygon::shuffle(URBG&& rbg)
	{
		m_data.shuffle(std::forward<URBG>(rbg));

		return *this;
	}

	template <class Shape2DType>
	inline bool MultiPolygon::intersects(const Shape2DType& other) const
	{
		return Geometry2D::Intersect(*this, other);
	}

	template <class Shape2DType>
	inline Optional<Array<Vec2>> MultiPolygon::intersectsAt(const Shape2DType& other) const
	{
		return Geometry2D::IntersectAt(*this, other);
	}

	template <class Shape2DType>
	inline bool MultiPolygon::contains(const Shape2DType& other) const
	{
		return Geometry2D::Contains(*this, other);
	}
}

template <>
void std::swap(s3d::MultiPolygon& a, s3d::MultiPolygon& b) noexcept
{
	a.swap(b);
}
