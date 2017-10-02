//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Duration.hpp"

namespace s3d
{
	/// <summary>
	/// ウィンドウイベントのフラグ
	/// </summary>
	namespace WindowEvent
	{
		enum Flag : uint32
		{
			/// <summary>
			/// ウィンドウの [x] ボタンが押される
			/// </summary>
			CloseButton = 0x01,

			/// <summary>
			/// エスケープキーが押される
			/// </summary>
			EscapeKey = 0x02,

			/// <summary>
			/// ウィンドウのフォーカスが外れる
			/// </summary>
			Unfocus = 0x04,

			/// <summary>
			/// 何らかのキーが押される
			/// </summary>
			AnyKey = 0x08,

			/// <summary>
			/// デフォルト（ウィンドウの [x] ボタンが押されるか、エスケープキーが押される）
			/// </summary>
			Default = CloseButton | EscapeKey,

			/// <summary>
			/// 設定しない
			/// </summary>
			/// <remarks>
			/// 必ず System::Exit() を実行して終了する必要があります。
			/// </remarks>
			Manual = 0x00,
		};
	};

	namespace System
	{
		/// <summary>
		/// グラフィックスと入力を更新します。
		/// 終了イベントが発生した場合や、エンジンの内部でエラーが発生した場合 false を返します。
		/// </summary>
		/// <returns>
		/// アプリケーションが続行できる場合 true, アプリケーションを終了する場合 false
		/// </returns>
		bool Update(bool clearGraphics = true);

		/// <summary>
		/// アプリケーションの終了をエンジンに伝えます。
		/// 次の System::Update() は必ず false を返します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void Exit();

		/// <summary>
		/// アプリケーションを終了させるウィンドウイベントを設定します。
		/// </summary>
		/// <param name="windowEventFlag">
		/// WindowEvent::Flag の組み合わせ
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetExitEvent(uint32 windowEventFlag);

		/// <summary>
		/// 直前のフレームで発生したウィンドウイベントを返します。
		/// </summary>
		/// <returns>
		/// 直前のフレームで発生したウィンドウイベントを表す WindowEvent::Flag の組み合わせ
		/// </returns>
		uint32 GetPreviousEvent();

		double DeltaTime(double maxDuration = 0.1);

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

		/// <summary>
		/// System::Update() が呼ばれた回数（＝更新したフレーム数）を返します。
		/// </summary>
		/// <returns>
		/// System::Update() が呼ばれた回数
		/// </returns>
		int32 FrameCount();

		/// <summary>
		/// フレームカウントを変更します。
		/// </summary>
		/// <param name="count">
		/// 設定する値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void SetFrameCount(int32 count);
	
		bool LaunchBrowser(const FilePath& url);

		/// <summary>
		/// ライセンス情報を表示します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void ShowLicenses();
	}
}
