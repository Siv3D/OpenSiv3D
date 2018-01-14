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
		int32 FPS();

		void EnableAssetCreationWarning(bool enabled);
	}
}
