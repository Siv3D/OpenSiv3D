//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CTexture_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Texture/TextureCommon.hpp>

namespace s3d
{
	CTexture_GL4::CTexture_GL4()
	{
		// do nothing
	}

	CTexture_GL4::~CTexture_GL4()
	{
		LOG_SCOPED_TRACE(U"CTexture_GL4::~CTexture_GL4()");

		m_textures.destroy();
	}

	void CTexture_GL4::init()
	{
		// null Texture を管理に登録
		{
			const Image image{ 16, Palette::Yellow };
			const Array<Image> mips = {
				Image{ 8, Palette::Yellow }, Image{ 4, Palette::Yellow },
				Image{ 2, Palette::Yellow }, Image{ 1, Palette::Yellow }
			};

			// null Texture を作成
			auto nullTexture = std::make_unique<GL4Texture>(image, mips, TextureDesc::Mipped);

			if (not nullTexture->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null Texture initialization failed");
			}

			// 管理に登録
			m_textures.setNullData(std::move(nullTexture));
		}
	}

	void CTexture_GL4::updateAsyncTextureLoad(const size_t)
	{
		// [Siv3D ToDo]
	}

	Texture::IDType CTexture_GL4::createUnmipped(const Image& image, const TextureDesc desc)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		//if (not isMainThread())
		//{
		//	return pushRequest(image, Array<Image>(), desc);
		//}

		auto texture = std::make_unique<GL4Texture>(image, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size:{0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GL4::createMipped(const Image& image, const Array<Image>& mips, const TextureDesc desc)
	{
		if (not image)
		{
			return Texture::IDType::NullAsset();
		}

		//if (not isMainThread())
		//{
		//	return pushRequest(image, mips, desc);
		//}

		auto texture = std::make_unique<GL4Texture>(image, mips, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Default, size: {0}x{1}, format: {2})"_fmt(image.width(), image.height(), texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GL4::createDynamic(const Size& size, const void* pData, uint32 stride, const TextureFormat& format, const TextureDesc desc)
	{
		if ((size.x <= 0) || (size.y <= 0))
		{
			return Texture::IDType::NullAsset();
		}

		auto texture = std::make_unique<GL4Texture>(GL4Texture::Dynamic{}, size, pData, stride, format, desc);

		if (not texture->isInitialized())
		{
			return Texture::IDType::NullAsset();
		}

		const String info = U"(type: Dynamic, size: {0}x{1}, format: {2})"_fmt(size.x, size.y, texture->getFormat().name());
		return m_textures.add(std::move(texture), info);
	}

	Texture::IDType CTexture_GL4::createDynamic(const Size& size, const ColorF& color, const TextureFormat& format, const TextureDesc desc)
	{
		const Array<Byte> initialData = GenerateInitialColorBuffer(size, color, format);

		if (not initialData)
		{
			return Texture::IDType::NullAsset();
		}

		return createDynamic(size, initialData.data(), static_cast<uint32>(initialData.size() / size.y), format, desc);

	}

	void CTexture_GL4::release(const Texture::IDType handleID)
	{
		m_textures.erase(handleID);
	}

	Size CTexture_GL4::getSize(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getSize();
	}

	TextureDesc CTexture_GL4::getDesc(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getDesc();
	}

	TextureFormat CTexture_GL4::getFormat(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getFormat();
	}

	bool CTexture_GL4::fill(const Texture::IDType handleID, const ColorF& color, const bool wait)
	{
		return m_textures[handleID]->fill(color, wait);
	}

	bool CTexture_GL4::fillRegion(const Texture::IDType handleID, const ColorF& color, const Rect& rect)
	{
		return m_textures[handleID]->fillRegion(color, rect);
	}

	bool CTexture_GL4::fill(const Texture::IDType handleID, const void* src, uint32 stride, const bool wait)
	{
		return m_textures[handleID]->fill(src, stride, wait);
	}

	bool CTexture_GL4::fillRegion(const Texture::IDType handleID, const void* src, const uint32 stride, const Rect& rect, const bool wait)
	{
		return m_textures[handleID]->fillRegion(src, stride, rect, wait);
	}

	GLuint CTexture_GL4::getTexture(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getTexture();
	}

	GLuint CTexture_GL4::getFrameBuffer(const Texture::IDType handleID)
	{
		return m_textures[handleID]->getFrameBuffer();
	}
}
