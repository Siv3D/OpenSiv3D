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
# include "Texture.hpp"
# include "FloatRect.hpp"

namespace s3d
{
	struct TextureRegion
	{
		Texture texture;

		FloatRect uvRect = FloatRect(0.0f, 0.0f, 0.0f, 0.0f);

		Float2 size = Float2(0.0f, 0.0f);

		TextureRegion() = default;

		TextureRegion(const Texture& _texture);

		TextureRegion(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			double sx,
			double sy);

		TextureRegion(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const Vec2& _size);

		TextureRegion(
			const Texture& _texture,
			const FloatRect& _uvRect,
			double sx,
			double sy);

		TextureRegion(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const Vec2& _size);

		[[nodiscard]] RectF region(double x, double y) const;

		[[nodiscard]] RectF region(const Vec2& pos = Vec2(0, 0)) const;

		[[nodiscard]] RectF regionAt(double x, double y) const;

		[[nodiscard]] RectF regionAt(const Vec2& pos) const;

		/// <summary>
		/// テクスチャを描きます。
		/// </summary>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(const ColorF& diffuse = Palette::White) const;

		RectF draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 描画開始位置の X 座標
		/// </param>
		/// <param name="y">
		/// 描画開始位置の Y 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF draw(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(double x, double y, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(double x, double y, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		/// <summary>
		/// 指定した位置にテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 描画開始位置
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		RectF draw(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(const Vec2& pos, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(const Vec2& pos, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;


		RectF draw(Arg::topLeft_<Vec2> topLeft, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::topRight_<Vec2> topRight, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::topCenter_<Vec2> topCenter, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::rightCenter_<Vec2>rightCenter, const ColorF& diffuse = Palette::White) const;

		RectF draw(Arg::center_<Vec2> center, const ColorF& diffuse = Palette::White) const;

		RectF drawClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="x">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="y">
		/// 中心位置の X 座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		/// <summary>
		/// 中心位置を指定してテクスチャを描きます。
		/// </summary>
		/// <param name="pos">
		/// 中心位置の座標
		/// </param>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF drawAtClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawAtClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		[[nodiscard]] TextureRegion mirrored() const;

		[[nodiscard]] TextureRegion mirrored(bool doMirror) const;

		[[nodiscard]] TextureRegion flipped() const;

		[[nodiscard]] TextureRegion flipped(bool doFlip) const;

		[[nodiscard]] TextureRegion scaled(double s) const;

		[[nodiscard]] TextureRegion scaled(double sx, double sy) const;

		[[nodiscard]] TextureRegion scaled(const Vec2& s) const;

		[[nodiscard]] TextureRegion resized(double _size) const;

		[[nodiscard]] TextureRegion resized(double width, double height) const;

		[[nodiscard]] TextureRegion resized(const Vec2& _size) const;

		[[nodiscard]] TextureRegion fitted(double width, double height, bool scaleUp = true) const;

		[[nodiscard]] TextureRegion fitted(const Vec2& _size, bool scaleUp = true) const;

		[[nodiscard]] TexturedQuad rotated(double angle) const;

		[[nodiscard]] TexturedQuad rotatedAt(double x, double y, double angle) const;

		[[nodiscard]] TexturedQuad rotatedAt(const Vec2& pos, double angle) const;
	};
}
