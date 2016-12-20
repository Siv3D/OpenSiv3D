//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
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
			/// マウスの左クリック
			/// </summary>
			LeftClick = 0x04,

			/// <summary>
			/// マウスの右クリック
			/// </summary>
			RightClick = 0x08,

			/// <summary>
			/// ウィンドウのフォーカスが外れる
			/// </summary>
			Unfocus = 0x10,

			/// <summary>
			/// 何らかのキーが押される
			/// </summary>
			AnyKey = 0x20,

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
		
		bool Update();
	}
}
