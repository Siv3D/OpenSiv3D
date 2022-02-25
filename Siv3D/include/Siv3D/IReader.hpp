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
# include <memory>
# include "Common.hpp"
# include "Concepts.hpp"

namespace s3d
{
	/// @brief Reader インタフェース
	class IReader
	{
	public:

		/// @brief デストラクタ 
		virtual ~IReader() = default;

		/// @brief 読み込み位置を変更しないデータ読み込みをサポートしているかを返します。
		/// @return 読み込み位置を変更しないデータ読み込みをサポートしている場合 true, それ以外の場合は false
		[[nodiscard]]
		virtual bool supportsLookahead() const noexcept = 0;

		/// @brief Reader が使用可能かを返します。
		/// @return Reader が使用可能な場合 true, それ以外の場合は false
		[[nodiscard]]
		virtual bool isOpen() const noexcept = 0;

		/// @brief Reader のサイズを返します。
		/// @return Reader のサイズ（バイト）
		[[nodiscard]]
		virtual int64 size() const = 0;

		/// @brief Reader の現在の読み込み位置を返します。
		/// @return 現在の読み込み位置（バイト）
		[[nodiscard]]
		virtual int64 getPos() const = 0;

		/// @brief Reader の読み込み位置を変更します。
		/// @param pos 新しい読み込み位置（バイト）
		/// @return 読み込み位置の変更に成功した場合 true, それ以外の場合は false
		virtual bool setPos(int64 pos) = 0;

		/// @brief Reader を読み飛ばし、読み込み位置を変更します。
		/// @param offset 読み飛ばすサイズ（バイト）
		/// @return 新しい読み込み位置（バイト）
		virtual int64 skip(int64 offset) = 0;

		/// @brief Reader からデータを読み込みます。
		/// @param dst 読み込み先
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		virtual int64 read(void* dst, int64 size) = 0;

		/// @brief Reader からデータを読み込みます。
		/// @param dst 読み込み先
		/// @param pos 先頭から数えた読み込み開始位置（バイト）
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		virtual int64 read(void* dst, int64 pos, int64 size) = 0;

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
		virtual int64 lookahead(void* dst, int64 size) const = 0;

		/// @brief Reader から読み込み位置を変更しないでデータを読み込みます。
		/// @param dst 読み込み先
		/// @param pos 先頭から数えた読み込み開始位置（バイト）
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		virtual int64 lookahead(void* dst, int64 pos, int64 size) const = 0;

		/// @brief 読み込み位置を変更しないで Reader からデータを読み込みます。
		/// @tparam Type 読み込む値の型
		/// @param dst 読み込み先
		/// @return 読み込みに成功したら true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool lookahead(TriviallyCopyable& dst) const;
	};
}

# include "detail/IReader.ipp"
