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
	/// @brief FFT サンプル数
	enum class FFTSampleLength : uint8
	{
		/// @brief 256 サンプル
		/// @remark 44.1kHz のサウンドに対して周波数分解能 172Hz
		SL256,

		/// @brief 512 サンプル
		/// @remark 44.1kHz のサウンドに対して周波数分解能 86.1Hz
		SL512,

		/// @brief 1024 サンプル
		/// @remark 44.1kHz のサウンドに対して周波数分解能 43.1Hz
		SL1K,

		/// @brief 2048 サンプル
		/// @remark 44.1kHz のサウンドに対して周波数分解能 21.5Hz
		SL2K,

		/// @brief 4096 サンプル
		/// @remark 44.1kHz のサウンドに対して周波数分解能 10.8Hz
		SL4K,

		/// @brief 8192 サンプル
		/// @remark 44.1kHz のサウンドに対して周波数分解能 5.38Hz	
		SL8K,

		/// @brief 16384 サンプル
		/// @remark 44.1kHz のサウンドに対して周波数分解能 2.69Hz
		SL16K,

		/// @brief デフォルト (8192 サンプル)
		/// @remark 44.1kHz のサウンドに対して周波数分解能 5.38Hz
		Default = SL8K
	};
}