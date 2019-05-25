//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <type_traits>
# include <array>
# include <string>
# include "Fwd.hpp"
# include "StringView.hpp"
# include "TypeTraits.hpp"

namespace s3d
{
	class ByteArrayViewAdapter
	{
	public:

		using value_type	= Byte;
		using pointer		= const Byte*;
		using const_pointer = const Byte*;
		using size_type		= size_t;

	protected:

		const Byte* m_data = nullptr;

		size_type m_size = 0;

	public:

		constexpr ByteArrayViewAdapter() noexcept
			: m_data(nullptr)
			, m_size(0) {}

		constexpr ByteArrayViewAdapter(std::nullptr_t) noexcept
			: ByteArrayViewAdapter() {}

		constexpr ByteArrayViewAdapter(const void* ptr, const size_type size_bytes) noexcept
			: m_data(static_cast<const_pointer>(ptr))
			, m_size(size_bytes) {}

		template <class Type, std::enable_if_t<
			(std::is_trivially_copyable_v<Type>
			&& !std::is_pointer_v<Type>
			&& !IsMemoryContiguousContainer_v<Type>)>* = nullptr>
		constexpr ByteArrayViewAdapter(const Type& value)
			: ByteArrayViewAdapter(std::addressof(value), sizeof(Type)) {}

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		constexpr ByteArrayViewAdapter(const Type* first, const Type* last)
			: ByteArrayViewAdapter(first, sizeof(Type) * std::distance(first, last)) {}

		template <class Type, size_t N, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		constexpr ByteArrayViewAdapter(const Type(&arr)[N])
			: ByteArrayViewAdapter(std::addressof(arr[0]), sizeof(Type) * N) {}

		template <class E, size_t N, std::enable_if_t<std::is_trivially_copyable_v<E>>* = nullptr>
		constexpr ByteArrayViewAdapter(const std::array<E, N>& c)
			: ByteArrayViewAdapter(std::data(c), sizeof(E) * N) {}

		template <class Container, std::enable_if_t<IsMemoryContiguousContainer_v<Container>>* = nullptr>
		constexpr ByteArrayViewAdapter(const Container& c)
			: ByteArrayViewAdapter(std::data(c), sizeof(typename Container::value_type) * std::size(c)) {}

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
	};
}
