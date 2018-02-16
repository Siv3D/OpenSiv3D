//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <iterator>
# include <type_traits>
# include <algorithm>
# include <cstring>
# include <array>
# include "Fwd.hpp"
# include "Byte.hpp"

namespace s3d
{
	class ByteArrayView
	{
	public:

		using value_type				= Byte;
		using pointer					= const Byte*;
		using const_pointer				= const Byte*;
		using reference					= const Byte&;
		using const_reference			= const Byte&;
		using const_iterator			= const_pointer;
		using iterator					= const_iterator;
		using const_reverse_iterator	= std::reverse_iterator<const_iterator>;
		using reverse_iterator			= const_reverse_iterator;
		using size_type					= size_t;
		using difference_type			= ptrdiff_t;

		static constexpr size_type npos = size_type{ static_cast<size_type>(-1) };

	private:

		const Byte* m_data = nullptr;

		size_type m_size = 0;

	public:

		constexpr ByteArrayView() noexcept
			: m_data(nullptr)
			, m_size(0) {}

		constexpr ByteArrayView(const ByteArrayView&) noexcept = default;

		constexpr ByteArrayView(std::nullptr_t) noexcept
			: ByteArrayView() {}

		constexpr ByteArrayView(const void* ptr, const size_type size_bytes) noexcept
			: m_data(static_cast<const_pointer>(ptr))
			, m_size(size_bytes) {}

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		constexpr ByteArrayView(const Type& value)
			: ByteArrayView(std::addressof(value), sizeof(Type)) {}

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		constexpr ByteArrayView(const Type* first, const Type* last)
			: ByteArrayView(first, sizeof(Type) * std::distance(first, last)) {}

		template <class Type, size_t N, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		constexpr ByteArrayView(const Type(&arr)[N])
			: ByteArrayView(std::addressof(arr[0]), sizeof(Type) * N) {}

		template <class Type, size_t N, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		constexpr ByteArrayView(const std::array<Type, N>& arr)
			: ByteArrayView(arr.data(), sizeof(Type) * N) {}

		template <class Container, std::enable_if_t<std::is_trivially_copyable_v<typename Container::value_type> &&
			std::is_convertible_v<typename Container::pointer, decltype(std::declval<Container>().data())>>* = nullptr>
		constexpr ByteArrayView(const Container& c)
			: ByteArrayView(c.data(), sizeof(typename Container::value_type) * c.size()) {}

		constexpr ByteArrayView& operator =(const ByteArrayView&) noexcept = default;

		[[nodiscard]] constexpr const_iterator begin() const noexcept { return m_data; }

		[[nodiscard]] constexpr const_iterator end() const noexcept { return m_data + m_size; }

		[[nodiscard]] constexpr const_iterator cbegin() const noexcept { return m_data; }

		[[nodiscard]] constexpr const_iterator cend() const noexcept { return m_data + m_size; }

		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

		[[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }

		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

		[[nodiscard]] constexpr const_reference operator[](size_type index) const {	return m_data[index]; }

		[[nodiscard]] constexpr const_reference at(const size_type index) const
		{
			if (index >= m_size)
			{
				throw std::out_of_range("ByteArrayView::at() index out of range");
			}

			return m_data[index];
		}

		[[nodiscard]] constexpr const_pointer data() const noexcept { return m_data; }

		[[nodiscard]] constexpr size_type size() const noexcept { return m_size; }

		[[nodiscard]] constexpr size_type size_bytes() const noexcept { return m_size; }

		[[nodiscard]] constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); }

		[[nodiscard]] constexpr bool empty() const noexcept { return (m_size == 0); }

		[[nodiscard]] constexpr bool isEmpty() const noexcept { return (m_size == 0); }

		[[nodiscard]] explicit constexpr operator bool() const noexcept
		{
			return (m_size != 0);
		}

		constexpr void swap(ByteArrayView& other) noexcept
		{
			const ByteArrayView tmp(other);

			other = *this;

			*this = tmp;
		}

		size_type copy(void* const dst, const size_type size, const size_type pos = 0) const
		{
			if (pos > m_size)
			{
				throw std::out_of_range("ByteArrayView::copy()");
			}

			const size_type len = std::min(size, m_size - pos);

			const Byte* src = m_data + pos;

			::memcpy(dst, src, len);

			return len;
		}

		[[nodiscard]] constexpr ByteArrayView subView(const size_type pos = 0, const size_type size = npos) const
		{
			if (pos > m_size)
			{
				throw std::out_of_range("ByteArrayView::subView()");
			}

			return ByteArrayView(m_data + pos, std::min(size, m_size - pos));
		}

		[[nodiscard]] String toHex() const;
	};
}
