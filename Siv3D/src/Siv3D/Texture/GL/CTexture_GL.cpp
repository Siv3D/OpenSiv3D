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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "CTexture_GL.hpp"
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	namespace detail
	{
		Array<Byte> GenerateInitialColorBuffer(const Size& size, const ColorF& color, const TextureFormat format)
		{
			const size_t num_pixels = size.x * size.y;
			
			if (format == TextureFormat::R8G8B8A8_Unorm)
			{
				Array<Byte> bytes(num_pixels * sizeof(uint32));
				
				const uint32 value = Color(color).asUint32();
				
				uint32* pDst = static_cast<uint32*>(static_cast<void*>(bytes.data()));
				
				for (size_t i = 0; i < num_pixels; ++i)
				{
					*pDst++ = value;
				}
				
				return bytes;
			}
			
			return Array<Byte>();
		}
	}
	
	CTexture_GL::~CTexture_GL()
	{
		m_textures.destroy();
	}
	
	bool CTexture_GL::init()
	{
		const auto nullTexture = std::make_shared<Texture_GL>(Texture_GL::Null{});
		
		if (!nullTexture->isInitialized())
		{
			return false;
		}
		
		m_textures.setNullData(nullTexture);
		
		return true;
	}
	
	TextureID CTexture_GL::createFromBackBuffer()
	{
		return TextureID::NullAsset();
	}
	
	TextureID CTexture_GL::create(const Image& image, const TextureDesc desc)
	{
		if (!image)
		{
			return TextureID::NullAsset();
		}
		
		const auto texture = std::make_shared<Texture_GL>(image, desc);
		
		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}
		
		return m_textures.add(texture);
	}

	TextureID CTexture_GL::create(const Image& image, const Array<Image>& mipmaps, const TextureDesc desc)
	{
		if (!image)
		{
			return TextureID::NullAsset();
		}
		
		const auto texture = std::make_shared<Texture_GL>(image, mipmaps, desc);
		
		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}
		
		return m_textures.add(texture);
	}

	TextureID CTexture_GL::createDynamic(const Size& size, const void* pData, const uint32 stride, const TextureFormat format, const TextureDesc desc)
	{
		const auto texture = std::make_shared<Texture_GL>(size, pData, stride, format, desc);
		
		if (!texture->isInitialized())
		{
			return TextureID::NullAsset();
		}
		
		return m_textures.add(texture);
	}

	TextureID CTexture_GL::createDynamic(const Size& size, const ColorF& color, const TextureFormat format, const TextureDesc desc)
	{
		const Array<Byte> initialData = detail::GenerateInitialColorBuffer(size, color, format);
		
		return createDynamic(size, initialData.data(), static_cast<uint32>(initialData.size() / size.y), format, desc);
	}

	TextureID CTexture_GL::createRT(const Size&, const uint32)
	{
		return TextureID::NullAsset();
	}
	
	void CTexture_GL::release(const TextureID handleID)
	{
		m_textures.erase(handleID);
	}
	
	Size CTexture_GL::getSize(const TextureID handleID)
	{
		return m_textures[handleID]->getSize();
	}

	TextureDesc CTexture_GL::getDesc(TextureID handleID)
	{
		return m_textures[handleID]->getDesc();
	}
	
	
	void CTexture_GL::setPS(const uint32 slot, const TextureID handleID)
	{
		::glActiveTexture(GL_TEXTURE0 + slot);
		::glBindTexture(GL_TEXTURE_2D, m_textures[handleID]->getTexture());
	}

	bool CTexture_GL::fill(const TextureID handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(color, wait);
	}

	bool CTexture_GL::fill(const TextureID handleID, const void* const src, const uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(src, stride, wait);
	}
}

# endif
