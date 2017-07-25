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
		// [x] Windows | [ ] macOS | [ ] Linux
		Size frameSize;

		/// <summary>
		/// ウィンドウのタイトルバーの高さ
		/// </summary>
		// [x] Windows | [ ] macOS | [ ] Linux
		int32 titleBarHeight;

		/// <summary>
		/// ウィンドウのタイトル
		/// </summary>
		String title;

		// [x] Windows | [ ] macOS | [ ] Linux
		ShowState showState;

		// [x] Windows | [ ] macOS | [ ] Linux
		bool focused;

		bool fullScreen;
	};

	namespace Window
	{
		/// <summary>
		/// デフォルトのクライアント解像度
		/// </summary>
		constexpr s3d::Size DefaultClientSize(640, 480);

		void SetTitle(const String& title);

		template <class... Args>
		inline void SetTitle(const Args&... args)
		{
			SetTitle(Format(args...));
		}
		
		const WindowState& GetState();

		/// <summary>
		/// ウィンドウのクライアント領域のサイズを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域のサイズ
		/// </returns>
		inline s3d::Size Size()
		{
			return GetState().clientSize;
		}

		/// <summary>
		/// ウィンドウのクライアント領域の中央の座標を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の中央の座標
		/// </returns>
		inline Point Center()
		{
			return GetState().clientSize / 2;
		}

		/// <summary>
		/// ウィンドウのクライアント領域の幅を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の幅(ピクセル）
		/// </returns>
		inline int32 Width()
		{
			return GetState().clientSize.x;
		}

		/// <summary>
		/// ウィンドウのクライアント領域の高さを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の高さ(ピクセル）
		/// </returns>
		inline int32 Height()
		{
			return GetState().clientSize.y;
		}

		/// <summary>
		/// ウィンドウのクライアント領域と同じサイズの Rect を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域と同じサイズの Rect
		/// </returns>
		inline Rect ClientRect()
		{
			return Rect(GetState().clientSize);
		}

		void SetPos(const Point& pos);

		void Centering();

		/// <summary>
		/// ウィンドウのサイズを変更します。
		/// </summary>
		/// <param name="width">
		/// 新しいウィンドウのクライアント領域の幅(ピクセル）
		/// </param>
		/// <param name="height">
		/// 新しいウィンドウのクライアント領域の高さ(ピクセル）
		/// </param>
		/// <param name="centering">
		/// サイズ変更後にセンタリングするか
		/// </param>
		/// <remarks>
		/// フルスクリーンの場合、この関数は失敗します。
		/// </remarks>
		/// <returns>
		/// サイズの変更に成功したら true, それ以外の場合は false 
		/// </returns>
		bool Resize(int32 width, int32 height, bool centering = true);

		/// <summary>
		/// ウィンドウのサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しいウィンドウのクライアント領域のサイズ(ピクセル）
		/// </param>
		/// <param name="centering">
		/// サイズ変更後にセンタリングするか
		/// </param>
		/// <remarks>
		/// フルスクリーンの場合、この関数は失敗します。
		/// </remarks>
		/// <returns>
		/// サイズの変更に成功したら true, それ以外の場合は false 
		/// </returns>
		inline bool Resize(const s3d::Size& size, bool centering = true)
		{
			return Resize(size.x, size.y, centering);
		}

		void SetBaseSize(const s3d::Size& size);

		s3d::Size BaseSize();

		inline Point BaseCenter()
		{
			return BaseSize() / 2;
		}

		inline int32 BaseWidth()
		{
			return BaseSize().x;
		}

		inline int32 BaseHeight()
		{
			return BaseSize().y;
		}

		inline Rect BaseClientRect()
		{
			return Rect(BaseSize());
		}
	}
}
