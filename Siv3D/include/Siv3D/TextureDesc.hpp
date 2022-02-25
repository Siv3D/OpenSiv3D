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

namespace s3d
{
	/// @brief テクスチャの設定
	enum class TextureDesc : uint8
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
	};
}

# include "detail/TextureDesc.ipp"
