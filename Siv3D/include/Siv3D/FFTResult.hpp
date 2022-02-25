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
# include "Array.hpp"

namespace s3d
{
	/// @brief FFT の結果
	struct FFTResult
	{
		/// @brief 結果
		Array<float> buffer;

		/// @brief 結果の周波数分解能
		double resolution = 0.0;

		/// @brief 元の波形のサンプルレート
		uint32 sampleRate = 0;
	};
}
