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
# include "Color.hpp"
# include "Window.hpp"
# include "SamplerState.hpp"

namespace s3d
{
	/// <summary>
	/// ウィンドウを手動でリサイズしたときのシーンのサイズの扱いです。
	/// </summary>
	enum class ScaleMode
	{
		/// <summary>
		/// ウィンドウのクライアント領域のサイズに合わせてシーンをリサイズします。
		/// </summary>
		ResizeFill,

		/// <summary>
		/// シーンのサイズはそのままで、アスペクト比を維持して拡大縮小してクライアント領域にフィットさせ描画します。
		/// </summary>
		AspectFit,
	};

	namespace Scene
	{
		/// <summary>
		/// シーンの幅と高さ（ピクセル）のデフォルト値です。
		/// </summary>
		inline constexpr s3d::Size DefaultSceneSize = Window::DefaultClientSize;
		
		/// <summary>
		/// ウィンドウを手動でリサイズしたときのシーンのサイズの扱いのデフォルト値です。
		/// </summary>
		inline constexpr ScaleMode DefaultScaleMode = ScaleMode::AspectFit;

		/// <summary>
		/// ウィンドウのクライアント領域がシーンのサイズと異なる場合、シーンを拡大縮小描画するために使うテクスチャフィルタのデフォルト値です。
		/// </summary>
		inline constexpr TextureFilter DefaultFilter = TextureFilter::Linear;

		/// <summary>
		/// シーンの背景色のデフォルト色です。
		/// </summary>
		inline constexpr ColorF DefaultBackgroundColor = Palette::DefaultBackground;

		/// <summary>
		/// ウィンドウのクライアント領域がシーンよりも大きい場合に余白となるスペース「レターボックス」のデフォルト色です。
		/// </summary>
		inline constexpr ColorF DefaultLetterBoxColor = Palette::DefaultLetterbox;

		/// <summary>
		/// `Scene::DeltaTime()` が返す最大の時間（秒）のデフォルト値です。
		/// </summary>
		inline constexpr double DefaultMaxDeltaTime = 0.1;


		/// <summary>
		/// シーンの幅と高さを変更します。
		/// </summary>
		void Resize(const s3d::Size& size);

		/// <summary>
		/// シーンの幅と高さを変更します。
		/// </summary>
		void Resize(int32 width, int32 height);

		/// <summary>
		/// シーンの幅と高さ（ピクセル）の現在の設定を返します。
		/// </summary>
		[[nodiscard]] s3d::Size Size();

		/// <summary>
		/// シーンの幅（ピクセル）の現在の設定を返します。
		/// </summary>
		[[nodiscard]] int32 Width();

		/// <summary>
		/// シーンの高さ（ピクセル）の現在の設定を返します。
		/// </summary>
		[[nodiscard]] int32 Height();

		/// <summary>
		/// シーンの中心の座標を `Point` 型で返します。
		/// </summary>
		[[nodiscard]] Point Center();

		/// <summary>
		/// シーンの中心の座標を `Vec2` 型で返します。
		/// </summary>
		[[nodiscard]] Vec2 CenterF();

		/// <summary>
		/// 左上が (0, 0) で現在のシーンと同じ大きさの `Rect` を返します。
		/// </summary>
		[[nodiscard]] s3d::Rect Rect();

		/// <summary>
		/// ウィンドウを手動でリサイズしたときのシーンのサイズの扱いを設定します。
		/// </summary>
		void SetScaleMode(ScaleMode scaleMode);

		/// <summary>
		/// ウィンドウを手動でリサイズしたときのシーンのサイズの扱いの現在の設定を返します。
		/// </summary>
		[[nodiscard]] ScaleMode GetScaleMode();

		/// <summary>
		/// ウィンドウのクライアント領域がシーンのサイズと異なる場合にシーンを拡大縮小描画するために使うテクスチャフィルタを設定します。
		/// </summary>
		void SetTextureFilter(TextureFilter textureFilter);

		/// <summary>
		/// ウィンドウのクライアント領域がシーンのサイズと異なる場合にシーンを拡大縮小描画するために使うテクスチャフィルタの現在の設定を返します。
		/// </summary>
		[[nodiscard]] TextureFilter GetTextureFilter();

		/// <summary>
		/// シーンの背景色を設定します。
		/// </summary>
		void SetBackground(const ColorF& color);

		/// <summary>
		/// ウィンドウのクライアント領域がシーンよりも大きい場合に余白となるスペース「レターボックス」の色を設定します。
		/// </summary>
		void SetLetterbox(const ColorF& color);

		/// <summary>
		/// `Scene::DeltaTime()` が返す最大の時間（秒）を設定します。
		/// </summary>
		void SetMaxDeltaTime(double timeSec);

		/// <summary>
		/// `Scene::DeltaTime()` が返す最大の時間（秒）の現在の設定を返します。
		/// </summary>
		[[nodiscard]] double GetMaxDeltaTime();

		/// <summary>
		/// 前回の `System::Update()` からの経過時間（秒）を返します。
		/// </summary>
		[[nodiscard]] double DeltaTime();

		/// <summary>
		/// アプリケーションが起動してからの経過時間（秒）を返します。
		/// </summary>
		[[nodiscard]] double Time();

		/// <summary>
		/// `System::Update()` が呼ばれた回数（= フレームカウント）を返します。
		/// </summary>
		[[nodiscard]] int32 FrameCount();

		/// <summary>
		/// ウィンドウのクライアント領域上の座標をシーン上の座標に変換します。
		/// </summary>
		[[nodiscard]] Vec2 ClientToScene(const Vec2& pos);
	}
}
