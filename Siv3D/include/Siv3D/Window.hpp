//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Formatter.hpp"
# include "Monitor.hpp"
# include "PointVector.hpp"
# include "StringView.hpp"
# include "WindowStyle.hpp"
# include "WindowState.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	namespace Window
	{	
		/// @brief ウィンドウのデフォルトのタイトル
		inline constexpr StringView DefaultTitle = U"Siv3D App";

		/// @brief ウィンドウのタイトルを変更します。
		/// @param title 新しいタイトル
		void SetTitle(const String& title);

		/// @brief ウィンドウのタイトルを変更します。
		/// @tparam ...Args 新しいタイトルの値の型
		/// @param ...args 新しいタイトル
		SIV3D_CONCEPT_FORMATTABLE_ARGS
		inline void SetTitle(const Args&... args);

		/// @brief 現在のウィンドウのタイトルを返します。
		/// @return  現在のウィンドウのタイトル
		[[nodiscard]]
		const String& GetTitle() noexcept;

		/// @brief 現在のウィンドウの状態を返します。
		/// @return 現在のウィンドウの状態
		[[nodiscard]]
		const WindowState& GetState() noexcept;

		/// @brief ウィンドウスタイルを変更します。
		/// @param style 新しいウィンドウスタイル
		void SetStyle(WindowStyle style);

		/// @brief 現在のウィンドウスタイルを返します。
		/// @return 現在のウィンドウスタイル
		[[nodiscard]]
		inline WindowStyle GetStyle() noexcept;

		/// @brief ウィンドウを指定したスクリーン座標に移動させます。
		/// @param pos 移動先のスクリーン座標
		void SetPos(Point pos);

		/// @brief ウィンドウを指定したスクリーン座標に移動させます。
		/// @param x 移動先のスクリーン X 座標
		/// @param y 移動先のスクリーン Y 座標
		inline void SetPos(int32 x, int32 y);

		/// @brief 現在のウィンドウの位置をスクリーン座標で返します。
		/// @return 現在のウィンドウの位置
		[[nodiscard]]
		inline Point GetPos() noexcept;

		/// @brief ウィンドウを現在のモニタのワークエリアの中央に移動させます。
		void Centering();

		/// @brief ウィンドウを最大化します。
		void Maximize();

		/// @brief 最大・最小化されたウィンドウを元のサイズに戻します。
		void Restore();

		/// @brief ウィンドウを最小化します。
		void Minimize();

		/// @brief ウィンドウのクライアントサイズを仮想サイズ基準で変更します。
		/// @param size 新しいサイズ（ピクセル）
		/// @param centering ウィンドウを画面の中心に移動させるか
		/// @return サイズの変更に成功した場合 true, それ以外の場合は false
		inline bool Resize(Size size, s3d::Centering centering = Centering::Yes);

		/// @brief ウィンドウのクライアントサイズを仮想サイズ基準で変更します。
		/// @param width 新しい幅（ピクセル）
		/// @param height 新しい高さ（ピクセル）
		/// @param centering ウィンドウを画面の中心に移動させるか
		/// @return サイズの変更に成功した場合 true, それ以外の場合は false
		inline bool Resize(int32 width, int32 height, s3d::Centering centering = Centering::Yes);

		/// @brief ウィンドウのクライアントサイズを仮想サイズ基準で変更します。
		/// @param size 新しいサイズ（ピクセル）
		/// @param centering ウィンドウを画面の中心に移動させるか
		/// @return サイズの変更に成功した場合 true, それ以外の場合は false
		bool ResizeVirtual(Size size, s3d::Centering centering = Centering::Yes);

		/// @brief ウィンドウのクライアントサイズを仮想サイズ基準で変更します。
		/// @param width 新しい幅（ピクセル）
		/// @param height 新しい高さ（ピクセル）
		/// @param centering ウィンドウを画面の中心に移動させるか
		/// @return サイズの変更に成功した場合 true, それ以外の場合は false
		inline bool ResizeVirtual(int32 width, int32 height, s3d::Centering centering = Centering::Yes);

		/// @brief ウィンドウのクライアントサイズを実サイズ基準で変更します。
		/// @param size 新しいサイズ（ピクセル）
		/// @param centering ウィンドウを画面の中心に移動させるか
		/// @return サイズの変更に成功した場合 true, それ以外の場合は false
		bool ResizeActual(Size size, s3d::Centering centering = Centering::Yes);

		/// @brief ウィンドウのクライアントサイズを実サイズ基準で変更します。
		/// @param width 新しい幅（ピクセル）
		/// @param height 新しい高さ（ピクセル）
		/// @param centering ウィンドウを画面の中心に移動させるか
		/// @return サイズの変更に成功した場合 true, それ以外の場合は false
		inline bool ResizeActual(int32 width, int32 height, s3d::Centering centering = Centering::Yes);

		/// @brief ウィンドウを手動でリサイズするときの最小サイズを実サイズ基準で設定します。
		/// @param size 設定するサイズ（ピクセル）
		void SetMinimumFrameBufferSize(Size size);

		/// @brief ウィンドウモードとフルスクリーンモードを切り替えます。
		/// @param fullscreen フルスクリーンモードにする場合 true, ウィンドウモードにする場合 false
		/// @param monitorIndex 表示するモニタのインデックス
		void SetFullscreen(bool fullscreen, size_t monitorIndex = System::GetCurrentMonitorIndex());

		/// @brief Windows 版において、Alt + Enter キーによるウィンドウモードとフルスクリーンモードの切り替えを有効にするかを設定します。
		/// @param enabled Alt + Enter キーによるウィンドウモードとフルスクリーンモードの切り替えを有効にする場合は true, 無効にする場合は false
		/// @remark Windows 版ではデフォルトで有効、それ以外のプラットフォームでは常に無効です。
		void SetToggleFullscreenEnabled(bool enabled);

		/// @brief Alt + Enter キーによるウィンドウモードとフルスクリーンモードの切り替えが有効であるかを返します。
		/// @return Alt + Enter キーによるウィンドウモードとフルスクリーンモードの切り替えが有効である場合 true, それ以外の場合は false
		/// @remark Windows 版以外では常に false を返します。
		[[nodiscard]]
		bool IsToggleFullscreenEnabled();
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::Window
	{
		/// @brief ウィンドウハンドルを返します。
		/// @return ウィンドウハンドル
		/// @remark この関数の戻り値を HWND にキャストして使用します。
		[[nodiscard]]
		void* GetHWND();
	}

# endif
}

# include "detail/Window.ipp"
