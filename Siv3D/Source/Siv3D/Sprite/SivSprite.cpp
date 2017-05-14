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

# include <Siv3D/Sprite.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	void Sprite::draw() const
	{
		Siv3DEngine::GetRenderer2D()->addSprite(none, *this, 0, indices.size());
	}

	void Sprite::draw(const Texture& texture) const
	{
		Siv3DEngine::GetRenderer2D()->addSprite(texture, *this, 0, indices.size());
	}

	void Sprite::drawSubset(const uint32 startIndex, const uint32 indexCount) const
	{
		Siv3DEngine::GetRenderer2D()->addSprite(none, *this, startIndex, indexCount);
	}

	void Sprite::drawSubset(const uint32 startIndex, const uint32 indexCount, const Texture& texture) const
	{
		Siv3DEngine::GetRenderer2D()->addSprite(texture, *this, startIndex, indexCount);
	}
}
