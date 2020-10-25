//-----------------------------------------------
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
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "Window.hpp"
# include "TextureFilter.hpp"
# include "ResizeMode.hpp"

namespace s3d
{
	namespace Scene
	{
		/// @brief シーンの幅と高さ（ピクセル）のデフォルト値です。
		inline constexpr s3d::Size DefaultSceneSize = Window::DefaultClientSize;

		/// @brief ウィンドウをリサイズしたときのシーンのサイズの扱いのデフォルト値です。
		inline constexpr ResizeMode DefaultResizeMode = ResizeMode::Virtual;

		/// @brief ウィンドウのフレームバッファのサイズがシーンのサイズと異なる際、シーンの拡大縮小描画に用いるテクスチャフィルタのデフォルト値です。
		inline constexpr TextureFilter DefaultTextureFilter = TextureFilter::Linear;

		/// @brief シーンの背景色のデフォルト色です。
		inline constexpr ColorF DefaultBackgroundColor = Palette::DefaultBackground;

		/// @brief ウィンドウのクライアント領域がシーンよりも大きい場合に余白となるスペース「レターボックス」のデフォルト色です。
		inline constexpr ColorF DefaultLetterBoxColor = Palette::DefaultLetterbox;

		/// @brief `Scene::DeltaTime()` が返す最大の時間（秒）のデフォルト値です。
		inline constexpr double DefaultMaxDeltaTime = 0.1;
	}

	namespace Scene
	{
		void Resize(s3d::Size size);

		inline void Resize(int32 width, int32 height);

		/// @brief シーンの幅と高さ（ピクセル）の現在の設定を返します。
		/// @return シーンの幅と高さ（ピクセル）
		[[nodiscard]]
		s3d::Size Size() noexcept;

		/// @brief シーンの幅（ピクセル）の現在の設定を返します。
		/// @return シーンの幅（ピクセル）
		[[nodiscard]]
		inline int32 Width() noexcept;

		/// @brief シーンの高さ（ピクセル）の現在の設定を返します。
		/// @return シーンの高さ（ピクセル）
		[[nodiscard]]
		inline int32 Height() noexcept;

		/// @brief シーンの中心の座標を `Point` 型で返します。
		/// @return シーンの中心の座標
		[[nodiscard]]
		inline Point Center() noexcept;

		/// @brief シーンの中心の座標を `Vec2` 型で返します。
		/// @return シーンの中心の座標
		[[nodiscard]]
		inline Vec2 CenterF() noexcept;

		/// @brief 左上が (0, 0) で現在のシーンと同じ大きさの `Rect` を返します。
		/// @return シーンと同じ大きさの `Rect`
		[[nodiscard]]
		inline s3d::Rect Rect() noexcept;

		void SetResizeMode(ResizeMode resizeMode);

		[[nodiscard]]
		ResizeMode GetResizeMode() noexcept;

		void SetTextureFilter(TextureFilter textureFilter);

		[[nodiscard]]
		TextureFilter GetTextureFilter() noexcept;

		void SetBackground(const ColorF& color);

		[[nodiscard]]
		const ColorF& GetBackground() noexcept;

		void SetLetterbox(const ColorF& color);

		[[nodiscard]]
		const ColorF& GetLetterBox() noexcept;

		void SetMaxDeltaTime(double timeSec);

		[[nodiscard]] 
		double GetMaxDeltaTime() noexcept;

		[[nodiscard]]
		double DeltaTime() noexcept;

		[[nodiscard]]
		double Time() noexcept;

		/// @brief `System::Update()` が呼ばれた回数（= フレームカウント）を返します。
		/// @remark ユーザの環境によってフレームレートが変わるため、この値をアニメーション等の制御に使ってはいけません。
		/// @return `System::Update()` が呼ばれた回数
		[[nodiscard]]
		int32 FrameCount() noexcept;

		[[nodiscard]]
		Vec2 ClientToScene(Vec2 pos) noexcept;
	}
}

# include "detail/Scene.ipp"
