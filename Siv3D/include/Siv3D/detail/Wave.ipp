//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline Wave::Wave(const Arg::samplingRate_<uint32> samplingRate, const allocator_type& alloc) noexcept
		: m_data(alloc)
		, m_samplingRate{ *samplingRate } {}

	inline Wave::Wave(const size_t count, const value_type& value, const Arg::samplingRate_<uint32> samplingRate, const allocator_type& alloc)
		: m_data(count, value, alloc)
		, m_samplingRate{ *samplingRate } {}

	inline Wave::Wave(const size_t count, const Arg::samplingRate_<uint32> samplingRate, const allocator_type& alloc)
		: m_data(count, alloc)
		, m_samplingRate{ *samplingRate } {}

	template <class Iterator>
	inline Wave::Wave(Iterator first, Iterator last, const Arg::samplingRate_<uint32> samplingRate, const allocator_type& alloc)
		: m_data(first, last, alloc)
		, m_samplingRate{ *samplingRate } {}

	inline Wave::Wave(const Wave& samples)
		: m_data(samples.begin(), samples.end()) {}

	inline Wave::Wave(const Wave& samples, const allocator_type& alloc)
		: m_data(samples.begin(), samples.end(), alloc) {}

	inline Wave::Wave(Wave&& samples) noexcept
		: m_data(std::move(samples.m_data)) {}

	inline Wave::Wave(std::initializer_list<value_type> init, const Arg::samplingRate_<uint32> samplingRate, const allocator_type& alloc)
		: m_data(init, alloc)
		, m_samplingRate{ *samplingRate } {}

	inline Wave::Wave(const Array<value_type>& samples, const Arg::samplingRate_<uint32> samplingRate)
		: m_data(samples)
		, m_samplingRate{ *samplingRate } {}

	inline Wave::Wave(Array<value_type>&& samples, const Arg::samplingRate_<uint32> samplingRate) noexcept
		: m_data(std::move(samples))
		, m_samplingRate{ *samplingRate } {}

	inline Wave::Wave(const Arg::reserve_<size_type> size, const Arg::samplingRate_<uint32> samplingRate)
		: m_data(size)
		, m_samplingRate{ *samplingRate } {}

	inline Wave& Wave::operator =(const Array<value_type>& other)
	{
		m_data = other;

		return *this;
	}

	inline Wave& Wave::operator =(Array<value_type>&& other) noexcept
	{
		m_data = std::move(other);

		return *this;
	}

	inline Wave& Wave::operator =(const Wave& other)
	{
		m_data = other.m_data;
		m_samplingRate = other.m_samplingRate;

		return *this;
	}

	inline Wave& Wave::operator =(Wave&& other) noexcept
	{
		m_data = std::move(other.m_data);
		m_samplingRate = other.m_samplingRate;

		return *this;
	}

	inline const Array<Wave::value_type>& Wave::asArray() const noexcept
	{
		return m_data;
	}

	inline Wave::operator const Array<Wave::value_type>& () const noexcept
	{
		return m_data;
	}

	inline uint32 Wave::samplingRate() const noexcept
	{
		return m_samplingRate;
	}

	inline void Wave::setSamplingRate(const uint32 samplingRate) noexcept
	{
		m_samplingRate = samplingRate;
	}

	inline size_t Wave::samples() const noexcept
	{
		return m_data.size();
	}

	inline size_t Wave::lengthSample() const noexcept
	{
		return m_data.size();
	}

	inline double Wave::lengthSec() const noexcept
	{
		return static_cast<double>(size()) / m_samplingRate;
	}

	inline void Wave::fillZero()
	{
		m_data.fill(WaveSample::Zero());
	}

	template <class Iterator>
	inline void Wave::assign(Iterator first, Iterator last)
	{
		m_data.assign(first, last);
	}

	inline void Wave::assign(size_type n, const value_type& value)
	{
		m_data.assign(n, value);
	}

	inline void Wave::assign(std::initializer_list<value_type> il)
	{
		m_data.assign(il);
	}

	inline void Wave::assign(const Array<value_type>& other)
	{
		m_data = other;
	}

	inline void Wave::assign(Array<value_type>&& other) noexcept
	{
		m_data = std::move(other);
	}

	inline void Wave::assign(const Wave& other)
	{
		m_data = other.m_data;
	}

	inline void Wave::assign(Wave&& other) noexcept
	{
		m_data = std::move(other.m_data);
	}

	inline Wave::allocator_type Wave::get_allocator() const noexcept
	{
		return m_data.get_allocator();
	}

	inline Wave::value_type& Wave::at(const size_t index)&
	{
		return m_data.at(index);
	}

	inline const Wave::value_type& Wave::at(const size_t index) const&
	{
		return m_data.at(index);
	}

	inline Wave::value_type Wave::at(const size_t index)&&
	{
		return m_data.at(index);
	}

	inline Wave::value_type& Wave::operator[](const size_t index) & noexcept
	{
		return m_data[index];
	}

	inline const Wave::value_type& Wave::operator[](const size_t index) const& noexcept
	{
		return m_data[index];
	}

	inline Wave::value_type Wave::operator[](const size_t index) && noexcept
	{
		return std::move(m_data[index]);
	}

	inline void Wave::push_front(const value_type& value)
	{
		m_data.push_front(value);
	}

	inline void Wave::push_back(const value_type& value)
	{
		m_data.push_back(value);
	}

	inline void Wave::pop_front()
	{
		m_data.pop_front();
	}

	inline void Wave::pop_front_N(const size_t n)
	{
		m_data.pop_front_N(n);
	}

	inline void Wave::pop_back() noexcept
	{
		m_data.pop_back();
	}

	inline void Wave::pop_back_N(const size_t n)
	{
		m_data.pop_back_N(n);
	}

	inline Wave& Wave::operator <<(const value_type& value)
	{
		m_data.push_back(value);

		return *this;
	}

	template <class... Args>
	Wave::iterator Wave::emplace(const_iterator position, Args&&... args)
	{
		return m_data.emplace(position, std::forward<Args>(args)...);
	}

	template <class... Args>
	decltype(auto) Wave::emplace_back(Args&&... args)
	{
		return m_data.emplace_back(std::forward<Args>(args)...);
	}

	inline Wave::value_type& Wave::front() noexcept
	{
		return m_data.front();
	}

	inline const Wave::value_type& Wave::front() const noexcept
	{
		return m_data.front();
	}

	inline Wave::value_type& Wave::back() noexcept
	{
		return m_data.back();
	}

	inline const Wave::value_type& Wave::back() const noexcept
	{
		return m_data.back();
	}

	inline void Wave::swap(Wave& other) noexcept
	{
		m_data.swap(other.m_data);
	}

	inline const Wave::value_type* Wave::data() const noexcept
	{
		return m_data.data();
	}

	inline Wave::value_type* Wave::data() noexcept
	{
		return m_data.data();
	}

	inline Wave::iterator Wave::begin() noexcept
	{
		return m_data.begin();
	}

	inline Wave::iterator Wave::end() noexcept
	{
		return m_data.end();
	}

	inline Wave::const_iterator Wave::begin() const noexcept
	{
		return m_data.begin();
	}

	inline Wave::const_iterator Wave::end() const noexcept
	{
		return m_data.end();
	}

	inline Wave::const_iterator Wave::cbegin() const noexcept
	{
		return m_data.cbegin();
	}

	inline Wave::const_iterator Wave::cend() const noexcept
	{
		return m_data.cend();
	}

	inline Wave::reverse_iterator Wave::rbegin() noexcept
	{
		return m_data.rbegin();
	}

	inline Wave::reverse_iterator Wave::rend() noexcept
	{
		return m_data.rend();
	}

	inline Wave::const_reverse_iterator Wave::rbegin() const noexcept
	{
		return m_data.rbegin();
	}

	inline Wave::const_reverse_iterator Wave::rend() const noexcept
	{
		return m_data.rend();
	}

	inline Wave::const_reverse_iterator Wave::crbegin() const noexcept
	{
		return m_data.crbegin();
	}

	inline Wave::const_reverse_iterator Wave::crend() const noexcept
	{
		return m_data.crend();
	}

	inline bool Wave::empty() const noexcept
	{
		return m_data.empty();
	}

	inline bool Wave::isEmpty() const noexcept
	{
		return m_data.empty();
	}

	inline Wave::operator bool() const noexcept
	{
		return (not m_data.empty());
	}

	inline size_t Wave::size() const noexcept
	{
		return m_data.size();
	}

	inline size_t Wave::size_bytes() const noexcept
	{
		return (m_data.size() * sizeof(value_type));
	}

	inline size_t Wave::max_size() const noexcept
	{
		return m_data.max_size();
	}

	inline void Wave::reserve(const size_t newCapacity)
	{
		m_data.reserve(newCapacity);
	}

	inline size_t Wave::capacity() const noexcept
	{
		return m_data.capacity();
	}

	inline void Wave::shrink_to_fit()
	{
		m_data.shrink_to_fit();
	}

	inline void Wave::clear() noexcept
	{
		m_data.clear();
	}

	inline void Wave::release()
	{
		clear();

		shrink_to_fit();
	}

	inline Wave::iterator Wave::insert(const_iterator where, const value_type& value)
	{
		return m_data.insert(where, value);
	}

	inline Wave::iterator Wave::insert(const_iterator where, const size_t count, const value_type& value)
	{
		return m_data.insert(where, count, value);
	}

	template <class Iterator>
	inline Wave::iterator Wave::insert(const_iterator where, Iterator first, Iterator last)
	{
		return m_data.insert(where, first, last);
	}

	inline Wave::iterator Wave::insert(const_iterator where, std::initializer_list<value_type> il)
	{
		return m_data.insert(where, il);
	}

	inline Wave::iterator Wave::erase(const_iterator where) noexcept
	{
		return m_data.erase(where);
	}

	inline Wave::iterator Wave::erase(const_iterator first, const_iterator last) noexcept
	{
		return m_data.erase(first, last);
	}

	inline void Wave::resize(const size_t newSize)
	{
		m_data.resize(newSize);
	}

	inline void Wave::resize(const size_t newSize, const value_type& value)
	{
		m_data.resize(newSize, value);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Wave::value_type>>*>
	inline bool Wave::all(Fty f) const
	{
		return std::all_of(m_data.begin(), m_data.end(), f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Wave::value_type>>*>
	inline bool Wave::any(Fty f) const
	{
		return std::any_of(m_data.begin(), m_data.end(), f);
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Wave::value_type>>*>
	inline size_t Wave::count_if(Fty f) const
	{
		return m_data.count_if(f);
	}

	inline Wave& Wave::fill(const value_type& value)
	{
		m_data.fill(value);

		return *this;
	}

	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, Wave::value_type>>*>
	inline bool Wave::none(Fty f) const
	{
		return std::none_of(m_data.begin(), m_data.end(), f);
	}

	inline Wave& Wave::append(const Array<value_type>& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	inline Wave& Wave::append(const Wave& other)
	{
		m_data.insert(end(), other.begin(), other.end());

		return *this;
	}

	inline Wave& Wave::remove_at(const size_t index)
	{
		m_data.remove_at(index);

		return *this;
	}

	template <class Fty>
	inline Wave& Wave::remove_if(Fty f)
	{
		m_data.remove_if(f);

		return *this;
	}

	inline Wave& Wave::reverse()
	{
		m_data.reverse();

		return *this;
	}

	inline Wave Wave::reversed() const
	{
		return Wave(rbegin(), rend());
	}

	inline Wave Wave::slice(const size_t index) const
	{
		if (index >= size())
		{
			return{};
		}

		return Wave(begin() + index, end());
	}

	inline Wave Wave::slice(const size_t index, const size_t length) const
	{
		if (index >= size())
		{
			return{};
		}

		return Wave(begin() + index, begin() + Min(index + length, size()));
	}
}
