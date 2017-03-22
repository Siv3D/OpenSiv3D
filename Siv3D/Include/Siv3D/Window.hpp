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
# include "Format.hpp"
# include "Rectangle.hpp"

namespace s3d
{
	enum class ShowState
	{
		Normal,

		Minimized,

		Maximized,
	};

	/// <summary>
	/// ウィンドウの状態
	/// </summary>
	struct WindowState
	{
		/// <summary>
		/// クライアント画面（描画可能域）の幅と高さ
		/// </summary>
		Size clientSize;

		/// <summary>
		/// 枠線を含めたウィンドウの幅と高さ
		/// </summary>
		Size windowSize;

		/// <summary>
		/// ウィンドウの左上の位置
		/// </summary>
		Point pos;

		/// <summary>
		/// ウィンドウの枠線の幅と高さ
		/// </summary>
		Size frameSize;

		/// <summary>
		/// ウィンドウのタイトルバーの高さ
		/// </summary>
		int32 titleBarHeight;

		/// <summary>
		/// ウィンドウのタイトル
		/// </summary>
		String title;

		ShowState showState;

		bool focused;
	};

	namespace Window
	{
		constexpr Size DefaultClientSize(640, 480);

		void SetTitle(const String& title);

		template <class... Args>
		inline void SetTitle(const Args&... args)
		{
			SetTitle(Format(args...));
		}
		
		const WindowState& GetState();

		// [x] Windows | [ ] macOS | [ ] Linux
		void SetPos(const Point& pos);

		// [ ] Windows | [ ] macOS | [ ] Linux
		void Centering();
	}
}
