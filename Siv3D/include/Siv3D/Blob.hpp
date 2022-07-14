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
# include "Common.hpp"
# include "Array.hpp"
# include "Byte.hpp"
# include "IReader.hpp"
# include "MD5Value.hpp"

namespace s3d
{
	/// @brief バイナリデータ
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
		explicit Blob(Arg::reserve_<size_t> resrveSizeBytes);

		SIV3D_NODISCARD_CXX20
		explicit Blob(FilePathView path);

		SIV3D_NODISCARD_CXX20
		explicit Blob(IReader& reader);

		SIV3D_NODISCARD_CXX20
		Blob(const void* src, size_t sizeBytes);

		SIV3D_NODISCARD_CXX20
		explicit Blob(const Array<Byte>& data);

		SIV3D_NODISCARD_CXX20
		explicit Blob(Array<Byte>&& data);

		Blob& operator =(const Array<Byte>& other);

		Blob& operator =(Array<Byte>&& other) noexcept;

		Blob& operator =(const Blob& other);

		Blob& operator =(Blob&& other) noexcept;

		void create(const Blob& other);

		void create(Blob&& other);

		void create(const void* src, size_t sizeBytes);

		void create(const Array<Byte>& data);

		void create(Array<Byte>&& data);

		bool createFromFile(FilePathView path);

		[[nodiscard]]
		friend bool operator ==(const Blob& lhs, const Blob& rhs) noexcept
		{
			return (lhs.asArray() == rhs.asArray());
		}

		[[nodiscard]]
		friend bool operator !=(const Blob& lhs, const Blob& rhs) noexcept
		{
			return (lhs.asArray() != rhs.asArray());
		}

		[[nodiscard]]
		const Byte& operator [](const size_t index) const;

		[[nodiscard]]
		Byte& operator [](const size_t index);

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

		/// @brief バイナリデータのサイズ（バイト）を返します。
		/// @remark `size_bytes()` と同じです。
		/// @return バイナリデータのサイズ（バイト）
		[[nodiscard]]
		size_t size() const noexcept;

		/// @brief バイナリデータのサイズ（バイト）を返します。
		/// @remark `size` と同じです。
		/// @return バイナリデータのサイズ（バイト）
		[[nodiscard]]
		size_t size_bytes() const noexcept;

		[[nodiscard]]
		size_t capacity() const noexcept;

		void reserve(size_t sizeBytes);

		void resize(size_t sizeBytes);

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

		/// @brief 末尾にバイナリデータを追加します。
		/// @param src 追加するデータの先頭ポインタ
		/// @param sizeBytes 追加するデータのサイズ
		void append(const void* src, size_t sizeBytes);

		/// @brief バイナリデータをファイルに保存します。
		/// @param path ファイルパス
		/// @return 保存に成功した場合 true, それ以外の場合は false
		bool save(FilePathView path) const;

		/// @brief バイナリデータを MD5 のハッシュ値に変換します。
		/// @return バイナリデータの MD5 ハッシュ値
		[[nodiscard]]
		MD5Value md5() const;

		/// @brief バイナリデータを Base64 エンコードします。
		/// @return エンコードされたデータ
		[[nodiscard]]
		std::string base64() const;

		/// @brief バイナリデータを Base64 エンコードします。
		/// @return エンコードされたデータ
		[[nodiscard]]
		String base64Str() const;

		/// @brief バイナリデータを Base64 エンコードし、dst に格納します。
		/// @param dst エンコードされたデータの格納先
		void base64(std::string& dst) const;

		/// @brief バイナリデータを Base64 エンコードし、dst に格納します。
		/// @param dst エンコードされたデータの格納先
		void base64(String& dst) const;

	private:

		base_type m_data;
	};
}

# include "detail/Blob.ipp"
