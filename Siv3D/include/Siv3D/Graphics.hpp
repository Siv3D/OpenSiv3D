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
	}
}
