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

# include <Siv3D/Sprite.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>

namespace s3d
{
	Sprite::Sprite()
	{

	}

	Sprite::Sprite(const size_t vertexSize, const size_t indexSize)
		: vertices(vertexSize)
		, indices(indexSize)
	{
	
	}

	Sprite::Sprite(Array<Vertex2D> _vertices, Array<uint16> _indices)
		: vertices(std::move(_vertices))
		, indices(std::move(_indices))
	{
	
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::draw() const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addSprite(*this, 0, static_cast<uint16>(indices.size()));
	}

	void Sprite::draw(const Texture& texture) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addSprite(texture, *this, 0, static_cast<uint16>(indices.size()));
	}

	void Sprite::drawSubset(const uint32 startIndex, const uint32 indexCount) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addSprite(*this, static_cast<uint16>(startIndex), static_cast<uint16>(indexCount));
	}

	void Sprite::drawSubset(const uint32 startIndex, const uint32 indexCount, const Texture& texture) const
	{
		Siv3DEngine::Get<ISiv3DRenderer2D>()->addSprite(texture, *this, static_cast<uint16>(startIndex), static_cast<uint16>(indexCount));
	}
}
