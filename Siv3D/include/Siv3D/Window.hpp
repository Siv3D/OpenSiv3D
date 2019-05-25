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
		/// デフォルトのクライアント解像度
		/// </summary>
		constexpr s3d::Size DefaultClientSize(800, 600);
	}

	enum class WindowStyle
	{
		Fixed,

		Sizable,

		Frameless,
	};

	enum class WindowResizeOption
	{
		ResizeSceneSize,

		KeepSceneSize,

		UseDefaultScaleMode,
	};

	struct WindowState
	{
		Size clientSize = Window::DefaultClientSize;

		Size minimumSize = Size(240, 180);

		Rect bounds = Rect(0);

		Size frameSize = Size(0, 0);

		int32 titleBarHeight = 0;

		WindowStyle style = WindowStyle::Fixed;

		double contentScale = 1.0;
		
		bool minimized = false;

		bool maximized = false;

		bool fullscreen = false;
	};

	namespace Window
	{
		void SetTitle(const String& title);

		template <class... Args>
		inline void SetTitle(const Args&... args)
		{
			SetTitle(Format(args...));
		}

		const String& GetTitle();

		WindowState GetState();

		void SetStyle(WindowStyle style);

		WindowStyle GetStyle();

		/// <summary>
		/// ウィンドウのクライアント領域のサイズを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域のサイズ
		/// </returns>
		[[nodiscard]] Size ClientSize();

		/// <summary>
		/// ウィンドウのクライアント領域の中央の座標を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の中央の座標
		/// </returns>
		[[nodiscard]] Point ClientCenter();

		/// <summary>
		/// ウィンドウのクライアント領域の幅を返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の幅(ピクセル）
		/// </returns>
		[[nodiscard]] int32 ClientWidth();

		/// <summary>
		/// ウィンドウのクライアント領域の高さを返します。
		/// </summary>
		/// <returns>
		/// ウィンドウのクライアント領域の高さ(ピクセル）
		/// </returns>
		[[nodiscard]] int32 ClientHeight();

		void SetPos(const Point& pos);

		void SetPos(int32 x, int32 y);

		void Centering();

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
		/// フルスクリーンモードが解除されます。
		/// </remarks>
		/// <returns>
		/// サイズの変更に成功したら true, それ以外の場合は false 
		/// </returns>
		bool Resize(const Size& size, WindowResizeOption option = WindowResizeOption::ResizeSceneSize, bool centering = true);

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
		/// フルスクリーンモードが解除されます。
		/// </remarks>
		/// <returns>
		/// サイズの変更に成功したら true, それ以外の場合は false 
		/// </returns>
		bool Resize(int32 width, int32 height, WindowResizeOption option = WindowResizeOption::ResizeSceneSize, bool centering = true);

		void Maximize();

		void Restore();

		void Minimize();

		bool SetFullscreen(bool fullscreen, const Optional<Size>& fullscreenResolution = unspecified);
	}

# if defined(SIV3D_TARGET_WINDOWS)

	namespace Platform::Windows::Window
	{
		void* GetHWND();

		bool ChangeDisplayResolution(const Size& size);
	}

# endif
}
