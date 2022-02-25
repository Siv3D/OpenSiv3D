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
	/// @brief WAVE の保存形式
	enum class WAVEFormat : uint8
	{
		/// @brief 8bit ステレオ
		StereoUint8,

		/// @brief 16bit ステレオ
		StereoSint16,

		/// @brief 32bit float ステレオ
		StereoFloat32,

		/// @brief デフォルト（16bit ステレオ）
		Default = StereoSint16,
	};
}
