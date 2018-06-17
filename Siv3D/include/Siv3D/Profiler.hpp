//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"

namespace s3d
{
	struct Statistics
	{
		size_t drawcalls = 0;

		size_t triangles = 0;
	};

	/// <summary>
	/// プロファイリング
	/// </summary>
	/// <remarks>
	/// プロファイリング機能を提供します。
	/// </remarks>
	namespace Profiler
	{
		/// <summary>
		/// 実測のフレームレートを取得します。
		/// </summary>
		/// <returns>
		/// フレームレート
		/// </returns>
		[[nodiscard]] int32 FPS();

		void EnableAssetCreationWarning(bool enabled);

		[[nodiscard]] Statistics GetStatistics();
	}
}
