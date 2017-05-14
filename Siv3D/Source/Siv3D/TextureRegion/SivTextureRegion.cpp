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
			Float4(diffuse.r, diffuse.g, diffuse.b, diffuse.a)
		);

		return RectF{ x, y, size };
	}

	RectF TextureRegion::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		const Vec2 sizeHalf = size * 0.5;

		Siv3DEngine::GetRenderer2D()->addTextureRegion(
			texture,
			{ x - sizeHalf.x, y - sizeHalf.y, x + sizeHalf.x, y + sizeHalf.y },
			uvRect,
			Float4(diffuse.r, diffuse.g, diffuse.b, diffuse.a)
		);

		return RectF{ x - sizeHalf.x, y - sizeHalf.y, size };
	}

	TextureRegion TextureRegion::mirror() const
	{
		return TextureRegion{ texture,
			uvRect.right, uvRect.top, uvRect.left, uvRect.bottom,
			size };
	}

	TextureRegion TextureRegion::flip() const
	{
		return TextureRegion{ texture,
			uvRect.left, uvRect.bottom, uvRect.right, uvRect.top,
			size };
	}

	TextureRegion TextureRegion::scale(const double sx, const double sy) const
	{
		return TextureRegion{ texture,
			uvRect,
			size.x * sx, size.y*sy };
	}

	TextureRegion TextureRegion::resize(const double width, const double height) const
	{
		return TextureRegion{ texture,
			uvRect,
			width, height };
	}

	TexturedQuad TextureRegion::rotate(const double angle) const
	{
		return TexturedQuad(texture,
			uvRect,
			RectF(size).rotated(angle),
			size * 0.5f);
	}

	TexturedQuad TextureRegion::rotateAt(const double x, const double y, const double angle) const
	{
		return TexturedQuad(texture,
			uvRect,
			RectF(size).rotatedAt(x, y, angle),
			Float2(x, y));
	}

	TexturedQuad TextureRegion::rotateAt(const Vec2& pos, const double angle) const
	{
		return rotateAt(pos.x, pos.y, angle);
	}
}
