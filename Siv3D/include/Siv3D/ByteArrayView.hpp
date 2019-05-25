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
# include <iterator>
# include <type_traits>
# include <algorithm>
# include <cstring>
# include <array>
# include "Fwd.hpp"
# include "Byte.hpp"
# include "ByteArrayViewAdapter.hpp"
# include "LetterCase.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// バイト配列ビュー
	/// Byte array view
	/// </summary>
	class ByteArrayView : public ByteArrayViewAdapter
	{
	public:

		using reference					= const Byte&;
		using const_reference			= const Byte&;
		using const_iterator			= const_pointer;
		using iterator					= const_iterator;
		using const_reverse_iterator	= std::reverse_iterator<const_iterator>;
		using reverse_iterator			= const_reverse_iterator;
		using difference_type			= ptrdiff_t;

		static constexpr size_type npos = size_type{ static_cast<size_type>(-1) };

	public:

		constexpr ByteArrayView() noexcept
			: ByteArrayViewAdapter() {}

		explicit constexpr ByteArrayView(std::nullptr_t) noexcept
			: ByteArrayViewAdapter(nullptr) {}

		constexpr ByteArrayView(const void* ptr, const size_type size_bytes) noexcept
			: ByteArrayViewAdapter(ptr, size_bytes) {}

		template <class Type, std::enable_if_t<
			(std::is_trivially_copyable_v<Type>
				&& !std::is_pointer_v<Type>
				&& !IsMemoryContiguousContainer_v<Type>)>* = nullptr>
		explicit constexpr ByteArrayView(const Type& value)
			: ByteArrayViewAdapter(value) {}

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		constexpr ByteArrayView(const Type* first, const Type* last)
			: ByteArrayViewAdapter(first, last) {}

		template <class Type, size_t N, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		explicit constexpr ByteArrayView(const Type(&arr)[N])
			: ByteArrayViewAdapter(arr) {}

		template <class E, size_t N, std::enable_if_t<std::is_trivially_copyable_v<E>>* = nullptr>
		constexpr ByteArrayView(const std::array<E, N>& c)
			: ByteArrayViewAdapter(c) {}

		template <class Container, std::enable_if_t<IsMemoryContiguousContainer_v<Container>>* = nullptr>
		explicit constexpr ByteArrayView(const Container& c)
			: ByteArrayViewAdapter(c) {}

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

		constexpr void swap(ByteArrayView& other) noexcept
		{
			const ByteArrayView tmp(other);

			other = *this;

			*this = tmp;
		}

		size_type copyTo(void* const dst, size_type size, size_type pos = 0) const;

		[[nodiscard]] constexpr ByteArrayView subView(const size_type pos = 0, const size_type size = npos) const
		{
			if (pos > m_size)
			{
				throw std::out_of_range("ByteArrayView::subView()");
			}

			return ByteArrayView(m_data + pos, std::min(size, m_size - pos));
		}

		[[nodiscard]] String toHex(LetterCase letterCase = LetterCase::Upper, const String& sep = U", ", const String& begin = U"{", const String& end = U"}") const;
	};
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::ByteArrayView>
	{
		[[nodiscard]] size_t operator()(const s3d::ByteArrayView& value) const noexcept
		{
			return s3d::Hash::FNV1a(value.data(), value.size_bytes());
		}
	};
}
