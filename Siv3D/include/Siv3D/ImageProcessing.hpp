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
# include "Image.hpp"

namespace s3d
{
	namespace ImageProcessing
	{
		/// @brief 何枚のミップマップ画像が作成されるかを返します。
		/// @param width 元の画像の幅（ピクセル）
		/// @param height 元の画像の高さ（ピクセル）
		/// @return 作成されるミップマップ画像の枚数
		[[nodiscard]]
		inline constexpr size_t CalculateMipCount(uint32 width, uint32 height) noexcept;

		/// @brief 画像からミップマップ画像を作成します。
		/// @param src 画像
		/// @return ミップマップ画像
		[[nodiscard]] 
		Array<Image> GenerateMips(const Image& src);
	}
}

# include "detail/ImageProcessing.ipp"
