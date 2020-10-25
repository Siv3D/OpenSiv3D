//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "ImageFormat.hpp"
# include "PixelFormat.hpp"
# include "PointVector.hpp"

namespace s3d
{
	/// @brief 画像ファイルの情報
	struct ImageInfo
	{
		/// @brief 画像のエンコード形式
		ImageFormat imageFormat = ImageFormat::Unknown;

		/// @brief ピクセルの保存形式
		PixelFormat pixelFormat = PixelFormat::Unknown;

		/// @brief 画像のサイズ
		Size size = Size(0, 0);

		/// @brief アニメーションの有無
		bool isAnimated = false;
	};
}
