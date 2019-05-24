//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
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
		/// 
		/// 
		/// </summary>
		[[nodiscard]] bool Update();

		/// <summary>
		/// 
		/// 
		/// </summary>
		void Exit();

		/// <summary>
		/// 
		/// 
		/// </summary>
		void SetTerminationTriggers(uint32 userActionFlags);

		/// <summary>
		/// 
		/// 
		/// </summary>
		[[nodiscard]] uint32 GetTerminationTriggers();

		/// <summary>
		/// 
		/// 
		/// </summary>
		[[nodiscard]] uint32 GetUserActions();

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
		/// <param name="duration">
		/// 処理を停止する時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Sleep(const Duration& duration);

		bool LaunchBrowser(const FilePath& url);
	}
}
