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
# include <Siv3D/Common.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Input.hpp>

namespace s3d
{
	/// @brief 入力操作を可視化するアイコン
	namespace InputIcon
	{
		/// @brief デフォルトのハイライトカラー
		inline constexpr ColorF DefaultHighlightColor{ 1.0, 0.6, 0.6 };

		/// @brief アイコンのサイズ（ピクセル）を返します。
		/// @param label アイコンのラベル
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @return アイコンのサイズ（ピクセル）
		[[nodiscard]]
		inline Vec2 GetSize(StringView label, const Font& font, double size);

		/// @brief アイコンのサイズ（ピクセル）を返します。
		/// @param input 入力オブジェクト
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @return アイコンのサイズ（ピクセル）
		[[nodiscard]]
		inline Vec2 GetSize(const Input& input, const Font& font, double size);

		/// @brief 入力操作を可視化するアイコンを描画します。
		/// @param label アイコンのラベル
		/// @param isPressed 押されている状態か
		/// @param center アイコンを描画する中心座標
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @param keyColor アイコンの色
		/// @param labelColor ラベルの色
		inline void DrawAt(StringView label, bool isPressed, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black);

		/// @brief 入力操作を可視化するインタラクティブなアイコンを描画します。
		/// @param input 入力オブジェクト
		/// @param center アイコンを描画する中心座標
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @param keyColor アイコンの色
		/// @param labelColor ラベルの色
		/// @param highlightColor 押されている操作のときのアイコンのハイライト色
		inline void DrawInteractiveAt(const Input& input, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);

		/// @brief 入力操作を可視化するアイコンを描画します。
		/// @param input 入力オブジェクト
		/// @param isPressed 押されている状態か
		/// @param center アイコンを描画する中心座標
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @param keyColor アイコンの色
		/// @param labelColor ラベルの色
		/// @param highlightColor 押されている操作のときのアイコンのハイライト色
		inline void DrawAt(const Input& input, bool isPressed, const Vec2& center, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);

		/// @brief 入力操作を可視化するアイコンを描画します。
		/// @param label アイコンのラベル
		/// @param isPressed 押されている状態か
		/// @param pos アイコンを描画する左上の座標
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @param keyColor アイコンの色
		/// @param labelColor ラベルの色
		inline void Draw(StringView label, bool isPressed, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black);

		/// @brief 入力操作を可視化するインタラクティブなアイコンを描画します。
		/// @param input 入力オブジェクト
		/// @param pos アイコンを描画する左上の座標
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @param keyColor アイコンの色
		/// @param labelColor ラベルの色
		/// @param highlightColor 押されている操作のときのアイコンのハイライト色
		inline void DrawInteractive(const Input& input, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);

		/// @brief 入力操作を可視化するアイコンを描画します。
		/// @param input 入力オブジェクト
		/// @param isPressed 押されている状態か
		/// @param pos アイコンを描画する左上の座標
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @param keyColor アイコンの色
		/// @param labelColor ラベルの色
		/// @param highlightColor 押されている操作のときのアイコンのハイライト色
		inline void Draw(const Input& input, bool isPressed, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);

		/// @brief 入力操作を可視化するアイコンを描画します。
		/// @remark Glyph と混在して描画しやすいよう描画座標が調整されます。
		/// @param input 入力オブジェクト
		/// @param pos アイコンを描画する左上の座標
		/// @param font ラベルに使用するフォント
		/// @param size アイコンの縦のサイズ（ピクセル）
		/// @param keyColor アイコンの色
		/// @param labelColor ラベルの色
		/// @param highlightColor 押されている操作のときのアイコンのハイライト色
		/// @return アイコンの幅（ピクセル）
		inline double DrawAsGlyph(const Input& input, const Vec2& pos, const Font& font, double size, const ColorF& keyColor = Palette::White, const ColorF& labelColor = Palette::Black, const ColorF& highlightColor = DefaultHighlightColor);
	}
}

# include "detail/InputIcon.ipp"

/*

// example

# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::Seagreen);
	const Font font{ 30, Typeface::Medium };
	const double keySize = (font.fontSize() * 1.5);

	while (System::Update())
	{
		InputIcon::DrawInteractive(KeyA, Vec2{ 100, 50 }, font, keySize);
		InputIcon::DrawInteractive(KeyB, Vec2{ 200, 50 }, font, keySize);
		InputIcon::DrawInteractive(MouseL, Vec2{ 300, 50 }, font, keySize);

		InputIcon::DrawInteractive(KeyF2, Vec2{ 100, 150 }, font, keySize);
		InputIcon::DrawInteractive(KeyUp, Vec2{ 100, 250 }, font, keySize);
		InputIcon::DrawInteractive(KeyEnter, Vec2{ 100, 350 }, font, keySize);
		InputIcon::DrawInteractive(KeyBackspace, Vec2{ 100, 450 }, font, keySize);
	}
}

*/
