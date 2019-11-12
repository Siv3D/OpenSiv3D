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

# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	TextureRegion::TextureRegion(const Texture& _texture)
		: texture(_texture)
		, uvRect(0.0f, 0.0f, 1.0f, 1.0f)
		, size(_texture.size())
	{

	}

	TextureRegion::TextureRegion(
		const Texture& _texture,
		float l,
		float t,
		float r,
		float b,
		double sx,
		double sy)
		: texture(_texture)
		, uvRect(l, t, r, b)
		, size(sx, sy)
	{

	}

	TextureRegion::TextureRegion(
		const Texture& _texture,
		float l,
		float t,
		float r,
		float b,
		const Vec2& _size)
		: texture(_texture)
		, uvRect(l, t, r, b)
		, size(_size)
	{

	}

	TextureRegion::TextureRegion(
		const Texture& _texture,
		const FloatRect& _uvRect,
		double sx,
		double sy)
		: texture(_texture)
		, uvRect(_uvRect)
		, size(sx, sy)
	{

	}

	TextureRegion::TextureRegion(
		const Texture& _texture,
		const FloatRect& _uvRect,
		const Vec2& _size)
		: texture(_texture)
		, uvRect(_uvRect)
		, size(_size)
	{

	}

	RectF TextureRegion::region(const double x, const double y) const
	{
		return{ x, y, size };
	}

	RectF TextureRegion::region(const Vec2& pos) const
	{
		return region(pos.x, pos.y);
	}

	RectF TextureRegion::regionAt(const double x, const double y) const
	{
		return{ x - size.x * 0.5, y - size.y * 0.5, size };
	}

	RectF TextureRegion::regionAt(const Vec2& pos) const
	{
		return regionAt(pos.x, pos.y);
	}

	TextureRegion TextureRegion::stretched(const double x, const double y) const
	{
		TextureRegion result(*this);
		result.size.x += static_cast<float>(x * 2);
		result.size.y += static_cast<float>(y * 2);

		const Size textureSize = texture.size();
		const float dx = static_cast<float>(x / textureSize.x);
		const float dy = static_cast<float>(y / textureSize.y);
		result.uvRect.left -= dx;
		result.uvRect.right += dx;
		result.uvRect.top -= dy;
		result.uvRect.bottom += dy;

		return result;
	}

	TextureRegion TextureRegion::stretched(const Vec2& _size) const
	{
		return stretched(_size.x, _size.y);
	}

	RectF TextureRegion::draw(const ColorF& diffuse) const
	{
		return draw(0.0, 0.0, diffuse);
	}

	RectF TextureRegion::draw(const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return draw(0.0, 0.0, color0, color1, color2, color3);
	}

	RectF TextureRegion::draw(Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(*topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF TextureRegion::draw(Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const
	{
		return draw(*leftColor, *rightColor, *rightColor, *leftColor);
	}

	RectF TextureRegion::draw(const double x, const double y, const ColorF& diffuse) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			texture,
			{ x, y, x + size.x, y + size.y },
			uvRect,
			diffuse.toFloat4()
		);

		return RectF{ x, y, size };
	}

	RectF TextureRegion::draw(const double x, const double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			texture,
			{ x, y, x + size.x, y + size.y },
			uvRect,
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4(), color3.toFloat4() }
		);

		return RectF{ x, y, size };
	}

	RectF TextureRegion::draw(const double x, const double y, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(x, y, *topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF TextureRegion::draw(const double x, const double y, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const
	{
		return draw(x, y, *leftColor, *rightColor, *rightColor, *leftColor);
	}

	RectF TextureRegion::draw(const Vec2& pos, const ColorF& diffuse) const
	{
		return draw(pos.x, pos.y, diffuse);
	}

	RectF TextureRegion::draw(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return draw(pos.x, pos.y, color0, color1, color2, color3);
	}

	RectF TextureRegion::draw(const Vec2& pos, Arg::top_<ColorF> topColor, Arg::bottom_<ColorF> bottomColor) const
	{
		return draw(pos.x, pos.y, *topColor, *topColor, *bottomColor, *bottomColor);
	}

	RectF TextureRegion::draw(const Vec2& pos, Arg::left_<ColorF> leftColor, Arg::right_<ColorF> rightColor) const
	{
		return draw(pos.x, pos.y, *leftColor, *rightColor, *rightColor, *leftColor);
	}


	RectF TextureRegion::draw(Arg::topLeft_<Vec2> topLeft, const ColorF& diffuse) const
	{
		return draw(topLeft->x, topLeft->y, diffuse);
	}

	RectF TextureRegion::draw(Arg::topRight_<Vec2> topRight, const ColorF& diffuse) const
	{
		return draw(topRight->x - size.x, topRight->y, diffuse);
	}

	RectF TextureRegion::draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& diffuse) const
	{
		return draw(bottomLeft->x, bottomLeft->y - size.y, diffuse);
	}

	RectF TextureRegion::draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& diffuse) const
	{
		return draw(bottomRight->x - size.x, bottomRight->y - size.y, diffuse);
	}

	RectF TextureRegion::draw(Arg::topCenter_<Vec2> topCenter, const ColorF& diffuse) const
	{
		return draw(topCenter->x - size.x * 0.5, topCenter->y, diffuse);
	}

	RectF TextureRegion::draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& diffuse) const
	{
		return draw(bottomCenter->x - size.x * 0.5, bottomCenter->y - size.y, diffuse);
	}

	RectF TextureRegion::draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& diffuse) const
	{
		return draw(leftCenter->x, leftCenter->y - size.y * 0.5, diffuse);
	}

	RectF TextureRegion::draw(Arg::rightCenter_<Vec2>rightCenter, const ColorF& diffuse) const
	{
		return draw(rightCenter->x - size.x, rightCenter->y - size.y * 0.5, diffuse);
	}

	RectF TextureRegion::draw(Arg::center_<Vec2> center, const ColorF& diffuse) const
	{
		return drawAt(center->x, center->y, diffuse);
	}

	RectF TextureRegion::drawClipped(const double x, const double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		const double clipRight = clipRect.x + clipRect.w;
		const double clipBottom = clipRect.y + clipRect.h;

		const double left = std::max(x, clipRect.x);
		const double right = std::min(x + size.x, clipRight);
		const double top = std::max(y, clipRect.y);
		const double bottom = std::min(y + size.y, clipBottom);

		if (clipRight <= left
			|| right <= clipRect.x
			|| clipBottom <= top
			|| bottom <= clipRect.y)
		{
			return RectF(left, top, 0, 0);
		}

		const float xLeftTrimmed	= static_cast<float>(left - x);
		const float xRightTrimmed	= static_cast<float>((x + size.x) - right);
		const float yTopTrimmed		= static_cast<float>(top - y);
		const float yBottomTrimmed	= static_cast<float>((y + size.y) - bottom);

		const float uLeftTrimmed	= xLeftTrimmed / size.x * (uvRect.right - uvRect.left);
		const float uRightTrimmed	= xRightTrimmed / size.x * (uvRect.right - uvRect.left);
		const float vTopTrimmed		= yTopTrimmed / size.y * (uvRect.bottom - uvRect.top);
		const float vBottomTrimmed	= yBottomTrimmed / size.y * (uvRect.bottom - uvRect.top);

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			texture,
			FloatRect(left, top, right, bottom),
			FloatRect(uvRect.left + uLeftTrimmed, uvRect.top + vTopTrimmed, uvRect.right - uRightTrimmed, uvRect.bottom - vBottomTrimmed),
			diffuse.toFloat4()
		);

		return RectF(left, top, right - left, bottom - top);
	}

	RectF TextureRegion::drawClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse) const
	{
		return drawClipped(pos.x, pos.y, clipRect, diffuse);
	}

	RectF TextureRegion::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		const Vec2 sizeHalf = size * 0.5;

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			texture,
			{ x - sizeHalf.x, y - sizeHalf.y, x + sizeHalf.x, y + sizeHalf.y },
			uvRect,
			diffuse.toFloat4()
		);

		return RectF{ x - sizeHalf.x, y - sizeHalf.y, size };
	}

	RectF TextureRegion::drawAt(const double x, const double y, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		const Vec2 sizeHalf = size * 0.5;

		Siv3DEngine::Get<ISiv3DRenderer2D>()->addTextureRegion(
			texture,
			{ x - sizeHalf.x, y - sizeHalf.y, x + sizeHalf.x, y + sizeHalf.y },
			uvRect,
			{ color0.toFloat4(), color1.toFloat4(), color2.toFloat4(), color3.toFloat4() }
		);

		return RectF{ x - sizeHalf.x, y - sizeHalf.y, size };
	}

	RectF TextureRegion::drawAt(const Vec2& pos, const ColorF& diffuse) const
	{
		return drawAt(pos.x, pos.y, diffuse);
	}

	RectF TextureRegion::drawAt(const Vec2& pos, const ColorF& color0, const ColorF& color1, const ColorF& color2, const ColorF& color3) const
	{
		return drawAt(pos.x, pos.y, color0, color1, color2, color3);
	}

	RectF TextureRegion::drawAtClipped(const double x, const double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		return drawClipped(x - size.x * 0.5, y - size.y * 0.5, clipRect, diffuse);
	}

	RectF TextureRegion::drawAtClipped(const Vec2& pos, const RectF& clipRect, const ColorF& diffuse) const
	{
		return drawAtClipped(pos.x, pos.y, clipRect, diffuse);
	}

	TextureRegion TextureRegion::mirrored() const
	{
		return TextureRegion{ texture,
			uvRect.right, uvRect.top, uvRect.left, uvRect.bottom,
			size };
	}

	TextureRegion TextureRegion::mirrored(const bool doMirror) const
	{
		if (doMirror)
		{
			return mirrored();
		}
		else
		{
			return *this;
		}
	}

	TextureRegion TextureRegion::flipped() const
	{
		return TextureRegion{ texture,
			uvRect.left, uvRect.bottom, uvRect.right, uvRect.top,
			size };
	}

	TextureRegion TextureRegion::flipped(const bool doFlip) const
	{
		if (doFlip)
		{
			return flipped();
		}
		else
		{
			return *this;
		}
	}

	TextureRegion TextureRegion::scaled(double s) const
	{
		return scaled(s, s);
	}

	TextureRegion TextureRegion::scaled(const double sx, const double sy) const
	{
		return TextureRegion{ texture,
			uvRect,
			size.x * sx, size.y*sy };
	}

	TextureRegion TextureRegion::scaled(const Vec2& s) const
	{
		return scaled(s.x, s.y);
	}

	TextureRegion TextureRegion::resized(const double _size) const
	{
		return resized(_size, _size);
	}

	TextureRegion TextureRegion::resized(const double width, const double height) const
	{
		return TextureRegion{ texture,
			uvRect,
			width, height };
	}

	TextureRegion TextureRegion::resized(const Vec2& _size) const
	{
		return resized(_size.x, _size.y);
	}

	TextureRegion TextureRegion::fitted(double width, double height, const bool scaleUp) const
	{
		if (!scaleUp)
		{
			width = std::min<double>(width, size.x);
			height = std::min<double>(height, size.y);
		}

		const double w = size.x;
		const double h = size.y;
		double ws = width / w;	// 何% scalingするか
		double hs = height / h;

		double targetWidth, targetHeight;

		if (ws < hs)
		{
			targetWidth = width;
			targetHeight = h * ws;
		}
		else
		{
			targetWidth = w * hs;
			targetHeight = height;
		}

		TextureRegion result = *this;
		result.size = Float2(targetWidth, targetHeight);

		return result;
	}

	TextureRegion TextureRegion::fitted(const Vec2& _size, const bool scaleUp) const
	{
		return fitted(_size.x, _size.y, scaleUp);
	}

	TexturedQuad TextureRegion::rotated(const double angle) const
	{
		return TexturedQuad(texture,
			uvRect,
			RectF(size).rotated(angle),
			size * 0.5f);
	}

	TexturedQuad TextureRegion::rotatedAt(const double x, const double y, const double angle) const
	{
		return TexturedQuad(texture,
			uvRect,
			RectF(size).rotatedAt(x, y, angle),
			Float2(x, y));
	}

	TexturedQuad TextureRegion::rotatedAt(const Vec2& pos, const double angle) const
	{
		return rotatedAt(pos.x, pos.y, angle);
	}
}
