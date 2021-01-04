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
# include "Common.hpp"
# include "Array.hpp"
# include "Byte.hpp"

namespace s3d
{
	class Blob
	{
	public:

		using base_type					= Array<Byte>;
		using iterator					= base_type::iterator;
		using const_iterator			= base_type::const_iterator;
		using reverse_iterator			= base_type::reverse_iterator;
		using const_reverse_iterator	= base_type::const_reverse_iterator;

		SIV3D_NODISCARD_CXX20
		Blob() = default;

		SIV3D_NODISCARD_CXX20
		Blob(const Blob&) = default;

		SIV3D_NODISCARD_CXX20
		Blob(Blob&&) = default;

		SIV3D_NODISCARD_CXX20
		explicit Blob(size_t sizeBytes);

		SIV3D_NODISCARD_CXX20
		explicit Blob(FilePathView path);

		SIV3D_NODISCARD_CXX20
		Blob(const void* src, size_t sizeBytes);

		SIV3D_NODISCARD_CXX20
		explicit Blob(const Array<Byte>& data);

		SIV3D_NODISCARD_CXX20
		explicit Blob(Array<Byte>&& data);

		void create(const Blob& other);

		void create(Blob&& other);

		void create(const void* src, size_t sizeBytes);

		void create(const Array<Byte>& data);

		void create(Array<Byte>&& data);

		bool createFromFile(FilePathView path);

		[[nodiscard]]
		const Byte& operator[](const size_t index) const;

		[[nodiscard]]
		Byte& operator[](const size_t index);

		[[nodiscard]]
		const Byte* data() const noexcept;

		[[nodiscard]]
		Byte* data() noexcept;

		[[nodiscard]]
		const Array<Byte>& asArray() const noexcept;

		[[nodiscard]]
		bool empty() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		size_t size() const noexcept;

		[[nodiscard]]
		size_t capacity() const noexcept;

		void reserve(size_t sizeBytes);

		void shrink_to_fit();

		void clear();

		void release();

		[[nodiscard]]
		iterator begin() noexcept;

		[[nodiscard]]
		iterator end() noexcept;

		[[nodiscard]]
		const_iterator begin() const noexcept;

		[[nodiscard]]
		const_iterator end() const noexcept;

		[[nodiscard]]
		const_iterator cbegin() const noexcept;

		[[nodiscard]]
		const_iterator cend() const noexcept;

		[[nodiscard]]
		reverse_iterator rbegin() noexcept;

		[[nodiscard]]
		reverse_iterator rend() noexcept;

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept;

		void append(const void* src, size_t sizeBytes);

		bool save(FilePathView path) const;

	private:

		base_type m_data;
	};
}

# include "detail/Blob.ipp"
