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
# include "IReader.hpp"
# include "Byte.hpp"

namespace s3d
{
	class MemoryViewReader : public IReader
	{
	public:

		SIV3D_NODISCARD_CXX20
		MemoryViewReader() = default;

		SIV3D_NODISCARD_CXX20
		constexpr MemoryViewReader(const void* data, size_t size_bytes) noexcept;

		/// @brief 読み込み位置を変更しないデータ読み込みをサポートしているかを返します。
		/// @return 読み込み位置を変更しないデータ読み込みをサポートしている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool supportsLookahead() const noexcept override;

		/// @brief Reader が使用可能かを返します。
		/// @return Reader が使用可能な場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const noexcept override;

		/// @brief Reader のサイズを返します。
		/// @return Reader のサイズ（バイト）
		[[nodiscard]]
		int64 size() const override;

		/// @brief Reader の現在の読み込み位置を返します。
		/// @return 現在の読み込み位置（バイト）
		[[nodiscard]]
		int64 getPos() const override;

		/// @brief Reader の読み込み位置を変更します。
		/// @param pos 新しい読み込み位置（バイト）
		/// @return 読み込み位置の変更に成功した場合 true, それ以外の場合は false
		bool setPos(int64 pos) override;

		/// @brief Reader を読み飛ばし、読み込み位置を変更します。
		/// @param offset 読み飛ばすサイズ（バイト）
		/// @return 新しい読み込み位置（バイト）
		int64 skip(int64 offset) override;

		/// @brief Reader からデータを読み込みます。
		/// @param dst 読み込み先
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		int64 read(void* dst, int64 size) override;

		/// @brief Reader からデータを読み込みます。
		/// @param dst 読み込み先
		/// @param pos 先頭から数えた読み込み開始位置（バイト）
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		int64 read(void* dst, int64 pos, int64 size) override;

		/// @brief Reader からデータを読み込みます。
		/// @tparam Type 読み込む値の型
		/// @param dst 読み込み先
		/// @return 読み込みに成功した場合 true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool read(TriviallyCopyable& dst);

		/// @brief Reader から読み込み位置を変更しないでデータを読み込みます。
		/// @param dst 読み込み先
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		int64 lookahead(void* dst, int64 size) const override;

		/// @brief Reader から読み込み位置を変更しないでデータを読み込みます。
		/// @param dst 読み込み先
		/// @param pos 先頭から数えた読み込み開始位置（バイト）
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		int64 lookahead(void* dst, int64 pos, int64 size) const override;

		/// @brief 読み込み位置を変更しないで Reader からデータを読み込みます。
		/// @tparam Type 読み込む値の型
		/// @param dst 読み込み先
		/// @return 読み込みに成功したら true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool lookahead(TriviallyCopyable& dst) const;

	private:

		int64 m_size = 0;

		int64 m_pos = 0;

		const Byte* m_ptr = nullptr;
	};
}

# include "detail/MemoryViewReader.ipp"
