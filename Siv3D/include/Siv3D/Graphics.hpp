//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Optional.hpp"

namespace s3d
{
	namespace Graphics
	{
		inline constexpr uint32 DefaultSampleCount = 4;

		/// @brief VSync の有効無効を設定します。
		/// @param enabled VSync を有効にする場合 true, 無効にする場合 false
		/// @remark デフォルトでは有効です。
		void SetVSyncEnabled(bool enabled);

		/// @brief VSync が有効であるかを返します。
		/// @return VSync が有効である場合 true, 無効である場合 false
		[[nodiscard]]
		bool IsVSyncEnabled();

		/// @brief VSync 無効時の目標フレームレートを設定します。
		/// @param fps 目標フレームレート（FPS）。フレームレート制限を無効にする場合は none
		/// @remark デフォルトでは none です。
		void SetTargetFrameRate(const Optional<double>& fps);

		/// @brief VSync 無効時の目標フレームレートを取得します。
		/// @return 目標フレームレート（FPS）。フレームレート制限が無効の場合は none
		[[nodiscard]]
		Optional<double> GetTargetFrameRate();
	}
}
