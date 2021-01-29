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

namespace s3d
{
	/// @brief テクスチャの設定
	enum class TextureDesc : uint32
	{
		/// @brief ミップマップなし
		Unmipped,

		/// @brief ミップマップなし、sRGB
		UnmippedSRGB,

		/// @brief ミップマップあり
		Mipped,

		/// @brief ミップマップあり、sRGB
		MippedSRGB,

		/// @brief Signed Distance Field
		SDF,

		/// @brief 3D 用のテクスチャのデフォルト [ミップマップあり、sRGB]
		For3D = MippedSRGB,
	};
}

# include "detail/TextureDesc.ipp"
