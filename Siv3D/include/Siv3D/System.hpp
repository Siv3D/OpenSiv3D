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
		/// 描画や入力情報など、フレームを更新します。
		/// </summary>
		[[nodiscard]] bool Update();

		/// <summary>
		/// プログラムを終了するために、この直後の `System::Update()` が `false` を返すように設定します。
		/// </summary>
		void Exit();

		/// <summary>
		/// アプリケーション終了トリガーに設定するユーザアクションを設定します。
		/// </summary>
		void SetTerminationTriggers(uint32 userActionFlags);

		/// <summary>
		/// アプリケーション終了トリガーに設定したユーザアクションのフラグの現在の設定を返します。
		/// </summary>
		[[nodiscard]] uint32 GetTerminationTriggers();

		/// <summary>
		/// 前回のフレームで発生したユーザアクションのフラグを返します。
		/// </summary>
		[[nodiscard]] uint32 GetUserActions();

		/// <summary>
		/// 現在のスレッドの実行を指定した時間だけ停止します。
		/// </summary>
		/// <param name="milliseconds">
		/// 処理を停止する時間（ミリ秒）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Sleep(int32 milliseconds);

		/// <summary>
		/// 現在のスレッドの実行を指定した時間だけ停止します。
		/// </summary>
		/// <param name="duration">
		/// 処理を停止する時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void Sleep(const Duration& duration);

		/// <summary>
		/// 指定した URL をデフォルトの Web ブラウザでオープンします。
		/// </summary>
		bool LaunchBrowser(const FilePath& url);
	}
}
