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
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/FloatQuad.hpp>

namespace s3d
{
	const Quad& TexturedQuad::draw(const ColorF& diffuse) const
	{
		Siv3DEngine::GetRenderer2D()->addTexturedQuad(texture, quad, uvRect, Float4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));

		return quad;
	}

	Quad TexturedQuad::draw(const double x, const double y, const ColorF& diffuse) const
	{
		const Quad q = quad.movedBy(x, y);

		Siv3DEngine::GetRenderer2D()->addTexturedQuad(texture, q, uvRect, Float4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));

		return q;
	}

	const Quad& TexturedQuad::drawAt(const ColorF& diffuse) const
	{
		Siv3DEngine::GetRenderer2D()->addTexturedQuad(texture, quad.movedBy(center), uvRect, Float4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));

		return quad;
	}

	Quad TexturedQuad::drawAt(const double x, const double y, const ColorF& diffuse) const
	{
		const Quad q = quad.movedBy(x - center.x, y - center.y);

		Siv3DEngine::GetRenderer2D()->addTexturedQuad(texture, q, uvRect, Float4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));

		return q;
	}
}
