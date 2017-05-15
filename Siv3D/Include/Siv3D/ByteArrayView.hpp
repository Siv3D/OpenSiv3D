//-----------------------------------------------
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
# include <type_traits>
# include <iterator>
# include <array>
# include "Fwd.hpp"

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

	private:

		const Byte* m_ptr = nullptr;

		size_type m_size = 0;

	public:

		constexpr ByteArrayView() noexcept
			: m_ptr(nullptr)
			, m_size(0) {}

		constexpr ByteArrayView(std::nullptr_t) noexcept
			: ByteArrayView() {}

		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		constexpr ByteArrayView(const Type* ptr, size_type count) noexcept
			: m_ptr(static_cast<const_pointer>(static_cast<const void*>(ptr)))
			, m_size(sizeof(Type) * count) {}

		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		constexpr ByteArrayView(const Type& value)
			: ByteArrayView(AddressOf(value), 1) {}

		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		constexpr ByteArrayView(const Type* first, const Type* last)
			: ByteArrayView(first, std::distance(first, last)) {}

		template <class Type, size_t N, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		constexpr ByteArrayView(const Type(&arr)[N])
			: ByteArrayView(AddressOf(arr[0]), N) {}

		template <class Type, size_t N, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		constexpr ByteArrayView(const std::array<Type, N>& arr)
			: ByteArrayView(AddressOf(arr[0]), N) {}

		template <class Container, std::enable_if_t<std::is_trivially_copyable<typename Container::value_type>::value &&
			std::is_convertible<typename Container::pointer, decltype(std::declval<Container>().data())>::value>* = nullptr>
		constexpr ByteArrayView(const Container& c)
			: ByteArrayView(c.data(), c.size()) {}

		constexpr ByteArrayView(const ByteArrayView&) noexcept = default;

		constexpr ByteArrayView(ByteArrayView&& other) noexcept = default;

		~ByteArrayView() noexcept = default;

		constexpr size_type size() const noexcept { return m_size; }

		constexpr size_type size_bytes() const noexcept { return size(); }

		constexpr bool empty() const noexcept { return size_bytes() == 0; }

		constexpr bool isEmpty() const noexcept { return empty(); }

		constexpr reference operator[](size_type index) const
		{
			return m_ptr[index];
		}

		constexpr pointer data() const noexcept { return m_ptr; }

		iterator begin() const noexcept { return m_ptr; }
		iterator end() const noexcept { return m_ptr + m_size; }

		const_iterator cbegin() const noexcept { return m_ptr; }
		const_iterator cend() const noexcept { return m_ptr + m_size; }

		reverse_iterator rbegin() const noexcept { return reverse_iterator{ end() }; }
		reverse_iterator rend() const noexcept { return reverse_iterator{ begin() }; }

		const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator{ cend() }; }
		const_reverse_iterator crend() const noexcept { return const_reverse_iterator{ cbegin() }; }

		String toHex() const;
	};
}
