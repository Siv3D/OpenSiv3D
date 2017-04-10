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
# include <Siv3D/Texture.hpp>

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

	Texture::Texture()
		: m_handle(std::make_shared<TextureHandle>())
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

	bool Texture::operator == (const Texture& texture) const
	{
		return m_handle->getID() == texture.m_handle->getID();
	}

	bool Texture::operator != (const Texture& texture) const
	{
		return m_handle->getID() != texture.m_handle->getID();
	}
}
