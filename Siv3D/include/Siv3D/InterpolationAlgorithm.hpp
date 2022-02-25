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
	/// @brief 画像拡大縮小の手法
	enum class InterpolationAlgorithm : uint32
	{
		/// @brief 最近傍補間
		Nearest,

		/// @brief バイリニア補間
		Linear,

		/// @brief バイキュービック補間
		Cubic,

		/// @brief エリア（画像の大幅な縮小に適している）
		Area,

		/// @brief Lanczos（拡大や、小幅な縮小に適している）
		Lanczos,

		/// @brief 最適な手法を自動選択
		Auto,
	};
}
