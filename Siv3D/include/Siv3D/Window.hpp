﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Formatter.hpp"
# include "PointVector.hpp"
# include "StringView.hpp"
# include "WindowStyle.hpp"
# include "WindowState.hpp"

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

		/// @brief ウィンドウを最大化します。
		void Maximize();

		/// @brief 最大・最小化されたウィンドウを元のサイズに戻します。
		void Restore();

		/// @brief ウィンドウを最小化します。
		void Minimize();

		/// @brief ウィンドウのクライアントサイズを仮想サイズ基準で変更します。
		/// @param size 新しいサイズ
		/// @return サイズの変更に成功した場合 true, それ以外の場合は false
		inline bool Resize(Size size);

		inline bool Resize(int32 width, int32 height);

		bool ResizeVirtual(Size size);

		inline bool ResizeVirtual(int32 width, int32 height);

		bool ResizeActual(Size size);

		inline bool ResizeActual(int32 width, int32 height);

		void SetMinimumFrameBufferSize(Size size);
	}
}

# include "detail/Window.ipp"
