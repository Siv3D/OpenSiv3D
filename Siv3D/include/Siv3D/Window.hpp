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
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	namespace Window
	{
		/// <summary>
		/// ウィンドウのクライアント領域の幅と高さ（ピクセル）のデフォルト値です。
		/// </summary>
		inline constexpr Size DefaultClientSize = Size(800, 600);
	}

	/// <summary>
	/// 
	/// </summary>
	enum class WindowStyle
	{
		/// <summary>
		/// 
		/// </summary>
		Fixed,

		/// <summary>
		/// 
		/// </summary>
		Sizable,

		/// <summary>
		/// 
		/// </summary>
		Frameless,
	};

	/// <summary>
	/// 
	/// </summary>
	enum class WindowResizeOption
	{
		/// <summary>
		/// 
		/// </summary>
		ResizeSceneSize,

		/// <summary>
		/// 
		/// </summary>
		KeepSceneSize,

		/// <summary>
		/// 
		/// </summary>
		UseDefaultScaleMode,
	};

	/// <summary>
	/// 
	/// </summary>
	struct WindowState
	{
		/// <summary>
		/// 
		/// </summary>
		Size clientSize = Window::DefaultClientSize;

		/// <summary>
		/// 
		/// </summary>
		Size minimumSize = Size(240, 180);

		/// <summary>
		/// 
		/// </summary>
		Rect bounds = Rect(0);

		/// <summary>
		/// 
		/// </summary>
		Size frameSize = Size(0, 0);

		/// <summary>
		/// 
		/// </summary>
		int32 titleBarHeight = 0;

		/// <summary>
		/// 
		/// </summary>
		WindowStyle style = WindowStyle::Fixed;

		/// <summary>
		/// 
		/// </summary>
		double contentScale = 1.0;

		/// <summary>
		/// 
		/// </summary>		
		bool minimized = false;

		/// <summary>
		/// 
		/// </summary>
		bool maximized = false;

		/// <summary>
		/// 
		/// </summary>
		bool fullscreen = false;
	};

	namespace Window
	{
		/// <summary>
		/// ウィンドウのタイトルを変更します。
		/// </summary>
		void SetTitle(const String& title);

		/// <summary>
		/// ウィンドウのタイトルを変更します。
		/// </summary>
		template <class... Args>
		inline void SetTitle(const Args&... args)
		{
			SetTitle(Format(args...));
		}

		/// <summary>
		/// 現在のウィンドウタイトルを返します。
		/// </summary>
		const String& GetTitle();

		/// <summary>
		/// 現在のウィンドウステートを返します。
		/// </summary>
		WindowState GetState();

		/// <summary>
		/// ウィンドウスタイルを変更します。
		/// </summary>
		void SetStyle(WindowStyle style);

		/// <summary>
		/// 現在のウィンドウスタイルを返します。
		/// </summary>
		WindowStyle GetStyle();

		/// <summary>
		/// 現在のウィンドウのクライアント領域の幅と高さ（ピクセル）を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の幅と高さ（ピクセル）
		/// </returns>
		[[nodiscard]] Size ClientSize();

		/// <summary>
		/// 現在のウィンドウのクライアント領域における中心座標（ピクセル）を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域における中心座標（ピクセル）
		/// </returns>
		[[nodiscard]] Point ClientCenter();

		/// <summary>
		/// 現在のウィンドウのクライアント領域の幅（ピクセル）を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の幅(ピクセル）
		/// </returns>
		[[nodiscard]] int32 ClientWidth();

		/// <summary>
		/// 現在のウィンドウのクライアント領域の高さ（ピクセル）を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の高さ(ピクセル）
		/// </returns>
		[[nodiscard]] int32 ClientHeight();

		/// <summary>
		/// ウィンドウを指定した座標に移動させます。
		/// </summary>
		void SetPos(const Point& pos);

		/// <summary>
		/// ウィンドウを指定した座標に移動させます。
		/// </summary>
		void SetPos(int32 x, int32 y);

		/// <summary>
		/// ウィンドウをスクリーンの中心に移動させます。
		/// </summary>
		void Centering();

		/// <summary>
		/// ウィンドウのクライアント領域のサイズを変更します。
		/// </summary>
		/// <param name="size">
		/// 新しいウィンドウのクライアント領域のサイズ(ピクセル）
		/// </param>
		/// <param name="option">
		/// シーンの解像度を追従させるかを決めるオプション
		/// </param>
		/// <param name="centering">
		/// サイズ変更後にウィンドウをスクリーンの中心に移動させるかのフラグ
		/// </param>
		/// <remarks>
		/// フルスクリーンモードが解除されます。
		/// </remarks>
		/// <returns>
		/// サイズの変更に成功した場合 `true`, それ以外の場合 `false`
		/// </returns>
		bool Resize(const Size& size, WindowResizeOption option = WindowResizeOption::ResizeSceneSize, bool centering = true);

		/// <summary>
		/// ウィンドウのクライアント領域のサイズを変更します。
		/// </summary>
		/// <param name="width">
		/// 新しいウィンドウのクライアント領域の幅(ピクセル）
		/// </param>
		/// <param name="height">
		/// 新しいウィンドウのクライアント領域の高さ(ピクセル）
		/// </param>
		/// <param name="option">
		/// シーンの解像度を追従させるかを決めるオプション
		/// </param>
		/// <param name="centering">
		/// サイズ変更後にウィンドウをスクリーンの中心に移動させるかのフラグ
		/// </param>
		/// <remarks>
		/// フルスクリーンモードが解除されます。
		/// </remarks>
		/// <returns>
		/// サイズの変更に成功した場合 `true`, それ以外の場合 `false`
		/// </returns>
		bool Resize(int32 width, int32 height, WindowResizeOption option = WindowResizeOption::ResizeSceneSize, bool centering = true);

		/// <summary>
		/// ウィンドウを最大化します。
		/// </summary>
		void Maximize();

		/// <summary>
		/// 最大・最小化されたウィンドウを元のサイズに戻します。
		/// </summary>
		void Restore();

		/// <summary>
		/// ウィンドウを最小化します。
		/// </summary>
		void Minimize();

		/// <summary>
		/// フルスクリーンモードの設定をします。
		/// </summary>
		[[nodiscard]] bool SetFullscreen(bool fullscreen, const Optional<Size>& fullscreenResolution = unspecified, WindowResizeOption option = WindowResizeOption::ResizeSceneSize);
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::Window
	{
		/// <summary>
		/// 
		/// </summary>
		[[nodiscard]] void* GetHWND();

		/// <summary>
		/// 
		/// </summary>
		[[nodiscard]] bool ChangeDisplayResolution(const Size& size);
	}

# endif
}
