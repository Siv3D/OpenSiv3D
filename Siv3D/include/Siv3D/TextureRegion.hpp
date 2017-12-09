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
# include "Texture.hpp"
# include "FloatRect.hpp"

namespace s3d
{
	struct TextureRegion
	{
		Texture texture;

		FloatRect uvRect;

		Float2 size;

		TextureRegion() = default;

		TextureRegion(const Texture& _texture)
			: texture(_texture)
			, uvRect(0.0f, 0.0f, 1.0f, 1.0f)
			, size(_texture.size()) {}

		TextureRegion(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			double sx,
			double sy)
			: texture(_texture)
			, uvRect(l, t, r, b)
			, size(sx, sy) {}

		TextureRegion(
			const Texture& _texture,
			float l,
			float t,
			float r,
			float b,
			const Vec2& _size)
			: texture(_texture)
			, uvRect(l, t, r, b)
			, size(_size) {}

		TextureRegion(
			const Texture& _texture,
			const FloatRect& _uvRect,
			double sx,
			double sy)
			: texture(_texture)
			, uvRect(_uvRect)
			, size(sx, sy) {}

		TextureRegion(
			const Texture& _texture,
			const FloatRect& _uvRect,
			const Vec2& _size)
			: texture(_texture)
			, uvRect(_uvRect)
			, size(_size) {}

		RectF region(double x, double y) const
		{
			return{ x, y, size };
		}

		RectF region(const Vec2& pos = Vec2(0, 0)) const
		{
			return region(pos.x, pos.y);
		}

		RectF regionAt(double x, double y) const
		{
			return{ x - size.x * 0.5, y - size.y * 0.5, size };
		}

		RectF regionAt(const Vec2& pos) const
		{
			return regionAt(pos.x, pos.y);
		}

		/// <summary>
		/// テクスチャを描きます。
		/// </summary>
		/// <param name="diffuse">
		/// 乗算する色
		/// </param>
		/// <returns>
		/// 描画領域
		/// </returns>
		RectF draw(const ColorF& diffuse = Palette::White) const
		{
			return draw(0.0, 0.0, diffuse);
		}

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
		RectF draw(const Vec2& pos, const ColorF& diffuse = Palette::White) const
		{
			return draw(pos.x, pos.y, diffuse);
		}

		RectF draw(Arg::topLeft_<Vec2> topLeft, const ColorF& diffuse = Palette::White) const
		{
			return draw(topLeft->x, topLeft->y, diffuse);
		}

		RectF draw(Arg::topRight_<Vec2> topRight, const ColorF& diffuse = Palette::White) const
		{
			return draw(topRight->x - size.x, topRight->y, diffuse);
		}

		RectF draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& diffuse = Palette::White) const
		{
			return draw(bottomLeft->x, bottomLeft->y - size.y, diffuse);
		}

		RectF draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& diffuse = Palette::White) const
		{
			return draw(bottomRight->x - size.x, bottomRight->y - size.y, diffuse);
		}

		RectF draw(Arg::topCenter_<Vec2> topCenter, const ColorF& diffuse = Palette::White) const
		{
			return draw(topCenter->x - size.x * 0.5, topCenter->y, diffuse);
		}

		RectF draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& diffuse = Palette::White) const
		{
			return draw(bottomCenter->x - size.x * 0.5, bottomCenter->y - size.y, diffuse);
		}

		RectF draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& diffuse = Palette::White) const
		{
			return draw(leftCenter->x, leftCenter->y - size.y * 0.5, diffuse);
		}

		RectF draw(Arg::rightCenter_<Vec2>rightCenter, const ColorF& diffuse = Palette::White) const
		{
			return draw(rightCenter->x - size.x, rightCenter->y - size.y * 0.5, diffuse);
		}

		RectF draw(Arg::center_<Vec2> center, const ColorF& diffuse = Palette::White) const
		{
			return drawAt(center->x, center->y, diffuse);
		}

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
		RectF drawAt(const Vec2& pos, const ColorF& diffuse = Palette::White) const
		{
			return drawAt(pos.x, pos.y, diffuse);
		}

		TextureRegion mirror() const;

		TextureRegion mirror(bool doMirror) const;

		TextureRegion flip() const;

		TextureRegion flip(bool doFlip) const;

		TextureRegion scale(double s) const
		{
			return scale(s, s);
		}

		TextureRegion scale(double sx, double sy) const;

		TextureRegion scale(const Vec2& s) const
		{
			return scale(s.x, s.y);
		}

		TextureRegion resize(double width, double height) const;

		TextureRegion resize(const Vec2& _size) const
		{
			return resize(_size.x, _size.y);
		}

		TexturedQuad rotate(double angle) const;

		TexturedQuad rotateAt(double x, double y, double angle) const;

		TexturedQuad rotateAt(const Vec2& pos, double angle) const;
	};
}
