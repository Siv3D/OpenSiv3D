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
# include "Concepts.hpp"

namespace s3d
{
	/// @brief Writer インタフェース
	class IWriter
	{
	public:

		/// @brief デストラクタ 
		virtual ~IWriter() = default;

		/// @brief Writer が使用可能かを返します。
		/// @return Writer が使用可能な場合 true, それ以外の場合は false
		[[nodiscard]]
		virtual bool isOpen() const noexcept = 0;

		/// @brief Writer のサイズを返します。
		/// @return Writer のサイズ（バイト）
		[[nodiscard]]
		virtual int64 size() const = 0;

		/// @brief Writer の現在の書き込み位置を返します。
		/// @return 現在の書き込み位置（バイト）
		[[nodiscard]]
		virtual int64 getPos() const = 0;

		/// @brief Writer の書き込み位置を変更します。
		/// @param pos 新しい書き込み位置（バイト）
		/// @return 書き込み位置の変更に成功した場合 true, それ以外の場合は false
		virtual bool setPos(int64 pos) = 0;

		/// @brief Writer にデータを書き込みます。
		/// @param src 書き込むデータ
		/// @param sizeBytes 書き込むサイズ（バイト）
		/// @return 実際に書き込んだサイズ（バイト）
		virtual int64 write(const void* src, int64 sizeBytes) = 0;

		/// @brief Writer にデータを書き込みます。
		/// @tparam TriviallyCopyable 書き込む値の型
		/// @param src 書き込むデータ
		/// @return 書き込みに成功した場合 true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool write(const TriviallyCopyable& src);
	};
}

# include "detail/IWriter.ipp"
