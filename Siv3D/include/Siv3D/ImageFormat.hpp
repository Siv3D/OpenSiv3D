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

namespace s3d
{
	/// @brief 画像フォーマット
	enum class ImageFormat : uint8
	{
		/// @brief 不明
		Unknown,

		/// @brief DDS
		DDS,

		/// @brief PNG
		PNG,

		/// @brief JPEG
		JPEG,

		/// @brief JPEG 2000
		JPEG2000,

		/// @brief BMP
		BMP,

		/// @brief WebP
		WebP,

		/// @brief GIF
		GIF,

		/// @brief TIFF
		TIFF,

		/// @brief TGA
		TGA,

		/// @brief PPM
		PPM,

		/// @brief SVG
		SVG,

		/// @brief 指定しない（データと拡張子から判断）
		Unspecified = Unknown,
	};
}
