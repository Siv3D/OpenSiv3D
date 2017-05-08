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
# include "ITexture.hpp"
# include "../Renderer2D/IRenderer2D.hpp"
# include <Siv3D/Texture.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/FloatRect.hpp>

namespace s3d
{
	template <>
	AssetHandle<Texture::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetTexture())
		{
			p->release(m_id);
		}
	}

	Texture::Texture(BackBuffer)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::GetTexture()->createFromBackBuffer()))
	{

	}

	Texture::Texture(Render, const Size& size, const uint32 multisampleCount)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::GetTexture()->createRT(size, multisampleCount)))
	{

	}

	Texture::Texture()
		: m_handle(std::make_shared<TextureHandle>())
	{

	}

	Texture::Texture(const Image& image, const TextureDesc desc)
		: m_handle(std::make_shared<TextureHandle>(Siv3DEngine::GetTexture()->create(image, desc)))
	{
		//ASSET_CREATION;
	}

	Texture::Texture(const FilePath& path, const TextureDesc desc)
		: Texture(Image(path), desc)
	{

	}

	Texture::Texture(IReader&& reader, const TextureDesc desc)
		: Texture(Image(std::move(reader)), desc)
	{

	}

	Texture::~Texture()
	{

	}

	void Texture::release()
	{
		m_handle = std::make_shared<TextureHandle>();
	}

	bool Texture::isEmpty() const
	{
		return m_handle->getID() == TextureHandle::NullID;
	}

	Texture::IDType Texture::id() const
	{
		return m_handle->getID();
	}

	bool Texture::operator ==(const Texture& texture) const
	{
		return m_handle->getID() == texture.m_handle->getID();
	}

	bool Texture::operator !=(const Texture& texture) const
	{
		return m_handle->getID() != texture.m_handle->getID();
	}

	int32 Texture::width() const
	{
		return Siv3DEngine::GetTexture()->getSize(m_handle->getID()).x;
	}

	int32 Texture::height() const
	{
		return Siv3DEngine::GetTexture()->getSize(m_handle->getID()).y;
	}

	Size Texture::size() const
	{
		return Siv3DEngine::GetTexture()->getSize(m_handle->getID());
	}






	RectF Texture::draw(const double x, const double y, const ColorF& diffuse) const
	{
		const Size size = Siv3DEngine::GetTexture()->getSize(m_handle->getID());

		Siv3DEngine::GetRenderer2D()->addTextureRegion(
			*this,
			FloatRect(x, y, x + size.x, y + size.y),
			FloatRect(0.0f, 0.0f, 1.0f, 1.0f),
			Float4(diffuse.r, diffuse.g, diffuse.b, diffuse.a)
		);

		return RectF(x, y, size);
	}
}
