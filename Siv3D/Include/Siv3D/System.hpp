//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Duration.hpp"

namespace s3d
{
	namespace System
	{
		/// <summary>
		/// 指定したミリ秒だけ処理を停止します。
		/// </summary>
		/// <param name="milliseconds">
		/// 処理を停止する時間（ミリ秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Sleep(int32 milliseconds);

		/// <summary>
		/// 指定したミリ秒だけ処理を停止します。
		/// </summary>
		/// <param name="milliseconds">
		/// 処理を停止する時間（ミリ秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		inline void Sleep(const MillisecondsF& milliseconds)
		{
			Sleep(static_cast<int32>(milliseconds.count()));
		}
	}
}
