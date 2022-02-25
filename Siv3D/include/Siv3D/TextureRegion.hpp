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
# include "Texture.hpp"
# include "FloatRect.hpp"

namespace s3d
{
	struct TextureRegion
	{
		Texture texture;

		FloatRect uvRect = FloatRect{ 0.0f, 0.0f, 0.0f, 0.0f };

		Float2 size = Float2{ 0.0f, 0.0f };

		SIV3D_NODISCARD_CXX20
		TextureRegion() = default;

		SIV3D_NODISCARD_CXX20
		TextureRegion(const Texture& _texture);

		SIV3D_NODISCARD_CXX20
		TextureRegion(const Texture& _texture, float l, float t, float r, float b, double sx, double sy);

		SIV3D_NODISCARD_CXX20
		TextureRegion(const Texture& _texture, float l, float t, float r, float b, const Vec2& _size);

		SIV3D_NODISCARD_CXX20
		TextureRegion(const Texture& _texture, const FloatRect& _uvRect, double sx, double sy);

		SIV3D_NODISCARD_CXX20
		TextureRegion(const Texture& _texture, const FloatRect& _uvRect, const Vec2& _size);
	
		[[nodiscard]]
		RectF region(double x, double y) const noexcept;

		[[nodiscard]]
		RectF region(Vec2 pos = Vec2{ 0, 0 }) const noexcept;

		[[nodiscard]]
		RectF regionAt(double x, double y) const noexcept;

		[[nodiscard]]
		RectF regionAt(Vec2 pos) const noexcept;

		[[nodiscard]]
		TextureRegion stretched(double x, double y) const;

		[[nodiscard]]
		TextureRegion stretched(Vec2 _size) const;

		RectF draw(const ColorF& diffuse = Palette::White) const;

		RectF draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

		RectF draw(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF draw(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		RectF draw(double x, double y, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const;

		RectF draw(double x, double y, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const;

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

		RectF drawAt(double x, double y, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(double x, double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;

		/// @brief 中心位置を指定してテクスチャの一部分を描画します。
		/// @param pos 描画する中心の座標
		/// @param diffuse 描画時に乗算する色
		/// @return テクスチャが描画された領域
		RectF drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const;

		RectF drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const;


		RectF drawClipped(double x, double y, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse = Palette::White) const;

		RectF drawAtClipped(double x, double y, const RectF & clipRect, const ColorF & diffuse = Palette::White) const;

		RectF drawAtClipped(const Vec2 & pos, const RectF & clipRect, const ColorF & diffuse = Palette::White) const;


		[[nodiscard]]
		TextureRegion mirrored() const;

		[[nodiscard]]
		TextureRegion mirrored(bool doMirror) const;

		[[nodiscard]]
		TextureRegion flipped() const;

		[[nodiscard]]
		TextureRegion flipped(bool doFlip) const;

		[[nodiscard]]
		TextureRegion scaled(double s) const;

		[[nodiscard]]
		TextureRegion scaled(double sx, double sy) const;

		[[nodiscard]]
		TextureRegion scaled(Vec2 s) const;

		[[nodiscard]]
		TextureRegion resized(double _size) const;

		[[nodiscard]]
		TextureRegion resized(double width, double height) const;

		[[nodiscard]]
		TextureRegion resized(Vec2 _size) const;

		[[nodiscard]]
		TextureRegion fitted(double width, double height, AllowScaleUp allowScaleUp = AllowScaleUp::Yes) const;

		[[nodiscard]]
		TextureRegion fitted(const Vec2& _size, AllowScaleUp allowScaleUp = AllowScaleUp::Yes) const;

		[[nodiscard]]
		TexturedQuad rotated(double angle) const;

		[[nodiscard]]
		TexturedQuad rotatedAt(double x, double y, double angle) const;

		[[nodiscard]]
		TexturedQuad rotatedAt(const Vec2& pos, double angle) const;

		[[nodiscard]]
		TexturedRoundRect rounded(double r) const;
	};
}
