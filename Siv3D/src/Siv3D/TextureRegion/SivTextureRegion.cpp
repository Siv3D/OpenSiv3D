//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>

namespace s3d
{
	RectF TextureRegion::draw(const double x, const double y, const ColorF& diffuse) const
	{
		Siv3DEngine::GetRenderer2D()->addTextureRegion(
			texture,
			{ x, y, x + size.x, y + size.y },
			uvRect,
			diffuse.toFloat4()
		);

		return RectF{ x, y, size };
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

		Siv3DEngine::GetRenderer2D()->addTextureRegion(
			texture,
			FloatRect(left, top, right, bottom),
			FloatRect(uvRect.left + uLeftTrimmed, uvRect.top + vTopTrimmed, uvRect.right - uRightTrimmed, uvRect.bottom - vBottomTrimmed),
			diffuse.toFloat4()
		);

		return RectF(left, top, right - left, bottom - top);
	}

	RectF TextureRegion::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		const Vec2 sizeHalf = size * 0.5;

		Siv3DEngine::GetRenderer2D()->addTextureRegion(
			texture,
			{ x - sizeHalf.x, y - sizeHalf.y, x + sizeHalf.x, y + sizeHalf.y },
			uvRect,
			diffuse.toFloat4()
		);

		return RectF{ x - sizeHalf.x, y - sizeHalf.y, size };
	}

	RectF TextureRegion::drawAtClipped(const double x, const double y, const RectF& clipRect, const ColorF& diffuse) const
	{
		return drawClipped(x - size.x * 0.5, y - size.y * 0.5, clipRect, diffuse);
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

	TextureRegion TextureRegion::fitted(const double _size, const bool scaleUp) const
	{
		return fitted(_size, _size, scaleUp);
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
