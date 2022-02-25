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
# include "ProfilerStat.hpp"

namespace s3d
{
	namespace Profiler
	{
		/// @brief 1 秒間に更新されたフレーム数（フレームレート）を返します。
		/// @remark この値は 1 秒ごとに更新されます。
		/// @return 1 秒間に更新されたフレーム数
		[[nodiscard]]
		int32 FPS() noexcept;

		/// @brief アセットを毎フレーム連続して作成した場合の警告の ON / OFF を設定します。
		/// @param enbaled 警告を有効にするか
		void EnableAssetCreationWarning(bool enbaled);

		[[nodiscard]]
		const ProfilerStat& GetStat();
	}
}
